#include "package.h"
///负责打包解包
void unpack_package_to_1553(UINT traffic_repos_id,unsigned char* buffer,UINT buf_size,char* bus_type,char* bus_lid,char* RT_lid){
    //printf("ret_size:%d 打包发回的数据为:%s\n",buf_size,buffer);
    UINT cur_prio=0;
    UINT buffer_pos=0;
    UINT block_size=0;
    UINT size=0;
    UINT prev_priority=MAX_PRIORITY;
    UINT anchor=0;
    //处理数据
    if(buf_size<=0)return;
    if(is_RT_section_writeable(traffic_repos_id)==false) return;//抛出异常
    char* dev_lid=get_priority_deterio_dev_lid(bus_type,bus_lid,RT_lid,SEND_PRIORITY_FLAG,prev_priority,&cur_prio,&anchor);
    prev_priority=cur_prio;
    while(strcmp(dev_lid,"")!=0){
        UINT is_valid=*(buffer+buffer_pos)/DATA_BLOCK_VALID_PREFIX;
        if(is_valid==1){
            block_size=*(buffer+buffer_pos)%DATA_BLOCK_VALID_PREFIX;
            //printf("block_size:%d\n",block_size);
            buffer_pos++;
            ctrl_dev_write_data(traffic_repos_id,dev_lid,buffer+buffer_pos,block_size,&size);
            //printf("size:%d,buf:%s\n",size,buffer+buffer_pos);
            if(size!=block_size){
                printf("write err!");
                return;
            }
            buffer_pos+=block_size;
        }
        else{
            buffer_pos++;
        }
        dev_lid=get_priority_deterio_dev_lid(bus_type,bus_lid,RT_lid,SEND_PRIORITY_FLAG,prev_priority,&cur_prio,&anchor);
        prev_priority=cur_prio;
    }
    if(buf_size!=buffer_pos)printf("unpack to 1553有数据丢失\n");
}
void pack_package_to_1553(UINT traffic_repos_id,UINT light_pos,char* bus_type,char* bus_lid,char* RT_lid,unsigned char* buffer_1553,UINT* buffer_size){
    UINT cur_prio=0;
    UINT block_size=0;
    UINT size=0;
    UINT buffer_pos=0;
    UINT prev_priority=MAX_PRIORITY;
    UINT anchor=0;
    bool is_send_valid=false;
    unsigned char read_buffer[READ_BUFFER_MAX_SIZE]={0};
    unsigned char buffer_tmp[READ_BUFFER_MAX_SIZE]={0};
    char* dev_lid=get_priority_deterio_dev_lid(bus_type,bus_lid,RT_lid,RECEIVE_PRIORITY_FLAG,prev_priority,&cur_prio,&anchor);
    prev_priority=cur_prio;
    if(strcmp(dev_lid,"")==0){
        *buffer_size=0;
        return;
    }
    while(strcmp(dev_lid,"")!=0){
        block_size=get_dev_trans_attr(bus_type,bus_lid,RT_lid,dev_lid,RECEIVE_BLOCK_FLAG);
        void* p_time_node=get_time_node();
        ctrl_dev_read_data(traffic_repos_id,dev_lid,read_buffer,block_size,&size,p_time_node);
        int j=0;
        //printf("dev_lid:%s size:%d\n",dev_lid,size);
        //for(;j<size;j++){
        //    printf("dev_lid:%s--%d ",dev_lid,read_buffer[j]);
        //}
        //printf("%d -- %s\n",size,read_buffer);
        //比较时间是否超时，若超时抛出异常
        if(size!=0&&block_size!=size){//抛出异常,应用层应该以一个block的大小发送指令/数据
            void* p_route=get_route_node();
            get_dev_route_map(dev_lid,&p_route);
            char* RT_lid=get_route_RT_lid(p_route);
            throw_event(0,RT_lid,EVT_APP_DATA_SIZE_ERR);
            free_route_node(&p_route);
        }
        if(size==0){
            *(buffer_tmp+buffer_pos)|=DATA_BLOCK_VALID_PREFIX;
            buffer_pos++;
        }
        else{
            is_send_valid=true;
            *(buffer_tmp+buffer_pos)=size;
            *(buffer_tmp+buffer_pos)|=DATA_BLOCK_VALID_PREFIX;
            buffer_pos++;
            //printf("size:%d pos:%d\n",size,buffer_pos);
            memcpy(buffer_tmp+buffer_pos,read_buffer,size);
            buffer_pos=buffer_pos+size;
            memset(read_buffer,0,READ_BUFFER_MAX_SIZE);
        }
        dev_lid=get_priority_deterio_dev_lid(bus_type,bus_lid,RT_lid,RECEIVE_PRIORITY_FLAG,prev_priority,&cur_prio,&anchor);
        prev_priority=cur_prio;
        free_time_node(&p_time_node);
    }
    if(is_send_valid==true){
        *buffer_size=buffer_pos;
        buffer_tmp[buffer_pos]='\0';
        strcpy(buffer_1553,buffer_tmp);
        //int i=0;
        //for(;i<*buffer_size;i++){
        //    printf("-%x",buffer_tmp[i]);
        //}
    }
    else{
        *buffer_size=0;
    }
}
