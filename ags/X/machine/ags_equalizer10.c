/* GSequencer - Advanced GTK Sequencer
 * Copyright (C) 2005-2018 Joël Krähemann
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

#include <ags/X/machine/ags_equalizer10.h>
#include <ags/X/machine/ags_equalizer10_callbacks.h>

#include <ags/libags.h>
#include <ags/libags-audio.h>

void ags_equalizer10_class_init(AgsEqualizer10Class *equalizer10);
void ags_equalizer10_connectable_interface_init(AgsConnectableInterface *connectable);
void ags_equalizer10_plugin_interface_init(AgsPluginInterface *plugin);
void ags_equalizer10_init(AgsEqualizer10 *equalizer10);
void ags_equalizer10_finalize(GObject *gobject);

void ags_equalizer10_map_recall(AgsMachine *machine);

void ags_equalizer10_connect(AgsConnectable *connectable);
void ags_equalizer10_disconnect(AgsConnectable *connectable);

gchar* ags_equalizer10_get_name(AgsPlugin *plugin);
void ags_equalizer10_set_name(AgsPlugin *plugin, gchar *name);
gchar* ags_equalizer10_get_xml_type(AgsPlugin *plugin);
void ags_equalizer10_set_xml_type(AgsPlugin *plugin, gchar *xml_type);
void ags_equalizer10_read(AgsFile *file, xmlNode *node, AgsPlugin *plugin);
xmlNode* ags_equalizer10_write(AgsFile *file, xmlNode *parent, AgsPlugin *plugin);

/**
 * SECTION:ags_equalizer10
 * @short_description: equalizer10 sequencer
 * @title: AgsEqualizer10
 * @section_id:
 * @include: ags/X/machine/ags_equalizer10.h
 *
 * The #AgsEqualizer10 is a composite widget to act as equalizer10 sequencer.
 */

static gpointer ags_equalizer10_parent_class = NULL;

static AgsConnectableInterface *ags_equalizer10_parent_connectable_interface;

GType
ags_equalizer10_get_type(void)
{
  static GType ags_type_equalizer10 = 0;

  if(!ags_type_equalizer10){
    static const GTypeInfo ags_equalizer10_info = {
      sizeof(AgsEqualizer10Class),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) ags_equalizer10_class_init,
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof(AgsEqualizer10),
      0,    /* n_preallocs */
      (GInstanceInitFunc) ags_equalizer10_init,
    };

    static const GInterfaceInfo ags_connectable_interface_info = {
      (GInterfaceInitFunc) ags_equalizer10_connectable_interface_init,
      NULL, /* interface_finalize */
      NULL, /* interface_data */
    };

    static const GInterfaceInfo ags_plugin_interface_info = {
      (GInterfaceInitFunc) ags_equalizer10_plugin_interface_init,
      NULL, /* interface_finalize */
      NULL, /* interface_data */
    };

    ags_type_equalizer10 = g_type_register_static(AGS_TYPE_MACHINE,
						  "AgsEqualizer10", &ags_equalizer10_info,
						  0);
    
    g_type_add_interface_static(ags_type_equalizer10,
				AGS_TYPE_CONNECTABLE,
				&ags_connectable_interface_info);

    g_type_add_interface_static(ags_type_equalizer10,
				AGS_TYPE_PLUGIN,
				&ags_plugin_interface_info);
  }

  return(ags_type_equalizer10);
}

void
ags_equalizer10_class_init(AgsEqualizer10Class *equalizer10)
{
  GObjectClass *gobject;
  GtkWidgetClass *widget;
  AgsMachineClass *machine;

  ags_equalizer10_parent_class = g_type_class_peek_parent(equalizer10);

  /* GObjectClass */
  gobject = (GObjectClass *) equalizer10;

  gobject->finalize = ags_equalizer10_finalize;

  /* GtkWidget */
  widget = (GtkWidgetClass *) equalizer10;

  /*  */
  machine = (AgsMachineClass *) equalizer10;

  machine->map_recall = ags_equalizer10_map_recall;
}

void
ags_equalizer10_connectable_interface_init(AgsConnectableInterface *connectable)
{
  ags_equalizer10_parent_connectable_interface = g_type_interface_peek_parent(connectable);

  connectable->connect = ags_equalizer10_connect;
  connectable->disconnect = ags_equalizer10_disconnect;
}

void
ags_equalizer10_plugin_interface_init(AgsPluginInterface *plugin)
{
  plugin->get_name = ags_equalizer10_get_name;
  plugin->set_name = ags_equalizer10_set_name;
  plugin->get_xml_type = ags_equalizer10_get_xml_type;
  plugin->set_xml_type = ags_equalizer10_set_xml_type;
  plugin->read = ags_equalizer10_read;
  plugin->write = ags_equalizer10_write;
}

void
ags_equalizer10_init(AgsEqualizer10 *equalizer10)
{
  GtkVBox *vbox;

  g_signal_connect_after((GObject *) equalizer10, "parent_set",
			 G_CALLBACK(ags_equalizer10_parent_set_callback), (gpointer) equalizer10);

  equalizer10->name = NULL;
  equalizer10->xml_type = "ags-equalizer10";

  vbox = (GtkVBox *) gtk_vbox_new(FALSE, 0);
  gtk_container_add((GtkContainer*) gtk_bin_get_child((GtkBin *) equalizer10), (GtkWidget *) vbox);

}

void
ags_equalizer10_finalize(GObject *gobject)
{  
  G_OBJECT_CLASS(ags_equalizer10_parent_class)->finalize(gobject);
}

void
ags_equalizer10_connect(AgsConnectable *connectable)
{
  AgsEqualizer10 *equalizer10;

  if((AGS_MACHINE_CONNECTED & (AGS_MACHINE(connectable)->flags)) != 0){
    return;
  }

  equalizer10 = AGS_EQUALIZER10(connectable);

  g_signal_connect_after(equalizer10, "resize-audio-channels",
			 G_CALLBACK(ags_equalizer10_resize_audio_channels_callback), NULL);
  
  g_signal_connect_after(equalizer10, "resize-pads",
			 G_CALLBACK(ags_equalizer10_resize_pads_callback), NULL);

  /* call parent */
  ags_equalizer10_parent_connectable_interface->connect(connectable);
}

void
ags_equalizer10_disconnect(AgsConnectable *connectable)
{
  AgsEqualizer10 *equalizer10;

  int i;

  if((AGS_MACHINE_CONNECTED & (AGS_MACHINE(connectable)->flags)) == 0){
    return;
  }

  equalizer10 = AGS_EQUALIZER10(connectable);

  g_object_disconnect(equalizer10,
		      "resize-audio-channels",
		      G_CALLBACK(ags_equalizer10_resize_audio_channels_callback),
		      NULL,
		      NULL);

  g_object_disconnect(equalizer10,
		      "resize-pads",
		      G_CALLBACK(ags_equalizer10_resize_pads_callback),
		      NULL,
		      NULL);

  /* call parent */
  ags_equalizer10_parent_connectable_interface->disconnect(connectable);
}

void
ags_equalizer10_map_recall(AgsMachine *machine)
{
  AgsEqualizer10 *equalizer10;
  
  AgsAudio *audio;
  AgsChannel *channel;
  
  AgsMutexManager *mutex_manager;

  guint audio_channels;
  guint i;

  pthread_mutex_t *application_mutex;
  pthread_mutex_t *audio_mutex;
  pthread_mutex_t *channel_mutex;
  
  mutex_manager = ags_mutex_manager_get_instance();
  application_mutex = ags_mutex_manager_get_application_mutex(mutex_manager);

  equalizer10 = machine;
  
  audio = machine->audio;

  /* lookup audio mutex */
  pthread_mutex_lock(application_mutex);

  audio_mutex = ags_mutex_manager_lookup(mutex_manager,
					 (GObject *) audio);
  
  pthread_mutex_unlock(application_mutex);
  
  /* get some fields */
  pthread_mutex_lock(audio_mutex);

  audio_channels = audio->audio_channels;

  channel = audio->input;
  
  pthread_mutex_unlock(audio_mutex);

  /* ags-eq10 */
  ags_recall_factory_create(audio,
			    NULL, NULL,
			    "ags-eq10",
			    0, audio_channels,
			    0, 1,
			    (AGS_RECALL_FACTORY_INPUT |
			     AGS_RECALL_FACTORY_PLAY |
			     AGS_RECALL_FACTORY_RECALL |
			     AGS_RECALL_FACTORY_ADD),
			    0);
  
  /* call parent */
  AGS_MACHINE_CLASS(ags_equalizer10_parent_class)->map_recall(machine);
}

gchar*
ags_equalizer10_get_name(AgsPlugin *plugin)
{
  return(AGS_EQUALIZER10(plugin)->name);
}

void
ags_equalizer10_set_name(AgsPlugin *plugin, gchar *name)
{
  AGS_EQUALIZER10(plugin)->name = name;
}

gchar*
ags_equalizer10_get_xml_type(AgsPlugin *plugin)
{
  return(AGS_EQUALIZER10(plugin)->xml_type);
}

void
ags_equalizer10_set_xml_type(AgsPlugin *plugin, gchar *xml_type)
{
  AGS_EQUALIZER10(plugin)->xml_type = xml_type;
}

void
ags_equalizer10_read(AgsFile *file, xmlNode *node, AgsPlugin *plugin)
{
  AgsEqualizer10 *gobject;

  gobject = AGS_EQUALIZER10(plugin);

  ags_file_add_id_ref(file,
		      g_object_new(AGS_TYPE_FILE_ID_REF,
				   "application-context", file->application_context,
				   "file", file,
				   "node", node,
				   "xpath", g_strdup_printf("xpath=//*[@id='%s']", xmlGetProp(node, AGS_FILE_ID_PROP)),
				   "reference", gobject,
				   NULL));
}

xmlNode*
ags_equalizer10_write(AgsFile *file, xmlNode *parent, AgsPlugin *plugin)
{
  AgsEqualizer10 *equalizer10;
  xmlNode *node;
  GList *list;
  gchar *id;
  guint i;

  equalizer10 = AGS_EQUALIZER10(plugin);

  id = ags_id_generator_create_uuid();
  
  node = xmlNewNode(NULL,
		    "ags-equalizer10");
  xmlNewProp(node,
	     AGS_FILE_ID_PROP,
	     id);

  ags_file_add_id_ref(file,
		      g_object_new(AGS_TYPE_FILE_ID_REF,
				   "application-context", file->application_context,
				   "file", file,
				   "node", node,
				   "xpath", g_strdup_printf("xpath=//*[@id='%s']", id),
				   "reference", equalizer10,
				   NULL));

  return(node);
}

/**
 * ags_equalizer10_new:
 * @soundcard: the assigned soundcard.
 *
 * Creates an #AgsEqualizer10
 *
 * Returns: a new #AgsEqualizer10
 *
 * Since: 1.5.0
 */
AgsEqualizer10*
ags_equalizer10_new(GObject *soundcard)
{
  AgsEqualizer10 *equalizer10;

  equalizer10 = (AgsEqualizer10 *) g_object_new(AGS_TYPE_EQUALIZER10,
						NULL);

  g_object_set(G_OBJECT(AGS_MACHINE(equalizer10)->audio),
	       "soundcard", soundcard,
	       NULL);

  return(equalizer10);
}
