#ifndef MAGNETORQUER_H
#define MAGNETORQUER_H

#define MAGNETORQUER_GLOBAL_INDEX 0
#define MAGNETORQUER_OPEN_INDEX 1
#define MAGNETORQUER_SETX_INDEX 2
#define MAGNETORQUER_SETY_INDEX 3
#define MAGNETORQUER_SETZ_INDEX 4
#define MAGNETORQUER_SETXYZ_INDEX 5

#define MAGNETORQUER_OP_NUM 5

struct magnetorquer_device_operation{
    int (*general_magnetorquer_open)(void*, void*);
    int (*general_magnetorquer_setx)(void*, void*);
    int (*general_magnetorquer_sety)(void*, void*);
    int (*general_magnetorquer_setz)(void*, void*);
    int (*general_magnetorquer_setxyz)(void*, void*);
};

static int magnetorquer_set_helper(int dev_open_idx, int op_idx, 
                                   const char* func_name, void* data);
extern  int magnetorquer_open(char* lid);
extern  int magnetorquer_setx(int index, void* data);
extern  int magnetorquer_sety(int index, void* data);
extern  int magnetorquer_setz(int index, void* data);
extern  int magnetorquer_setxyz(int index, void* data);

#endif
