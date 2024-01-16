/*
Thread to take messages from the other modules and display them on the screen or lcd or whatever.
*/

#include "mbed.h"
#include "display.h"
#include "config.h"

static MemoryPool<message_t, 32> mpool;
static Queue<message_t, 32> queue;

void queueMessage(message_t)
{
    message_t *message = mpool.alloc();
    if(message)
    {
        queue.put(message);
    }
}

void displayTask()
{
    while (true)
    {
        osEvent evt = queue.get();

            if(evt.status == osEventMessage)
            {
                message_t *message = (message_t*)evt.value.p;
                printf("%d %s\n",message->displayType, message->buffer);
                mpool.free(message);
            }
    }
}