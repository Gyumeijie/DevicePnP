#ifndef ANALOGSUNSENSOR_H
#define ANALOGSUNSENSOR_H

extern  int analogsunsensor_open(char* lid);
extern  int analogsunsensor_read(int index, unsigned int* data);

#endif
