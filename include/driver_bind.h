#ifndef DRIVER_BIND_H
#define DRIVER_BIND_H

extern int bind_drivers(void);

static void do_bind(struct device* devp, struct driver* drip);

#endif 
