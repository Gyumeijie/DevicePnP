#include "device.h"
#include "dev_t.h"
#include "device_register.h"
#include "error_report.h" 
#include "XmlParser.h"
#include <string.h>
#include <malloc.h>
#include <stdio.h>


int register_devices(void)
{
       
       
   int i;
   unsigned int device_num = get_devices_descrip_item_num();
   for (i=0; i<device_num; i++){
      // 获取设备的属性
      void* device_attrs_item = get_devices_descrip_item();
      char* lid = get_device_lid(device_attrs_item);
      char* type = get_device_type(device_attrs_item);
      char* interface = get_device_interface(device_attrs_item);

      // 根据设备类型申请设备号
      devno_t devno = alloc_devno(type);

      // 分配并初始化设备结构体
      struct device* devp = malloc(sizeof(struct device));
      if(! check_null(__FILE__, __func__, "devp", devp)) return FAILURE;

      devp->devno = devno;
      strcpy(devp->interface, interface);
      strcpy(devp->lid, lid);
      strcpy(devp->type, type);
      devp->device_operation = NULL;
      devp->private_data = NULL;

      // 建立设备逻辑标识符与设备结构体的连接
      lid2dev_mapping(lid, devp);
      
      // 注册到设备索引表中
      add_device(GET_MAJOR(devno), devp);
   }

  return SUCCESS;
}

