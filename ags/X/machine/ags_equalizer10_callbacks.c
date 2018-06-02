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

#include <ags/X/machine/ags_equalizer10_callbacks.h>

#include <ags/X/ags_window.h>

void
ags_equalizer10_parent_set_callback(GtkWidget *widget, GtkObject *old_parent, AgsEqualizer10 *equalizer10)
{
  AgsWindow *window;

  gchar *str;
  
  if(old_parent != NULL){
    return;
  }

  window = AGS_WINDOW(gtk_widget_get_ancestor((GtkWidget *) equalizer10, AGS_TYPE_WINDOW));

  str = g_strdup_printf("Default %d",
			ags_window_find_machine_counter(window, AGS_TYPE_EQUALIZER10)->counter);

  g_object_set(AGS_MACHINE(equalizer10),
	       "machine-name", str,
	       NULL);

  ags_window_increment_machine_counter(window,
				       AGS_TYPE_EQUALIZER10);
  g_free(str);
}

void
ags_equalizer10_resize_audio_channels_callback(AgsEqualizer10 *equalizer10,
						guint audio_channels, guint audio_channels_old,
						gpointer data)
{
  AgsAudio *audio;

  guint i;
  
  audio = AGS_MACHINE(equalizer10)->audio;
  
  if(audio_channels > audio_channels_old){
    if((AGS_MACHINE_MAPPED_RECALL & (AGS_MACHINE(equalizer10)->flags)) != 0){
      AgsChannel *channel;
      AgsPort *port;
            
      AgsMutexManager *mutex_manager;
      
      guint i;

      pthread_mutex_t *application_mutex;
      pthread_mutex_t *audio_mutex;
      pthread_mutex_t *channel_mutex;
  
      mutex_manager = ags_mutex_manager_get_instance();
      application_mutex = ags_mutex_manager_get_application_mutex(mutex_manager);      

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
  
      /* ags-analyse */
      ags_recall_factory_create(audio,
				NULL, NULL,
				"ags-eq10",
				audio_channels_old, audio_channels,
				0, 1,
				(AGS_RECALL_FACTORY_INPUT |
				 AGS_RECALL_FACTORY_PLAY |
				 AGS_RECALL_FACTORY_RECALL |
				 AGS_RECALL_FACTORY_ADD),
				0);

      //TODO:JK: implement me
    }
  }else{
    //TODO:JK: implement me
  }
}

void
ags_equalizer10_resize_pads_callback(AgsEqualizer10 *equalizer10,
				      GType channel_type,
				      guint pads, guint pads_old,
				      gpointer data)
{  
  if(pads_old == 0 && channel_type == AGS_TYPE_INPUT){
    if((AGS_MACHINE_MAPPED_RECALL & (AGS_MACHINE(equalizer10)->flags)) != 0){
      AgsAudio *audio;
      AgsChannel *channel;
      AgsPort *port;
      
      AgsMutexManager *mutex_manager;
      
      guint audio_channels;
      guint i;

      pthread_mutex_t *application_mutex;
      pthread_mutex_t *audio_mutex;
      pthread_mutex_t *channel_mutex;
  
      mutex_manager = ags_mutex_manager_get_instance();
      application_mutex = ags_mutex_manager_get_application_mutex(mutex_manager);      

      audio = AGS_MACHINE(equalizer10)->audio;

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
  
      /* ags-analyse */
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

      //TODO:JK: implement me
    }
  }

  if(pads == 0 && channel_type == AGS_TYPE_INPUT){
    //TODO:JK: implement me
  }
}
