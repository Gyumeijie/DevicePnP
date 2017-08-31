#ifndef GYROSCOPE_H
#define GYROSCOPE_H

#define NULL (void*)0

extern int gyroscope_open(char* lid);

extern void gyroscope_getx(int index, unsigned int* data);

#endif
