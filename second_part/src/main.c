#include "manage_transport_center.h"
#include "app.h"
int main(){
    init_vi_dev_visit_sys();
    pthread_t tid;
    pthread_create(&tid,NULL,app_write_pthread_func,NULL);
    pthread_t tid1;
    pthread_create(&tid,NULL,app_read_pthread_func,NULL);
    while(1){
        //print_traffic_light();
        usleep(200000000);
    }
    return 0;
}
