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

#include <ags/audio/recall/ags_analyse_audio_signal.h>
#include <ags/audio/recall/ags_analyse_channel.h>

#include <ags/libags.h>

#include <ags/audio/ags_recall_channel_run.h>

#include <ags/i18n.h>

void ags_analyse_audio_signal_class_init(AgsAnalyseAudioSignalClass *analyse_audio_signal);
void ags_analyse_audio_signal_connectable_interface_init(AgsConnectableInterface *connectable);
void ags_analyse_audio_signal_dynamic_connectable_interface_init(AgsDynamicConnectableInterface *dynamic_connectable);
void ags_analyse_audio_signal_init(AgsAnalyseAudioSignal *analyse_audio_signal);
void ags_analyse_audio_signal_set_property(GObject *gobject,
					   guint prop_id,
					   const GValue *value,
					   GParamSpec *param_spec);
void ags_analyse_audio_signal_get_property(GObject *gobject,
					   guint prop_id,
					   GValue *value,
					   GParamSpec *param_spec);
void ags_analyse_audio_signal_connect(AgsConnectable *connectable);
void ags_analyse_audio_signal_disconnect(AgsConnectable *connectable);
void ags_analyse_audio_signal_connect_dynamic(AgsDynamicConnectable *dynamic_connectable);
void ags_analyse_audio_signal_disconnect_dynamic(AgsDynamicConnectable *dynamic_connectable);
void ags_analyse_audio_signal_finalize(GObject *gobject);

/**
 * SECTION:ags_analyse_audio_signal
 * @short_description: analyses audio signal
 * @title: AgsAnalyseAudioSignal
 * @section_id:
 * @include: ags/audio/recall/ags_analyse_audio_signal.h
 *
 * The #AgsAnalyseAudioSignal class analyses the audio signal.
 */

enum{
  PROP_0,
};

static gpointer ags_analyse_audio_signal_parent_class = NULL;
static AgsConnectableInterface *ags_analyse_audio_signal_parent_connectable_interface;
static AgsDynamicConnectableInterface *ags_analyse_audio_signal_parent_dynamic_connectable_interface;

GType
ags_analyse_audio_signal_get_type()
{
  static GType ags_type_analyse_audio_signal = 0;

  if(!ags_type_analyse_audio_signal){
    static const GTypeInfo ags_analyse_audio_signal_info = {
      sizeof (AgsAnalyseAudioSignalClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) ags_analyse_audio_signal_class_init,
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (AgsAnalyseAudioSignal),
      0,    /* n_preallocs */
      (GInstanceInitFunc) ags_analyse_audio_signal_init,
    };

    static const GInterfaceInfo ags_connectable_interface_info = {
      (GInterfaceInitFunc) ags_analyse_audio_signal_connectable_interface_init,
      NULL, /* interface_finalize */
      NULL, /* interface_data */
    };

    static const GInterfaceInfo ags_dynamic_connectable_interface_info = {
      (GInterfaceInitFunc) ags_analyse_audio_signal_dynamic_connectable_interface_init,
      NULL, /* interface_finalize */
      NULL, /* interface_data */
    };

    ags_type_analyse_audio_signal = g_type_register_static(AGS_TYPE_RECALL_AUDIO_SIGNAL,
							   "AgsAnalyseAudioSignal",
							   &ags_analyse_audio_signal_info,
							   0);

    g_type_add_interface_static(ags_type_analyse_audio_signal,
				AGS_TYPE_CONNECTABLE,
				&ags_connectable_interface_info);

    g_type_add_interface_static(ags_type_analyse_audio_signal,
				AGS_TYPE_DYNAMIC_CONNECTABLE,
				&ags_dynamic_connectable_interface_info);
  }

  return (ags_type_analyse_audio_signal);
}

void
ags_analyse_audio_signal_class_init(AgsAnalyseAudioSignalClass *analyse_audio_signal)
{
  GObjectClass *gobject;
  AgsRecallClass *recall;
  GParamSpec *param_spec;

  ags_analyse_audio_signal_parent_class = g_type_class_peek_parent(analyse_audio_signal);

  /* GObjectClass */
  gobject = (GObjectClass *) analyse_audio_signal;

  gobject->set_property = ags_analyse_audio_signal_set_property;
  gobject->get_property = ags_analyse_audio_signal_get_property;

  gobject->finalize = ags_analyse_audio_signal_finalize;

  /* properties */

  /* AgsRecallClass */
  recall = (AgsRecallClass *) analyse_audio_signal;
}

void
ags_analyse_audio_signal_connectable_interface_init(AgsConnectableInterface *connectable)
{
  ags_analyse_audio_signal_parent_connectable_interface = g_type_interface_peek_parent(connectable);

  connectable->connect = ags_analyse_audio_signal_connect;
  connectable->disconnect = ags_analyse_audio_signal_disconnect;
}

void
ags_analyse_audio_signal_dynamic_connectable_interface_init(AgsDynamicConnectableInterface *dynamic_connectable)
{
  ags_analyse_audio_signal_parent_dynamic_connectable_interface = g_type_interface_peek_parent(dynamic_connectable);

  dynamic_connectable->connect_dynamic = ags_analyse_audio_signal_connect_dynamic;
  dynamic_connectable->disconnect_dynamic = ags_analyse_audio_signal_disconnect_dynamic;
}

void
ags_analyse_audio_signal_init(AgsAnalyseAudioSignal *analyse_audio_signal)
{
  AGS_RECALL(analyse_audio_signal)->child_type = G_TYPE_NONE;

  analyse_audio_signal->comout = NULL;

  analyse_audio_signal->in = NULL;
  analyse_audio_signal->out = NULL;
}

void
ags_analyse_audio_signal_finalize(GObject *gobject)
{
  /* call parent */
  G_OBJECT_CLASS(ags_analyse_audio_signal_parent_class)->finalize(gobject);

  /* empty */
}

void
ags_analyse_audio_signal_set_property(GObject *gobject,
				      guint prop_id,
				      const GValue *value,
				      GParamSpec *param_spec)
{
  AgsAnalyseAudioSignal *analyse_audio_signal;

  analyse_audio_signal = AGS_ANALYSE_AUDIO_SIGNAL(gobject);

  switch(prop_id){
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(gobject, prop_id, param_spec);
    break;
  }
}

void
ags_analyse_audio_signal_get_property(GObject *gobject,
				      guint prop_id,
				      GValue *value,
				      GParamSpec *param_spec)
{
  AgsAnalyseAudioSignal *analyse_audio_signal;

  analyse_audio_signal = AGS_ANALYSE_AUDIO_SIGNAL(gobject);

  switch(prop_id){
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(gobject, prop_id, param_spec);
    break;
  }
}

void
ags_analyse_audio_signal_connect(AgsConnectable *connectable)
{
  if((AGS_RECALL_CONNECTED & (AGS_RECALL(connectable)->flags)) != 0){
    return;
  }

  /* call parent */
  ags_analyse_audio_signal_parent_connectable_interface->connect(connectable);

  /* empty */
}

void
ags_analyse_audio_signal_disconnect(AgsConnectable *connectable)
{
  /* call parent */
  ags_analyse_audio_signal_parent_connectable_interface->disconnect(connectable);

  /* empty */
}

void
ags_analyse_audio_signal_connect_dynamic(AgsDynamicConnectable *dynamic_connectable)
{
  if((AGS_RECALL_DYNAMIC_CONNECTED & (AGS_RECALL(dynamic_connectable)->flags)) != 0){
    return;
  }

  /* call parent */
  ags_analyse_audio_signal_parent_dynamic_connectable_interface->connect_dynamic(dynamic_connectable);

  /* empty */
}

void
ags_analyse_audio_signal_disconnect_dynamic(AgsDynamicConnectable *dynamic_connectable)
{
  /* call parent */
  ags_analyse_audio_signal_parent_dynamic_connectable_interface->disconnect_dynamic(dynamic_connectable);

  /* empty */
}

/**
 * ags_analyse_audio_signal_new:
 * @audio_signal: an #AgsAudioSignal
 *
 * Creates an #AgsAnalyseAudioSignal
 *
 * Returns: a new #AgsAnalyseAudioSignal
 *
 * Since: 1.5.0
 */
AgsAnalyseAudioSignal*
ags_analyse_audio_signal_new(AgsAudioSignal *audio_signal)
{
  AgsAnalyseAudioSignal *analyse_audio_signal;

  analyse_audio_signal = (AgsAnalyseAudioSignal *) g_object_new(AGS_TYPE_ANALYSE_AUDIO_SIGNAL,
								NULL);

  return(analyse_audio_signal);
}
