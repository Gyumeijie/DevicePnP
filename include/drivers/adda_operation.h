#ifndef ADDA_OPERATION_H
#define ADDA_OPERATION_H

extern int ad_devices_read(unsigned int data[], unsigned int cnt, 
                           unsigned int channel_num[]);

extern int da_devices_write(unsigned int data[], unsigned int cnt, 
                            unsigned int channel_num[]);

static unsigned int ad_read(unsigned int channel_num);

static int da_write(unsigned int channel_num, unsigned int data);

#endif 
