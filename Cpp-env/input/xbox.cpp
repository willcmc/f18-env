#include "xbox.h"

xbox::xbox(){
    this->fd = open ("/dev/input/js0", O_NONBLOCK);
    if(this->fd < 0) printf("cannot open device js0.\n");
    else printf("/dev/input/js0 opened successfully.\n");
}

float xbox::get_input(int axis){
    read(fd, &this->e, sizeof(this->e));
    if (this->e.type == JS_EVENT_AXIS && this->e.number == axis) return e.value/32767.0;
    return 0;
}