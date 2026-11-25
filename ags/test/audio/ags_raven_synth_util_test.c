/* GSequencer - Advanced GTK Sequencer
 * Copyright (C) 2005-2026 Joël Krähemann
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

#include <glib.h>
#include <glib-object.h>

#include <CUnit/CUnit.h>
#include <CUnit/Automated.h>
#include <CUnit/Basic.h>

#include <ags/libags.h>
#include <ags/libags-audio.h>

int ags_raven_synth_util_test_init_suite();
int ags_raven_synth_util_test_clean_suite();

void ags_raven_synth_util_test_alloc();
void ags_raven_synth_util_test_copy();
void ags_raven_synth_util_test_free();
void ags_raven_synth_util_test_get_source();
void ags_raven_synth_util_test_set_source();
void ags_raven_synth_util_test_get_source_stride();
void ags_raven_synth_util_test_set_source_stride();
void ags_raven_synth_util_test_get_buffer_length();
void ags_raven_synth_util_test_set_buffer_length();
void ags_raven_synth_util_test_get_samplerate();
void ags_raven_synth_util_test_set_samplerate();
void ags_raven_synth_util_test_get_synth_oscillator_mode();
void ags_raven_synth_util_test_set_synth_oscillator_mode();
void ags_raven_synth_util_test_get_frequency();
void ags_raven_synth_util_test_set_frequency();
void ags_raven_synth_util_test_get_phase();
void ags_raven_synth_util_test_set_phase();
void ags_raven_synth_util_test_get_lfo_oscillator_mode();
void ags_raven_synth_util_test_set_lfo_oscillator_mode();
void ags_raven_synth_util_test_get_lfo_frequency();
void ags_raven_synth_util_test_set_lfo_frequency();
void ags_raven_synth_util_test_get_lfo_depth();
void ags_raven_synth_util_test_set_lfo_depth();
void ags_raven_synth_util_test_get_tuning();
void ags_raven_synth_util_test_set_tuning();
void ags_raven_synth_util_test_get_volume();
void ags_raven_synth_util_test_set_volume();
void ags_raven_synth_util_test_get_frame_count();
void ags_raven_synth_util_test_set_frame_count();
void ags_raven_synth_util_test_get_offset();
void ags_raven_synth_util_test_set_offset();

void ags_raven_synth_util_test_compute_sin_s8();
void ags_raven_synth_util_test_compute_sin_s16();
void ags_raven_synth_util_test_compute_sin_s24();
void ags_raven_synth_util_test_compute_sin_s32();
void ags_raven_synth_util_test_compute_sin_s64();
void ags_raven_synth_util_test_compute_sin_float();
void ags_raven_synth_util_test_compute_sin_double();
void ags_raven_synth_util_test_compute_sin_complex();

void ags_raven_synth_util_test_compute_sawtooth_s8();
void ags_raven_synth_util_test_compute_sawtooth_s16();
void ags_raven_synth_util_test_compute_sawtooth_s24();
void ags_raven_synth_util_test_compute_sawtooth_s32();
void ags_raven_synth_util_test_compute_sawtooth_s64();
void ags_raven_synth_util_test_compute_sawtooth_float();
void ags_raven_synth_util_test_compute_sawtooth_double();
void ags_raven_synth_util_test_compute_sawtooth_complex();

void ags_raven_synth_util_test_compute_triangle_s8();
void ags_raven_synth_util_test_compute_triangle_s16();
void ags_raven_synth_util_test_compute_triangle_s24();
void ags_raven_synth_util_test_compute_triangle_s32();
void ags_raven_synth_util_test_compute_triangle_s64();
void ags_raven_synth_util_test_compute_triangle_float();
void ags_raven_synth_util_test_compute_triangle_double();
void ags_raven_synth_util_test_compute_triangle_complex();

void ags_raven_synth_util_test_compute_square_s8();
void ags_raven_synth_util_test_compute_square_s16();
void ags_raven_synth_util_test_compute_square_s24();
void ags_raven_synth_util_test_compute_square_s32();
void ags_raven_synth_util_test_compute_square_s64();
void ags_raven_synth_util_test_compute_square_float();
void ags_raven_synth_util_test_compute_square_double();
void ags_raven_synth_util_test_compute_square_complex();

void ags_raven_synth_util_test_compute_impulse_s8();
void ags_raven_synth_util_test_compute_impulse_s16();
void ags_raven_synth_util_test_compute_impulse_s24();
void ags_raven_synth_util_test_compute_impulse_s32();
void ags_raven_synth_util_test_compute_impulse_s64();
void ags_raven_synth_util_test_compute_impulse_float();
void ags_raven_synth_util_test_compute_impulse_double();
void ags_raven_synth_util_test_compute_impulse_complex();

#define AGS_RAVEN_SYNTH_UTIL_TEST_AUDIO_CHANNELS (1)

#define AGS_RAVEN_SYNTH_UTIL_TEST_BUFFER_SIZE (1024)
#define AGS_RAVEN_SYNTH_UTIL_TEST_FORMAT (AGS_SOUNDCARD_SIGNED_16_BIT)
#define AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE (44100)

#define AGS_RAVEN_SYNTH_UTIL_TEST_FREQ (440.0)
#define AGS_RAVEN_SYNTH_UTIL_TEST_PHASE (0.0)
#define AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME (1.0)
#define AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE (44100)
#define AGS_RAVEN_SYNTH_UTIL_TEST_OFFSET (0)
#define AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT (1024)
#define AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE (AGS_SYNTH_OSCILLATOR_SIN)
#define AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ (8.0)
#define AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH (0.5)
#define AGS_RAVEN_SYNTH_UTIL_TEST_TUNING (0.0)

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int
ags_raven_synth_util_test_init_suite()
{ 
  return(0);
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int
ags_raven_synth_util_test_clean_suite()
{
  return(0);
}

void
ags_raven_synth_util_test_alloc()
{
  AgsRavenSynthUtil *raven_synth_util;

  raven_synth_util = ags_raven_synth_util_alloc();

  CU_ASSERT(raven_synth_util != NULL);

  CU_ASSERT(raven_synth_util->source == NULL);
  CU_ASSERT(raven_synth_util->source_stride == 1);
  
  CU_ASSERT(raven_synth_util->buffer_length == 0);
  CU_ASSERT(raven_synth_util->format == AGS_SOUNDCARD_DEFAULT_FORMAT);
  CU_ASSERT(raven_synth_util->samplerate == AGS_SOUNDCARD_DEFAULT_SAMPLERATE);

  CU_ASSERT(raven_synth_util->synth_oscillator_mode == AGS_SYNTH_OSCILLATOR_SIN);
  
  CU_ASSERT(raven_synth_util->frequency == AGS_RAVEN_SYNTH_UTIL_DEFAULT_FREQUENCY);
  CU_ASSERT(raven_synth_util->phase == 0.0);
  CU_ASSERT(raven_synth_util->volume == 1.0);
}

void
ags_raven_synth_util_test_copy()
{
  AgsRavenSynthUtil raven_synth_util = {0,};
  AgsRavenSynthUtil *copy_raven_synth_util;

  raven_synth_util = AGS_RAVEN_SYNTH_UTIL_INITIALIZER;

  raven_synth_util.source = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_AUDIO_CHANNELS * AGS_RAVEN_SYNTH_UTIL_TEST_BUFFER_SIZE,
					     AGS_RAVEN_SYNTH_UTIL_TEST_FORMAT);
  
  ags_raven_synth_util_set_buffer_length(&raven_synth_util,
					 AGS_RAVEN_SYNTH_UTIL_TEST_BUFFER_SIZE);
  
  copy_raven_synth_util = ags_raven_synth_util_copy(&raven_synth_util);
  
  CU_ASSERT(copy_raven_synth_util != NULL);
    
  CU_ASSERT(copy_raven_synth_util->source == raven_synth_util.source);
  CU_ASSERT(copy_raven_synth_util->source_stride == raven_synth_util.source_stride);
  
  CU_ASSERT(copy_raven_synth_util->buffer_length == raven_synth_util.buffer_length);
  CU_ASSERT(copy_raven_synth_util->format == raven_synth_util.format);
  CU_ASSERT(copy_raven_synth_util->samplerate == raven_synth_util.samplerate);
}

void
ags_raven_synth_util_test_free()
{
  AgsRavenSynthUtil *raven_synth_util;
  
  raven_synth_util = (AgsRavenSynthUtil *) g_new(AgsRavenSynthUtil,
						 1);

  raven_synth_util[0] = AGS_RAVEN_SYNTH_UTIL_INITIALIZER;
  
  CU_ASSERT(raven_synth_util != NULL);

  raven_synth_util->source = NULL;
  
  ags_raven_synth_util_free(raven_synth_util);
  
  raven_synth_util = ags_raven_synth_util_alloc();

  CU_ASSERT(raven_synth_util != NULL);

  ags_raven_synth_util_free(raven_synth_util);
}

void
ags_raven_synth_util_test_get_source()
{
  AgsRavenSynthUtil raven_synth_util = {0,};

  raven_synth_util.source = NULL;

  CU_ASSERT(ags_raven_synth_util_get_source(&raven_synth_util) == NULL);
  
  raven_synth_util.source = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_BUFFER_SIZE,
					     AGS_RAVEN_SYNTH_UTIL_TEST_FORMAT);

  CU_ASSERT(ags_raven_synth_util_get_source(&raven_synth_util) == raven_synth_util.source);
}

void
ags_raven_synth_util_test_set_source()
{
  AgsRavenSynthUtil raven_synth_util = {0,};

  gpointer source;
  
  raven_synth_util.source = NULL;

  source = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_BUFFER_SIZE,
			    AGS_RAVEN_SYNTH_UTIL_TEST_FORMAT);
  
  ags_raven_synth_util_set_source(&raven_synth_util,
				  source);
  
  CU_ASSERT(raven_synth_util.source == source);
}

void
ags_raven_synth_util_test_get_source_stride()
{
  AgsRavenSynthUtil raven_synth_util = {0,};

  raven_synth_util.source_stride = 0;

  CU_ASSERT(ags_raven_synth_util_get_source_stride(&raven_synth_util) == 0);
  
  raven_synth_util.source_stride = 1;

  CU_ASSERT(ags_raven_synth_util_get_source_stride(&raven_synth_util) == raven_synth_util.source_stride);
}

void
ags_raven_synth_util_test_set_source_stride()
{
  AgsRavenSynthUtil raven_synth_util = {0,};
  
  raven_synth_util.source_stride = 0;

  ags_raven_synth_util_set_source_stride(&raven_synth_util,
					 1);
  
  CU_ASSERT(raven_synth_util.source_stride == 1);
}

void
ags_raven_synth_util_test_get_buffer_length()
{
  AgsRavenSynthUtil raven_synth_util = {0,};

  raven_synth_util.buffer_length = 0;

  CU_ASSERT(ags_raven_synth_util_get_buffer_length(&raven_synth_util) == 0);
  
  raven_synth_util.buffer_length = 512;

  CU_ASSERT(ags_raven_synth_util_get_buffer_length(&raven_synth_util) == raven_synth_util.buffer_length);
}

void
ags_raven_synth_util_test_set_buffer_length()
{
  AgsRavenSynthUtil raven_synth_util = {0,};
  
  raven_synth_util.buffer_length = 0;

  ags_raven_synth_util_set_buffer_length(&raven_synth_util,
					 512);
  
  CU_ASSERT(raven_synth_util.buffer_length == 512);
}

void
ags_raven_synth_util_test_get_format()
{
  AgsRavenSynthUtil raven_synth_util = {0,};

  raven_synth_util.format = AGS_SOUNDCARD_SIGNED_16_BIT;

  CU_ASSERT(ags_raven_synth_util_get_format(&raven_synth_util) == AGS_SOUNDCARD_SIGNED_16_BIT);
  
  raven_synth_util.format = AGS_SOUNDCARD_FLOAT;

  CU_ASSERT(ags_raven_synth_util_get_format(&raven_synth_util) == raven_synth_util.format);
}

void
ags_raven_synth_util_test_set_format()
{
  AgsRavenSynthUtil raven_synth_util = {0,};
  
  raven_synth_util.format = AGS_SOUNDCARD_SIGNED_16_BIT;

  ags_raven_synth_util_set_format(&raven_synth_util,
				  AGS_SOUNDCARD_FLOAT);
  
  CU_ASSERT(raven_synth_util.format == AGS_SOUNDCARD_FLOAT);
}

void
ags_raven_synth_util_test_get_samplerate()
{
  AgsRavenSynthUtil raven_synth_util = {0,};

  raven_synth_util.samplerate = 44100;

  CU_ASSERT(ags_raven_synth_util_get_samplerate(&raven_synth_util) == 44100);
  
  raven_synth_util.samplerate = 48000;

  CU_ASSERT(ags_raven_synth_util_get_samplerate(&raven_synth_util) == 48000);
}

void
ags_raven_synth_util_test_set_samplerate()
{
  AgsRavenSynthUtil raven_synth_util = {0,};
  
  raven_synth_util.samplerate = 44100;

  ags_raven_synth_util_set_samplerate(&raven_synth_util,
				      48000);
  
  CU_ASSERT(raven_synth_util.samplerate == 48000);
}

void
ags_raven_synth_util_test_get_synth_oscillator_mode()
{
  AgsRavenSynthUtil raven_synth_util = {0,};

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_SAWTOOTH;

  CU_ASSERT(ags_raven_synth_util_get_synth_oscillator_mode(&raven_synth_util) == AGS_SYNTH_OSCILLATOR_SAWTOOTH);
  
  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_SQUARE;

  CU_ASSERT(ags_raven_synth_util_get_synth_oscillator_mode(&raven_synth_util) == AGS_SYNTH_OSCILLATOR_SQUARE);
}

void
ags_raven_synth_util_test_set_synth_oscillator_mode()
{
  AgsRavenSynthUtil raven_synth_util = {0,};
  
  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_SQUARE;

  ags_raven_synth_util_set_synth_oscillator_mode(&raven_synth_util,
						 AGS_SYNTH_OSCILLATOR_SAWTOOTH);
  
  CU_ASSERT(raven_synth_util.synth_oscillator_mode == AGS_SYNTH_OSCILLATOR_SAWTOOTH);
}

void
ags_raven_synth_util_test_get_frequency()
{
  AgsRavenSynthUtil raven_synth_util = {0,};

  raven_synth_util.frequency = 440.0;

  CU_ASSERT(ags_raven_synth_util_get_frequency(&raven_synth_util) == 440.0);
  
  raven_synth_util.frequency = 220.0;

  CU_ASSERT(ags_raven_synth_util_get_frequency(&raven_synth_util) == 220.0);
}

void
ags_raven_synth_util_test_set_frequency()
{
  AgsRavenSynthUtil raven_synth_util = {0,};
  
  raven_synth_util.frequency = 440.0;

  ags_raven_synth_util_set_frequency(&raven_synth_util,
				     440.0);
  
  CU_ASSERT(raven_synth_util.frequency == 440.0);
}

void
ags_raven_synth_util_test_get_phase()
{
  AgsRavenSynthUtil raven_synth_util = {0,};

  raven_synth_util.phase = 1.0;

  CU_ASSERT(ags_raven_synth_util_get_phase(&raven_synth_util) == 1.0);
  
  raven_synth_util.phase = 0.25;

  CU_ASSERT(ags_raven_synth_util_get_phase(&raven_synth_util) == 0.25);
}

void
ags_raven_synth_util_test_set_phase()
{
  AgsRavenSynthUtil raven_synth_util = {0,};
  
  raven_synth_util.phase = 1.0;

  ags_raven_synth_util_set_phase(&raven_synth_util,
				 0.35);
  
  CU_ASSERT(raven_synth_util.phase == 0.35);
}

void
ags_raven_synth_util_test_get_lfo_oscillator_mode()
{
  //TODO:JK: implement me
}

void
ags_raven_synth_util_test_set_lfo_oscillator_mode()
{
  //TODO:JK: implement me
}

void
ags_raven_synth_util_test_get_lfo_frequency()
{
  //TODO:JK: implement me
}

void
ags_raven_synth_util_test_set_lfo_frequency()
{
  //TODO:JK: implement me
}

void
ags_raven_synth_util_test_get_lfo_depth()
{
  //TODO:JK: implement me
}

void
ags_raven_synth_util_test_set_lfo_depth()
{
  //TODO:JK: implement me
}

void
ags_raven_synth_util_test_get_tuning()
{
  //TODO:JK: implement me
}

void
ags_raven_synth_util_test_set_tuning()
{
  //TODO:JK: implement me
}

void
ags_raven_synth_util_test_get_volume()
{
  //TODO:JK: implement me
}

void
ags_raven_synth_util_test_set_volume()
{
  //TODO:JK: implement me
}

void
ags_raven_synth_util_test_get_frame_count()
{
  //TODO:JK: implement me
}

void
ags_raven_synth_util_test_set_frame_count()
{
  //TODO:JK: implement me
}

void
ags_raven_synth_util_test_get_offset()
{
  //TODO:JK: implement me
}

void
ags_raven_synth_util_test_set_offset()
{
  //TODO:JK: implement me
}

void
ags_raven_synth_util_test_compute_sin_s8()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gint8 *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_SIGNED_8_BIT);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_SIGNED_8_BIT;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_SIN;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_sin_s8(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_SIGNED_8_BIT,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_sin_s16()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gint16 *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_SIGNED_16_BIT);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_SIGNED_16_BIT;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_SIN;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_sin_s16(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_SIGNED_16_BIT,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_sin_s24()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gint32 *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_SIGNED_24_BIT);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_SIGNED_24_BIT;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_SIN;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_sin_s24(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_SIGNED_24_BIT,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_sin_s32()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gint32 *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_SIGNED_32_BIT);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_SIGNED_32_BIT;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_SIN;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_sin_s32(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_SIGNED_32_BIT,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_sin_s64()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gint64 *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_SIGNED_64_BIT);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_SIGNED_64_BIT;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_SIN;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_sin_s64(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_SIGNED_64_BIT,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_sin_float()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gfloat *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_FLOAT);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_FLOAT;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_SIN;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_sin_float(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_FLOAT,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_sin_double()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gdouble *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_DOUBLE);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_DOUBLE;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_SIN;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_sin_double(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_DOUBLE,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_sin_complex()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  AgsComplex *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_COMPLEX);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_COMPLEX;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_SIN;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_sin_complex(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_COMPLEX,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}


void
ags_raven_synth_util_test_compute_sawtooth_s8()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gint8 *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_SIGNED_8_BIT);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_SIGNED_8_BIT;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_SAWTOOTH;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_sawtooth_s8(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_SIGNED_8_BIT,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_sawtooth_s16()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gint16 *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_SIGNED_16_BIT);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_SIGNED_16_BIT;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_SAWTOOTH;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_sawtooth_s16(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_SIGNED_16_BIT,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_sawtooth_s24()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gint32 *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_SIGNED_24_BIT);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_SIGNED_24_BIT;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_SAWTOOTH;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_sawtooth_s24(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_SIGNED_24_BIT,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_sawtooth_s32()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gint32 *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_SIGNED_32_BIT);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_SIGNED_32_BIT;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_SAWTOOTH;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_sawtooth_s32(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_SIGNED_32_BIT,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_sawtooth_s64()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gint64 *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_SIGNED_64_BIT);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_SIGNED_64_BIT;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_SAWTOOTH;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_sawtooth_s64(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_SIGNED_64_BIT,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_sawtooth_float()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gfloat *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_FLOAT);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_FLOAT;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_SAWTOOTH;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_sawtooth_float(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_FLOAT,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_sawtooth_double()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gdouble *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_DOUBLE);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_DOUBLE;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_SAWTOOTH;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_sawtooth_double(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_DOUBLE,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_sawtooth_complex()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  AgsComplex *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_COMPLEX);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_COMPLEX;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_SAWTOOTH;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_sawtooth_complex(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_COMPLEX,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_triangle_s8()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gint8 *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_SIGNED_8_BIT);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_SIGNED_8_BIT;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_TRIANGLE;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_triangle_s8(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_SIGNED_8_BIT,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_triangle_s16()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gint16 *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_SIGNED_16_BIT);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_SIGNED_16_BIT;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_TRIANGLE;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_triangle_s16(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_SIGNED_16_BIT,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_triangle_s24()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gint32 *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_SIGNED_24_BIT);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_SIGNED_24_BIT;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_TRIANGLE;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_triangle_s24(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_SIGNED_24_BIT,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_triangle_s32()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gint32 *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_SIGNED_32_BIT);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_SIGNED_32_BIT;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_TRIANGLE;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_triangle_s32(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_SIGNED_32_BIT,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_triangle_s64()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gint64 *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_SIGNED_64_BIT);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_SIGNED_64_BIT;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_TRIANGLE;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_triangle_s64(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_SIGNED_64_BIT,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_triangle_float()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gfloat *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_FLOAT);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_FLOAT;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_TRIANGLE;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_triangle_float(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_FLOAT,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_triangle_double()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gdouble *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_DOUBLE);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_DOUBLE;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_TRIANGLE;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_triangle_double(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_DOUBLE,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_triangle_complex()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  AgsComplex *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_COMPLEX);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_COMPLEX;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_TRIANGLE;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_triangle_complex(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_COMPLEX,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_square_s8()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gint8 *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_SIGNED_8_BIT);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_SIGNED_8_BIT;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_SQUARE;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_square_s8(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_SIGNED_8_BIT,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_square_s16()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gint16 *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_SIGNED_16_BIT);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_SIGNED_16_BIT;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_SQUARE;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_square_s16(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_SIGNED_16_BIT,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_square_s24()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gint32 *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_SIGNED_24_BIT);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_SIGNED_24_BIT;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_SQUARE;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_square_s24(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_SIGNED_24_BIT,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_square_s32()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gint32 *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_SIGNED_32_BIT);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_SIGNED_32_BIT;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_SQUARE;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_square_s32(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_SIGNED_32_BIT,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_square_s64()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gint64 *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_SIGNED_64_BIT);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_SIGNED_64_BIT;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_SQUARE;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_square_s64(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_SIGNED_64_BIT,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_square_float()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gfloat *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_FLOAT);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_FLOAT;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_SQUARE;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_square_float(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_FLOAT,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_square_double()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gdouble *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_DOUBLE);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_DOUBLE;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_SQUARE;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_square_double(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_DOUBLE,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_square_complex()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  AgsComplex *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_COMPLEX);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_COMPLEX;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_SQUARE;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_square_complex(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_COMPLEX,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_impulse_s8()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gint8 *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_SIGNED_8_BIT);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_SIGNED_8_BIT;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_IMPULSE;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_impulse_s8(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_SIGNED_8_BIT,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_impulse_s16()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gint16 *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_SIGNED_16_BIT);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_SIGNED_16_BIT;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_IMPULSE;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_impulse_s16(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_SIGNED_16_BIT,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_impulse_s24()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gint32 *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_SIGNED_24_BIT);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_SIGNED_24_BIT;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_IMPULSE;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_impulse_s24(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_SIGNED_24_BIT,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_impulse_s32()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gint32 *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_SIGNED_32_BIT);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_SIGNED_32_BIT;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_IMPULSE;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_impulse_s32(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_SIGNED_32_BIT,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_impulse_s64()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gint64 *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_SIGNED_64_BIT);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_SIGNED_64_BIT;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_IMPULSE;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_impulse_s64(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_SIGNED_64_BIT,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_impulse_float()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gfloat *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_FLOAT);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_FLOAT;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_IMPULSE;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_impulse_float(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_FLOAT,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_impulse_double()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  gdouble *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_DOUBLE);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_DOUBLE;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_IMPULSE;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_impulse_double(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_DOUBLE,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

void
ags_raven_synth_util_test_compute_impulse_complex()
{
  AgsRavenSynthUtil raven_synth_util;
  AgsSynthUtil synth_util;
  
  AgsComplex *buffer;

  guint xcross_count;

  raven_synth_util.source =
    buffer = ags_stream_alloc(AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT,
			      AGS_SOUNDCARD_COMPLEX);

  raven_synth_util.source_stride = 1;
  
  raven_synth_util.buffer_length = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  raven_synth_util.format = AGS_SOUNDCARD_COMPLEX;
  raven_synth_util.samplerate = AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE;

  raven_synth_util.synth_oscillator_mode = AGS_SYNTH_OSCILLATOR_IMPULSE;

  raven_synth_util.frequency = AGS_RAVEN_SYNTH_UTIL_TEST_FREQ;
  raven_synth_util.phase = AGS_RAVEN_SYNTH_UTIL_TEST_PHASE;
  raven_synth_util.volume = AGS_RAVEN_SYNTH_UTIL_TEST_VOLUME;

  raven_synth_util.lfo_oscillator_mode = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_OSC_MODE;
  
  raven_synth_util.lfo_frequency = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_FREQ;
  raven_synth_util.lfo_depth = AGS_RAVEN_SYNTH_UTIL_TEST_LFO_DEPTH;
  raven_synth_util.tuning = AGS_RAVEN_SYNTH_UTIL_TEST_TUNING;

  raven_synth_util.offset = 0;
  raven_synth_util.frame_count = AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT;
  
  ags_raven_synth_util_compute_impulse_complex(&raven_synth_util);
  
  xcross_count = ags_synth_util_get_xcross_count(&synth_util,
						 buffer,
						 AGS_SOUNDCARD_COMPLEX,
						 AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT);

  CU_ASSERT(xcross_count + 2 > ((gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_FRAME_COUNT / (gdouble) AGS_RAVEN_SYNTH_UTIL_TEST_SAMPLERATE) * AGS_RAVEN_SYNTH_UTIL_TEST_FREQ);
}

int
main(int argc, char **argv)
{
  CU_pSuite pSuite = NULL;

  /* initialize the CUnit test registry */
  if(CUE_SUCCESS != CU_initialize_registry()){
    return CU_get_error();
  }

  /* add a suite to the registry */
  pSuite = CU_add_suite("AgsRavenSynthUtilTest", ags_raven_synth_util_test_init_suite, ags_raven_synth_util_test_clean_suite);
  
  if(pSuite == NULL){
    CU_cleanup_registry();
    
    return CU_get_error();
  }

  /* add the tests to the suite */
  if((CU_add_test(pSuite, "test of ags_raven_synth_util.c alloc", ags_raven_synth_util_test_alloc) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c copy", ags_raven_synth_util_test_copy) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c free", ags_raven_synth_util_test_free) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c get source", ags_raven_synth_util_test_get_source) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c set source", ags_raven_synth_util_test_set_source) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c get source stride", ags_raven_synth_util_test_get_source_stride) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c set source stride", ags_raven_synth_util_test_set_source_stride) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c get buffer length", ags_raven_synth_util_test_get_buffer_length) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c set buffer length", ags_raven_synth_util_test_set_buffer_length) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c get samplerate", ags_raven_synth_util_test_get_samplerate) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c set samplerate", ags_raven_synth_util_test_set_samplerate) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c get synth oscillator mode", ags_raven_synth_util_test_get_synth_oscillator_mode) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c set synth oscillator mode", ags_raven_synth_util_test_set_synth_oscillator_mode) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c get frequency", ags_raven_synth_util_test_get_frequency) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c set frequency", ags_raven_synth_util_test_set_frequency) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c get phase", ags_raven_synth_util_test_get_phase) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c set phase", ags_raven_synth_util_test_set_phase) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c get volume", ags_raven_synth_util_test_get_volume) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c set volume", ags_raven_synth_util_test_set_volume) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c get lfo oscillator mode", ags_raven_synth_util_test_get_lfo_oscillator_mode) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c set lfo oscillator mode", ags_raven_synth_util_test_set_lfo_oscillator_mode) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c get lfo frequency", ags_raven_synth_util_test_get_lfo_frequency) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c set lfo frequency", ags_raven_synth_util_test_set_lfo_frequency) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c get lfo depth", ags_raven_synth_util_test_get_lfo_depth) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c set lfo depth", ags_raven_synth_util_test_set_lfo_depth) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c get tuning", ags_raven_synth_util_test_get_tuning) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c set tuning", ags_raven_synth_util_test_set_tuning) == NULL) ||     
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c get frame count", ags_raven_synth_util_test_get_frame_count) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c set frame count", ags_raven_synth_util_test_set_frame_count) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c get offset", ags_raven_synth_util_test_get_offset) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c set offset", ags_raven_synth_util_test_set_offset) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute sin s8", ags_raven_synth_util_test_compute_sin_s8) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute sin s16", ags_raven_synth_util_test_compute_sin_s16) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute sin s24", ags_raven_synth_util_test_compute_sin_s24) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute sin s32", ags_raven_synth_util_test_compute_sin_s32) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute sin s64", ags_raven_synth_util_test_compute_sin_s64) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute sin float", ags_raven_synth_util_test_compute_sin_float) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute sin double", ags_raven_synth_util_test_compute_sin_double) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute sin complex", ags_raven_synth_util_test_compute_sin_complex) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute sawtooth s8", ags_raven_synth_util_test_compute_sawtooth_s8) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute sawtooth s16", ags_raven_synth_util_test_compute_sawtooth_s16) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute sawtooth s24", ags_raven_synth_util_test_compute_sawtooth_s24) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute sawtooth s32", ags_raven_synth_util_test_compute_sawtooth_s32) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute sawtooth s64", ags_raven_synth_util_test_compute_sawtooth_s64) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute sawtooth float", ags_raven_synth_util_test_compute_sawtooth_float) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute sawtooth double", ags_raven_synth_util_test_compute_sawtooth_double) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute sawtooth complex", ags_raven_synth_util_test_compute_sawtooth_complex) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute triangle s8", ags_raven_synth_util_test_compute_triangle_s8) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute triangle s16", ags_raven_synth_util_test_compute_triangle_s16) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute triangle s24", ags_raven_synth_util_test_compute_triangle_s24) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute triangle s32", ags_raven_synth_util_test_compute_triangle_s32) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute triangle s64", ags_raven_synth_util_test_compute_triangle_s64) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute triangle float", ags_raven_synth_util_test_compute_triangle_float) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute triangle double", ags_raven_synth_util_test_compute_triangle_double) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute triangle complex", ags_raven_synth_util_test_compute_triangle_complex) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute square s8", ags_raven_synth_util_test_compute_square_s8) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute square s16", ags_raven_synth_util_test_compute_square_s16) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute square s24", ags_raven_synth_util_test_compute_square_s24) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute square s32", ags_raven_synth_util_test_compute_square_s32) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute square s64", ags_raven_synth_util_test_compute_square_s64) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute square float", ags_raven_synth_util_test_compute_square_float) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute square double", ags_raven_synth_util_test_compute_square_double) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute square complex", ags_raven_synth_util_test_compute_square_complex) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute impulse s16", ags_raven_synth_util_test_compute_impulse_s16) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute impulse s24", ags_raven_synth_util_test_compute_impulse_s24) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute impulse s32", ags_raven_synth_util_test_compute_impulse_s32) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute impulse s64", ags_raven_synth_util_test_compute_impulse_s64) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute impulse float", ags_raven_synth_util_test_compute_impulse_float) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute impulse double", ags_raven_synth_util_test_compute_impulse_double) == NULL) ||
     (CU_add_test(pSuite, "test of ags_raven_synth_util.c compute impulse complex", ags_raven_synth_util_test_compute_impulse_complex) == NULL)){
    CU_cleanup_registry();
      
    return CU_get_error();
  }
  
  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  
  CU_cleanup_registry();
  
  return(CU_get_error());
}
