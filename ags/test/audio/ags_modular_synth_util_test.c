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

#include <string.h>

int ags_modular_synth_util_test_init_suite();
int ags_modular_synth_util_test_clean_suite();

void ags_modular_synth_util_test_alloc();
void ags_modular_synth_util_test_copy();
void ags_modular_synth_util_test_free();
void ags_modular_synth_util_test_get_source();
void ags_modular_synth_util_test_set_source();
void ags_modular_synth_util_test_get_source_stride();
void ags_modular_synth_util_test_set_source_stride();
void ags_modular_synth_util_test_get_buffer_length();
void ags_modular_synth_util_test_set_buffer_length();
void ags_modular_synth_util_test_get_format();
void ags_modular_synth_util_test_set_format();
void ags_modular_synth_util_test_get_samplerate();
void ags_modular_synth_util_test_set_samplerate();
void ags_modular_synth_util_test_get_osc_0_oscillator();
void ags_modular_synth_util_test_set_osc_0_oscillator();
void ags_modular_synth_util_test_get_osc_0_frequency();
void ags_modular_synth_util_test_set_osc_0_frequency();
void ags_modular_synth_util_test_get_osc_0_phase();
void ags_modular_synth_util_test_set_osc_0_phase();
void ags_modular_synth_util_test_get_osc_0_volume();
void ags_modular_synth_util_test_set_osc_0_volume();
void ags_modular_synth_util_test_get_osc_1_oscillator();
void ags_modular_synth_util_test_set_osc_1_oscillator();
void ags_modular_synth_util_test_get_osc_1_frequency();
void ags_modular_synth_util_test_set_osc_1_frequency();
void ags_modular_synth_util_test_get_osc_1_phase();
void ags_modular_synth_util_test_set_osc_1_phase();
void ags_modular_synth_util_test_get_osc_1_volume();
void ags_modular_synth_util_test_set_osc_1_volume();
void ags_modular_synth_util_test_get_pitch_tuning();
void ags_modular_synth_util_test_set_pitch_tuning();
void ags_modular_synth_util_test_get_volume();
void ags_modular_synth_util_test_set_volume();
void ags_modular_synth_util_test_get_env_0_attack();
void ags_modular_synth_util_test_set_env_0_attack();
void ags_modular_synth_util_test_get_env_0_decay();
void ags_modular_synth_util_test_set_env_0_decay();
void ags_modular_synth_util_test_get_env_0_sustain();
void ags_modular_synth_util_test_set_env_0_sustain();
void ags_modular_synth_util_test_get_env_0_release();
void ags_modular_synth_util_test_set_env_0_release();
void ags_modular_synth_util_test_get_env_0_gain();
void ags_modular_synth_util_test_set_env_0_gain();
void ags_modular_synth_util_test_get_env_0_sends();
void ags_modular_synth_util_test_set_env_0_sends();
void ags_modular_synth_util_test_get_env_0_frequency();
void ags_modular_synth_util_test_set_env_0_frequency();
void ags_modular_synth_util_test_get_env_1_attack();
void ags_modular_synth_util_test_set_env_1_attack();
void ags_modular_synth_util_test_get_env_1_decay();
void ags_modular_synth_util_test_set_env_1_decay();
void ags_modular_synth_util_test_get_env_1_sustain();
void ags_modular_synth_util_test_set_env_1_sustain();
void ags_modular_synth_util_test_get_env_1_release();
void ags_modular_synth_util_test_set_env_1_release();
void ags_modular_synth_util_test_get_env_1_gain();
void ags_modular_synth_util_test_set_env_1_gain();
void ags_modular_synth_util_test_get_env_1_frequency();
void ags_modular_synth_util_test_set_env_1_frequency();
void ags_modular_synth_util_test_get_env_1_sends();
void ags_modular_synth_util_test_set_env_1_sends();
void ags_modular_synth_util_test_get_lfo_0_oscillator();
void ags_modular_synth_util_test_set_lfo_0_oscillator();
void ags_modular_synth_util_test_get_lfo_0_frequency();
void ags_modular_synth_util_test_set_lfo_0_frequency();
void ags_modular_synth_util_test_get_lfo_0_depth();
void ags_modular_synth_util_test_set_lfo_0_depth();
void ags_modular_synth_util_test_get_lfo_0_tuning();
void ags_modular_synth_util_test_set_lfo_0_tuning();
void ags_modular_synth_util_test_get_lfo_0_sends();
void ags_modular_synth_util_test_set_lfo_0_sends();
void ags_modular_synth_util_test_get_lfo_1_oscillator();
void ags_modular_synth_util_test_set_lfo_1_oscillator();
void ags_modular_synth_util_test_get_lfo_1_frequency();
void ags_modular_synth_util_test_set_lfo_1_frequency();
void ags_modular_synth_util_test_get_lfo_1_depth();
void ags_modular_synth_util_test_set_lfo_1_depth();
void ags_modular_synth_util_test_get_lfo_1_tuning();
void ags_modular_synth_util_test_set_lfo_1_tuning();
void ags_modular_synth_util_test_get_lfo_1_sends();
void ags_modular_synth_util_test_set_lfo_1_sends();
void ags_modular_synth_util_test_get_noise_frequency();
void ags_modular_synth_util_test_set_noise_frequency();
void ags_modular_synth_util_test_get_noise_gain();
void ags_modular_synth_util_test_set_noise_gain();
void ags_modular_synth_util_test_get_noise_sends();
void ags_modular_synth_util_test_set_noise_sends();
void ags_modular_synth_util_test_compute_s8();
void ags_modular_synth_util_test_compute_s16();
void ags_modular_synth_util_test_compute_s24();
void ags_modular_synth_util_test_compute_s32();
void ags_modular_synth_util_test_compute_s64();
void ags_modular_synth_util_test_compute_float();
void ags_modular_synth_util_test_compute_double();
void ags_modular_synth_util_test_compute_complex();
void ags_modular_synth_util_test_compute();

#define AGS_MODULAR_SYNTH_UTIL_TEST_AUDIO_CHANNELS (1)

#define AGS_MODULAR_SYNTH_UTIL_TEST_BUFFER_SIZE (1024)
#define AGS_MODULAR_SYNTH_UTIL_TEST_FORMAT (AGS_SOUNDCARD_SIGNED_16_BIT)
#define AGS_MODULAR_SYNTH_UTIL_TEST_SAMPLERATE (44100)

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int
ags_modular_synth_util_test_init_suite()
{ 
  return(0);
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int
ags_modular_synth_util_test_clean_suite()
{
  return(0);
}

void
ags_modular_synth_util_test_alloc()
{
  AgsModularSynthUtil *modular_synth_util;

  modular_synth_util = ags_modular_synth_util_alloc();

  CU_ASSERT(modular_synth_util != NULL);

  CU_ASSERT(modular_synth_util->source == NULL);
  CU_ASSERT(modular_synth_util->source_stride == 1);
  
  CU_ASSERT(modular_synth_util->buffer_length == 0);
  CU_ASSERT(modular_synth_util->format == AGS_SOUNDCARD_DEFAULT_FORMAT);
  CU_ASSERT(modular_synth_util->samplerate == AGS_SOUNDCARD_DEFAULT_SAMPLERATE);

  CU_ASSERT(modular_synth_util->volume == 1.0);

  CU_ASSERT(modular_synth_util->pitch_util != NULL);

  CU_ASSERT(modular_synth_util->env_0_util != NULL);
  CU_ASSERT(modular_synth_util->env_1_util != NULL);

  CU_ASSERT(modular_synth_util->lfo_0_util != NULL);
  CU_ASSERT(modular_synth_util->lfo_1_util != NULL);
  
  CU_ASSERT(modular_synth_util->noise_util != NULL);
}

void
ags_modular_synth_util_test_copy()
{
  AgsModularSynthUtil modular_synth_util = {0,};
  AgsModularSynthUtil *copy_modular_synth_util;

  modular_synth_util = AGS_MODULAR_SYNTH_UTIL_INITIALIZER;

  modular_synth_util.source = ags_stream_alloc(AGS_MODULAR_SYNTH_UTIL_TEST_AUDIO_CHANNELS * AGS_MODULAR_SYNTH_UTIL_TEST_BUFFER_SIZE,
					       AGS_MODULAR_SYNTH_UTIL_TEST_FORMAT);
  
  ags_modular_synth_util_set_buffer_length(&modular_synth_util,
					   AGS_MODULAR_SYNTH_UTIL_TEST_BUFFER_SIZE);
  
  copy_modular_synth_util = ags_modular_synth_util_copy(&modular_synth_util);
  
  CU_ASSERT(copy_modular_synth_util != NULL);
    
  CU_ASSERT(copy_modular_synth_util->source == modular_synth_util.source);
  CU_ASSERT(copy_modular_synth_util->source_stride == modular_synth_util.source_stride);
  
  CU_ASSERT(copy_modular_synth_util->buffer_length == modular_synth_util.buffer_length);
  CU_ASSERT(copy_modular_synth_util->format == modular_synth_util.format);
  CU_ASSERT(copy_modular_synth_util->samplerate == modular_synth_util.samplerate);

  CU_ASSERT(copy_modular_synth_util->pitch_tuning == modular_synth_util.pitch_tuning);
  CU_ASSERT(copy_modular_synth_util->volume == modular_synth_util.volume);
}

void
ags_modular_synth_util_test_free()
{
  AgsModularSynthUtil *modular_synth_util;
  
  modular_synth_util = (AgsModularSynthUtil *) g_new(AgsModularSynthUtil,
						     1);

  modular_synth_util[0] = AGS_MODULAR_SYNTH_UTIL_INITIALIZER;
  
  CU_ASSERT(modular_synth_util != NULL);

  modular_synth_util->source = NULL;
  
  ags_modular_synth_util_free(modular_synth_util);
  
  modular_synth_util = ags_modular_synth_util_alloc();

  CU_ASSERT(modular_synth_util != NULL);

  ags_modular_synth_util_free(modular_synth_util);
}

void
ags_modular_synth_util_test_get_source()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.source = NULL;

  CU_ASSERT(ags_modular_synth_util_get_source(&modular_synth_util) == NULL);
  
  modular_synth_util.source = ags_stream_alloc(AGS_MODULAR_SYNTH_UTIL_TEST_BUFFER_SIZE,
					       AGS_MODULAR_SYNTH_UTIL_TEST_FORMAT);

  CU_ASSERT(ags_modular_synth_util_get_source(&modular_synth_util) == modular_synth_util.source);
}

void
ags_modular_synth_util_test_set_source()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  gpointer source;
  
  modular_synth_util.source = NULL;

  source = ags_stream_alloc(AGS_MODULAR_SYNTH_UTIL_TEST_BUFFER_SIZE,
			    AGS_MODULAR_SYNTH_UTIL_TEST_FORMAT);
  
  ags_modular_synth_util_set_source(&modular_synth_util,
				    source);
  
  CU_ASSERT(modular_synth_util.source == source);
}

void
ags_modular_synth_util_test_get_source_stride()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.source_stride = 0;

  CU_ASSERT(ags_modular_synth_util_get_source_stride(&modular_synth_util) == 0);
  
  modular_synth_util.source_stride = 1;

  CU_ASSERT(ags_modular_synth_util_get_source_stride(&modular_synth_util) == modular_synth_util.source_stride);
}

void
ags_modular_synth_util_test_set_source_stride()
{
  AgsModularSynthUtil modular_synth_util = {0,};
  
  modular_synth_util.source_stride = 0;

  ags_modular_synth_util_set_source_stride(&modular_synth_util,
					   1);
  
  CU_ASSERT(modular_synth_util.source_stride == 1);
}

void
ags_modular_synth_util_test_get_buffer_length()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.buffer_length = 0;

  CU_ASSERT(ags_modular_synth_util_get_buffer_length(&modular_synth_util) == 0);
  
  modular_synth_util.buffer_length = 512;

  CU_ASSERT(ags_modular_synth_util_get_buffer_length(&modular_synth_util) == modular_synth_util.buffer_length);
}

void
ags_modular_synth_util_test_set_buffer_length()
{
  AgsModularSynthUtil modular_synth_util = {0,};
  
  modular_synth_util.buffer_length = 0;

  ags_modular_synth_util_set_buffer_length(&modular_synth_util,
					   512);
  
  CU_ASSERT(modular_synth_util.buffer_length == 512);
}

void
ags_modular_synth_util_test_get_format()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.format = AGS_SOUNDCARD_SIGNED_16_BIT;

  CU_ASSERT(ags_modular_synth_util_get_format(&modular_synth_util) == AGS_SOUNDCARD_SIGNED_16_BIT);
  
  modular_synth_util.format = AGS_SOUNDCARD_FLOAT;

  CU_ASSERT(ags_modular_synth_util_get_format(&modular_synth_util) == modular_synth_util.format);
}

void
ags_modular_synth_util_test_set_format()
{
  AgsModularSynthUtil modular_synth_util = {0,};
  
  modular_synth_util.format = AGS_SOUNDCARD_SIGNED_16_BIT;

  ags_modular_synth_util_set_format(&modular_synth_util,
				    AGS_SOUNDCARD_FLOAT);
  
  CU_ASSERT(modular_synth_util.format == AGS_SOUNDCARD_FLOAT);
}

void
ags_modular_synth_util_test_get_samplerate()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.samplerate = 44100;

  CU_ASSERT(ags_modular_synth_util_get_samplerate(&modular_synth_util) == 44100);
  
  modular_synth_util.samplerate = 48000;

  CU_ASSERT(ags_modular_synth_util_get_samplerate(&modular_synth_util) == 48000);
}

void
ags_modular_synth_util_test_set_samplerate()
{
  AgsModularSynthUtil modular_synth_util = {0,};
  
  modular_synth_util.samplerate = 44100;

  ags_modular_synth_util_set_samplerate(&modular_synth_util,
					48000);
  
  CU_ASSERT(modular_synth_util.samplerate == 48000);
}

void
ags_modular_synth_util_test_get_osc_0_oscillator()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.osc_0_oscillator = AGS_SYNTH_OSCILLATOR_SAWTOOTH;

  CU_ASSERT(ags_modular_synth_util_get_osc_0_oscillator(&modular_synth_util) == AGS_SYNTH_OSCILLATOR_SAWTOOTH);
  
  modular_synth_util.osc_0_oscillator = AGS_SYNTH_OSCILLATOR_SQUARE;

  CU_ASSERT(ags_modular_synth_util_get_osc_0_oscillator(&modular_synth_util) == AGS_SYNTH_OSCILLATOR_SQUARE);
}

void
ags_modular_synth_util_test_set_osc_0_oscillator()
{
  AgsModularSynthUtil modular_synth_util = {0,};
  
  modular_synth_util.osc_0_oscillator = AGS_SYNTH_OSCILLATOR_SQUARE;

  ags_modular_synth_util_set_osc_0_oscillator(&modular_synth_util,
					      AGS_SYNTH_OSCILLATOR_SAWTOOTH);
  
  CU_ASSERT(modular_synth_util.osc_0_oscillator == AGS_SYNTH_OSCILLATOR_SAWTOOTH);
}

void
ags_modular_synth_util_test_get_osc_0_frequency()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.osc_0_frequency = 1;

  CU_ASSERT(ags_modular_synth_util_get_osc_0_frequency(&modular_synth_util) == 1.0);
  
  modular_synth_util.osc_0_frequency = 0.25;

  CU_ASSERT(ags_modular_synth_util_get_osc_0_frequency(&modular_synth_util) == 0.25);
}

void
ags_modular_synth_util_test_set_osc_0_frequency()
{
  AgsModularSynthUtil modular_synth_util = {0,};
  
  modular_synth_util.osc_0_frequency = 1.0;

  ags_modular_synth_util_set_osc_0_frequency(&modular_synth_util,
					     0.35);
  
  CU_ASSERT(modular_synth_util.osc_0_frequency == 0.35);
}

void
ags_modular_synth_util_test_get_osc_0_phase()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.osc_0_phase = 1;

  CU_ASSERT(ags_modular_synth_util_get_osc_0_phase(&modular_synth_util) == 1.0);
  
  modular_synth_util.osc_0_phase = 0.25;

  CU_ASSERT(ags_modular_synth_util_get_osc_0_phase(&modular_synth_util) == 0.25);
}

void
ags_modular_synth_util_test_set_osc_0_phase()
{
  AgsModularSynthUtil modular_synth_util = {0,};
  
  modular_synth_util.osc_0_phase = 1.0;

  ags_modular_synth_util_set_osc_0_phase(&modular_synth_util,
					 0.35);
  
  CU_ASSERT(modular_synth_util.osc_0_phase == 0.35);
}

void
ags_modular_synth_util_test_get_osc_0_volume()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.osc_0_volume = 0.5;

  CU_ASSERT(ags_modular_synth_util_get_osc_0_volume(&modular_synth_util) == 0.5);
  
  modular_synth_util.osc_0_volume = 0.25;

  CU_ASSERT(ags_modular_synth_util_get_osc_0_volume(&modular_synth_util) == 0.25);
}

void
ags_modular_synth_util_test_set_osc_0_volume()
{
  AgsModularSynthUtil modular_synth_util = {0,};
  
  modular_synth_util.osc_0_volume = 1.0;

  ags_modular_synth_util_set_osc_0_volume(&modular_synth_util,
					  0.35);
  
  CU_ASSERT(modular_synth_util.osc_0_volume == 0.35);
}

void
ags_modular_synth_util_test_get_osc_1_oscillator()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.osc_1_oscillator = AGS_SYNTH_OSCILLATOR_SAWTOOTH;

  CU_ASSERT(ags_modular_synth_util_get_osc_1_oscillator(&modular_synth_util) == AGS_SYNTH_OSCILLATOR_SAWTOOTH);
  
  modular_synth_util.osc_1_oscillator = AGS_SYNTH_OSCILLATOR_SQUARE;

  CU_ASSERT(ags_modular_synth_util_get_osc_1_oscillator(&modular_synth_util) == AGS_SYNTH_OSCILLATOR_SQUARE);
}

void
ags_modular_synth_util_test_set_osc_1_oscillator()
{
  AgsModularSynthUtil modular_synth_util = {0,};
  
  modular_synth_util.osc_1_oscillator = AGS_SYNTH_OSCILLATOR_SQUARE;

  ags_modular_synth_util_set_osc_1_oscillator(&modular_synth_util,
					      AGS_SYNTH_OSCILLATOR_SAWTOOTH);
  
  CU_ASSERT(modular_synth_util.osc_1_oscillator == AGS_SYNTH_OSCILLATOR_SAWTOOTH);
}

void
ags_modular_synth_util_test_get_osc_1_frequency()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.osc_1_frequency = 1;

  CU_ASSERT(ags_modular_synth_util_get_osc_1_frequency(&modular_synth_util) == 1.0);
  
  modular_synth_util.osc_1_frequency = 0.25;

  CU_ASSERT(ags_modular_synth_util_get_osc_1_frequency(&modular_synth_util) == 0.25);
}

void
ags_modular_synth_util_test_set_osc_1_frequency()
{
  AgsModularSynthUtil modular_synth_util = {0,};
  
  modular_synth_util.osc_1_frequency = 1.0;

  ags_modular_synth_util_set_osc_1_frequency(&modular_synth_util,
					     0.35);
  
  CU_ASSERT(modular_synth_util.osc_1_frequency == 0.35);
}

void
ags_modular_synth_util_test_get_osc_1_phase()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.osc_1_phase = 1;

  CU_ASSERT(ags_modular_synth_util_get_osc_1_phase(&modular_synth_util) == 1.0);
  
  modular_synth_util.osc_1_phase = 0.25;

  CU_ASSERT(ags_modular_synth_util_get_osc_1_phase(&modular_synth_util) == 0.25);
}

void
ags_modular_synth_util_test_set_osc_1_phase()
{
  AgsModularSynthUtil modular_synth_util = {0,};
  
  modular_synth_util.osc_1_phase = 1.0;

  ags_modular_synth_util_set_osc_1_phase(&modular_synth_util,
					 0.35);
  
  CU_ASSERT(modular_synth_util.osc_1_phase == 0.35);
}

void
ags_modular_synth_util_test_get_osc_1_volume()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.osc_1_volume = 0.5;

  CU_ASSERT(ags_modular_synth_util_get_osc_1_volume(&modular_synth_util) == 0.5);
  
  modular_synth_util.osc_1_volume = 0.25;

  CU_ASSERT(ags_modular_synth_util_get_osc_1_volume(&modular_synth_util) == 0.25);
}

void
ags_modular_synth_util_test_set_osc_1_volume()
{
  AgsModularSynthUtil modular_synth_util = {0,};
  
  modular_synth_util.osc_1_volume = 1.0;

  ags_modular_synth_util_set_osc_1_volume(&modular_synth_util,
					  0.35);
  
  CU_ASSERT(modular_synth_util.osc_1_volume == 0.35);
}

void
ags_modular_synth_util_test_get_volume()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.volume = 0.5;

  CU_ASSERT(ags_modular_synth_util_get_volume(&modular_synth_util) == 0.5);
  
  modular_synth_util.volume = 0.25;

  CU_ASSERT(ags_modular_synth_util_get_volume(&modular_synth_util) == 0.25);
}

void
ags_modular_synth_util_test_set_volume()
{
  AgsModularSynthUtil modular_synth_util = {0,};
  
  modular_synth_util.volume = 1.0;

  ags_modular_synth_util_set_volume(&modular_synth_util,
				    0.35);
  
  CU_ASSERT(modular_synth_util.volume == 0.35);
}

void
ags_modular_synth_util_test_get_pitch_tuning()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.pitch_tuning = 1200.0;

  CU_ASSERT(ags_modular_synth_util_get_pitch_tuning(&modular_synth_util) == 1200.0);
  
  modular_synth_util.pitch_tuning = 200.0;

  CU_ASSERT(ags_modular_synth_util_get_pitch_tuning(&modular_synth_util) == 200.0);
}

void
ags_modular_synth_util_test_set_pitch_tuning()
{
  AgsModularSynthUtil modular_synth_util = {0,};
  
  modular_synth_util.pitch_tuning = 0.0;

  ags_modular_synth_util_set_pitch_tuning(&modular_synth_util,
					  200.0);
  
  CU_ASSERT(modular_synth_util.pitch_tuning == 200.0);
}

void
ags_modular_synth_util_test_get_env_0_attack()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.env_0_attack = 0.5;

  CU_ASSERT(ags_modular_synth_util_get_env_0_attack(&modular_synth_util) == 0.5);

  modular_synth_util.env_0_attack = 0.75;

  CU_ASSERT(ags_modular_synth_util_get_env_0_attack(&modular_synth_util) == 0.75);
}

void
ags_modular_synth_util_test_set_env_0_attack()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.env_0_attack = 0.0;

  ags_modular_synth_util_set_env_0_attack(&modular_synth_util,
					  1.0);
  
  CU_ASSERT(modular_synth_util.env_0_attack == 1.0);
}

void
ags_modular_synth_util_test_get_env_0_decay()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.env_0_decay = 0.5;

  CU_ASSERT(ags_modular_synth_util_get_env_0_decay(&modular_synth_util) == 0.5);

  modular_synth_util.env_0_decay = 0.75;

  CU_ASSERT(ags_modular_synth_util_get_env_0_decay(&modular_synth_util) == 0.75);
}

void
ags_modular_synth_util_test_set_env_0_decay()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.env_0_decay = 0.0;

  ags_modular_synth_util_set_env_0_decay(&modular_synth_util,
					 1.0);
  
  CU_ASSERT(modular_synth_util.env_0_decay == 1.0);
}

void
ags_modular_synth_util_test_get_env_0_sustain()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.env_0_sustain = 0.5;

  CU_ASSERT(ags_modular_synth_util_get_env_0_sustain(&modular_synth_util) == 0.5);

  modular_synth_util.env_0_sustain = 0.75;

  CU_ASSERT(ags_modular_synth_util_get_env_0_sustain(&modular_synth_util) == 0.75);
}

void
ags_modular_synth_util_test_set_env_0_sustain()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.env_0_sustain = 0.0;

  ags_modular_synth_util_set_env_0_sustain(&modular_synth_util,
					   1.0);
  
  CU_ASSERT(modular_synth_util.env_0_sustain == 1.0);
}

void
ags_modular_synth_util_test_get_env_0_release()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.env_0_release = 0.5;

  CU_ASSERT(ags_modular_synth_util_get_env_0_release(&modular_synth_util) == 0.5);

  modular_synth_util.env_0_release = 0.75;

  CU_ASSERT(ags_modular_synth_util_get_env_0_release(&modular_synth_util) == 0.75);
}

void
ags_modular_synth_util_test_set_env_0_release()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.env_0_release = 0.0;

  ags_modular_synth_util_set_env_0_release(&modular_synth_util,
					   1.0);
  
  CU_ASSERT(modular_synth_util.env_0_release == 1.0);
}

void
ags_modular_synth_util_test_get_env_0_gain()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.env_0_gain = 0.5;

  CU_ASSERT(ags_modular_synth_util_get_env_0_gain(&modular_synth_util) == 0.5);

  modular_synth_util.env_0_gain = 0.75;

  CU_ASSERT(ags_modular_synth_util_get_env_0_gain(&modular_synth_util) == 0.75);
}

void
ags_modular_synth_util_test_set_env_0_gain()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.env_0_gain = 0.0;

  ags_modular_synth_util_set_env_0_gain(&modular_synth_util,
					1.0);
  
  CU_ASSERT(modular_synth_util.env_0_gain == 1.0);
}

void
ags_modular_synth_util_test_get_env_0_frequency()
{

  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.env_0_frequency = 6.0;

  CU_ASSERT(ags_modular_synth_util_get_env_0_frequency(&modular_synth_util) == 6.0);

  modular_synth_util.env_0_frequency = 8.0;

  CU_ASSERT(ags_modular_synth_util_get_env_0_frequency(&modular_synth_util) == 8.0);
}

void
ags_modular_synth_util_test_set_env_0_frequency()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.env_0_frequency = 0.0;

  ags_modular_synth_util_set_env_0_frequency(&modular_synth_util,
					     6.0);
  
  CU_ASSERT(modular_synth_util.env_0_frequency == 6.0);
}

void
ags_modular_synth_util_test_get_env_0_sends()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  gint64 *env_0_sends;
  gint64 local_env_0_sends[AGS_MODULAR_SYNTH_SENDS_COUNT] = {0,};

  guint env_0_sends_count;

  modular_synth_util.env_0_sends[0] = AGS_MODULAR_SYNTH_SENDS_OSC_0_VOLUME;

  env_0_sends_count = 0;

  env_0_sends = ags_modular_synth_util_get_env_0_sends(&modular_synth_util,
						       &env_0_sends_count);

  CU_ASSERT(env_0_sends_count == AGS_MODULAR_SYNTH_SENDS_COUNT);

  local_env_0_sends[0] = AGS_MODULAR_SYNTH_SENDS_OSC_0_VOLUME;

  CU_ASSERT(memcmp(env_0_sends, local_env_0_sends, AGS_MODULAR_SYNTH_SENDS_COUNT * sizeof(gint64)) == 0);
}

void
ags_modular_synth_util_test_set_env_0_sends()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  gint64 env_0_sends[AGS_MODULAR_SYNTH_SENDS_COUNT] = {0,};

  guint env_0_sends_count;

  env_0_sends[0] = AGS_MODULAR_SYNTH_SENDS_OSC_0_VOLUME;

  env_0_sends_count = 1;

  ags_modular_synth_util_set_env_0_sends(&modular_synth_util,
					 &(env_0_sends[0]),
					 env_0_sends_count);

  CU_ASSERT(memcmp(env_0_sends, modular_synth_util.env_0_sends, AGS_MODULAR_SYNTH_SENDS_COUNT * sizeof(gint64)) == 0);
}

void
ags_modular_synth_util_test_get_env_1_attack()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.env_1_attack = 0.5;

  CU_ASSERT(ags_modular_synth_util_get_env_1_attack(&modular_synth_util) == 0.5);

  modular_synth_util.env_1_attack = 0.75;

  CU_ASSERT(ags_modular_synth_util_get_env_1_attack(&modular_synth_util) == 0.75);
}

void
ags_modular_synth_util_test_set_env_1_attack()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.env_1_attack = 0.0;

  ags_modular_synth_util_set_env_1_attack(&modular_synth_util,
					  1.0);
  
  CU_ASSERT(modular_synth_util.env_1_attack == 1.0);
}

void
ags_modular_synth_util_test_get_env_1_decay()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.env_1_decay = 0.5;

  CU_ASSERT(ags_modular_synth_util_get_env_1_decay(&modular_synth_util) == 0.5);

  modular_synth_util.env_1_decay = 0.75;

  CU_ASSERT(ags_modular_synth_util_get_env_1_decay(&modular_synth_util) == 0.75);
}

void
ags_modular_synth_util_test_set_env_1_decay()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.env_1_decay = 0.0;

  ags_modular_synth_util_set_env_1_decay(&modular_synth_util,
					 1.0);
  
  CU_ASSERT(modular_synth_util.env_1_decay == 1.0);
}

void
ags_modular_synth_util_test_get_env_1_sustain()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.env_1_sustain = 0.5;

  CU_ASSERT(ags_modular_synth_util_get_env_1_sustain(&modular_synth_util) == 0.5);

  modular_synth_util.env_1_sustain = 0.75;

  CU_ASSERT(ags_modular_synth_util_get_env_1_sustain(&modular_synth_util) == 0.75);
}

void
ags_modular_synth_util_test_set_env_1_sustain()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.env_1_sustain = 0.0;

  ags_modular_synth_util_set_env_1_sustain(&modular_synth_util,
					   1.0);
  
  CU_ASSERT(modular_synth_util.env_1_sustain == 1.0);
}

void
ags_modular_synth_util_test_get_env_1_release()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.env_1_release = 0.5;

  CU_ASSERT(ags_modular_synth_util_get_env_1_release(&modular_synth_util) == 0.5);

  modular_synth_util.env_1_release = 0.75;

  CU_ASSERT(ags_modular_synth_util_get_env_1_release(&modular_synth_util) == 0.75);
}

void
ags_modular_synth_util_test_set_env_1_release()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.env_1_release = 0.0;

  ags_modular_synth_util_set_env_1_release(&modular_synth_util,
					   1.0);
  
  CU_ASSERT(modular_synth_util.env_1_release == 1.0);
}

void
ags_modular_synth_util_test_get_env_1_gain()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.env_1_gain = 0.5;

  CU_ASSERT(ags_modular_synth_util_get_env_1_gain(&modular_synth_util) == 0.5);

  modular_synth_util.env_1_gain = 0.75;

  CU_ASSERT(ags_modular_synth_util_get_env_1_gain(&modular_synth_util) == 0.75);
}

void
ags_modular_synth_util_test_set_env_1_gain()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.env_1_gain = 0.0;

  ags_modular_synth_util_set_env_1_gain(&modular_synth_util,
					1.0);
  
  CU_ASSERT(modular_synth_util.env_1_gain == 1.0);
}

void
ags_modular_synth_util_test_get_env_1_frequency()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.env_1_frequency = 6.0;

  CU_ASSERT(ags_modular_synth_util_get_env_1_frequency(&modular_synth_util) == 6.0);

  modular_synth_util.env_1_frequency = 8.0;

  CU_ASSERT(ags_modular_synth_util_get_env_1_frequency(&modular_synth_util) == 8.0);
}

void
ags_modular_synth_util_test_set_env_1_frequency()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.env_1_frequency = 0.0;

  ags_modular_synth_util_set_env_1_frequency(&modular_synth_util,
					     6.0);
  
  CU_ASSERT(modular_synth_util.env_1_frequency == 6.0);
}

void
ags_modular_synth_util_test_get_env_1_sends()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  gint64 *env_1_sends;
  gint64 local_env_1_sends[AGS_MODULAR_SYNTH_SENDS_COUNT] = {0,};

  guint env_1_sends_count;

  modular_synth_util.env_1_sends[0] = AGS_MODULAR_SYNTH_SENDS_OSC_0_VOLUME;

  env_1_sends_count = 0;

  env_1_sends = ags_modular_synth_util_get_env_1_sends(&modular_synth_util,
						       &env_1_sends_count);

  CU_ASSERT(env_1_sends_count == AGS_MODULAR_SYNTH_SENDS_COUNT);

  local_env_1_sends[0] = AGS_MODULAR_SYNTH_SENDS_OSC_0_VOLUME;

  CU_ASSERT(memcmp(env_1_sends, local_env_1_sends, AGS_MODULAR_SYNTH_SENDS_COUNT * sizeof(gint64)) == 0);
}

void
ags_modular_synth_util_test_set_env_1_sends()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  gint64 env_1_sends[AGS_MODULAR_SYNTH_SENDS_COUNT] = {0,};

  guint env_1_sends_count;

  env_1_sends[0] = AGS_MODULAR_SYNTH_SENDS_OSC_0_VOLUME;

  env_1_sends_count = 1;

  ags_modular_synth_util_set_env_1_sends(&modular_synth_util,
					 &(env_1_sends[0]),
					 env_1_sends_count);

  CU_ASSERT(memcmp(env_1_sends, modular_synth_util.env_1_sends, AGS_MODULAR_SYNTH_SENDS_COUNT * sizeof(gint64)) == 0);
}

void
ags_modular_synth_util_test_get_lfo_0_oscillator()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.lfo_0_oscillator = AGS_SYNTH_OSCILLATOR_SIN;

  CU_ASSERT(ags_modular_synth_util_get_lfo_0_oscillator(&modular_synth_util) == AGS_SYNTH_OSCILLATOR_SIN);

  modular_synth_util.lfo_0_oscillator = AGS_SYNTH_OSCILLATOR_SAWTOOTH;

  CU_ASSERT(ags_modular_synth_util_get_lfo_0_oscillator(&modular_synth_util) == AGS_SYNTH_OSCILLATOR_SAWTOOTH);
}

void
ags_modular_synth_util_test_set_lfo_0_oscillator()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.lfo_0_oscillator = AGS_SYNTH_OSCILLATOR_SIN;

  ags_modular_synth_util_set_lfo_0_oscillator(&modular_synth_util,
					      AGS_SYNTH_OSCILLATOR_SAWTOOTH);
  
  CU_ASSERT(modular_synth_util.lfo_0_oscillator == AGS_SYNTH_OSCILLATOR_SAWTOOTH);
}

void
ags_modular_synth_util_test_get_lfo_0_frequency()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.lfo_0_frequency = 6.0;

  CU_ASSERT(ags_modular_synth_util_get_lfo_0_frequency(&modular_synth_util) == 6.0);

  modular_synth_util.lfo_0_frequency = 8.0;

  CU_ASSERT(ags_modular_synth_util_get_lfo_0_frequency(&modular_synth_util) == 8.0);
}

void
ags_modular_synth_util_test_set_lfo_0_frequency()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.lfo_0_frequency = 0.0;

  ags_modular_synth_util_set_lfo_0_frequency(&modular_synth_util,
					     6.0);
  
  CU_ASSERT(modular_synth_util.lfo_0_frequency == 6.0);
}

void
ags_modular_synth_util_test_get_lfo_0_depth()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.lfo_0_depth = 1.0;

  CU_ASSERT(ags_modular_synth_util_get_lfo_0_depth(&modular_synth_util) == 1.0);

  modular_synth_util.lfo_0_depth = 0.25;

  CU_ASSERT(ags_modular_synth_util_get_lfo_0_depth(&modular_synth_util) == 0.25);
}

void
ags_modular_synth_util_test_set_lfo_0_depth()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.lfo_0_depth = 0.0;

  ags_modular_synth_util_set_lfo_0_depth(&modular_synth_util,
					 1.0);
  
  CU_ASSERT(modular_synth_util.lfo_0_depth == 1.0);
}

void
ags_modular_synth_util_test_get_lfo_0_tuning()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.lfo_0_tuning = 1200.0;

  CU_ASSERT(ags_modular_synth_util_get_lfo_0_tuning(&modular_synth_util) == 1200.0);

  modular_synth_util.lfo_0_tuning = 200.0;

  CU_ASSERT(ags_modular_synth_util_get_lfo_0_tuning(&modular_synth_util) == 200.0);
}

void
ags_modular_synth_util_test_set_lfo_0_tuning()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.lfo_0_tuning = 0.0;

  ags_modular_synth_util_set_lfo_0_tuning(&modular_synth_util,
					  200.0);
  
  CU_ASSERT(modular_synth_util.lfo_0_tuning == 200.0);
}

void
ags_modular_synth_util_test_get_lfo_0_sends()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  gint64 *lfo_0_sends;
  gint64 local_lfo_0_sends[AGS_MODULAR_SYNTH_SENDS_COUNT] = {0,};

  guint lfo_0_sends_count;

  modular_synth_util.lfo_0_sends[0] = AGS_MODULAR_SYNTH_SENDS_OSC_0_VOLUME;

  lfo_0_sends_count = 0;

  lfo_0_sends = ags_modular_synth_util_get_lfo_0_sends(&modular_synth_util,
						       &lfo_0_sends_count);

  CU_ASSERT(lfo_0_sends_count == AGS_MODULAR_SYNTH_SENDS_COUNT);

  local_lfo_0_sends[0] = AGS_MODULAR_SYNTH_SENDS_OSC_0_VOLUME;

  CU_ASSERT(memcmp(lfo_0_sends, local_lfo_0_sends, AGS_MODULAR_SYNTH_SENDS_COUNT * sizeof(gint64)) == 0);
}

void
ags_modular_synth_util_test_set_lfo_0_sends()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  gint64 lfo_0_sends[AGS_MODULAR_SYNTH_SENDS_COUNT] = {0,};

  guint lfo_0_sends_count;

  lfo_0_sends[0] = AGS_MODULAR_SYNTH_SENDS_OSC_0_VOLUME;

  lfo_0_sends_count = 1;

  ags_modular_synth_util_set_lfo_0_sends(&modular_synth_util,
					 &(lfo_0_sends[0]),
					 lfo_0_sends_count);

  CU_ASSERT(memcmp(lfo_0_sends, modular_synth_util.lfo_0_sends, AGS_MODULAR_SYNTH_SENDS_COUNT * sizeof(gint64)) == 0);
}

void
ags_modular_synth_util_test_get_lfo_1_oscillator()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.lfo_1_oscillator = AGS_SYNTH_OSCILLATOR_SIN;

  CU_ASSERT(ags_modular_synth_util_get_lfo_1_oscillator(&modular_synth_util) == AGS_SYNTH_OSCILLATOR_SIN);

  modular_synth_util.lfo_1_oscillator = AGS_SYNTH_OSCILLATOR_SAWTOOTH;

  CU_ASSERT(ags_modular_synth_util_get_lfo_1_oscillator(&modular_synth_util) == AGS_SYNTH_OSCILLATOR_SAWTOOTH);
}

void
ags_modular_synth_util_test_set_lfo_1_oscillator()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.lfo_1_oscillator = AGS_SYNTH_OSCILLATOR_SIN;

  ags_modular_synth_util_set_lfo_1_oscillator(&modular_synth_util,
					      AGS_SYNTH_OSCILLATOR_SAWTOOTH);
  
  CU_ASSERT(modular_synth_util.lfo_1_oscillator == AGS_SYNTH_OSCILLATOR_SAWTOOTH);
}

void
ags_modular_synth_util_test_get_lfo_1_frequency()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.lfo_1_frequency = 6.0;

  CU_ASSERT(ags_modular_synth_util_get_lfo_1_frequency(&modular_synth_util) == 6.0);

  modular_synth_util.lfo_1_frequency = 8.0;

  CU_ASSERT(ags_modular_synth_util_get_lfo_1_frequency(&modular_synth_util) == 8.0);
}

void
ags_modular_synth_util_test_set_lfo_1_frequency()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.lfo_1_frequency = 0.0;

  ags_modular_synth_util_set_lfo_1_frequency(&modular_synth_util,
					     6.0);
  
  CU_ASSERT(modular_synth_util.lfo_1_frequency == 6.0);
}

void
ags_modular_synth_util_test_get_lfo_1_depth()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.lfo_1_depth = 1.0;

  CU_ASSERT(ags_modular_synth_util_get_lfo_1_depth(&modular_synth_util) == 1.0);

  modular_synth_util.lfo_1_depth = 0.25;

  CU_ASSERT(ags_modular_synth_util_get_lfo_1_depth(&modular_synth_util) == 0.25);
}

void
ags_modular_synth_util_test_set_lfo_1_depth()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.lfo_1_depth = 0.0;

  ags_modular_synth_util_set_lfo_1_depth(&modular_synth_util,
					 1.0);
  
  CU_ASSERT(modular_synth_util.lfo_1_depth == 1.0);
}

void
ags_modular_synth_util_test_get_lfo_1_tuning()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.lfo_1_tuning = 1200.0;

  CU_ASSERT(ags_modular_synth_util_get_lfo_1_tuning(&modular_synth_util) == 1200.0);

  modular_synth_util.lfo_1_tuning = 200.0;

  CU_ASSERT(ags_modular_synth_util_get_lfo_1_tuning(&modular_synth_util) == 200.0);
}

void
ags_modular_synth_util_test_set_lfo_1_tuning()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.lfo_1_tuning = 0.0;

  ags_modular_synth_util_set_lfo_1_tuning(&modular_synth_util,
					  200.0);
  
  CU_ASSERT(modular_synth_util.lfo_1_tuning == 200.0);
}

void
ags_modular_synth_util_test_get_lfo_1_sends()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  gint64 *lfo_1_sends;
  gint64 local_lfo_1_sends[AGS_MODULAR_SYNTH_SENDS_COUNT] = {0,};

  guint lfo_1_sends_count;

  modular_synth_util.lfo_1_sends[0] = AGS_MODULAR_SYNTH_SENDS_OSC_0_VOLUME;

  lfo_1_sends_count = 0;

  lfo_1_sends = ags_modular_synth_util_get_lfo_1_sends(&modular_synth_util,
						       &lfo_1_sends_count);

  CU_ASSERT(lfo_1_sends_count == AGS_MODULAR_SYNTH_SENDS_COUNT);

  local_lfo_1_sends[0] = AGS_MODULAR_SYNTH_SENDS_OSC_0_VOLUME;

  CU_ASSERT(memcmp(lfo_1_sends, local_lfo_1_sends, AGS_MODULAR_SYNTH_SENDS_COUNT * sizeof(gint64)) == 0);
}

void
ags_modular_synth_util_test_set_lfo_1_sends()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  gint64 lfo_1_sends[AGS_MODULAR_SYNTH_SENDS_COUNT] = {0,};

  guint lfo_1_sends_count;

  lfo_1_sends[0] = AGS_MODULAR_SYNTH_SENDS_OSC_0_VOLUME;

  lfo_1_sends_count = 1;

  ags_modular_synth_util_set_lfo_1_sends(&modular_synth_util,
					 &(lfo_1_sends[0]),
					 lfo_1_sends_count);

  CU_ASSERT(memcmp(lfo_1_sends, modular_synth_util.lfo_1_sends, AGS_MODULAR_SYNTH_SENDS_COUNT * sizeof(gint64)) == 0);
}

void
ags_modular_synth_util_test_get_noise_frequency()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.noise_frequency = 6.0;

  CU_ASSERT(ags_modular_synth_util_get_noise_frequency(&modular_synth_util) == 6.0);

  modular_synth_util.noise_frequency = 8.0;

  CU_ASSERT(ags_modular_synth_util_get_noise_frequency(&modular_synth_util) == 8.0);
}

void
ags_modular_synth_util_test_set_noise_frequency()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.noise_frequency = 0.0;

  ags_modular_synth_util_set_noise_frequency(&modular_synth_util,
					     6.0);
  
  CU_ASSERT(modular_synth_util.noise_frequency == 6.0);
}

void
ags_modular_synth_util_test_get_noise_gain()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.noise_gain = 1.0;

  CU_ASSERT(ags_modular_synth_util_get_noise_gain(&modular_synth_util) == 1.0);

  modular_synth_util.noise_gain = 0.25;

  CU_ASSERT(ags_modular_synth_util_get_noise_gain(&modular_synth_util) == 0.25);
}

void
ags_modular_synth_util_test_set_noise_gain()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  modular_synth_util.noise_gain = 0.0;

  ags_modular_synth_util_set_noise_gain(&modular_synth_util,
					1.0);
  
  CU_ASSERT(modular_synth_util.noise_gain == 1.0);
}

void
ags_modular_synth_util_test_get_noise_sends()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  gint64 *noise_sends;
  gint64 local_noise_sends[AGS_MODULAR_SYNTH_SENDS_COUNT] = {0,};

  guint noise_sends_count;

  modular_synth_util.noise_sends[0] = AGS_MODULAR_SYNTH_SENDS_OSC_0_VOLUME;

  noise_sends_count = 0;

  noise_sends = ags_modular_synth_util_get_noise_sends(&modular_synth_util,
						       &noise_sends_count);

  CU_ASSERT(noise_sends_count == AGS_MODULAR_SYNTH_SENDS_COUNT);

  local_noise_sends[0] = AGS_MODULAR_SYNTH_SENDS_OSC_0_VOLUME;

  CU_ASSERT(memcmp(noise_sends, local_noise_sends, AGS_MODULAR_SYNTH_SENDS_COUNT * sizeof(gint64)) == 0);
}

void
ags_modular_synth_util_test_set_noise_sends()
{
  AgsModularSynthUtil modular_synth_util = {0,};

  gint64 noise_sends[AGS_MODULAR_SYNTH_SENDS_COUNT] = {0,};

  guint noise_sends_count;

  noise_sends[0] = AGS_MODULAR_SYNTH_SENDS_OSC_0_VOLUME;

  noise_sends_count = 1;

  ags_modular_synth_util_set_noise_sends(&modular_synth_util,
					 &(noise_sends[0]),
					 noise_sends_count);

  CU_ASSERT(memcmp(noise_sends, modular_synth_util.noise_sends, AGS_MODULAR_SYNTH_SENDS_COUNT * sizeof(gint64)) == 0);
}

void
ags_modular_synth_util_test_compute_s8()
{
  AgsModularSynthUtil *modular_synth_util;

  gpointer source;

  source = ags_stream_alloc(1024,
			    AGS_SOUNDCARD_SIGNED_8_BIT);

  modular_synth_util = ags_modular_synth_util_alloc();

  modular_synth_util->source = source;

  ags_modular_synth_util_set_buffer_length(modular_synth_util,
					   1024);
  
  modular_synth_util->format = AGS_SOUNDCARD_SIGNED_8_BIT;
  
  modular_synth_util->volume = 0.5;
  
  ags_modular_synth_util_compute_s8(modular_synth_util);
}

void
ags_modular_synth_util_test_compute_s16()
{
  AgsModularSynthUtil *modular_synth_util;

  gpointer source;

  source = ags_stream_alloc(1024,
			    AGS_SOUNDCARD_SIGNED_16_BIT);

  modular_synth_util = ags_modular_synth_util_alloc();

  modular_synth_util->source = source;

  ags_modular_synth_util_set_buffer_length(modular_synth_util,
					   1024);
  
  modular_synth_util->format = AGS_SOUNDCARD_SIGNED_16_BIT;
  
  modular_synth_util->volume = 0.5;
  
  ags_modular_synth_util_compute_s16(modular_synth_util);
}

void
ags_modular_synth_util_test_compute_s24()
{
  AgsModularSynthUtil *modular_synth_util;

  gpointer source;

  source = ags_stream_alloc(1024,
			    AGS_SOUNDCARD_SIGNED_24_BIT);

  modular_synth_util = ags_modular_synth_util_alloc();

  modular_synth_util->source = source;

  ags_modular_synth_util_set_buffer_length(modular_synth_util,
					   1024);
  
  modular_synth_util->format = AGS_SOUNDCARD_SIGNED_24_BIT;
  
  modular_synth_util->volume = 0.5;
  
  ags_modular_synth_util_compute_s24(modular_synth_util);
}

void
ags_modular_synth_util_test_compute_s32()
{
  AgsModularSynthUtil *modular_synth_util;

  gpointer source;

  source = ags_stream_alloc(1024,
			    AGS_SOUNDCARD_SIGNED_32_BIT);

  modular_synth_util = ags_modular_synth_util_alloc();
  modular_synth_util->source = source;

  ags_modular_synth_util_set_buffer_length(modular_synth_util,
					   1024);
  
  modular_synth_util->format = AGS_SOUNDCARD_SIGNED_32_BIT;
  
  modular_synth_util->volume = 0.5;
  
  ags_modular_synth_util_compute_s32(modular_synth_util);
}

void
ags_modular_synth_util_test_compute_s64()
{
  AgsModularSynthUtil *modular_synth_util;

  gpointer source;

  source = ags_stream_alloc(1024,
			    AGS_SOUNDCARD_SIGNED_64_BIT);

  modular_synth_util = ags_modular_synth_util_alloc();

  modular_synth_util->source = source;

  ags_modular_synth_util_set_buffer_length(modular_synth_util,
					   1024);
  
  modular_synth_util->format = AGS_SOUNDCARD_SIGNED_64_BIT;
  
  modular_synth_util->volume = 0.5;
  
  ags_modular_synth_util_compute_s64(modular_synth_util);
}

void
ags_modular_synth_util_test_compute_float()
{
  AgsModularSynthUtil *modular_synth_util;

  gpointer source;

  source = ags_stream_alloc(1024,
			    AGS_SOUNDCARD_FLOAT);

  modular_synth_util = ags_modular_synth_util_alloc();

  modular_synth_util->source = source;

  ags_modular_synth_util_set_buffer_length(modular_synth_util,
					   1024);
  
  modular_synth_util->format = AGS_SOUNDCARD_FLOAT;
  
  modular_synth_util->volume = 0.5;
  
  ags_modular_synth_util_compute_float(modular_synth_util);
}

void
ags_modular_synth_util_test_compute_double()
{
  AgsModularSynthUtil *modular_synth_util;

  gpointer source;

  source = ags_stream_alloc(1024,
			    AGS_SOUNDCARD_DOUBLE);

  modular_synth_util = ags_modular_synth_util_alloc();

  modular_synth_util->source = source;

  ags_modular_synth_util_set_buffer_length(modular_synth_util,
					   1024);
  
  modular_synth_util->format = AGS_SOUNDCARD_DOUBLE;
  
  modular_synth_util->volume = 0.5;
  
  ags_modular_synth_util_compute_double(modular_synth_util);
}

void
ags_modular_synth_util_test_compute_complex()
{
  AgsModularSynthUtil *modular_synth_util;

  gpointer source;

  source = ags_stream_alloc(1024,
			    AGS_SOUNDCARD_COMPLEX);

  modular_synth_util = ags_modular_synth_util_alloc();

  modular_synth_util->source = source;

  ags_modular_synth_util_set_buffer_length(modular_synth_util,
					   1024);
  
  modular_synth_util->format = AGS_SOUNDCARD_COMPLEX;
  
  modular_synth_util->volume = 0.5;

  ags_modular_synth_util_compute_complex(modular_synth_util);
}

void
ags_modular_synth_util_test_compute()
{
  AgsModularSynthUtil *modular_synth_util;

  gpointer source;

  source = ags_stream_alloc(1024,
			    AGS_SOUNDCARD_SIGNED_16_BIT);

  modular_synth_util = ags_modular_synth_util_alloc();

  modular_synth_util->source = source;

  ags_modular_synth_util_set_buffer_length(modular_synth_util,
					   1024);
  
  modular_synth_util->format = AGS_SOUNDCARD_SIGNED_16_BIT;
  
  modular_synth_util->volume = 0.5;
  
  ags_modular_synth_util_compute(modular_synth_util);
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
  pSuite = CU_add_suite("AgsModularSynthUtilTest", ags_modular_synth_util_test_init_suite, ags_modular_synth_util_test_clean_suite);
  
  if(pSuite == NULL){
    CU_cleanup_registry();
    
    return CU_get_error();
  }

  /* add the tests to the suite */
  if((CU_add_test(pSuite, "test of AgsModularSynthUtil alloc", ags_modular_synth_util_test_alloc) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil copy", ags_modular_synth_util_test_copy) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil free", ags_modular_synth_util_test_free) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get source", ags_modular_synth_util_test_get_source) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set source", ags_modular_synth_util_test_set_source) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get source stride", ags_modular_synth_util_test_get_source_stride) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set source stride", ags_modular_synth_util_test_set_source_stride) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get buffer length", ags_modular_synth_util_test_get_buffer_length) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set buffer length", ags_modular_synth_util_test_set_buffer_length) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get format", ags_modular_synth_util_test_get_format) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set format", ags_modular_synth_util_test_set_format) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get samplerate", ags_modular_synth_util_test_get_samplerate) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set samplerate", ags_modular_synth_util_test_set_samplerate) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get osc-0 oscillator", ags_modular_synth_util_test_get_osc_0_oscillator) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set osc-0 oscillator", ags_modular_synth_util_test_set_osc_0_oscillator) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get osc-0 frequency", ags_modular_synth_util_test_get_osc_0_frequency) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set osc-0 frequency", ags_modular_synth_util_test_set_osc_0_frequency) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get osc-0 phase", ags_modular_synth_util_test_get_osc_0_phase) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set osc-0 phase", ags_modular_synth_util_test_set_osc_0_phase) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get osc-0 volume", ags_modular_synth_util_test_get_osc_0_volume) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set osc-0 volume", ags_modular_synth_util_test_set_osc_0_volume) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get osc-1 oscillator", ags_modular_synth_util_test_get_osc_1_oscillator) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set osc-1 oscillator", ags_modular_synth_util_test_set_osc_1_oscillator) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get osc-1 frequency", ags_modular_synth_util_test_get_osc_1_frequency) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set osc-1 frequency", ags_modular_synth_util_test_set_osc_1_frequency) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get osc-1 phase", ags_modular_synth_util_test_get_osc_1_phase) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set osc-1 phase", ags_modular_synth_util_test_set_osc_1_phase) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get osc-1 volume", ags_modular_synth_util_test_get_osc_1_volume) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set osc-1 volume", ags_modular_synth_util_test_set_osc_1_volume) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get pitch tuning", ags_modular_synth_util_test_get_pitch_tuning) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set pitch tuning", ags_modular_synth_util_test_set_pitch_tuning) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get volume", ags_modular_synth_util_test_get_volume) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set volume", ags_modular_synth_util_test_set_volume) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get env-0 attack", ags_modular_synth_util_test_get_env_0_attack) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set env-0 attack", ags_modular_synth_util_test_set_env_0_attack) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get env-0 decay", ags_modular_synth_util_test_get_env_0_decay) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set env-0 decay", ags_modular_synth_util_test_set_env_0_decay) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get env-0 sustain", ags_modular_synth_util_test_get_env_0_sustain) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set env-0 sustain", ags_modular_synth_util_test_set_env_0_sustain) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get env-0 release", ags_modular_synth_util_test_get_env_0_release) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set env-0 release", ags_modular_synth_util_test_set_env_0_release) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get env-0 gain", ags_modular_synth_util_test_get_env_0_gain) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set env-0 gain", ags_modular_synth_util_test_set_env_0_gain) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get env-0 sends", ags_modular_synth_util_test_get_env_0_sends) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set env-0 sends", ags_modular_synth_util_test_set_env_0_sends) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get env-0 frequency", ags_modular_synth_util_test_get_env_0_frequency) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set env-1 frequency", ags_modular_synth_util_test_set_env_1_frequency) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get env-1 attack", ags_modular_synth_util_test_get_env_1_attack) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set env-1 attack", ags_modular_synth_util_test_set_env_1_attack) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get env-1 decay", ags_modular_synth_util_test_get_env_1_decay) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set env-1 decay", ags_modular_synth_util_test_set_env_1_decay) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get env-1 sustain", ags_modular_synth_util_test_get_env_1_sustain) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set env-1 sustain", ags_modular_synth_util_test_set_env_1_sustain) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get env-1 release", ags_modular_synth_util_test_get_env_1_release) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set env-1 release", ags_modular_synth_util_test_set_env_1_release) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get env-1 gain", ags_modular_synth_util_test_get_env_1_gain) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set env-1 gain", ags_modular_synth_util_test_set_env_1_gain) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get env-1 sends", ags_modular_synth_util_test_get_env_1_sends) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set env-1 sends", ags_modular_synth_util_test_set_env_1_sends) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get env-1 frequency", ags_modular_synth_util_test_get_env_1_frequency) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set env-1 frequency", ags_modular_synth_util_test_set_env_1_frequency) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get lfo-0 oscillator", ags_modular_synth_util_test_get_lfo_0_oscillator) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set lfo-0 oscillator", ags_modular_synth_util_test_set_lfo_0_oscillator) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get lfo-0 frequency", ags_modular_synth_util_test_get_lfo_0_frequency) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set lfo-0 frequency", ags_modular_synth_util_test_set_lfo_0_frequency) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get lfo-0 depth", ags_modular_synth_util_test_get_lfo_0_depth) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set lfo-0 depth", ags_modular_synth_util_test_set_lfo_0_depth) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get lfo-0 tuning", ags_modular_synth_util_test_get_lfo_0_tuning) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set lfo-0 tuning", ags_modular_synth_util_test_set_lfo_0_tuning) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get lfo-1 oscillator", ags_modular_synth_util_test_get_lfo_1_oscillator) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set lfo-1 oscillator", ags_modular_synth_util_test_set_lfo_1_oscillator) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get lfo-1 frequency", ags_modular_synth_util_test_get_lfo_1_frequency) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set lfo-1 frequency", ags_modular_synth_util_test_set_lfo_1_frequency) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get lfo-1 depth", ags_modular_synth_util_test_get_lfo_1_depth) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set lfo-1 depth", ags_modular_synth_util_test_set_lfo_1_depth) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get lfo-1 tuning", ags_modular_synth_util_test_get_lfo_1_tuning) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set lfo-1 tuning", ags_modular_synth_util_test_set_lfo_1_tuning) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get noise frequency", ags_modular_synth_util_test_get_noise_frequency) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set noise frequency", ags_modular_synth_util_test_set_noise_frequency) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get noise gain", ags_modular_synth_util_test_get_noise_gain) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set noise gain", ags_modular_synth_util_test_set_noise_gain) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil get noise sends", ags_modular_synth_util_test_get_noise_sends) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil set noise sends", ags_modular_synth_util_test_set_noise_sends) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil compute s8", ags_modular_synth_util_test_compute_s8) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil compute s16", ags_modular_synth_util_test_compute_s16) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil compute s24", ags_modular_synth_util_test_compute_s24) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil compute s32", ags_modular_synth_util_test_compute_s32) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil compute s64", ags_modular_synth_util_test_compute_s64) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil compute float", ags_modular_synth_util_test_compute_float) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil compute double", ags_modular_synth_util_test_compute_double) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil compute complex", ags_modular_synth_util_test_compute_complex) == NULL) ||
     (CU_add_test(pSuite, "test of AgsModularSynthUtil compute", ags_modular_synth_util_test_compute) == NULL)){
    CU_cleanup_registry();
      
    return CU_get_error();
  }
  
  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  
  CU_cleanup_registry();
  
  return(CU_get_error());
}
