#ifndef DRIVER_LOADERS_H
#define DRIVER_LOADERS_H

#define MAX_DRIVER_LOADER 256
#define NULL  ((void*)0)

typedef void (*driver_loader) (void);

//在这里添加设备驱动加载函数
extern void gyroscope_driver_loader(void);
extern void analogsunsensor_driver_loader(void);
extern void magnetometer_driver_loader(void);
extern void magnetorquer_driver_loader(void);
extern void flywheel_driver_loader(void);

static driver_loader driver_loaders_table[MAX_DRIVER_LOADER] = {
     gyroscope_driver_loader,
     analogsunsensor_driver_loader,
     magnetometer_driver_loader,
     magnetorquer_driver_loader,
     flywheel_driver_loader
};
static unsigned int driver_loader_num = 5;

extern unsigned int get_driver_loader_num(void);

extern driver_loader get_driver_loader(void);

#endif
