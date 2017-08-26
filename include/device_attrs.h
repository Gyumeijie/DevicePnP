#ifndef INTERFACE_REGISTER_H
#define INTERFACE_REGISTER_H

#define NULL ((void*)0)

struct device_attrs{
   char lid[20];
   char type[20];
   char interface[10];
};

static struct device_attrs attrs_items[2] = {
  {"gyroscope1", "gyroscope", "i2c"},
  {"analogsunsensor1", "analogsunsensor","ad"},
#if 0
  {"gyroscope3", "gyroscope", "i2c"},
  {"gyroscope4", "gyroscope", "i2c"},
  {"gyroscope5", "gyroscope", "i2c"},
  {"gyroscope6", "gyroscope", "i2c"},
  {"gyroscope7", "gyroscope", "i2c"},
  {"gyroscope8", "gyroscope", "i2c"},
  {"starsensor1", "starsensor","rs422"},
  {"analogsunsensor1", "analogsunsensor","ad"},
#endif
};

static unsigned int attrs_item_num = 2;

extern unsigned int get_attrs_item_num(void);

extern void* get_device_attrs_item(void);

extern char* get_device_lid(void* attrs);

extern char* get_device_type(void* attrs);

extern char* get_device_interface(void* attrs);

#endif
