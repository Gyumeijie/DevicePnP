#include "my_dev_socket.h"
int main(){
    create_dev_unit(8000);
    create_dev_unit(8010);
    while(1);
    return 0;
}
