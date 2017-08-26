#include "device_register.h"
#include "device.h"
#include "dev_t.h"
#include "init.h"
#include <stdio.h>

int main()
{
    struct device* devp = NULL;
    devno_t devno;
    char* lid;

    init();
    register_devices();
    int device_num = get_device_num();
    int i;

    printf("testing device register\n");
    for (i=0; i<device_num; i++){
        devp = get_device();
        devno = devp->devno;
        printf("lid: %s major: %d minor: %d  interface:%s\n",
                devp->lid, GET_MAJOR(devno), GET_MINOR(devno), devp->interface);
    }


    printf("testing device find: gyroscope1\n");
    devp = find_device("gyroscope1"); 
    if (devp != NULL){
       devno = devp->devno;
       lid = devp->lid;
       printf("lid: %s major: %d minor: %d  interface:%s\n",
                devp->lid, GET_MAJOR(devno), GET_MINOR(devno), devp->interface);
    }


    return 0;
}

