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

#include <ags/audio/recall/ags_play_wave_channel_run.h>
#include <ags/audio/recall/ags_play_wave_channel.h>

#include <ags/libags.h>

#include <ags/audio/ags_recall_id.h>
#include <ags/audio/ags_recall_container.h>

#include <ags/i18n.h>

void ags_play_wave_channel_run_class_init(AgsPlayWaveChannelRunClass *play_wave_channel_run);
void ags_play_wave_channel_run_connectable_interface_init(AgsConnectableInterface *connectable);
void ags_play_wave_channel_run_dynamic_connectable_interface_init(AgsDynamicConnectableInterface *dynamic_connectable);
void ags_play_wave_channel_run_plugin_interface_init(AgsPluginInterface *plugin);
void ags_play_wave_channel_run_init(AgsPlayWaveChannelRun *play_wave_channel_run);
void ags_play_wave_channel_run_set_property(GObject *gobject,
					    guint prop_id,
					    const GValue *value,
					    GParamSpec *param_spec);
void ags_play_wave_channel_run_get_property(GObject *gobject,
					    guint prop_id,
					    GValue *value,
					    GParamSpec *param_spec);
void ags_play_wave_channel_run_dispose(GObject *gobject);
void ags_play_wave_channel_run_finalize(GObject *gobject);
void ags_play_wave_channel_run_connect(AgsConnectable *connectable);
void ags_play_wave_channel_run_disconnect(AgsConnectable *connectable);
void ags_play_wave_channel_run_read(AgsFile *file, xmlNode *node, AgsPlugin *plugin);
xmlNode* ags_play_wave_channel_run_write(AgsFile *file, xmlNode *parent, AgsPlugin *plugin);

AgsRecall* ags_play_wave_channel_run_duplicate(AgsRecall *recall,
					       AgsRecallID *recall_id,
					       guint *n_params, GParameter *parameter);

/**
 * SECTION:ags_play_wave_channel_run
 * @short_description: play wave
 * @title: AgsPlayWaveChannelRun
 * @section_id:
 * @include: ags/channel/recall/ags_play_wave_channel_run.h
 *
 * The #AgsPlayWaveChannelRun class play wave.
 */

enum{
  PROP_0,
  PROP_DELAY_CHANNEL_RUN,
  PROP_COUNT_BEATS_CHANNEL_RUN,
  PROP_WAVE,
};

static gpointer ags_play_wave_channel_run_parent_class = NULL;
static AgsConnectableInterface* ags_play_wave_channel_run_parent_connectable_interface;
static AgsDynamicConnectableInterface *ags_play_wave_channel_run_parent_dynamic_connectable_interface;
static AgsPluginInterface *ags_play_wave_channel_run_parent_plugin_interface;

GType
ags_play_wave_channel_run_get_type()
{
  static GType ags_type_play_wave_channel_run = 0;

  if(!ags_type_play_wave_channel_run){
    static const GTypeInfo ags_play_wave_channel_run_info = {
      sizeof (AgsPlayWaveChannelRunClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) ags_play_wave_channel_run_class_init,
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (AgsPlayWaveChannelRun),
      0,    /* n_preallocs */
      (GInstanceInitFunc) ags_play_wave_channel_run_init,
    };

    static const GInterfaceInfo ags_connectable_interface_info = {
      (GInterfaceInitFunc) ags_play_wave_channel_run_connectable_interface_init,
      NULL, /* interface_finalize */
      NULL, /* interface_data */
    };

    static const GInterfaceInfo ags_dynamic_connectable_interface_info = {
      (GInterfaceInitFunc) ags_play_wave_channel_run_dynamic_connectable_interface_init,
      NULL, /* interface_finalize */
      NULL, /* interface_data */
    };

    static const GInterfaceInfo ags_plugin_interface_info = {
      (GInterfaceInitFunc) ags_play_wave_channel_run_plugin_interface_init,
      NULL, /* interface_finalize */
      NULL, /* interface_data */
    };

    ags_type_play_wave_channel_run = g_type_register_static(AGS_TYPE_RECALL_CHANNEL_RUN,
							    "AgsPlayWaveChannelRun",
							    &ags_play_wave_channel_run_info,
							    0);

    g_type_add_interface_static(ags_type_play_wave_channel_run,
				AGS_TYPE_CONNECTABLE,
				&ags_connectable_interface_info);

    g_type_add_interface_static(ags_type_play_wave_channel_run,
				AGS_TYPE_DYNAMIC_CONNECTABLE,
				&ags_dynamic_connectable_interface_info);

    g_type_add_interface_static(ags_type_play_wave_channel_run,
				AGS_TYPE_PLUGIN,
				&ags_plugin_interface_info);
  }

  return (ags_type_play_wave_channel_run);
}

void
ags_play_wave_channel_run_class_init(AgsPlayWaveChannelRunClass *play_wave_channel_run)
{
  GObjectClass *gobject;
  AgsRecallClass *recall;
  GParamSpec *param_spec;

  ags_play_wave_channel_run_parent_class = g_type_class_peek_parent(play_wave_channel_run);

  /* GObjectClass */
  gobject = (GObjectClass *) play_wave_channel_run;

  gobject->set_property = ags_play_wave_channel_run_set_property;
  gobject->get_property = ags_play_wave_channel_run_get_property;

  gobject->dispose = ags_play_wave_channel_run_dispose;
  gobject->finalize = ags_play_wave_channel_run_finalize;

  /* properties */
  /**
   * AgsPlayWaveChannelRun:wave:
   *
   * The wave containing the notes.
   * 
   * Since: 1.5.0
   */
  param_spec = g_param_spec_object("wave",
				   i18n_pspec("assigned AgsWave"),
				   i18n_pspec("The AgsWave containing notes"),
				   AGS_TYPE_WAVE,
				   G_PARAM_READABLE | G_PARAM_WRITABLE);
  g_object_class_install_property(gobject,
				  PROP_WAVE,
				  param_spec);

  /* AgsRecallClass */
  recall = (AgsRecallClass *) play_wave_channel_run;

  recall->duplicate = ags_play_wave_channel_run_duplicate;
}

void
ags_play_wave_channel_run_connectable_interface_init(AgsConnectableInterface *connectable)
{
  ags_play_wave_channel_run_parent_connectable_interface = g_type_interface_peek_parent(connectable);

  connectable->connect = ags_play_wave_channel_run_connect;
  connectable->disconnect = ags_play_wave_channel_run_disconnect;
}

void
ags_play_wave_channel_run_dynamic_connectable_interface_init(AgsDynamicConnectableInterface *dynamic_connectable)
{
  ags_play_wave_channel_run_parent_dynamic_connectable_interface = g_type_interface_peek_parent(dynamic_connectable);
}

void
ags_play_wave_channel_run_plugin_interface_init(AgsPluginInterface *plugin)
{
  ags_play_wave_channel_run_parent_plugin_interface = g_type_interface_peek_parent(plugin);
  
  plugin->read = ags_play_wave_channel_run_read;
  plugin->write = ags_play_wave_channel_run_write;
}

void
ags_play_wave_channel_run_init(AgsPlayWaveChannelRun *play_wave_channel_run)
{
  AGS_RECALL(play_wave_channel_run)->name = "ags-play-wave";
  AGS_RECALL(play_wave_channel_run)->version = AGS_RECALL_DEFAULT_VERSION;
  AGS_RECALL(play_wave_channel_run)->build_id = AGS_RECALL_DEFAULT_BUILD_ID;
  AGS_RECALL(play_wave_channel_run)->xml_type = "ags-play-wave-channel-run";
  AGS_RECALL(play_wave_channel_run)->port = NULL;

  play_wave_channel_run->delay_channel_run = NULL;
  play_wave_channel_run->count_beats_channel_run = NULL;

  play_wave_channel_run->wave = NULL;

  play_wave_channel_run->timestamp = ags_timestamp_new();

  play_wave_channel_run->timestamp->flags &= (~AGS_TIMESTAMP_UNIX);
  play_wave_channel_run->timestamp->flags |= AGS_TIMESTAMP_OFFSET;

  play_wave_channel_run->timestamp->timer.ags_offset.offset = 0;
}

void
ags_play_wave_channel_run_set_property(GObject *gobject,
				       guint prop_id,
				       const GValue *value,
				       GParamSpec *param_spec)
{
  AgsPlayWaveChannelRun *play_wave_channel_run;

  play_wave_channel_run = AGS_PLAY_WAVE_CHANNEL_RUN(gobject);

  switch(prop_id){
  case PROP_WAVE:
    {
      AgsWave *wave;

      wave = (AgsWave *) g_value_get_object(value);

      if(play_wave_channel_run->wave == wave){
	return;
      }

      if(play_wave_channel_run->wave != NULL){
	g_object_unref(play_wave_channel_run->wave);
      }

      if(wave != NULL){
	g_object_ref(wave);
      }

      play_wave_channel_run->wave = wave;
    }
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(gobject, prop_id, param_spec);
    break;
  };
}

void
ags_play_wave_channel_run_get_property(GObject *gobject,
				       guint prop_id,
				       GValue *value,
				       GParamSpec *param_spec)
{
  AgsPlayWaveChannelRun *play_wave_channel_run;
  
  play_wave_channel_run = AGS_PLAY_WAVE_CHANNEL_RUN(gobject);

  switch(prop_id){
  case PROP_WAVE:
    {
      g_value_set_object(value, play_wave_channel_run->wave);
    }
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(gobject, prop_id, param_spec);
    break;
  };
}

void
ags_play_wave_channel_run_dispose(GObject *gobject)
{
  AgsPlayWaveChannelRun *play_wave_channel_run;

  play_wave_channel_run = AGS_PLAY_WAVE_CHANNEL_RUN(gobject);

  /* wave */
  if(play_wave_channel_run->wave != NULL){
    g_object_unref(G_OBJECT(play_wave_channel_run->wave));

    play_wave_channel_run->wave = NULL;
  }

  /* call parent */
  G_OBJECT_CLASS(ags_play_wave_channel_run_parent_class)->dispose(gobject);
}

void
ags_play_wave_channel_run_finalize(GObject *gobject)
{
  AgsPlayWaveChannelRun *play_wave_channel_run;

  play_wave_channel_run = AGS_PLAY_WAVE_CHANNEL_RUN(gobject);

  /* wave */
  if(play_wave_channel_run->wave != NULL){
    g_object_unref(G_OBJECT(play_wave_channel_run->wave));
  }

  /* timestamp */
  if(play_wave_channel_run->timestamp != NULL){
    g_object_unref(G_OBJECT(play_wave_channel_run->timestamp));
  }

  /* call parent */
  G_OBJECT_CLASS(ags_play_wave_channel_run_parent_class)->finalize(gobject);
}

void
ags_play_wave_channel_run_connect(AgsConnectable *connectable)
{
  if((AGS_RECALL_CONNECTED & (AGS_RECALL(connectable)->flags)) != 0){
    return;
  }

  /* call parent */
  ags_play_wave_channel_run_parent_connectable_interface->connect(connectable);
}

void
ags_play_wave_channel_run_disconnect(AgsConnectable *connectable)
{
  if((AGS_RECALL_CONNECTED & (AGS_RECALL(connectable)->flags)) == 0){
    return;
  }

  /* call parent */
  ags_play_wave_channel_run_parent_connectable_interface->disconnect(connectable);
}

void
ags_play_wave_channel_run_read(AgsFile *file, xmlNode *node, AgsPlugin *plugin)
{
  AgsFileLookup *file_lookup;

  xmlNode *iter;

  /* read parent */
  ags_play_wave_channel_run_parent_plugin_interface->read(file, node, plugin);

  /* read depenendency */
  iter = node->children;

  while(iter != NULL){
    if(iter->type == XML_ELEMENT_NODE){
      if(!xmlStrncmp(iter->name,
		     "ags-dependency-list",
		     19)){
	xmlNode *dependency_node;

	dependency_node = iter->children;

	while(dependency_node != NULL){
	  if(dependency_node->type == XML_ELEMENT_NODE){
	    if(!xmlStrncmp(dependency_node->name,
			   "ags-dependency",
			   15)){
	      file_lookup = (AgsFileLookup *) g_object_new(AGS_TYPE_FILE_LOOKUP,
							   "file", file,
							   "node", dependency_node,
							   "reference", G_OBJECT(plugin),
							   NULL);
	      ags_file_add_lookup(file, (GObject *) file_lookup);
	      g_signal_connect(G_OBJECT(file_lookup), "resolve",
			       G_CALLBACK(ags_play_wave_channel_run_read_resolve_dependency), G_OBJECT(plugin));
	    }
	  }
	  
	  dependency_node = dependency_node->next;
	}
      }
    }

    iter = iter->next;
  }
}

xmlNode*
ags_play_wave_channel_run_write(AgsFile *file, xmlNode *parent, AgsPlugin *plugin)
{
  AgsFileLookup *file_lookup;

  xmlNode *node, *child;
  xmlNode *dependency_node;
  
  GList *list;

  gchar *id;

  /* write parent */
  node = ags_play_wave_channel_run_parent_plugin_interface->write(file, parent, plugin);

  /* write dependencies */
  child = xmlNewNode(NULL,
		     "ags-dependency-list");

  xmlNewProp(child,
	     AGS_FILE_ID_PROP,
	     ags_id_generator_create_uuid());

  xmlAddChild(node,
	      child);

  list = AGS_RECALL(plugin)->dependencies;

  while(list != NULL){
    id = ags_id_generator_create_uuid();

    dependency_node = xmlNewNode(NULL,
				 "ags-dependency");

    xmlNewProp(dependency_node,
	       AGS_FILE_ID_PROP,
	       id);

    xmlAddChild(child,
		dependency_node);

    file_lookup = (AgsFileLookup *) g_object_new(AGS_TYPE_FILE_LOOKUP,
						 "file", file,
						 "node", dependency_node,
						 "reference", list->data,
						 NULL);
    ags_file_add_lookup(file, (GObject *) file_lookup);
    g_signal_connect(G_OBJECT(file_lookup), "resolve",
		     G_CALLBACK(ags_play_wave_channel_run_write_resolve_dependency), G_OBJECT(plugin));

    list = list->next;
  }

  return(node);
}

AgsRecall*
ags_play_wave_channel_run_duplicate(AgsRecall *recall,
				    AgsRecallID *recall_id,
				    guint *n_params, GParameter *parameter)
{
  AgsPlayWaveChannelRun *copy;

  copy = AGS_PLAY_WAVE_CHANNEL_RUN(AGS_RECALL_CLASS(ags_play_wave_channel_run_parent_class)->duplicate(recall,
												       recall_id,
												       n_params, parameter));

  return((AgsRecall *) copy);
}

/**
 * ags_play_wave_channel_run_new:
 *
 * Creates an #AgsPlayWaveChannelRun
 *
 * Returns: a new #AgsPlayWaveChannelRun
 *
 * Since: 1.5.0
 */
AgsPlayWaveChannelRun*
ags_play_wave_channel_run_new()
{
  AgsPlayWaveChannelRun *play_wave_channel_run;

  play_wave_channel_run = (AgsPlayWaveChannelRun *) g_object_new(AGS_TYPE_PLAY_WAVE_CHANNEL_RUN,
								 NULL);

  return(play_wave_channel_run);
}
