#ifndef FLYWHEEL_H
#define FLYWHEEL_H

#define FLYWHEEL_GLOBAL_INDEX 0
#define FLYWHEEL_OPEN_INDEX 1
#define FLYWHEEL_SET_SPEED_INDEX 2
#define FLYWHEEL_RECEIVE_INDEX 3

#define FLYWHEEL_OP_NUM 3

struct flywheel_device_operation{
    int (*general_flywheel_open)(void*, void*);
    int (*general_flywheel_set_speed)(void*, void*);
    int (*general_flywheel_receive)(void*, void*);
};

extern  int flywheel_open(char* lid);
extern  int flywheel_set_speed(int index, void* para);
extern  int flywheel_receive(int index, void* para);

#endif
