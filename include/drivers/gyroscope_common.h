#ifndef GYROSCOPE_COMMON_H
#define GYROSCOPE_COMMON_H


struct gyroscope_device_operation{
  void (*general_gyroscope_open)(void*);
  void (*general_gyroscope_getx)(void*, unsigned int*);
};

#endif
