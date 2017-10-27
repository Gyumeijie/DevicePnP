#include "my_dev_socket.h"
int main(){
    printf("这是001设备...\n");
    create_dev_unit(8000);
    while(1);
    return 0;
}
