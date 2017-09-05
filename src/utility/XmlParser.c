//
#include <stdio.h>
#include <stdlib.h>
#include "XmlParser.h"
#define ROUTE_MAX_LEN 5
#define ROUTE_VALUE_MAX_LEN 10
#define CONTENT_MAX_LEN 30
#define ROUTE_IO_NAME_POS 0
#define ROUTE_IO_LID_VALUE 1
#define ROUTE_CHANNEL_NAME_POS 2
#define ROUTE_CHANNEL_LID_VALUE_POS 3
#define DESCRIPTION_ITEM_MAX_LEN 20
#define TAG_NAME_MAX_LEN 30
void parseXml(mxml_node_t* root){
    ///解析成解析配置文件存储结构
    printf("enter parserXml\n");
    char* device_tag="device_entity";
    mxml_node_t* dev_node_p=NULL;
    mxml_node_t* dev_attr_node_p=NULL;
    mxml_node_t* io_node_p=NULL;
    mxml_node_t* io_attr_node_p=NULL;
    mxml_node_t* io_config_node_p=NULL;
    mxml_node_t* io_descrip_tmp_p=NULL;
    char dev_lid[DESCRIPTION_ITEM_MAX_LEN];
    char dev_type[DESCRIPTION_ITEM_MAX_LEN];
    char interface[DESCRIPTION_ITEM_MAX_LEN];
    char dev_attr_name[DESCRIPTION_ITEM_MAX_LEN];
    char dev_attr_value[DESCRIPTION_ITEM_MAX_LEN];
    UINT device_id_tmp=0;
    UINT io_id_tmp=0;
    for(dev_node_p=mxmlFindElement(root,root,device_tag,NULL,NULL,MXML_DESCEND);dev_node_p!=NULL;dev_node_p=mxmlFindElement(dev_node_p,root,device_tag,NULL,NULL,MXML_NO_DESCEND)){
        ///对每一个device_entity节点,提取lid，type，interface，attr，然后再找到io_entity依次迭代
        //创建一个DeviceNode节点
        DeviceNode* dev_node=(DeviceNode*)malloc(sizeof(DeviceNode));
        mxml_node_t* dev_dependence=mxmlFindElement(dev_node_p,root,"dependence",NULL,NULL,MXML_DESCEND);
        strcpy(dev_lid,mxmlElementGetAttr(dev_node_p,"lid"));
        strcpy(dev_type,mxmlElementGetAttr(dev_node_p,"type"));
        strcpy(interface,getInterface(mxmlGetText(dev_dependence,NULL),strlen(mxmlGetText(dev_dependence,NULL))));
        strcpy(dev_node->descrip.lid,dev_lid);
        strcpy(dev_node->descrip.type,dev_type);
        strcpy(dev_node->descrip.interface,interface);
        dev_node->device_id=device_id_tmp++;
        //添加设备属性并找到第一个io_entity和io_config
        dev_node->descrip.attr_len=0;
        mxml_node_t* descrip=mxmlFindElement(dev_node_p,root,"description",NULL,NULL,MXML_DESCEND);
        for(dev_attr_node_p=mxmlFindElement(descrip,root,NULL,NULL,NULL,MXML_DESCEND);dev_attr_node_p!=NULL;dev_attr_node_p=mxmlFindElement(dev_attr_node_p,descrip,NULL,NULL,NULL,MXML_NO_DESCEND)){
            strcpy(dev_node->descrip.attrs.attr_name[dev_node->descrip.attr_len],dev_attr_node_p->value.element.name);
            strcpy(dev_node->descrip.attrs.attr_value[dev_node->descrip.attr_len],mxmlGetText(dev_attr_node_p,NULL));
            dev_node->descrip.attr_len++;
            //printf("test\n");
            //printf("%d\n",dev_node->descrip.attr_len);
        }
        //printf("out for\n");
        //找到第一个io
        const char *dev_content_tmp=mxmlGetText(dev_dependence,NULL);
        UINT dev_content_tmp_len=strlen(dev_content_tmp);
        io_node_p=findDependedNode(dev_content_tmp,dev_content_tmp_len,root,false);
        io_config_node_p=findDependedNode(dev_content_tmp,dev_content_tmp_len,root,true);
        //赋值并迭代找io
        const char* io_lid=NULL;
        const char* io_type=NULL;
        char io_attr_name[DESCRIPTION_ITEM_MAX_LEN];
        char io_attr_value[DESCRIPTION_ITEM_MAX_LEN];
        char dev_lid[DESCRIPTION_ITEM_MAX_LEN];
        char rt_send_priority[DESCRIPTION_ITEM_MAX_LEN];
        char rt_receive_priority[DESCRIPTION_ITEM_MAX_LEN];
        char rt_send_block_size[DESCRIPTION_ITEM_MAX_LEN];
        char rt_receive_block_size[DESCRIPTION_ITEM_MAX_LEN];
        io_id_tmp=0;
        IONode* prev_p=NULL;
        for(;io_node_p!=NULL;){
            IONode* io_node=(IONode*)malloc(sizeof(IONode));
            io_node->next=NULL;
            if(io_id_tmp==0){
                dev_node->next=io_node;
                DeviceList[DeviceListPos++]=dev_node;
            }
            else{
                prev_p->next=io_node;
            }
            prev_p=io_node;
            io_node->IO_id=io_id_tmp++;
            if(strcmp(io_node_p->value.element.name,"channel")==0){
                io_lid=mxmlElementGetAttr(io_node_p->parent,"lid");
                io_type=mxmlElementGetAttr(io_node_p->parent,"type");
            }
            else{
                io_lid=mxmlElementGetAttr(io_node_p,"lid");
                io_type=mxmlElementGetAttr(io_node_p,"type");
            }
            printf("sssss %s %s\n",io_lid,io_type);
            strcpy(io_node->descrip.lid,io_lid);
            strcpy(io_node->descrip.type,io_type);
            io_node->descrip.io_attr_len=0;
            if(strcmp(io_type,"RT")==0){
                io_descrip_tmp_p=mxmlFindElement(io_node_p,root,"tranData_description",NULL,NULL,MXML_DESCEND);
                io_attr_node_p=mxmlFindElement(io_descrip_tmp_p,root,NULL,NULL,NULL,MXML_DESCEND_FIRST);

            }
            else{
                io_descrip_tmp_p=mxmlFindElement(io_node_p,root,"description",NULL,NULL,MXML_DESCEND);
                io_attr_node_p=mxmlFindElement(io_descrip_tmp_p,root,NULL,NULL,NULL,MXML_DESCEND_FIRST);
            }
            for(;io_attr_node_p!=NULL;io_attr_node_p=mxmlFindElement(io_attr_node_p,io_descrip_tmp_p,NULL,NULL,NULL,MXML_NO_DESCEND)){
                    io_node->descrip.io_attr_len=0;
                    //printf("node name:%s\n",io_attr_node_p->value.element.name);
                    mxml_node_t* p_tmp=mxmlFindElement(io_attr_node_p,root,NULL,NULL,NULL,MXML_DESCEND);
                    if(strcmp(io_type,"RT")==0){
                        //
                        UINT RTTransPos=0;
                        char* name_tmp=io_attr_node_p->value.element.name;
                        //printf("name_tmp:%s\n",name_tmp);
                        if(strcmp(name_tmp,"send_priority")==0){
                            RTTransPos=0;
                        }
                        else if(strcmp(name_tmp,"send_blockSize")==0){
                            RTTransPos=2;
                        }
                        else if(strcmp(name_tmp,"receive_priority")==0){
                            RTTransPos=1;
                        }
                        else if(strcmp(name_tmp,"receive_blockSize")==0){
                            RTTransPos=3;
                        }
                        else{
                            printf("RTTransPos wrong!\n");
                            return;
                        }
                        io_node->descrip.io_attrs.RTTrans[RTTransPos].len=0;
                        UINT pos_tmp=0;
                        for(;p_tmp!=NULL;p_tmp=mxmlFindElement(p_tmp,io_attr_node_p,NULL,NULL,NULL,MXML_NO_DESCEND)){
                            strcpy(io_node->descrip.io_attrs.RTTrans[RTTransPos].dev_lid[pos_tmp],mxmlElementGetAttr(p_tmp,"lid"));
                            if(RTTransPos==0)strcpy(io_node->descrip.io_attrs.RTTrans[RTTransPos].info.send_priority[pos_tmp++],mxmlGetText(p_tmp,NULL));

                            else if(RTTransPos==1)strcpy(io_node->descrip.io_attrs.RTTrans[RTTransPos].info.receive_priority[pos_tmp++],mxmlGetText(p_tmp,NULL));

                            else if(RTTransPos==2)strcpy(io_node->descrip.io_attrs.RTTrans[RTTransPos].info.send_block_size[pos_tmp++],mxmlGetText(p_tmp,NULL));

                            else if(RTTransPos==3)strcpy(io_node->descrip.io_attrs.RTTrans[RTTransPos].info.receive_block_size[pos_tmp++],mxmlGetText(p_tmp,NULL));
                           io_node->descrip.io_attrs.RTTrans[RTTransPos].len++;
                            }
                    }
                    else{
                        //直接放入io属性
                            strcpy(io_node->descrip.io_attrs.attrs.attr_name[io_node->descrip.io_attr_len],io_attr_node_p->value.element.name);
                            strcpy(io_node->descrip.io_attrs.attrs.attr_value[io_node->descrip.io_attr_len],mxmlGetText(io_attr_node_p,NULL));
                            io_node->descrip.io_attr_len++;


                    }

            }
            mxml_node_t* io_config_parent=mxmlFindElement(io_config_node_p,root,"parent",NULL,NULL,MXML_DESCEND);
            const char* io_config_content=mxmlGetText(io_config_parent,NULL);
            io_node_p=findDependedNode(io_config_content,strlen(io_config_content),root,false);
            io_config_node_p=findDependedNode(io_config_content,strlen(io_config_content),root,true);
        }
    }
    DeviceListLen=DeviceListPos;
}
char* getInterface(const char* dev_content,UINT dev_content_len){
    char* t=content;
    for(int i=0;i<dev_content_len;i++){
        content[i]=dev_content[i];
        if(dev_content[i]==':'){
            content[i]='\0';
            break;
        }
    }
    return t;
}
mxml_node_t* findDependedNode(const char* content,UINT content_len,mxml_node_t* root,bool isConfig){
    ///处理字符串
    //content="   sss_   ";
    //printf("enter findDependedNode()\n");
    //printf("content:%s,size:%d\n",content,content_len);
    mxml_node_t* t=NULL;
    char content_tmp[CONTENT_MAX_LEN];
    strcpy(content_tmp,content);
    char ROUTE[ROUTE_MAX_LEN][ROUTE_VALUE_MAX_LEN];
    memset(ROUTE[ROUTE_CHANNEL_NAME_POS],0,ROUTE_VALUE_MAX_LEN);
    memset(ROUTE[ROUTE_CHANNEL_LID_VALUE_POS],0,ROUTE_VALUE_MAX_LEN);
    int j=0;
    int k=0;
    UINT content_tmp_len=content_len;
    UINT ROUTE_pos=0;
    UINT ROUTE_VALUE_pos=0;
    bool isHaveChannel=false;
    char io_tag_name_tmp[TAG_NAME_MAX_LEN]="io_";
    char io_tag_type[TAG_NAME_MAX_LEN];
    char io_tag_entity_suffix[TAG_NAME_MAX_LEN]="_entity";
    char io_tag_config_suffix[TAG_NAME_MAX_LEN]="_config";
    char io_lid[TAG_NAME_MAX_LEN];
    char channel_tag_name[TAG_NAME_MAX_LEN];
    char channel_lid[TAG_NAME_MAX_LEN];
    //删掉content的前后空字符
    /*
    for(int i=0;i<content_len;i++){
        if(j==0){
            if(content[i]==' '){
                continue;
            }
            else{
                content_tmp[j++]=content[i];
                content_tmp_len++;
                continue;
            }
        }
        else{
                k=i;
                bool isLastWordsEmpty=true;
                for(int l=k;l<content_len;l++){
                    if(content[l]!=' '&&content[l]!='\0'){
                        isLastWordsEmpty=false;
                        printf("s %c\n",content[l]);
                    }
                 }
                if(isLastWordsEmpty==true){
                    break;
                }
                else{
                    content_tmp[j++]=content[i];
                    content_tmp_len++;
                    continue;
            }
        }
      content_tmp[j]='\0';
    }//处理完前后空字符
    */
    //printf("content_tmp:%s,size:%d\n",content_tmp,content_tmp_len);
    if(strcmp(content_tmp,"ROOT")==0)return NULL;
    ///放入ROUTE
    j=0;
    k=0;
    for(int i=0;i<content_tmp_len;i++){
        k=i;
        if(content_tmp[i]==':'||content_tmp[i]==';'||i==content_tmp_len-1){
            if(i==content_tmp_len-1)k++;
            for(int l=j;l<k;l++){
                *(ROUTE[ROUTE_pos]+ROUTE_VALUE_pos++)=*(content_tmp+l);
            }
            *(ROUTE[ROUTE_pos]+ROUTE_VALUE_pos)='\0';
            //printf("%s\n",ROUTE[ROUTE_pos]);//
            ROUTE_pos++;
            ROUTE_VALUE_pos=0;
            j=i+1;
        }
        else{
            continue;
        }
    }
    //printf("tttttest\n");
    ///查找Node
    //printf("%d %d\n",strlen(ROUTE[ROUTE_CHANNEL_NAME_POS]),strlen(ROUTE[ROUTE_CHANNEL_LID_VALUE_POS]));
    if(strlen(ROUTE[ROUTE_CHANNEL_NAME_POS])>0&&strlen(ROUTE[ROUTE_CHANNEL_LID_VALUE_POS])>0){
        isHaveChannel=true;
    }
    strcat(io_tag_name_tmp,ROUTE[ROUTE_IO_NAME_POS]);
    if(isConfig==false)strcat(io_tag_name_tmp,io_tag_entity_suffix);
    else strcat(io_tag_name_tmp,io_tag_config_suffix);
    strcpy(io_lid,ROUTE[ROUTE_IO_LID_VALUE]);
    strcpy(channel_tag_name,ROUTE[ROUTE_CHANNEL_NAME_POS]);
    strcpy(channel_lid,ROUTE[ROUTE_CHANNEL_LID_VALUE_POS]);
    //printf("%s %s %s %s\n",io_tag_name_tmp,io_lid,channel_tag_name,channel_lid);
    //printf("isHaveChannel: %d\n",isHaveChannel);
    if(isConfig==false){
         t=mxmlFindElement(root,root,io_tag_name_tmp,"lid",io_lid,MXML_DESCEND);
         if(isHaveChannel==true){
             t=mxmlFindElement(t,root,channel_tag_name,"lid",channel_lid,MXML_DESCEND);
         }
    }
    else{
        mxml_node_t* t_tmp=NULL;
        for(t_tmp=mxmlFindElement(root,root,io_tag_name_tmp,"lid",io_lid,MXML_DESCEND);t_tmp!=NULL;t_tmp=mxmlFindElement(t,root,io_tag_name_tmp,"lid",io_lid,MXML_DESCEND)){
            //printf("lid:%s\n",mxmlElementGetAttr(t,"lid"));
            t=t_tmp;
            if(isHaveChannel==true){
                if(strcmp(mxmlElementGetAttr(t,"channel"),channel_lid)==0){
                    break;
                }
            }
        }
    }

    //printf("name:%s\n",t->value.element.name);
    //while(true);
    return t;
}

void printList(){
printf("enter print...\n\n");
    for(int i=0;i<get_devices_descrip_item_num();i++){
    printf("____________________________\n");
    printf("enterpos: %d\n",entryPos);
        void* dev_p=get_devices_descrip_item();
        printf("device lid:%s\n",get_device_lid(dev_p));
        printf("device type:%s\n",get_device_type(dev_p));
        printf("device interface:%s\n",get_device_interface(dev_p));
        for(int j=0;j<DeviceList[i]->descrip.attr_len;j++){
            printf("%s: ",DeviceList[i]->descrip.attrs.attr_name[j]);
            printf("%s\n",DeviceList[i]->descrip.attrs.attr_value[j]);
        }
        printf("\n");
        IONode* io_tmp=DeviceList[i]->next;
        for(;io_tmp!=NULL;io_tmp=io_tmp->next){
            printf("io type:%s\n",io_tmp->descrip.type);
            printf("io lid:%s\n",io_tmp->descrip.lid);
            if(strcmp(io_tmp->descrip.type,"RT")==0){
                //RT_trans
                printf("___send priority_____\n");
                for(int k=0;k<io_tmp->descrip.io_attrs.RTTrans[0].len;k++){
                    printf("device lid:%s",io_tmp->descrip.io_attrs.RTTrans[0].dev_lid[k]);
                    printf("weight:%s\n",io_tmp->descrip.io_attrs.RTTrans[0].info.send_priority[k]);
                }
                for(int k=0;k<io_tmp->descrip.io_attrs.RTTrans[1].len;k++){
                    printf("device lid:%s",io_tmp->descrip.io_attrs.RTTrans[1].dev_lid[k]);
                    printf("weight:%s\n",io_tmp->descrip.io_attrs.RTTrans[1].info.send_priority[k]);
                }
                for(int k=0;k<io_tmp->descrip.io_attrs.RTTrans[2].len;k++){
                    printf("device lid:%s",io_tmp->descrip.io_attrs.RTTrans[2].dev_lid[k]);
                    printf("weight:%s\n",io_tmp->descrip.io_attrs.RTTrans[2].info.send_priority[k]);
                }
                for(int k=0;k<io_tmp->descrip.io_attrs.RTTrans[3].len;k++){
                    printf("device lid:%s",io_tmp->descrip.io_attrs.RTTrans[3].dev_lid[k]);
                    printf("weight:%s\n",io_tmp->descrip.io_attrs.RTTrans[3].info.send_priority[k]);
                }

            }
            else if(io_tmp->descrip.io_attr_len!=0){
                //io_attr
                printf("___io_attr______\n");
                for(int k=0;k<io_tmp->descrip.io_attr_len;k++){
                    printf("%s:",io_tmp->descrip.io_attrs.attrs.attr_name[k]);
                    printf("%s\n",io_tmp->descrip.io_attrs.attrs.attr_value[k]);
                }
            }
            printf("\n\n");
        }
    }
}
void* get_devices_descrip_item(void){
    entryPos=entryPos%DeviceListLen;
    return (void*)(&DeviceList[entryPos++]->descrip);
}
UINT get_devices_descrip_item_num(void){
    return DeviceListLen;
}
char* get_device_lid(void* descrip){
    return ((dev_descrip*)descrip)->lid;
}
char* get_device_type(void* descrip){
    return ((dev_descrip*)descrip)->type;
}
char* get_device_interface(void* descrip){
    return ((dev_descrip*)descrip)->interface;
}
