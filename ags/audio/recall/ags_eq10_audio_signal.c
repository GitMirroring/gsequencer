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

#include <ags/audio/recall/ags_eq10_audio_signal.h>
#include <ags/audio/recall/ags_eq10_channel.h>

#include <ags/libags.h>

#include <ags/audio/ags_input.h>
#include <ags/audio/ags_port.h>
#include <ags/audio/ags_recall_channel_run.h>
#include <ags/audio/ags_audio_buffer_util.h>

void ags_eq10_audio_signal_class_init(AgsEq10AudioSignalClass *eq10_audio_signal);
void ags_eq10_audio_signal_connectable_interface_init(AgsConnectableInterface *connectable);
void ags_eq10_audio_signal_dynamic_connectable_interface_init(AgsDynamicConnectableInterface *dynamic_connectable);
void ags_eq10_audio_signal_init(AgsEq10AudioSignal *eq10_audio_signal);
void ags_eq10_audio_signal_connect(AgsConnectable *connectable);
void ags_eq10_audio_signal_disconnect(AgsConnectable *connectable);
void ags_eq10_audio_signal_connect_dynamic(AgsDynamicConnectable *dynamic_connectable);
void ags_eq10_audio_signal_disconnect_dynamic(AgsDynamicConnectable *dynamic_connectable);
void ags_eq10_audio_signal_finalize(GObject *gobject);

void ags_eq10_audio_signal_run_inter(AgsRecall *recall);
AgsRecall* ags_eq10_audio_signal_duplicate(AgsRecall *recall,
					   AgsRecallID *recall_id,
					   guint *n_params, GParameter *parameter);

/**
 * SECTION:ags_eq10_audio_signal
 * @short_description: eq10s audio signal
 * @title: AgsEq10AudioSignal
 * @section_id:
 * @include: ags/audio/recall/ags_eq10_audio_signal.h
 *
 * The #AgsEq10AudioSignal class eq10s the audio signal.
 */

static gpointer ags_eq10_audio_signal_parent_class = NULL;
static AgsConnectableInterface *ags_eq10_audio_signal_parent_connectable_interface;
static AgsDynamicConnectableInterface *ags_eq10_audio_signal_parent_dynamic_connectable_interface;

GType
ags_eq10_audio_signal_get_type()
{
  static GType ags_type_eq10_audio_signal = 0;

  if(!ags_type_eq10_audio_signal){
    static const GTypeInfo ags_eq10_audio_signal_info = {
      sizeof (AgsEq10AudioSignalClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) ags_eq10_audio_signal_class_init,
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (AgsEq10AudioSignal),
      0,    /* n_preallocs */
      (GInstanceInitFunc) ags_eq10_audio_signal_init,
    };

    static const GInterfaceInfo ags_connectable_interface_info = {
      (GInterfaceInitFunc) ags_eq10_audio_signal_connectable_interface_init,
      NULL, /* interface_finalize */
      NULL, /* interface_data */
    };

    static const GInterfaceInfo ags_dynamic_connectable_interface_info = {
      (GInterfaceInitFunc) ags_eq10_audio_signal_dynamic_connectable_interface_init,
      NULL, /* interface_finalize */
      NULL, /* interface_data */
    };

    ags_type_eq10_audio_signal = g_type_register_static(AGS_TYPE_RECALL_AUDIO_SIGNAL,
							"AgsEq10AudioSignal",
							&ags_eq10_audio_signal_info,
							0);

    g_type_add_interface_static(ags_type_eq10_audio_signal,
				AGS_TYPE_CONNECTABLE,
				&ags_connectable_interface_info);

    g_type_add_interface_static(ags_type_eq10_audio_signal,
				AGS_TYPE_DYNAMIC_CONNECTABLE,
				&ags_dynamic_connectable_interface_info);
  }

  return (ags_type_eq10_audio_signal);
}

void
ags_eq10_audio_signal_class_init(AgsEq10AudioSignalClass *eq10_audio_signal)
{
  GObjectClass *gobject;
  AgsRecallClass *recall;
  GParamSpec *param_spec;

  ags_eq10_audio_signal_parent_class = g_type_class_peek_parent(eq10_audio_signal);

  /* GObjectClass */
  gobject = (GObjectClass *) eq10_audio_signal;

  gobject->finalize = ags_eq10_audio_signal_finalize;

  /* AgsRecallClass */
  recall = (AgsRecallClass *) eq10_audio_signal;

  recall->run_inter = ags_eq10_audio_signal_run_inter;
}

void
ags_eq10_audio_signal_connectable_interface_init(AgsConnectableInterface *connectable)
{
  ags_eq10_audio_signal_parent_connectable_interface = g_type_interface_peek_parent(connectable);

  connectable->connect = ags_eq10_audio_signal_connect;
  connectable->disconnect = ags_eq10_audio_signal_disconnect;
}

void
ags_eq10_audio_signal_dynamic_connectable_interface_init(AgsDynamicConnectableInterface *dynamic_connectable)
{
  ags_eq10_audio_signal_parent_dynamic_connectable_interface = g_type_interface_peek_parent(dynamic_connectable);

  dynamic_connectable->connect_dynamic = ags_eq10_audio_signal_connect_dynamic;
  dynamic_connectable->disconnect_dynamic = ags_eq10_audio_signal_disconnect_dynamic;
}

void
ags_eq10_audio_signal_init(AgsEq10AudioSignal *eq10_audio_signal)
{
  AGS_RECALL(eq10_audio_signal)->name = "ags-eq10";
  AGS_RECALL(eq10_audio_signal)->version = AGS_RECALL_DEFAULT_VERSION;
  AGS_RECALL(eq10_audio_signal)->build_id = AGS_RECALL_DEFAULT_BUILD_ID;
  AGS_RECALL(eq10_audio_signal)->xml_type = "ags-eq10-audio-signal";
  AGS_RECALL(eq10_audio_signal)->port = NULL;
}

void
ags_eq10_audio_signal_finalize(GObject *gobject)
{
  /* call parent */
  G_OBJECT_CLASS(ags_eq10_audio_signal_parent_class)->finalize(gobject);

  /* empty */
}

void
ags_eq10_audio_signal_connect(AgsConnectable *connectable)
{
  /* call parent */
  ags_eq10_audio_signal_parent_connectable_interface->connect(connectable);

  /* empty */
}

void
ags_eq10_audio_signal_disconnect(AgsConnectable *connectable)
{
  /* call parent */
  ags_eq10_audio_signal_parent_connectable_interface->disconnect(connectable);

  /* empty */
}

void
ags_eq10_audio_signal_connect_dynamic(AgsDynamicConnectable *dynamic_connectable)
{
  /* call parent */
  ags_eq10_audio_signal_parent_dynamic_connectable_interface->connect_dynamic(dynamic_connectable);

  /* empty */
}

void
ags_eq10_audio_signal_disconnect_dynamic(AgsDynamicConnectable *dynamic_connectable)
{
  /* call parent */
  ags_eq10_audio_signal_parent_dynamic_connectable_interface->disconnect_dynamic(dynamic_connectable);

  /* empty */
}

void
ags_eq10_audio_signal_run_inter(AgsRecall *recall)
{
  AGS_RECALL_CLASS(ags_eq10_audio_signal_parent_class)->run_inter(recall);

  if(recall->rt_safe &&
     recall->recall_id->recycling_context->parent != NULL &&
     AGS_RECALL_AUDIO_SIGNAL(recall)->source->note == NULL){
    return;
  }
  
  if(AGS_RECALL_AUDIO_SIGNAL(recall)->source->stream_current != NULL){
    AgsEq10Channel *eq10_channel;

    eq10_channel = AGS_EQ10_CHANNEL(AGS_RECALL_CHANNEL_RUN(recall->parent->parent)->recall_channel);

    //TODO:JK: implement me
  }else{
    ags_recall_done(recall);
  }
}

/**
 * ags_eq10_audio_signal_new:
 * @audio_signal: an #AgsAudioSignal
 *
 * Creates an #AgsEq10AudioSignal
 *
 * Returns: a new #AgsEq10AudioSignal
 *
 * Since: 1.5.0
 */
AgsEq10AudioSignal*
ags_eq10_audio_signal_new(AgsAudioSignal *audio_signal)
{
  AgsEq10AudioSignal *eq10_audio_signal;

  eq10_audio_signal = (AgsEq10AudioSignal *) g_object_new(AGS_TYPE_EQ10_AUDIO_SIGNAL,
							  NULL);

  return(eq10_audio_signal);
}
