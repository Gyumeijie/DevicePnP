#include "../../manage_transport_center.h"
#include "../../app_program/app.h"
int main(){
   init_vi_dev_visit_sys();
   pthread_t tid1;
   pthread_create(&tid1,NULL,app_write_pthread_func,NULL);
   pthread_t tid2;
   pthread_create(&tid2,NULL,app_read_pthread_func,NULL);
   while(1);
   return 0;
}
