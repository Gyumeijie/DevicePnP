#include "file.h"
void add_string(UINT send_or_rec,double data,UINT port){
    char a[20]={0};
    sprintf(a,"%d:%lf:%d;",send_or_rec,data,port);
    strcat(out_put_str,a);
}
void out_put(void){
    FILE* fp;
    fp=fopen("./data.txt","w+");
    if(fp==NULL)printf("打开文件失败\n");
    else{
        //printf("%s\n",out_put_str);
        //fwrite(fp,strlen(out_put_str),1,out_put_str);
        fprintf(fp,"%s",out_put_str);
        fclose(fp);
    }
}
void set_is_end(void){
    is_end++;
}
UINT is_end_t(void){
    return is_end;
}
void judge_result(void){
    FILE* fp;
    char buffer[100000]={0};
    fp=fopen("./data.txt","r+");
    if(fp==NULL){
        printf("打开文件失败\n");
        return;
    }
    fread(buffer,1,100000,fp);
    //printf("读取文件内容：%s",buffer);
    UINT buf_len=strlen(buffer);
    printf("正在分析测试结果...\n");
    t t_node[4000];
    UINT hash_t[4000]={0};
    UINT pos=0;
    int i=0;
    int t=0;
    //printf("buf_len:%d\n",buf_len);
    //for(;t<buf_len;t++){
    //    printf("buffer[%d]:%c",t,buffer[t]);
    //}
    UINT offset=0;
    for(;i<buf_len;i+=offset){
        offset=0;
        int j=0;
        for(;j<3;j++){
            char buf_tmp[10]={0};
            if(j==0){
                offset++;
                memcpy(buf_tmp,buffer+i,1);
                //printf("1-%s\n",buf_tmp);
                t_node[pos].send_or_rec=atof(buf_tmp);
            }
            if(j==1){
                    int s=i+2;
                    for(;s<buf_len;s++){
                        if(buffer[s]==':')break;
                    }
                    if(s==buf_len)return;
                    UINT m_len=s-i-2;
                    memset(buf_tmp,0,10);
                    memcpy(buf_tmp,buffer+i+2,m_len);
                    //printf("2-%s\n",buf_tmp);
                    t_node[pos].data=atof(buf_tmp);
                    offset+=m_len+1;
            }
            if(j==2){
                    int s=i+offset+1;
                    for(;s<buf_len;s++){
                        if(buffer[s]==';')break;
                    }
                    if(s==buf_len)return;
                    UINT m_len=s-(i+offset+1);
                    memset(buf_tmp,0,10);
                    memcpy(buf_tmp,buffer+i+offset+1,m_len);
                    //printf("3-%s\n",buf_tmp);
                    t_node[pos].port=atof(buf_tmp);
                    offset+=m_len+2;
            }

        }//for
        pos++;
    }//for
    //打印一下
    //int d=0;
    //for(;d<pos;d++){
    //    printf("%d %d:%d:%d\n",d,t_node[d].send_or_rec,t_node[d].data,t_node[d].port);
    //}


    int k=0;
    for(;k<pos;k++){
        if(t_node[k].send_or_rec==1&&t_node[k].port==8004){
            printf("位置：RT;状态：发送；数据：%lf；端口：%d\n",t_node[k].data,t_node[k].port);
            int l=k+1;
            for(;l<pos;l++){
                if(hash_t[l]==0&&t_node[l].send_or_rec==2&&t_node[l].port==8004&&t_node[l].data==t_node[k].data+1){
                    printf("                        匹配成功->位置：RT;状态：接收；数据：%lf；端口：%d\n",t_node[l].data,t_node[l].port);
                    hash_t[l]=1;
                    break;
                }
            }
            if(l==pos){
                printf("有数据不匹配，发生在8004端口,检测失败\n");
                exit(0);
            }

        }
    }
    printf("\n8004端口匹配成功\n\n");
    usleep(50000);
    k=0;
    for(;k<pos;k++){
        if(hash_t[k]==0&&t_node[k].send_or_rec==1&&t_node[k].port==8001){
            printf("位置：RT;状态：发送；数据：%lf；端口：%d\n",t_node[k].data,t_node[k].port);
            hash_t[k]=1;
            int m=k+1;
            for(;m<pos;m++){
                if(hash_t[m]==0&&t_node[m].send_or_rec==1&&t_node[m].port==8002){
                        printf("位置：RT;状态：发送；数据：%lf；端口：%d\n",t_node[m].data,t_node[m].port);
                    break;
                }
            }
            if(m==pos){
                printf("有数据不匹配，发生在8001/8002端口,检测失败\n");
                exit(0);
            }
            hash_t[m]=1;
            int l=m+1;
            for(;l<pos;l++){
                if(hash_t[l]==0&&t_node[l].send_or_rec==2&&t_node[l].port==8003&&t_node[l].data==t_node[k].data+t_node[m].data){
                    printf("                        匹配成功->位置：RT;状态：接收；数据：%lf；端口：%d\n",t_node[l].data,t_node[l].port);
                    hash_t[l]=1;
                    break;
                }
            }
            if(l==pos){
                printf("有数据不匹配，发生在8003端口,检测失败\n");
                exit(0);
            }

        }
        if(hash_t[k]==0&&t_node[k].send_or_rec==1&&t_node[k].port==8002){
            printf("位置：RT;状态：发送；数据：%lf；端口：%d\n",t_node[k].data,t_node[k].port);
            hash_t[k]=1;
            int m=k+1;
            for(;m<pos;m++){
                if(hash_t[m]==0&&t_node[m].send_or_rec==1&&t_node[m].port==8001){
            printf("位置：RT;状态：发送；数据：%lf；端口：%d\n",t_node[m].data,t_node[m].port);
                    break;
                }
            }
            if(m==pos){
                printf("有数据不匹配，发生在8001/8002端口,检测失败\n");
                exit(0);
            }
            hash_t[m]=1;
            int l=m+1;
            for(;l<pos;l++){
                if(hash_t[l]==0&&t_node[l].send_or_rec==2&&t_node[l].port==8003&&t_node[l].data==t_node[k].data+t_node[m].data){
                    printf("                        匹配成功->位置：RT;状态：接收；数据：%lf；端口：%d\n",t_node[l].data,t_node[l].port);
                    hash_t[l]=1;
                    break;
                }
            }
            if(l==pos){
                printf("有数据不匹配，发生在8003端口,检测失败\n");
                exit(0);
            }

        }
    }//
    printf("\n8001/8002端口匹配成功\n\n");
    usleep(50000);

    k=0;
    for(;k<pos;k++){
        if(hash_t[k]==0&&t_node[k].send_or_rec==1&&t_node[k].port==8005){
            printf("位置：RT;状态：发送；数据：%lf；端口：%d\n",t_node[k].data,t_node[k].port);
            hash_t[k]=1;
            int m=k+1;
            int n;
            for(;m<pos;m++){
                if(hash_t[m]==0&&t_node[m].send_or_rec==1&&t_node[m].port==8006){
                    printf("位置：RT;状态：发送；数据：%lf；端口：%d\n",t_node[m].data,t_node[m].port);
                    n=m+1;
                    for(;n<pos;n++){
                        if(hash_t[n]==0&&t_node[n].send_or_rec==1&&t_node[n].port==8007){
                            printf("位置：RT;状态：发送；数据：%lf；端口：%d\n",t_node[n].data,t_node[n].port);
                            break;
                        }
                    }
                    break;
                }
                if(hash_t[m]==0&&t_node[m].send_or_rec==1&&t_node[m].port==8007){
                    printf("位置：RT;状态：发送；数据：%lf；端口：%d\n",t_node[m].data,t_node[m].port);
                    n=m+1;
                    for(;n<pos;n++){
                        if(hash_t[n]==0&&t_node[n].send_or_rec==1&&t_node[n].port==8006){
                        printf("位置：RT;状态：发送；数据：%lf；端口：%d\n",t_node[n].data,t_node[n].port);
                            break;
                        }
                    }
                    break;
                }
            }
            if(m==pos||n==pos){
                printf("有数据不匹配，发生在8005/8006/8007端口,检测失败\n");
                exit(0);
            }
            hash_t[m]=1;
            hash_t[n]=1;
            int l=n+1;
            for(;l<pos;l++){
                if(hash_t[l]==0&&t_node[l].send_or_rec==2&&t_node[l].port==8007&&t_node[l].data==t_node[k].data+t_node[m].data+t_node[n].data){
                    printf("                        匹配成功->位置：RT;状态：接收；数据：%lf；端口：%d\n",t_node[l].data,t_node[l].port);
                    hash_t[l]=1;
                    break;
                }
            }
            if(l==pos){
                printf("有数据不匹配，发生在8007端口,检测失败\n");
                exit(0);
            }
            l=n+1;
            for(;l<pos;l++){
                if(hash_t[l]==0&&t_node[l].send_or_rec==2&&t_node[l].port==8008&&t_node[l].data==t_node[k].data+t_node[m].data+t_node[n].data){
                    printf("                        匹配成功->位置：RT;状态：接收；数据：%lf；端口：%d\n",t_node[l].data,t_node[l].port);
                    hash_t[l]=1;
                    break;
                }
            }
            if(l==pos){
                printf("有数据不匹配，发生在8008端口,检测失败\n");
                exit(0);
            }

        }



        if(hash_t[k]==0&&t_node[k].send_or_rec==1&&t_node[k].port==8006){
            printf("位置：RT;状态：发送；数据：%lf；端口：%d\n",t_node[k].data,t_node[k].port);
            hash_t[k]=1;
            int m=k+1;
            int n;
            for(;m<pos;m++){
                if(hash_t[m]==0&&t_node[m].send_or_rec==1&&t_node[m].port==8005){
                    printf("位置：RT;状态：发送；数据：%lf；端口：%d\n",t_node[m].data,t_node[m].port);
                    n=m+1;
                    for(;n<pos;n++){
                        if(hash_t[n]==0&&t_node[n].send_or_rec==1&&t_node[n].port==8007){
                        printf("位置：RT;状态：发送；数据：%lf；端口：%d\n",t_node[n].data,t_node[n].port);
                            break;
                        }
                    }
                    break;
                }
                if(hash_t[m]==0&&t_node[m].send_or_rec==1&&t_node[m].port==8007){
                    printf("位置：RT;状态：发送；数据：%lf；端口：%d\n",t_node[m].data,t_node[m].port);
                    n=m+1;
                    for(;n<pos;n++){
                        if(hash_t[n]==0&&t_node[n].send_or_rec==1&&t_node[n].port==8005){
                            printf("位置：RT;状态：发送；数据：%lf；端口：%d\n",t_node[n].data,t_node[n].port);
                            break;
                        }
                    }
                    break;
                }
            }
            if(m==pos||n==pos){
                printf("有数据不匹配，发生在8005/8006/8007端口,检测失败\n");
                exit(0);
            }
            hash_t[m]=1;
            hash_t[n]=1;
            int l=n+1;
            for(;l<pos;l++){
                if(hash_t[l]==0&&t_node[l].send_or_rec==2&&t_node[l].port==8007&&t_node[l].data==t_node[k].data+t_node[m].data+t_node[n].data){
                    printf("                        匹配成功->位置：RT;状态：接收；数据：%lf；端口：%d\n",t_node[l].data,t_node[l].port);
                    hash_t[l]=1;
                    break;
                }
            }
            if(l==pos){
                printf("有数据不匹配，发生在8007端口,检测失败\n");
                exit(0);
            }
            l=n+1;
            for(;l<pos;l++){
                if(hash_t[l]==0&&t_node[l].send_or_rec==2&&t_node[l].port==8008&&t_node[l].data==t_node[k].data+t_node[m].data+t_node[n].data){
                    printf("                        匹配成功->位置：RT;状态：接收；数据：%lf；端口：%d\n",t_node[l].data,t_node[l].port);
                    hash_t[l]=1;
                    break;
                }
            }
            if(l==pos){
                printf("有数据不匹配，发生在8008端口,检测失败\n");
                exit(0);
            }

        }



        if(hash_t[k]==0&&t_node[k].send_or_rec==1&&t_node[k].port==8007){
            printf("位置：RT;状态：发送；数据：%lf；端口：%d\n",t_node[k].data,t_node[k].port);
            hash_t[k]=1;
            int m=k+1;
            int n;
            for(;m<pos;m++){
                if(hash_t[m]==0&&t_node[m].send_or_rec==1&&t_node[m].port==8005){
                    printf("位置：RT;状态：发送；数据：%lf；端口：%d\n",t_node[m].data,t_node[m].port);
                    n=m+1;
                    for(;n<pos;n++){
                        if(hash_t[n]==0&&t_node[n].send_or_rec==1&&t_node[n].port==8006){
                        printf("位置：RT;状态：发送；数据：%lf；端口：%d\n",t_node[n].data,t_node[n].port);
                            break;
                        }
                    }
                    break;
                }
                if(hash_t[m]==0&&t_node[m].send_or_rec==1&&t_node[m].port==8006){
                    printf("位置：RT;状态：发送；数据：%lf；端口：%d\n",t_node[m].data,t_node[m].port);
                    n=m+1;
                    for(;n<pos;n++){
                        if(hash_t[n]==0&&t_node[n].send_or_rec==1&&t_node[n].port==8005){
                            printf("位置：RT;状态：发送；数据：%lf；端口：%d\n",t_node[n].data,t_node[n].port);
                            break;
                        }
                    }
                    break;
                }
            }
            if(m==pos||n==pos){
                printf("有数据不匹配，发生在8005/8006/8007端口,检测失败\n");
                exit(0);
            }
            hash_t[m]=1;
            hash_t[n]=1;
            int l=n+1;
            for(;l<pos;l++){
                if(hash_t[l]==0&&t_node[l].send_or_rec==2&&t_node[l].port==8007&&t_node[l].data==t_node[k].data+t_node[m].data+t_node[n].data){
                    printf("                        匹配成功->位置：RT;状态：接收；数据：%lf；端口：%d\n",t_node[l].data,t_node[l].port);
                    hash_t[l]=1;
                    break;
                }
            }
            if(l==pos){
                printf("有数据不匹配，发生在8007端口,检测失败\n");
                exit(0);
            }
            l=n+1;
            for(;l<pos;l++){
                if(hash_t[l]==0&&t_node[l].send_or_rec==2&&t_node[l].port==8008&&t_node[l].data==t_node[k].data+t_node[m].data+t_node[n].data){
                    printf("                        匹配成功->位置：RT;状态：接收；数据：%lf；端口：%d\n",t_node[l].data,t_node[l].port);
                    hash_t[l]=1;
                    break;
                }
            }
            if(l==pos){
                printf("有数据不匹配，发生在8008端口,检测失败\n");
                exit(0);
            }

        }
    }
    printf("\n8005/8006/8007端口匹配成功\n\n");
    usleep(50000);
    printf("数据匹配成功,测试通过!\n");
    exit(0);
}
