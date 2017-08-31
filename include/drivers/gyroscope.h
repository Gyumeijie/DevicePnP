#ifndef GYROSCOPE_H
#define GYROSCOPE_H

#define NULL (void*)0

extern int gyroscope_open(char* lid);

extern void gyroscope_getx(int index, unsigned int* data);

extern void gyroscope_gety(int index, unsigned int* data);

extern void gyroscope_getz(int index, unsigned int* data);

extern void gyroscope_getxyz(int index, unsigned int* data);

static void* get_para_struct(int dev_open_idx, int op_idx);
#endif
