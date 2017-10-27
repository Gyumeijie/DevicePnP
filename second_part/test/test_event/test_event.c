#include "../../handle_event.h"
#include "../../relevant_struct_def.h"
#include "pthread.h"
int main(){
    parseXml();
    create_data_trans_rule_form();
    init_event_repos_array();
    UINT evt_repos_id;
    get_one_event_repos(&evt_repos_id);
    throw_event(evt_repos_id,"02",EVT_RT_RECV_DATA);
    throw_event(evt_repos_id,"02",EVT_RT_RECV_DATA_ERR);
    throw_event(evt_repos_id,"02",EVT_1553_RECV_COMMAND);
    throw_event(evt_repos_id,"04",EVT_1553_RECV_COMMAND_ERR);
    throw_event(evt_repos_id,"02",EVT_WAIT_OVER_TIME);
    throw_event(evt_repos_id,"02",EVT_RED_LIGHT_READ_ERR);
    throw_event(evt_repos_id,"02",EVT_APP_READ_BLOCK_OVERFLOW);
    pthread_t tid;
    pthread_create(&tid,NULL,evt_repos_scan_pthread_func,NULL);
    while(1);
    return 0;
}
