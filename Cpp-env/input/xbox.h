#ifndef XBOX_H
#define XBOX_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

struct js_event {
    unsigned int time;      /* event timestamp in milliseconds */
    short value;   /* value */
    unsigned char type;     /* event type */
    unsigned char number;   /* axis/button number */
};

#define JS_EVENT_BUTTON         0x01    /* button pressed/released */
#define JS_EVENT_AXIS           0x02    /* joystick moved */
#define JS_EVENT_INIT           0x80    /* initial state of device */

class xbox{
    private:
        int fd;
        struct js_event e;
    public:
        xbox();
        float get_input(int axis);
};

#endif