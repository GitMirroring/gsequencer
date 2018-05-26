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

#include <ags/X/machine/ags_desk.h>
#include <ags/X/machine/ags_desk_callbacks.h>

#include <ags/libags.h>
#include <ags/libags-audio.h>
#include <ags/libags-gui.h>

void ags_desk_class_init(AgsDeskClass *desk);
void ags_desk_connectable_interface_init(AgsConnectableInterface *connectable);
void ags_desk_plugin_interface_init(AgsPluginInterface *plugin);
void ags_desk_init(AgsDesk *desk);
void ags_desk_finalize(GObject *gobject);

void ags_desk_map_recall(AgsMachine *machine);

void ags_desk_connect(AgsConnectable *connectable);
void ags_desk_disconnect(AgsConnectable *connectable);

gchar* ags_desk_get_name(AgsPlugin *plugin);
void ags_desk_set_name(AgsPlugin *plugin, gchar *name);
gchar* ags_desk_get_xml_type(AgsPlugin *plugin);
void ags_desk_set_xml_type(AgsPlugin *plugin, gchar *xml_type);
void ags_desk_read(AgsFile *file, xmlNode *node, AgsPlugin *plugin);
xmlNode* ags_desk_write(AgsFile *file, xmlNode *parent, AgsPlugin *plugin);

/**
 * SECTION:ags_desk
 * @short_description: desk sequencer
 * @title: AgsDesk
 * @section_id:
 * @include: ags/X/machine/ags_desk.h
 *
 * The #AgsDesk is a composite widget to act as desk sequencer.
 */

static gpointer ags_desk_parent_class = NULL;

static AgsConnectableInterface *ags_desk_parent_connectable_interface;

GType
ags_desk_get_type(void)
{
  static GType ags_type_desk = 0;

  if(!ags_type_desk){
    static const GTypeInfo ags_desk_info = {
      sizeof(AgsDeskClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) ags_desk_class_init,
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof(AgsDesk),
      0,    /* n_preallocs */
      (GInstanceInitFunc) ags_desk_init,
    };

    static const GInterfaceInfo ags_connectable_interface_info = {
      (GInterfaceInitFunc) ags_desk_connectable_interface_init,
      NULL, /* interface_finalize */
      NULL, /* interface_data */
    };

    static const GInterfaceInfo ags_plugin_interface_info = {
      (GInterfaceInitFunc) ags_desk_plugin_interface_init,
      NULL, /* interface_finalize */
      NULL, /* interface_data */
    };

    ags_type_desk = g_type_register_static(AGS_TYPE_MACHINE,
					   "AgsDesk", &ags_desk_info,
					   0);
    
    g_type_add_interface_static(ags_type_desk,
				AGS_TYPE_CONNECTABLE,
				&ags_connectable_interface_info);

    g_type_add_interface_static(ags_type_desk,
				AGS_TYPE_PLUGIN,
				&ags_plugin_interface_info);
  }

  return(ags_type_desk);
}

void
ags_desk_class_init(AgsDeskClass *desk)
{
  GObjectClass *gobject;
  GtkWidgetClass *widget;
  AgsMachineClass *machine;

  ags_desk_parent_class = g_type_class_peek_parent(desk);

  /* GObjectClass */
  gobject = (GObjectClass *) desk;

  gobject->finalize = ags_desk_finalize;

  /* GtkWidget */
  widget = (GtkWidgetClass *) desk;

  widget->show = ags_desk_show;
  widget->show_all = ags_desk_show_all;

  /*  */
  machine = (AgsMachineClass *) desk;

  machine->map_recall = ags_desk_map_recall;
}

void
ags_desk_connectable_interface_init(AgsConnectableInterface *connectable)
{
  ags_desk_parent_connectable_interface = g_type_interface_peek_parent(connectable);

  connectable->connect = ags_desk_connect;
  connectable->disconnect = ags_desk_disconnect;
}

void
ags_desk_plugin_interface_init(AgsPluginInterface *plugin)
{
  plugin->get_name = ags_desk_get_name;
  plugin->set_name = ags_desk_set_name;
  plugin->get_xml_type = ags_desk_get_xml_type;
  plugin->set_xml_type = ags_desk_set_xml_type;
  plugin->read = ags_desk_read;
  plugin->write = ags_desk_write;
}

void
ags_desk_init(AgsDesk *desk)
{
  //TODO:JK: implement me
}

void
ags_desk_finalize(GObject *gobject)
{  
  G_OBJECT_CLASS(ags_desk_parent_class)->finalize(gobject);
}

void
ags_desk_connect(AgsConnectable *connectable)
{
  AgsDesk *desk;

  int i;

  if((AGS_MACHINE_CONNECTED & (AGS_MACHINE(connectable)->flags)) != 0){
    return;
  }

  desk = AGS_DESK(connectable);

  /* call parent */
  ags_desk_parent_connectable_interface->connect(connectable);
}

void
ags_desk_disconnect(AgsConnectable *connectable)
{
  AgsDesk *desk;

  int i;

  if((AGS_MACHINE_CONNECTED & (AGS_MACHINE(connectable)->flags)) == 0){
    return;
  }

  desk = AGS_DESK(connectable);

  /* call parent */
  ags_desk_parent_connectable_interface->disconnect(connectable);
}

void
ags_desk_map_recall(AgsMachine *machine)
{

  /* call parent */
  AGS_MACHINE_CLASS(ags_desk_parent_class)->map_recall(machine);
}

gchar*
ags_desk_get_name(AgsPlugin *plugin)
{
  return(AGS_DESK(plugin)->name);
}

void
ags_desk_set_name(AgsPlugin *plugin, gchar *name)
{
  AGS_DESK(plugin)->name = name;
}

gchar*
ags_desk_get_xml_type(AgsPlugin *plugin)
{
  return(AGS_DESK(plugin)->xml_type);
}

void
ags_desk_set_xml_type(AgsPlugin *plugin, gchar *xml_type)
{
  AGS_DESK(plugin)->xml_type = xml_type;
}

void
ags_desk_read(AgsFile *file, xmlNode *node, AgsPlugin *plugin)
{
  AgsDesk *gobject;

  gobject = AGS_DESK(plugin);

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
ags_desk_write(AgsFile *file, xmlNode *parent, AgsPlugin *plugin)
{
  AgsDesk *desk;
  xmlNode *node;
  GList *list;
  gchar *id;
  guint i;

  desk = AGS_DESK(plugin);

  id = ags_id_generator_create_uuid();
  
  node = xmlNewNode(NULL,
		    "ags-desk");
  xmlNewProp(node,
	     AGS_FILE_ID_PROP,
	     id);

  ags_file_add_id_ref(file,
		      g_object_new(AGS_TYPE_FILE_ID_REF,
				   "application-context", file->application_context,
				   "file", file,
				   "node", node,
				   "xpath", g_strdup_printf("xpath=//*[@id='%s']", id),
				   "reference", desk,
				   NULL));

  return(node);
}

/**
 * ags_desk_new:
 * @soundcard: the assigned soundcard.
 *
 * Creates an #AgsDesk
 *
 * Returns: a new #AgsDesk
 *
 * Since: 1.5.0
 */
AgsDesk*
ags_desk_new(GObject *soundcard)
{
  AgsDesk *desk;

  desk = (AgsDesk *) g_object_new(AGS_TYPE_DESK,
				  NULL);

  g_object_set(G_OBJECT(AGS_MACHINE(desk)->audio),
	       "soundcard", soundcard,
	       NULL);

  return(desk);
}
