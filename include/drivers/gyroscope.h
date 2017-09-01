#ifndef GYROSCOPE_H
#define GYROSCOPE_H

#define NULL (void*)0

extern int gyroscope_open(char* lid);

extern int gyroscope_getx(int index, unsigned int* data);

extern int gyroscope_gety(int index, unsigned int* data);

extern int gyroscope_getz(int index, unsigned int* data);

extern int gyroscope_getxyz(int index, unsigned int* data);

static int gyroscope_get_helpler(int dev_open_idx, int op_idx, const char* func_name, unsigned int * data);
#endif
