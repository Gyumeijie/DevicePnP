#include "adda_operation.h"
#include "../data_acquisition/mf624.h"
#include <stdio.h>

static mf624_state_t* mfst = NULL;


/**
 *　输入：接受数据的数组data，设备通道号数量cnt，以及具体的通道号channel_num数组
 *　输出：无
 *　功能：读取指定通道号的数据
 */
int ad_devices_read(unsigned int data[], unsigned int cnt, 
                    unsigned int channel_num[])
{
    mfst = get_mf624_state();

    for (int i=0; i<cnt; i++){
        data[i] = ADC_read(mfst, channel_num[i]);
        printf("channel: %d  data: %d\n", channel_num[i], data[i]);
    }

    return cnt * sizeof(unsigned int);
}



int da_devices_write(unsigned int data[], unsigned int cnt, 
                     unsigned int channel_num[])
{
    mfst = get_mf624_state();

    for (int i=0; i<cnt; i++){
        DAC_write(mfst, channel_num[i], data[i]);
        printf("channel: %d  data: %d\n", channel_num[i], data[i]);
    }

    return cnt * sizeof(unsigned int);
}

