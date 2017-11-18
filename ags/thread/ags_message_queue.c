/* GSequencer - Advanced GTK Sequencer
 * Copyright (C) 2005-2017 Joël Krähemann
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

#include <ags/thread/ags_message_queue.h>

#include <ags/object/ags_connectable.h>

void ags_message_queue_class_init(AgsMessageQueueClass *message_queue);
void ags_message_queue_connectable_interface_init(AgsConnectableInterface *connectable);
void ags_message_queue_init(AgsMessageQueue *message_queue);
void ags_message_queue_connect(AgsConnectable *connectable);
void ags_message_queue_disconnect(AgsConnectable *connectable);
void ags_message_queue_dispose(GObject *gobject);
void ags_message_queue_finalize(GObject *gobject);

/**
 * SECTION:ags_message_queue
 * @short_description: message queue
 * @title: AgsMessageQueue
 * @section_id:
 * @include: ags/thread/ags_message_queue.h
 *
 * The #AgsMessageQueue acts as messages passing system.
 */

static gpointer ags_message_queue_parent_class = NULL;
static AgsConnectableInterface *ags_message_queue_parent_connectable_interface;

GType
ags_message_queue_get_type()
{
  static GType ags_type_message_queue = 0;

  if(!ags_type_message_queue){
    static const GTypeInfo ags_message_queue_info = {
      sizeof (AgsMessageQueueClass),
      NULL, /* base_init */
      NULL, /* base_finalize */
      (GClassInitFunc) ags_message_queue_class_init,
      NULL, /* class_finalize */
      NULL, /* class_data */
      sizeof (AgsMessageQueue),
      0,    /* n_preallocs */
      (GInstanceInitFunc) ags_message_queue_init,
    };

    static const GInterfaceInfo ags_connectable_interface_info = {
      (GInterfaceInitFunc) ags_message_queue_connectable_interface_init,
      NULL, /* interface_finalize */
      NULL, /* interface_data */
    };

    ags_type_message_queue = g_type_register_static(AGS_TYPE_THREAD,
						    "AgsMessageQueue",
						    &ags_message_queue_info,
						    0);
    
    g_type_add_interface_static(ags_type_message_queue,
				AGS_TYPE_CONNECTABLE,
				&ags_connectable_interface_info);
  }
  
  return(ags_type_message_queue);
}

void
ags_message_queue_class_init(AgsMessageQueueClass *message_queue)
{
  GObjectClass *gobject;

  ags_message_queue_parent_class = g_type_class_peek_parent(message_queue);

  gobject->dispose = ags_message_queue_dispose;
  gobject->finalize = ags_message_queue_finalize;
}

void
ags_message_queue_connectable_interface_init(AgsConnectableInterface *connectable)
{
  ags_message_queue_parent_connectable_interface = g_type_interface_peek_parent(connectable);

  connectable->connect = ags_message_queue_connect;
  connectable->disconnect = ags_message_queue_disconnect;
}

void
ags_message_queue_init(AgsMessageQueue *message_queue)
{
  message_queue->mutexattr = (pthread_mutexattr_t *) malloc(sizeof(pthread_mutexattr_t));
  pthread_mutexattr_init(message_queue->mutexattr);
  pthread_mutexattr_settype(message_queue->mutexattr,
			    PTHREAD_MUTEX_RECURSIVE);

  message_queue->mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(message_queue->mutex,
		     message_queue->mutexattr);

  message_queue->message = NULL;
}

void
ags_message_queue_connect(AgsConnectable *connectable)
{
  /* empty */

  ags_message_queue_parent_connectable_interface->connect(connectable);
}

void
ags_message_queue_disconnect(AgsConnectable *connectable)
{
  ags_message_queue_parent_connectable_interface->disconnect(connectable);

  /* empty */
}

void
ags_message_queue_dispose(GObject *gobject)
{
  AgsMessageQueue *message_queue;

  message_queue = AGS_MESSAGE_QUEUE(gobject);

  /* call parent */
  G_OBJECT_CLASS(ags_message_queue_parent_class)->dispose(gobject);
}

void
ags_message_queue_finalize(GObject *gobject)
{
  AgsMessageQueue *message_queue;

  message_queue = AGS_MESSAGE_QUEUE(gobject);

  /* call parent */
  G_OBJECT_CLASS(ags_message_queue_parent_class)->finalize(gobject);
}

/**
 * ags_message_envelope_alloc:
 * @sender: the sender as #GObject
 * @recipient: the recipient as #GObject
 * @doc: the message document
 * 
 * Allocate #AgsMessageEnvelope.
 * 
 * Since: 1.1.5
 */
AgsMessageEnvelope*
ags_message_envelope_alloc(GObject *sender,
			   GObject *recipient,
			   xmlDoc *doc)
{
  AgsMessageEnvelope *message;

  message = (AgsMessageEnvelope *) malloc(sizeof(AgsMessageEnvelope));

  message->sender = sender;
  message->recipient = recipient;

  message->doc = doc;

  return(message);
}

/**
 * ags_message_queue_add_message:
 * @message_queue: the #AgsMessageQueue
 * @message: the #AgsMessageEnvelope
 * 
 * Add @message to @message_queue.
 * 
 * Since: 1.1.5
 */
void
ags_message_queue_add_message(AgsMessageQueue *message_queue,
			      gpointer message)
{
  if(!AGS_IS_MESSAGE_QUEUE(message_queue) ||
     message == NULL){
    return;
  }

  pthread_mutex_lock(message_queue->mutex);

  message_queue->message = g_list_prepend(message_queue->message,
					  message);
  
  pthread_mutex_unlock(message_queue->mutex);
}

/**
 * ags_message_queue_remove_message:
 * @message_queue: the #AgsMessageQueue
 * @message: the #AgsMessageEnvelope
 * 
 * Remove @message from @message_queue.
 * 
 * Since: 1.1.5
 */
void
ags_message_queue_remove_message(AgsMessageQueue *message_queue,
				 gpointer message)
{
  if(!AGS_IS_MESSAGE_QUEUE(message_queue) ||
     message == NULL){
    return;
  }


  pthread_mutex_lock(message_queue->mutex);

  message_queue->message = g_list_remove(message_queue->message,
					 message);
  
  pthread_mutex_unlock(message_queue->mutex);
}

GList*
ags_message_queue_find_sender(AgsMessageQueue *message_queue,
			      GObject *sender)
{
  //TODO:JK: implement me
}

GList*
ags_message_queue_find_recipient(AgsMessageQueue *message_queue,
				 GObject *recipient)
{
  //TODO:JK: implement me
}

GList*
ags_message_queue_query(AgsMessageQueue *message_queue,
			gchar *xpath)
{
  //TODO:JK: implement me
}

/**
 * ags_message_queue_new:
 *
 * Create a new #AgsMessageQueue.
 *
 * Returns: the new #AgsMessageQueue
 *
 * Since: 1.1.5
 */ 
AgsMessageQueue*
ags_message_queue_new()
{
  AgsMessageQueue *message_queue;

  message_queue = (AgsMessageQueue *) g_object_new(AGS_TYPE_MESSAGE_QUEUE,
						   NULL);


  return(message_queue);
}
