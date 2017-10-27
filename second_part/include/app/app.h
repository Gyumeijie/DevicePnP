#ifndef APP_H
#define APP_H
#include "control_data_stream.h"
void* app_read_pthread_func(void* argc);
void* app_write_pthread_func(void* argc);
#endif
