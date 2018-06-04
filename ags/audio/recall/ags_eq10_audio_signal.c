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

#include <math.h>

void ags_eq10_audio_signal_class_init(AgsEq10AudioSignalClass *eq10_audio_signal);
void ags_eq10_audio_signal_connectable_interface_init(AgsConnectableInterface *connectable);
void ags_eq10_audio_signal_dynamic_connectable_interface_init(AgsDynamicConnectableInterface *dynamic_connectable);
void ags_eq10_audio_signal_init(AgsEq10AudioSignal *eq10_audio_signal);
void ags_eq10_audio_signal_connect(AgsConnectable *connectable);
void ags_eq10_audio_signal_disconnect(AgsConnectable *connectable);
void ags_eq10_audio_signal_connect_dynamic(AgsDynamicConnectable *dynamic_connectable);
void ags_eq10_audio_signal_disconnect_dynamic(AgsDynamicConnectable *dynamic_connectable);
void ags_eq10_audio_signal_finalize(GObject *gobject);

void ags_eq10_audio_signal_run_init_pre(AgsRecall *recall);
void ags_eq10_audio_signal_run_inter(AgsRecall *recall);
AgsRecall* ags_eq10_audio_signal_duplicate(AgsRecall *recall,
					   AgsRecallID *recall_id,
					   guint *n_params, GParameter *parameter);

#define AGS_EQ10_AUDIO_SIGNAL_2_POLE_FILTER(output, input,)

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

  recall->run_init_pre = ags_eq10_audio_signal_run_init_pre;
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

  eq10_audio_signal->buffer_28hz = NULL;
  eq10_audio_signal->buffer_56hz = NULL;
  eq10_audio_signal->buffer_112hz = NULL;
  eq10_audio_signal->buffer_224hz = NULL;
  eq10_audio_signal->buffer_448hz = NULL;
  eq10_audio_signal->buffer_896hz = NULL;
  eq10_audio_signal->buffer_1792hz = NULL;
  eq10_audio_signal->buffer_3548hz = NULL;
  eq10_audio_signal->buffer_7168hz = NULL;
  eq10_audio_signal->buffer_14336hz = NULL;

  eq10_audio_signal->output_buffer = NULL;
  eq10_audio_signal->input_bufer = NULL;  
}

void
ags_eq10_audio_signal_finalize(GObject *gobject)
{
  AgsEq10 *eq10;

  eq10 = (AgsEq10 *) gobject;
  
  g_free(eq10->buffer_28hz);
  g_free(eq10->buffer_56hz);
  g_free(eq10->buffer_112hz);
  g_free(eq10->buffer_224hz);
  g_free(eq10->buffer_448hz);
  g_free(eq10->buffer_896hz);
  g_free(eq10->buffer_1792hz);
  g_free(eq10->buffer_3548hz);
  g_free(eq10->buffer_7168hz);
  g_free(eq10->buffer_14336hz);

  g_free(eq10->output_buffer);
  g_free(eq10->input_buffer);
  
  /* call parent */
  G_OBJECT_CLASS(ags_eq10_audio_signal_parent_class)->finalize(gobject);
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
ags_eq10_audio_signal_run_init_pre(AgsRecall *recall)
{
  AgsAudioSignal *source;

  AgsEq10AudioSignal *eq10_audio_signal;

  guint buffer_size;

  eq10_audio_signal = recall;

  /* call parent */
  AGS_RECALL_CLASS(ags_eq10_audio_signal_parent_class)->run_init_pre(recall);

  source = AGS_RECALL_AUDIO_SIGNAL(eq10_audio_signal)->source;

  buffer_size = source->buffer_size;
  
  eq10_audio_signal->buffer_28hz = (double *) malloc(buffer_size * sizeof(double));
  eq10_audio_signal->buffer_56hz = (double *) malloc(buffer_size * sizeof(double));
  eq10_audio_signal->buffer_112hz = (double *) malloc(buffer_size * sizeof(double));
  eq10_audio_signal->buffer_224hz = (double *) malloc(buffer_size * sizeof(double));
  eq10_audio_signal->buffer_448hz = (double *) malloc(buffer_size * sizeof(double));
  eq10_audio_signal->buffer_896hz = (double *) malloc(buffer_size * sizeof(double));
  eq10_audio_signal->buffer_1792hz = (double *) malloc(buffer_size * sizeof(double));
  eq10_audio_signal->buffer_3548hz = (double *) malloc(buffer_size * sizeof(double));
  eq10_audio_signal->buffer_7168hz = (double *) malloc(buffer_size * sizeof(double));
  eq10_audio_signal->buffer_14336hz = (double *) malloc(buffer_size * sizeof(double));

  eq10_audio_signal->output_buffer = (double *) malloc(buffer_size * sizeof(double));
  eq10_audio_signal->input_bufer = (double *) malloc(buffer_size * sizeof(double));  

  /* initially empty */
  ags_audio_buffer_util_clear_double(eq10_audio_signal->buffer_28hz, 1,
				     buffer_size);
  ags_audio_buffer_util_clear_double(eq10_audio_signal->buffer_56hz, 1,
				     buffer_size);
  ags_audio_buffer_util_clear_double(eq10_audio_signal->buffer_112hz, 1,
				     buffer_size);
  ags_audio_buffer_util_clear_double(eq10_audio_signal->buffer_224hz, 1,
				     buffer_size);
  ags_audio_buffer_util_clear_double(eq10_audio_signal->buffer_448hz, 1,
				     buffer_size);
  ags_audio_buffer_util_clear_double(eq10_audio_signal->buffer_896hz, 1,
				     buffer_size);
  ags_audio_buffer_util_clear_double(eq10_audio_signal->buffer_1792hz, 1,
				     buffer_size);
  ags_audio_buffer_util_clear_double(eq10_audio_signal->buffer_3548hz, 1,
				     buffer_size);
  ags_audio_buffer_util_clear_double(eq10_audio_signal->buffer_7168hz, 1,
				     buffer_size);
  ags_audio_buffer_util_clear_double(eq10_audio_signal->buffer_14336hz, 1,
				     buffer_size);
}

void
ags_eq10_audio_signal_run_inter(AgsRecall *recall)
{
  AgsAudioSignal *source;

  AgsEq10Channel *eq10_channel;
  AgsEq10AudioSignal *eq10_audio_signal;

  GList *stream_source;

  gfloat peak_28hz;
  gfloat peak_56hz;
  gfloat peak_112hz;
  gfloat peak_224hz;
  gfloat peak_448hz;
  gfloat peak_896hz;
  gfloat peak_1792hz;
  gfloat peak_3548hz;
  gfloat peak_7192hz;
  gfloat peak_14336hz;
  
  guint output_copy_mode;
  guint input_copy_mode;
  guint buffer_size;
  guint samplerate;
  guint i;

  GValue value = {0,};
  
  eq10_audio_signal = recall;

  /* call parent */
  AGS_RECALL_CLASS(ags_eq10_audio_signal_parent_class)->run_inter(recall);

  source = AGS_RECALL_AUDIO_SIGNAL(eq10_audio_signal)->source;

  if(recall->rt_safe &&
     recall->recall_id->recycling_context->parent != NULL &&
     source->note == NULL){
    return;
  }

  stream_source = source->stream_current;

  if(stream_source == NULL){
    ags_recall_done(recall);

    return;
  }

  eq10_channel = AGS_EQ10_CHANNEL(AGS_RECALL_CHANNEL_RUN(recall->parent->parent)->recall_channel);

  /* copy mode */
  output_copy_mode = ags_audio_buffer_util_get_copy_mode(ags_audio_buffer_util_format_from_soundcard(source->format),
							 AGS_AUDIO_BUFFER_UTIL_DOUBLE);

  input_copy_mode = ags_audio_buffer_util_get_copy_mode(AGS_AUDIO_BUFFER_UTIL_DOUBLE,
							ags_audio_buffer_util_format_from_soundcard(source->format));

  buffer_size = source->buffer_size;
  samplerate = source->samplerate;
  
  /* clear buffer */
  ags_audio_buffer_util_clear_double(eq10_audio_signal->output_buffer, 1,
				     buffer_size);
  ags_audio_buffer_util_clear_double(eq10_audio_signal->input_buffer, 1,
				     buffer_size);

  /* copy input */
  ags_audio_buffer_util_copy_buffer_to_buffer(eq10_audio_signal->input_buffer, 1, 0,
					      stream_source->data, 1, 0,
					      buffer_size, copy_mode);

  /* retrieve port values */
  g_value_init(&value, G_TYPE_FLOAT);
  
  ags_port_safe_read(eq10_channel->peak_28hz, &value);
  
  peak_28hz = g_value_get_float(&value);
  g_value_reset(&value);

  ags_port_safe_read(eq10_channel->peak_56hz, &value);
  
  peak_56hz = g_value_get_float(&value);
  g_value_reset(&value);

  ags_port_safe_read(eq10_channel->peak_112hz, &value);
  
  peak_112hz = g_value_get_float(&value);
  g_value_reset(&value);

  ags_port_safe_read(eq10_channel->peak_224hz, &value);
  
  peak_224hz = g_value_get_float(&value);
  g_value_reset(&value);

  ags_port_safe_read(eq10_channel->peak_448hz, &value);
  
  peak_448hz = g_value_get_float(&value);
  g_value_reset(&value);
  
  ags_port_safe_read(eq10_channel->peak_896hz, &value);
  
  peak_896hz = g_value_get_float(&value);
  g_value_reset(&value);

  ags_port_safe_read(eq10_channel->peak_1792hz, &value);
  
  peak_1792hz = g_value_get_float(&value);
  g_value_reset(&value);

  ags_port_safe_read(eq10_channel->peak_3548hz, &value);
  
  peak_3548hz = g_value_get_float(&value);
  g_value_reset(&value);

  ags_port_safe_read(eq10_channel->peak_7168hz, &value);
  
  peak_7168hz = g_value_get_float(&value);
  g_value_reset(&value);

  ags_port_safe_read(eq10_channel->peak_14336hz, &value);
  
  peak_14336hz = g_value_get_float(&value);

  g_value_unset(&value);
  
  /* equalizer */
  for(i = 0; i < buffer_size; i++){
    gdouble x0, y1, y2;
    gdouble c, cs, csp1;
    gdouble Bc, gbc;
    gdouble nrm;
    gdouble a0, a1, a2; // denominator
    gdouble b0, b1, b2; // numerator
    
    /* 28 hz */
    c = cot(M_PI * 28.0 / (gdouble) samplerate);
    cs = c * c;
    csp1 = cs + 1.0;

    Bc = (28.0 / (gdouble) samplerate) * c;

    gBc = peak_28hz * Bc;

    nrm = 1.0 / (csp1 + Bc);

    /* coefficients */
    b0 =  (csp1 + gBc) * nrm;
    b1 =  2.0 * (1.0 - cs) * nrm;
    b2 =  (csp1 - gBc) * nrm;
    a0 =  1.0;
    a1 =  b1;
    a2 =  (csp1 - Bc) * nrm;
  }

  /* copy output */
  ags_audio_buffer_util_copy_buffer_to_buffer(stream_source->data, 1, 0,
					      eq10_audio_signal->output_buffer, 1, 0,
					      buffer_size, copy_mode);
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
