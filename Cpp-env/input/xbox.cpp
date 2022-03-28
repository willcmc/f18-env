#include "xbox.h"

xbox::xbox(){
    this->fd = open ("/dev/input/js0", O_NONBLOCK);
    if(this->fd < 0) printf("cannot open device js0.\n");
    else printf("/dev/input/js0 opened successfully.\n");
    for(int i = 0; i < 10; i++)
        this->last.push_back(0.0);
}

float xbox::get_input(int axis){
    read(this->fd, &this->e, sizeof(this->e));
    if (this->e.type == JS_EVENT_AXIS && this->e.number == axis) {
        this->last[axis] = e.value/32767.0;
        std::cout << "Axis " << axis << ": " << e.value << "\n";
        return this->last[axis];
    }
    return this->last[axis]; //(std::abs(this->last[axis]) <= 1)? this->last[axis] : 0;
}

void xbox::update(double* cntl){

    float js_pitch =  xbox::get_input(4); // pull back is +ve
    float js_roll =  xbox::get_input(3); // 

    cntl[0] = -js_pitch*0.4 - 0.1 - js_roll*0.2;
    cntl[1] = -js_pitch*0.4 - 0.1 + js_roll*0.2;
    cntl[2] = js_roll*0.4;
}