#include "my_dev_socket.h"
int main(){
    printf("这是002设备...\n");
    create_dev_unit(8050);
    while(1);
    return 0;
}
