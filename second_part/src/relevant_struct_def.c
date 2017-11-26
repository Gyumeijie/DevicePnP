#include "relevant_struct_def.h"
void get_current_time(void* time_stamp){
    timeStamp* p_tmp=(timeStamp*)time_stamp;
    time_t t;
    struct tm* lt;
    time(&t);
    lt=localtime(&t);
    p_tmp->year=lt->tm_year+1900;
    p_tmp->month=lt->tm_mon;
    p_tmp->day=lt->tm_mday;
    p_tmp->hour=lt->tm_hour;
    p_tmp->minute=lt->tm_min;
    p_tmp->second=lt->tm_sec;

}
void print_time(void* time_stamp){
    if(time_stamp==NULL)return;
    timeStamp* p_t=(timeStamp*)time_stamp;
    printf("时间戳：%d/%d/%d\n",p_t->hour,p_t->minute,p_t->second);
}
void* get_data_node_array(void){
    UINT size=CACHE_MAX_LEN;
    dataNode* p_data_node_array=(dataNode*)malloc(size*sizeof(dataNode));
    return (void*)p_data_node_array;
}
void free_data_node_array(void* p_data_node_array){
    if(p_data_node_array==NULL)return;
    free(p_data_node_array);
}
void plugin_data_node_array(void* data_node_array,unsigned char* buf,UINT buf_size,UINT* size){
    clear_data_node_array(data_node_array,buf_size);
    time_t t;
    struct tm* lt;
    time(&t);
    lt=localtime(&t);
    int i=0;
    for(;i<buf_size;i++){
        ((dataNode*)data_node_array+i)->dataPiece=buf[i];
        ((dataNode*)data_node_array+i)->time.year=lt->tm_year+1900;
        ((dataNode*)data_node_array+i)->time.month=lt->tm_mon;
        ((dataNode*)data_node_array+i)->time.day=lt->tm_mday;
        ((dataNode*)data_node_array+i)->time.hour=lt->tm_hour;
        ((dataNode*)data_node_array+i)->time.minute=lt->tm_min;
        ((dataNode*)data_node_array+i)->time.second=lt->tm_sec;
    }
    *size=buf_size;
}
void get_array_data_string(void* data_node_array,unsigned char* buf,UINT read_size,UINT* size,void* time){
    int i=0;
    read_size=read_size>CACHE_MAX_LEN?CACHE_MAX_LEN:read_size;
        for(;i<read_size;i++){
            buf[i]=((dataNode*)data_node_array+i)->dataPiece;
            if(i!=0)continue;
            ((timeStamp*)time)->year=((dataNode*)data_node_array+i)->time.year;
            ((timeStamp*)time)->month=((dataNode*)data_node_array+i)->time.month;
            ((timeStamp*)time)->day=((dataNode*)data_node_array+i)->time.day;
            ((timeStamp*)time)->hour=((dataNode*)data_node_array+i)->time.hour;
            ((timeStamp*)time)->minute=((dataNode*)data_node_array+i)->time.minute;
            ((timeStamp*)time)->second=((dataNode*)data_node_array+i)->time.second;
        }
    *size=i;
}
void insert_node_to_data_node_array(void* dest_array,UINT pos,void* src_data_node){
    memcpy(((dataNode*)dest_array)+pos,(dataNode*)src_data_node,sizeof(dataNode));

}
void clear_data_node_array(void* p_data_node_array,UINT array_size){
    memset(p_data_node_array,0,array_size*sizeof(dataNode));
}

void* get_time_node(void){
    void* p_time_node=(void*)(timeStamp*)malloc(sizeof(timeStamp));
    return p_time_node;
}
void free_time_node(void** pp_time_node){
    free(*pp_time_node);
    (*pp_time_node)==NULL;
}
void delay(UINT m_s){
    UINT i=0;
    UINT j=0;
    for(;i<m_s*100000;i++){
        j++;
    }
}
