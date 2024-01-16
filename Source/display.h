#ifndef DISPLAY
#define DISPLAY

typedef struct
{
    char buffer[80]; //ascii string of data to be displayed
    int displayType; //This lets display task know the requester (temp, light, etc)
} message_t;

void queueMessage(message_t);
void displayTask();
#endif