#include "my_dev_socket.h"
int main(){
    create_dev_unit(8001);
    create_dev_unit(8002);
    create_dev_unit(8003);
    create_dev_unit(8004);
    create_dev_unit(8005);
    create_dev_unit(8006);
    create_dev_unit(8007);
    create_dev_unit(8008);
    while(1){
        usleep(100000000);
    }
    return 0;
}
