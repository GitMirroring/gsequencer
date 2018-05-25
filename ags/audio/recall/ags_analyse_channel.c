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

#include <ags/audio/recall/ags_analyse_channel.h>

#include <ags/libags.h>

#include <ags/plugin/ags_base_plugin.h>

#include <ags/audio/ags_audio.h>
#include <ags/audio/ags_output.h>
#include <ags/audio/ags_input.h>

#include <math.h>

#include <ags/i18n.h>

void ags_analyse_channel_class_init(AgsAnalyseChannelClass *analyse_channel);
void ags_analyse_channel_connectable_interface_init(AgsConnectableInterface *connectable);
void ags_analyse_channel_plugin_interface_init(AgsPluginInterface *plugin);
void ags_analyse_channel_init(AgsAnalyseChannel *analyse_channel);
void ags_analyse_channel_set_property(GObject *gobject,
				      guint prop_id,
				      const GValue *value,
				      GParamSpec *param_spec);
void ags_analyse_channel_get_property(GObject *gobject,
				      guint prop_id,
				      GValue *value,
				      GParamSpec *param_spec);
void ags_analyse_channel_connect(AgsConnectable *connectable);
void ags_analyse_channel_disconnect(AgsConnectable *connectable);
void ags_analyse_channel_set_ports(AgsPlugin *plugin, GList *port);
void ags_analyse_channel_dispose(GObject *gobject);
void ags_analyse_channel_finalize(GObject *gobject);

/**
 * SECTION:ags_analyse_channel
 * @short_description: analyses channel
 * @title: AgsAnalyseChannel
 * @section_id:
 * @include: ags/audio/recall/ags_analyse_channel.h
 *
 * The #AgsAnalyseChannel class provides ports to the effect processor.
 */

enum{
  PROP_0,
  PROP_FREQUENCY_BUFFER,
  PROP_MAGNITUDE_BUFFER,
};

static gpointer ags_analyse_channel_parent_class = NULL;
static AgsConnectableInterface *ags_analyse_channel_parent_connectable_interface;
static AgsPluginInterface *ags_analyse_channel_parent_plugin_interface;

static const gchar *ags_analyse_channel_plugin_name = "ags-analyse";
static const gchar *ags_analyse_channel_plugin_specifier[] = {
  "./frequency-buffer[0]",
  "./magnitude-buffer[0]",
};
static const gchar *ags_analyse_channel_plugin_control_port[] = {
  "1/2",
  "2/2",
};

GType
ags_analyse_channel_get_type()
{
  static GType ags_type_analyse_channel = 0;

  if(!ags_type_analyse_channel){
    static const GTypeInfo ags_analyse_channel_info = {
      sizeof (AgsAnalyseChannelClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) ags_analyse_channel_class_init,
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (AgsAnalyseChannel),
      0,    /* n_preallocs */
      (GInstanceInitFunc) ags_analyse_channel_init,
    };

    static const GInterfaceInfo ags_connectable_interface_info = {
      (GInterfaceInitFunc) ags_analyse_channel_connectable_interface_init,
      NULL, /* interface_finalize */
      NULL, /* interface_data */
    };

    static const GInterfaceInfo ags_plugin_interface_info = {
      (GInterfaceInitFunc) ags_analyse_channel_plugin_interface_init,
      NULL, /* interface_finalize */
      NULL, /* interface_data */
    };
    
    ags_type_analyse_channel = g_type_register_static(AGS_TYPE_RECALL_CHANNEL,
						      "AgsAnalyseChannel",
						      &ags_analyse_channel_info,
						      0);

    g_type_add_interface_static(ags_type_analyse_channel,
				AGS_TYPE_CONNECTABLE,
				&ags_connectable_interface_info);

    g_type_add_interface_static(ags_type_analyse_channel,
				AGS_TYPE_PLUGIN,
				&ags_plugin_interface_info);
  }

  return(ags_type_analyse_channel);
}

void
ags_analyse_channel_connectable_interface_init(AgsConnectableInterface *connectable)
{
  ags_analyse_channel_parent_connectable_interface = g_type_interface_peek_parent(connectable);

  connectable->connect = ags_analyse_channel_connect;
  connectable->disconnect = ags_analyse_channel_disconnect;
}

void
ags_analyse_channel_plugin_interface_init(AgsPluginInterface *plugin)
{
  ags_analyse_channel_parent_plugin_interface = g_type_interface_peek_parent(plugin);

  plugin->set_ports = ags_analyse_channel_set_ports;
}

void
ags_analyse_channel_class_init(AgsAnalyseChannelClass *analyse_channel)
{
  GObjectClass *gobject;
  GParamSpec *param_spec;

  ags_analyse_channel_parent_class = g_type_class_peek_parent(analyse_channel);

  /* GObjectClass */
  gobject = (GObjectClass *) analyse_channel;

  gobject->set_property = ags_analyse_channel_set_property;
  gobject->get_property = ags_analyse_channel_get_property;

  gobject->dispose = ags_analyse_channel_dispose;
  gobject->finalize = ags_analyse_channel_finalize;

  /* properties */
  /**
   * AgsAnalyseChannel:frequency-buffer:
   * 
   * The frequency buffer.
   * 
   * Since: 1.5.0
   */
  param_spec = g_param_spec_object("frequency-buffer",
				   i18n_pspec("frequency buffer"),
				   i18n_pspec("The frequency buffer"),
				   AGS_TYPE_PORT,
				   G_PARAM_READABLE | G_PARAM_WRITABLE);
  g_object_class_install_property(gobject,
				  PROP_FREQUENCY_BUFFER,
				  param_spec);

  /**
   * AgsAnalyseChannel:magnitude-buffer:
   * 
   * The magnitude buffer.
   * 
   * Since: 1.5.0
   */
  param_spec = g_param_spec_object("magnitude-buffer",
				   i18n_pspec("magnitude buffer"),
				   i18n_pspec("The magnitude buffer"),
				   AGS_TYPE_PORT,
				   G_PARAM_READABLE | G_PARAM_WRITABLE);
  g_object_class_install_property(gobject,
				  PROP_MAGNITUDE_BUFFER,
				  param_spec);
}

void
ags_analyse_channel_init(AgsAnalyseChannel *analyse_channel)
{
  AgsResetAnalyse *reset_analyse;
  
  AgsConfig *config;
  
  GList *port;

  gchar *str;

  pthread_mutexattr_t *attr;
  
  AGS_RECALL(analyse_channel)->flags |= AGS_RECALL_HAS_OUTPUT_PORT;

  AGS_RECALL(analyse_channel)->name = "ags-analyse";
  AGS_RECALL(analyse_channel)->version = AGS_RECALL_DEFAULT_VERSION;
  AGS_RECALL(analyse_channel)->build_id = AGS_RECALL_DEFAULT_BUILD_ID;
  AGS_RECALL(analyse_channel)->xml_type = "ags-analyse-channel";

  config = ags_config_get_instance();

  /* ports */
  port = NULL;

  /* frequency buffer */
  analyse_channel->frequency_buffer = g_object_new(AGS_TYPE_PORT,
						   "plugin-name", ags_analyse_channel_plugin_name,
						   "specifier", ags_analyse_channel_plugin_specifier[0],
						   "control-port", ags_analyse_channel_plugin_control_port[0],
						   "port-value-is-pointer", TRUE,
						   "port-value-type", G_TYPE_DOUBLE,
						   "port-value-size", sizeof(gdouble),
						   "port-value-length", 1,
						   NULL);
  g_object_ref(analyse_channel->frequency_buffer);
  
  analyse_channel->frequency_buffer->port_value.ags_port_double = 0.0;

  /* add to port */  
  port = g_list_prepend(port, analyse_channel->frequency_buffer);
  g_object_ref(analyse_channel->frequency_buffer);

  /* magnitude buffer */
  analyse_channel->magnitude_buffer = g_object_new(AGS_TYPE_PORT,
						   "plugin-name", ags_analyse_channel_plugin_name,
						   "specifier", ags_analyse_channel_plugin_specifier[1],
						   "control-port", ags_analyse_channel_plugin_control_port[1],
						   "port-value-is-pointer", TRUE,
						   "port-value-type", G_TYPE_DOUBLE,
						   "port-value-size", sizeof(gdouble),
						   "port-value-length", 1,
						   NULL);
  g_object_ref(analyse_channel->magnitude_buffer);
  
  analyse_channel->magnitude_buffer->port_value.ags_port_double = 0.0;

  /* add to port */  
  port = g_list_prepend(port, analyse_channel->magnitude_buffer);
  g_object_ref(analyse_channel->magnitude_buffer);

  /* set port */
  AGS_RECALL(analyse_channel)->port = port;
}

void
ags_analyse_channel_set_property(GObject *gobject,
				 guint prop_id,
				 const GValue *value,
				 GParamSpec *param_spec)
{
  AgsAnalyseChannel *analyse_channel;

  analyse_channel = AGS_ANALYSE_CHANNEL(gobject);

  switch(prop_id){
  case PROP_FREQUENCY_BUFFER:
    {
      AgsPort *port;

      port = (AgsPort *) g_value_get_object(value);

      if(port == analyse_channel->frequency_buffer){
	return;
      }

      if(analyse_channel->frequency_buffer != NULL){
	g_object_unref(G_OBJECT(analyse_channel->frequency_buffer));
      }
      
      if(port != NULL){
	g_object_ref(G_OBJECT(port));
      }

      analyse_channel->frequency_buffer = port;
    }
    break;
  case PROP_MAGNITUDE_BUFFER:
    {
      AgsPort *port;

      port = (AgsPort *) g_value_get_object(value);

      if(port == analyse_channel->magnitude_buffer){
	return;
      }

      if(analyse_channel->magnitude_buffer != NULL){
	g_object_unref(G_OBJECT(analyse_channel->magnitude_buffer));
      }
      
      if(port != NULL){
	g_object_ref(G_OBJECT(port));
      }

      analyse_channel->magnitude_buffer = port;
    }
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(gobject, prop_id, param_spec);
    break;
  }  
}

void
ags_analyse_channel_get_property(GObject *gobject,
				 guint prop_id,
				 GValue *value,
				 GParamSpec *param_spec)
{
  AgsAnalyseChannel *analyse_channel;

  analyse_channel = AGS_ANALYSE_CHANNEL(gobject);

  switch(prop_id){
  case PROP_FREQUENCY_BUFFER:
    {
      g_value_set_object(value, analyse_channel->frequency_buffer);
    }
    break;
  case PROP_MAGNITUDE_BUFFER:
    {
      g_value_set_object(value, analyse_channel->magnitude_buffer);
    }
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(gobject, prop_id, param_spec);
    break;
  }
}

void
ags_analyse_channel_dispose(GObject *gobject)
{
  AgsAnalyseChannel *analyse_channel;

  AgsResetAnalyse *reset_analyse;

  analyse_channel = AGS_ANALYSE_CHANNEL(gobject);

  /* frequency buffer */
  if(analyse_channel->frequency_buffer != NULL){
    g_object_unref(G_OBJECT(analyse_channel->frequency_buffer));

    analyse_channel->frequency_buffer = NULL;
  }

  /* magnitude buffer */
  if(analyse_channel->magnitude_buffer != NULL){
    g_object_unref(G_OBJECT(analyse_channel->magnitude_buffer));

    analyse_channel->magnitude_buffer = NULL;
  }
  
  /* call parent */
  G_OBJECT_CLASS(ags_analyse_channel_parent_class)->dispose(gobject);
}

void
ags_analyse_channel_finalize(GObject *gobject)
{
  AgsAnalyseChannel *analyse_channel;

  AgsResetAnalyse *reset_analyse;

  analyse_channel = AGS_ANALYSE_CHANNEL(gobject);

  /* frequency buffer */
  if(analyse_channel->frequency_buffer != NULL){
    g_object_unref(G_OBJECT(analyse_channel->frequency_buffer));
  }

  /* magnitude buffer */
  if(analyse_channel->magnitude_buffer != NULL){
    g_object_unref(G_OBJECT(analyse_channel->magnitude_buffer));
  }
  
  /* call parent */
  G_OBJECT_CLASS(ags_analyse_channel_parent_class)->finalize(gobject);
}

void
ags_analyse_channel_connect(AgsConnectable *connectable)
{
  if((AGS_RECALL_CONNECTED & (AGS_RECALL(connectable)->flags)) != 0){
    return;
  }

  ags_analyse_channel_parent_connectable_interface->connect(connectable);

  /* empty */
}

void
ags_analyse_channel_disconnect(AgsConnectable *connectable)
{
  ags_analyse_channel_parent_connectable_interface->disconnect(connectable);

  /* empty */
}

void
ags_analyse_channel_set_ports(AgsPlugin *plugin, GList *port)
{
  while(port != NULL){
    if(!strncmp(AGS_PORT(port->data)->specifier,
		"./frequency-buffer[0]",
		22)){
      g_object_set(G_OBJECT(plugin),
		   "frequency-buffer", AGS_PORT(port->data),
		   NULL);
    }else if(!strncmp(AGS_PORT(port->data)->specifier,
		"./magnitude-buffer[0]",
		22)){
      g_object_set(G_OBJECT(plugin),
		   "magnitude-buffer", AGS_PORT(port->data),
		   NULL);
    }

    port = port->next;
  }
}

/**
 * ags_analyse_channel_new:
 * @source: the #AgsChannel as source
 *
 * Creates an #AgsAnalyseChannel
 *
 * Returns: a new #AgsAnalyseChannel
 *
 * Since: 1.5.0
 */
AgsAnalyseChannel*
ags_analyse_channel_new(AgsChannel *source)
{
  AgsAnalyseChannel *analyse_channel;

  analyse_channel = (AgsAnalyseChannel *) g_object_new(AGS_TYPE_ANALYSE_CHANNEL,
						       "channel", source,
						       NULL);

  return(analyse_channel);
}
