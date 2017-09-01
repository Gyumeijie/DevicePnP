#include "adda_operation.h"
#include <stdio.h>

/**
 *　输入：接受数据的数组data，设备通道号数量cnt，以及具体的通道号channel_num数组
 *　输出：无
 *　功能：读取指定通道号的数据
 */
int ad_devices_read(unsigned int data[], unsigned int cnt, unsigned int channel_num[])
{
    int i;
    for (i=0; i<cnt; i++){
        data[i] = ad_read(channel_num[i]);
        printf("channel: %d  data: %d\n", channel_num[i], data[i]);
    }

    return cnt * sizeof(unsigned int);
}


//测试用
static unsigned int ad_read(unsigned int channel_num)
{
    static int data[16] = {1, 2 ,3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    
    return data[channel_num];
}
