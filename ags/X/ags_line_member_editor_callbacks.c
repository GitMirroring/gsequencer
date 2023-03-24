/* GSequencer - Advanced GTK Sequencer
 * Copyright (C) 2005-2023 Joël Krähemann
 *
 * This file is part of GSequencer.
 *
 * GSequencer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GSequencer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GSequencer.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <ags/X/ags_line_member_editor_callbacks.h>

#include <ags/libags.h>
#include <ags/libags-audio.h>
#include <ags/libags-gui.h>

#include <ags/X/ags_ui_provider.h>
#include <ags/X/ags_window.h>
#include <ags/X/ags_machine.h>
#include <ags/X/ags_pad.h>
#include <ags/X/ags_line.h>
#include <ags/X/ags_effect_bridge.h>
#include <ags/X/ags_effect_pad.h>
#include <ags/X/ags_effect_line.h>
#include <ags/X/ags_line_member.h>
#include <ags/X/ags_machine_editor.h>
#include <ags/X/ags_line_editor.h>
#include <ags/X/ags_lv2_browser.h>
#include <ags/X/ags_ladspa_browser.h>

#include <ags/X/thread/ags_gui_thread.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include <ladspa.h>

void
ags_line_member_editor_add_callback(GtkWidget *button,
				    AgsLineMemberEditor *line_member_editor)
{
  gtk_widget_show_all((GtkWidget *) line_member_editor->plugin_browser);
}

void
ags_line_member_editor_plugin_browser_response_callback(GtkDialog *dialog,
							gint response,
							AgsLineMemberEditor *line_member_editor)
{
  AgsWindow *window;
  AgsMachine *machine;
  AgsMachineEditor *machine_editor;
  AgsLineEditor *line_editor;
  
  AgsApplicationContext *application_context;
  
  GList *pad, *pad_start;
  GList *list, *list_start;
  GList *control_type_name;
  
  gchar *plugin_name;
  gchar *filename, *effect;

  gint position;
  gboolean has_bridge;
  gboolean is_output;
  
  auto void ags_line_member_editor_plugin_browser_response_create_entry();
  
  void ags_line_member_editor_plugin_browser_response_create_entry(){
    GtkHBox *hbox;
    GtkCheckButton *check_button;
    GtkLabel *label;

    /* create entry */
    hbox = (GtkHBox *) gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(line_member_editor->line_member),
		       GTK_WIDGET(hbox),
		       FALSE, FALSE,
		       0);
      
    check_button = (GtkCheckButton *) gtk_check_button_new();
    gtk_box_pack_start(GTK_BOX(hbox),
		       GTK_WIDGET(check_button),
		       FALSE, FALSE,
		       0);

    //TODO:JK: ugly
    label = (GtkLabel *) gtk_label_new(g_strdup_printf("%s - %s",
						       filename,
						       effect));
    gtk_box_pack_start(GTK_BOX(hbox),
		       GTK_WIDGET(label),
		       FALSE, FALSE,
		       0);
    gtk_widget_show_all((GtkWidget *) hbox);
  }
  
  switch(response){
  case GTK_RESPONSE_ACCEPT:
    {
      machine_editor = (AgsMachineEditor *) gtk_widget_get_ancestor((GtkWidget *) line_member_editor,
								    AGS_TYPE_MACHINE_EDITOR);
      line_editor = (AgsLineEditor *) gtk_widget_get_ancestor((GtkWidget *) line_member_editor,
							      AGS_TYPE_LINE_EDITOR);

      machine = machine_editor->machine;

      window = (AgsWindow *) gtk_widget_get_toplevel((GtkWidget *) machine);

      application_context = (AgsApplicationContext *) window->application_context;

      if(AGS_IS_OUTPUT(line_editor->channel)){
	is_output = TRUE;
      }else{
	is_output = FALSE;
      }

      if(machine->bridge != NULL){
	has_bridge = TRUE;
      }else{
	has_bridge = FALSE;
      }

      position = 0;

      //NOTE:JK: related to ags-fx-buffer
      if((AGS_MACHINE_IS_SEQUENCER & (machine->flags)) != 0 ||
	 (AGS_MACHINE_IS_SYNTHESIZER & (machine->flags)) != 0 ||
	 (AGS_MACHINE_IS_WAVE_PLAYER & (machine->flags)) != 0){
	position = 1;
      }
      
      plugin_name = NULL;

      if(AGS_IS_LADSPA_BROWSER(AGS_PLUGIN_BROWSER(dialog)->active_browser)){
	plugin_name = "ags-fx-ladspa";
      }else if(AGS_IS_LV2_BROWSER(AGS_PLUGIN_BROWSER(dialog)->active_browser)){
	plugin_name = "ags-fx-lv2";
#if defined(AGS_WITH_VST3)
      }else if(AGS_IS_VST3_BROWSER(AGS_PLUGIN_BROWSER(dialog)->active_browser)){
	plugin_name = "ags-fx-vst3";
#endif
      }

      /* get control type */
      control_type_name = NULL;  

      if(AGS_PLUGIN_BROWSER(dialog)->active_browser != NULL){
	GList *start_port_editor, *port_editor;

	/* get port editor */
	start_port_editor = NULL;
		
	if(AGS_IS_LADSPA_BROWSER(AGS_PLUGIN_BROWSER(dialog)->active_browser)){
	  port_editor =
	    start_port_editor = ags_ladspa_browser_get_port_editor(AGS_PLUGIN_BROWSER(dialog)->active_browser);
	}else if(AGS_IS_LV2_BROWSER(AGS_PLUGIN_BROWSER(dialog)->active_browser)){
	  port_editor =
	    start_port_editor = ags_lv2_browser_get_port_editor(AGS_PLUGIN_BROWSER(dialog)->active_browser);
#if defined(AGS_WITH_VST3)
	}else if(AGS_IS_VST3_BROWSER(AGS_PLUGIN_BROWSER(dialog)->active_browser)){
	  port_editor =
	    start_port_editor = ags_vst3_browser_get_port_editor(AGS_PLUGIN_BROWSER(dialog)->active_browser);
#endif
	}else{
	  g_message("ags_line_member_editor_callbacks.c unsupported plugin browser");
	}
	  
	while(port_editor != NULL){
	  GtkTreeModel *model;
	  
	  GtkTreeIter iter;

	  gchar *control;

	  model = gtk_combo_box_get_model(AGS_PORT_EDITOR(port_editor->data)->port_control);

	  gtk_combo_box_get_active_iter(AGS_PORT_EDITOR(port_editor->data)->port_control,
					&iter);

	  control = NULL;

	  gtk_tree_model_get(model,
			     &iter,
			     0, &control,
			     -1);
	  
	  control_type_name = g_list_prepend(control_type_name,
					     control);
	      
	  port_editor = port_editor->next;
	}

	/* free lists */
	g_list_free(start_port_editor);
      }
      
      if(!has_bridge){	
	AgsLine *line;
	
	/* find pad and line */
	line = NULL;
	
	if(is_output){
	  pad_start = 
	    pad = gtk_container_get_children((GtkContainer *) machine_editor->machine->output);
	}else{
	  pad_start = 
	    pad = gtk_container_get_children((GtkContainer *) machine_editor->machine->input);
	}

	pad = g_list_nth(pad,
			 line_editor->channel->pad);

	if(pad != NULL){
	  list_start =
	    list = gtk_container_get_children((GtkContainer *) AGS_PAD(pad->data)->expander_set);

	  while(list != NULL){
	    if(AGS_LINE(list->data)->channel == line_editor->channel){
	      break;
	    }

	    list = list->next;
	  }

	  if(list != NULL){
	    line = AGS_LINE(list->data);
	    g_list_free(list_start);
	  }
	}

	g_list_free(pad_start);

	/* retrieve plugin */
	filename = ags_plugin_browser_get_plugin_filename(line_member_editor->plugin_browser);
	effect = ags_plugin_browser_get_plugin_effect(line_member_editor->plugin_browser);

	if(line != NULL){
	  GList *start_play, *start_recall;

	  guint audio_channel;
	  guint pad;

	  pad = ags_channel_get_pad(line->channel);
	  audio_channel = ags_channel_get_audio_channel(line->channel);
	  
	  start_play = ags_channel_get_play(line->channel);
	  start_recall = ags_channel_get_recall(line->channel);
	  
	  if(ags_recall_find_recall_id_with_effect(start_play,
						   NULL,
						   filename,
						   effect) == NULL &&
	     ags_recall_find_recall_id_with_effect(start_recall,
						   NULL,
						   filename,
						   effect) == NULL){
	    ags_line_member_editor_plugin_browser_response_create_entry();
	    
	    /* add effect */
	    ags_line_add_plugin(line,
				control_type_name,
				ags_recall_container_new(), ags_recall_container_new(),
				plugin_name,
				filename,
				effect,
				audio_channel, audio_channel + 1,
				pad, pad + 1,
				position,
				(AGS_FX_FACTORY_ADD | (is_output ? AGS_FX_FACTORY_OUTPUT: AGS_FX_FACTORY_INPUT)), 0);
	  }

	  g_list_free_full(start_play,
			   g_object_unref);
	  g_list_free_full(start_recall,
			   g_object_unref);
	}
      }else{
	AgsEffectBridge *effect_bridge;
	AgsEffectLine *effect_line;
	
	effect_bridge = (AgsEffectBridge *) machine->bridge;
	effect_line = NULL;
	
	/* find effect pad and effect line */
	if(is_output){
	  pad_start = 
	    pad = gtk_container_get_children((GtkContainer *) effect_bridge->output);
	}else{
	  pad_start = 
	    pad = gtk_container_get_children((GtkContainer *) effect_bridge->input);
	}

	pad = g_list_nth(pad,
			 line_editor->channel->pad);

	if(pad != NULL){
	  list_start =
	    list = gtk_container_get_children((GtkContainer *) AGS_EFFECT_PAD(pad->data)->table);

	  while(list != NULL){
	    if(AGS_EFFECT_LINE(list->data)->channel == line_editor->channel){
	      break;
	    }

	    list = list->next;
	  }

	  if(list != NULL){
	    effect_line = AGS_EFFECT_LINE(list->data);
	    g_list_free(list_start);
	  }
	}

	g_list_free(pad_start);

	/* retrieve plugin */
	filename = ags_plugin_browser_get_plugin_filename(line_member_editor->plugin_browser);
	effect = ags_plugin_browser_get_plugin_effect(line_member_editor->plugin_browser);

	if(effect_line != NULL){
	  GList *start_play, *start_recall;

	  guint audio_channel;
	  guint pad;

	  pad = ags_channel_get_pad(effect_line->channel);
	  audio_channel = ags_channel_get_audio_channel(effect_line->channel);

	  start_play = ags_channel_get_play(effect_line->channel);
	  start_recall = ags_channel_get_recall(effect_line->channel);

	  if(ags_recall_find_recall_id_with_effect(start_play,
						   NULL,
						   filename,
						   effect) == NULL &&
	     ags_recall_find_recall_id_with_effect(start_recall,
						   NULL,
						   filename,
						   effect) == NULL){
	    ags_line_member_editor_plugin_browser_response_create_entry();

	    /* add effect */
	    ags_effect_line_add_plugin(effect_line,
				       control_type_name,
				       ags_recall_container_new(), ags_recall_container_new(),
				       plugin_name,
				       filename,
				       effect,
				       audio_channel, audio_channel + 1,
				       pad, pad + 1,
				       position,
				       (AGS_FX_FACTORY_ADD | (is_output ? AGS_FX_FACTORY_OUTPUT: AGS_FX_FACTORY_INPUT)), 0);
	  }

	  g_list_free_full(start_play,
			   g_object_unref);
	  g_list_free_full(start_recall,
			   g_object_unref);
	}
      }
    }
    break;      
  }
}

void
ags_line_member_editor_remove_callback(GtkWidget *button,
				       AgsLineMemberEditor *line_member_editor)
{
  AgsMachine *machine;
  AgsMachineEditor *machine_editor;
  AgsLineEditor *line_editor;

  GList *line_member, *line_member_next;
  GList *list, *list_start, *pad, *pad_start;
  GList *children;

  guint nth;
  gboolean has_bridge;
  gboolean is_output;
  
  auto void ags_line_member_editor_plugin_browser_response_destroy_entry();
  
  void ags_line_member_editor_plugin_browser_response_destroy_entry(){
    /* destroy line member editor entry */
    gtk_widget_destroy(GTK_WIDGET(line_member->data));
  }
  
  if(button == NULL ||
     line_member_editor == NULL){
    return;
  }

  machine_editor = (AgsMachineEditor *) gtk_widget_get_ancestor((GtkWidget *) line_member_editor,
								AGS_TYPE_MACHINE_EDITOR);
  line_editor = (AgsLineEditor *) gtk_widget_get_ancestor((GtkWidget *) line_member_editor,
							  AGS_TYPE_LINE_EDITOR);

  line_member = gtk_container_get_children(GTK_CONTAINER(line_member_editor->line_member));

  machine = machine_editor->machine;

  if(AGS_IS_OUTPUT(line_editor->channel)){
    is_output = TRUE;
  }else{
    is_output = FALSE;
  }

  if(machine->bridge != NULL){
    has_bridge = TRUE;
  }else{
    has_bridge = FALSE;
  }

  if(!has_bridge){	
    AgsLine *line;
    
    /* retrieve line and pad */
    line = NULL;

    if(AGS_IS_OUTPUT(line_editor->channel)){
      pad_start = 
	pad = gtk_container_get_children((GtkContainer *) machine->output);
    }else{
      pad_start = 
	pad = gtk_container_get_children((GtkContainer *) machine->input);
    }

    pad = g_list_nth(pad,
		     line_editor->channel->pad);

    if(pad != NULL){
      list_start =
	list = gtk_container_get_children((GtkContainer *) AGS_PAD(pad->data)->expander_set);

      while(list != NULL){
	if(AGS_LINE(list->data)->channel == line_editor->channel){
	  break;
	}

	list = list->next;
      }

      if(list != NULL){
	line = AGS_LINE(list->data);
	g_list_free(list_start);
      }
    }

    g_list_free(pad_start);

    /* iterate line member */
    if(line != NULL){
      for(nth = 0; line_member != NULL; nth++){
	line_member_next = line_member->next;
	
	children = gtk_container_get_children((GtkContainer *) GTK_CONTAINER(line_member->data));

	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(children->data))){
	  ags_line_member_editor_plugin_browser_response_destroy_entry();

	  /* remove effect */
	  ags_line_remove_effect(line,
				 nth);
	}
      
	line_member = line_member_next;
      }
    }
  }else{
    AgsEffectBridge *effect_bridge;
    AgsEffectLine *effect_line;
	
    effect_bridge = AGS_EFFECT_BRIDGE(machine->bridge);

    effect_line = NULL;
    
    /* retrieve effect line and effect pad */
    if(is_output){
      pad_start = 
	pad = gtk_container_get_children((GtkContainer *) effect_bridge->output);
    }else{
      pad_start = 
	pad = gtk_container_get_children((GtkContainer *) effect_bridge->input);
    }

    pad = g_list_nth(pad,
		     line_editor->channel->pad);

    if(pad != NULL){
      list_start =
	list = gtk_container_get_children((GtkContainer *) AGS_EFFECT_PAD(pad->data)->table);

      while(list != NULL){
	if(AGS_EFFECT_LINE(list->data)->channel == line_editor->channel){
	  break;
	}

	list = list->next;
      }

      if(list != NULL){
	effect_line = AGS_EFFECT_LINE(list->data);
	g_list_free(list_start);
      }
    }

    g_list_free(pad_start);

    /* iterate line member */
    if(effect_line != NULL){
      for(nth = 0; line_member != NULL; nth++){
	children = gtk_container_get_children(GTK_CONTAINER(line_member->data));

	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(children->data))){
	  ags_line_member_editor_plugin_browser_response_destroy_entry();
	
	  /* remove effect */
	  ags_effect_line_remove_effect(effect_line,
					nth);
	}

	g_list_free(children);
	
	line_member = line_member->next;
      }
    }
  }
}
