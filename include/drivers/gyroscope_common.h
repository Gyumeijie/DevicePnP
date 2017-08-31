#ifndef GYROSCOPE_COMMON_H
#define GYROSCOPE_COMMON_H


struct gyroscope_device_operation{
  void (*general_gyroscope_open)(void*);
  void (*general_gyroscope_getx)(void*, unsigned int*);
  void (*general_gyroscope_gety)(void*, unsigned int*);
  void (*general_gyroscope_getz)(void*, unsigned int*);
  void (*general_gyroscope_getxyz)(void*, unsigned int*);
};

#endif
