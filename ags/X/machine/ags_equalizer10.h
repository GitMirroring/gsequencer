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

#ifndef __AGS_EQUALIZER10_H__
#define __AGS_EQUALIZER10_H__

#include <glib.h>
#include <glib-object.h>

#include <gtk/gtk.h>

#include <ags/X/ags_machine.h>

#define AGS_TYPE_EQUALIZER10                (ags_equalizer10_get_type())
#define AGS_EQUALIZER10(obj)                (G_TYPE_CHECK_INSTANCE_CAST((obj), AGS_TYPE_EQUALIZER10, AgsEqualizer10))
#define AGS_EQUALIZER10_CLASS(class)        (G_TYPE_CHECK_CLASS_CAST((class), AGS_TYPE_EQUALIZER10, AgsEqualizer10Class))
#define AGS_IS_EQUALIZER10(obj)             (G_TYPE_CHECK_INSTANCE_TYPE((obj), AGS_TYPE_EQUALIZER10))
#define AGS_IS_EQUALIZER10_CLASS(class)     (G_TYPE_CHECK_CLASS_TYPE ((class), AGS_TYPE_EQUALIZER10))
#define AGS_EQUALIZER10_GET_CLASS(obj)      (G_TYPE_INSTANCE_GET_CLASS (obj, AGS_TYPE_EQUALIZER10, AgsEqualizer10Class))

typedef struct _AgsEqualizer10 AgsEqualizer10;
typedef struct _AgsEqualizer10Class AgsEqualizer10Class;

struct _AgsEqualizer10
{
  AgsMachine machine;

  gchar *name;
  gchar *xml_type;

  GtkScale *peak_28hz;
  GtkScale *peak_56hz;
  GtkScale *peak_112hz;
  GtkScale *peak_224hz;
  GtkScale *peak_448hz;
  GtkScale *peak_896hz;
  GtkScale *peak_1792hz;
  GtkScale *peak_3548hz;
  GtkScale *peak_7168hz;
  GtkScale *peak_14336hz;
  
  GList *peak_28hz_port;
  GList *peak_56hz_port;
  GList *peak_112hz_port;
  GList *peak_224hz_port;
  GList *peak_448hz_port;
  GList *peak_896hz_port;
  GList *peak_1792hz_port;
  GList *peak_3548hz_port;
  GList *peak_7168hz_port;
  GList *peak_14336hz_port;
};

struct _AgsEqualizer10Class
{
  AgsMachineClass machine;
};

GType ags_equalizer10_get_type(void);

AgsEqualizer10* ags_equalizer10_new(GObject *soundcard);

#endif /*__AGS_EQUALIZER10_H__*/
