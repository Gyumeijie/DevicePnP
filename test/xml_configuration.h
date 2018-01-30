#ifndef XML_CONFIGURATION_H
#define XML_CONFIGURATION_H


const char config_str[] = "\
<?xml version=1.0 encoding=utf-8?>\n\
<machine architecture=sparc >\n\
<device_description>\n\
<device_entity type=gyroscope lid=gyroscope1>\n\
<description>\n\
<model>XM1</model>\n\
<dataSize>2</dataSize>\n\
</description>\n\
<operation>\n\
<!-->\n\
<-->\n\
<global name=\"global\" template_id=\"0\">\n\
 <template_data type=\"plain_struct\" name=\"global_template0_data\">\n\
 <para_list length=\"1\">\n\
 <para name=\"slave_address\" type=\"char\">0xD2</para>\n\
 </para_list>\n\
 </template_data>\n\
</global>\n\
<op_list length=\"4\">\n\
 <op name=\"gyroscope_open\" template_id=\"0\">\n\
 <template_data type=\"register_array\" name=\"open_template0_data\">\n\
 <para_list length=\"5\">\n\
 <para register_address=\"0x20\">0x00</para>\n\
 <para register_address=\"0x21\">0x00</para>\n\
 <para register_address=\"0x22\">0x08</para>\n\
 <para register_address=\"0x23\">0x03</para>\n\
 <para register_address=\"0x24\">0x00</para> \n\
 </para_list>\n\
 </template_data>\n\
 </op>\n\
 <op name=\"gyroscope_getx\" template_id=\"0\">\n\
 <template_data type=\"plain_struct\" name=\"getx_template0_data\">\n\
 <para_list length=\"2\">\n\
 <para name=\"register_address\" type=\"char\">0x28</para> \n\
 <para name=\"size\" type=\"int\">2</para>\n\
 </para_list> \n\
 </template_data>\n\
 </op>\n\
 <op name=\"gyroscope_gety\" template_id=\"0\">\n\
 <template_data type=\"plain_struct\" name=\"gety_template0_data\">\n\
 <para_list length=\"2\">\n\
 <para name=\"register_address\" type=\"char\">0x2c</para> \n\
 <para name=\"size\" type=\"int\">2</para>\n\
 </para_list>\n\
 </template_data>\n\
 </op>\n\
 <op name=\"gyroscope_getz\" template_id=\"0\">\n\
 <template_data type=\"plain_struct\" name=\"getz_template0_data\">\n\
 <para_list length=\"2\">\n\
 <para name=\"register_address\" type=\"char\">0x2f</para> \n\
 <para name=\"size\" type=\"int\">2</para>\n\
 </para_list>\n\
 </template_data>\n\
 </op>\n\
</op_list>\n\
</operation>\n\
<dependence>i2c:001</dependence>\n\
</device_entity>\n\
<device_entity type=magnetorquer lid=magnetorquer1>\n\
<description>\n\
<model>XM</model>\n\
<dataSize>4</dataSize>\n\
<voltage>3.0v</voltage>\n\
</description>\n\
 <operation>\n\
<!-->\n\
<-->\n\
<op_list length=\"4\">\n\
 <op name=\"magnetorquer_setx\" template_id=\"0\"> \n\
 <template_data type=\"plain_array\" name=\"setx_template0_data\">\n\
 <para_list length=\"1\">\n\
 <para type=\"int\">4</para>\n\
 </para_list>\n\
 </template_data>\n\
 </op>\n\
 <op name=\"magnetorquer_sety\" template_id=\"0\"> \n\
 <template_data type=\"plain_array\" name=\"sety_template0_data\">\n\
 <para_list length=\"1\">\n\
 <para type=\"int\">6</para>\n\
 </para_list>\n\
 </template_data>\n\
 </op>\n\
 <op name=\"magnetorquer_setz\" template_id=\"0\"> \n\
 <template_data type=\"plain_array\" name=\"setz_template0_data\">\n\
 <para_list length=\"1\">\n\
 <para type=\"int\">9</para>\n\
 </para_list>\n\
 </template_data>\n\
 </op>\n\
 <op name=\"magnetorquer_setxyz\" template_id=\"0\"> \n\
 <template_data type=\"plain_array\" name=\"setxyz_template0_data\">\n\
 <para_list length=\"3\">\n\
 <para type=\"int\">4</para>\n\
 <para type=\"int\">6</para>\n\
 <para type=\"int\">9</para>\n\
 </para_list>\n\
 </template_data>\n\
 </op>\n\
</op_list>\n\
 </operation>\n\
<dependence>da:002</dependence>\n\
</device_entity>\n\
<device_entity type=flywheel lid=flywheel1>\n\
<description>\n\
<model>XM</model>\n\
<dataSize>4</dataSize>\n\
<voltage>2.0v</voltage>\n\
</description>\n\
 <operation>\n\
<!-->\n\
<-->\n\
<op_list length=\"2\">\n\
 <op name=\"flywheel_set_speed\" template_id=\"0\">\n\
 <template_data type=\"command_sequence\" name=\"set_speed_template0_data\">\n\
 <para_list length=\"6\">\n\
 <para occupied_by=\"constant\">0xD3</para> \n\
 <para occupied_by=\"constant\">2</para>\n\
 <para occupied_by=\"computed\" size=\"4\" compute_id=\"0\"></para>\n\
 <para occupied_by=\"constant\">0x5B</para>\n\
 <para occupied_by=\"computed\" size=\"3\" compute_id=\"0\"></para>\n\
 <para occupied_by=\"checksum\"></para>\n\
 </para_list>\n\
 <code_block_list length=\"1\" name=\"compute\">\n\
 <code_block id=\"0\">\n\
use{;}&#x000A;action{&#x000A;result=*(int*)para;&#x000A;result=result*2+1;&#x000A;}&#x000A;\n\
 </code_block>\n\
 </code_block_list>\n\
 </template_data>\n\
 </op>\n\
 <op name=\"flywheel_receive\" template_id=\"0\">\n\
 <template_data type=\"bytes_array_assembly\" name=\"receive_template0_data\">\n\
 <para_list length=\"6\">\n\
 <para start=\"0\" num_byte=\"4\" postprocess_id=\"-1\"></para> \n\
 <para start=\"4\" num_byte=\"4\" postprocess_id=\"-1\"></para> \n\
 <para start=\"8\" num_byte=\"3\" postprocess_id=\"0\"></para> \n\
 <para start=\"11\" num_byte=\"3\" postprocess_id=\"0\"></para> \n\
 <para start=\"14\" num_byte=\"1\" postprocess_id=\"-1\"></para> \n\
 <para start=\"15\" num_byte=\"1\" postprocess_id=\"-1\"></para> \n\
 </para_list>\n\
 <code_block name=\"precondition\">\n\
use{;}&#x000A;action{&#x000A;if(bytes_arr[0]==0x00){&#x000A;result=1;&#x000A;}else{&#x000A;result=0;&#x000A;}&#x000A;;}&#x000A;\n\
 </code_block>\n\
 <code_block_list length=\"1\" name=\"postprocess\">\n\
 <code_block id=\"0\">\n\
use{float&#x0020;tmp;}&#x000A;action{&#x000A;tmp=asm_val;&#x000A;tmp=tmp*0.05;&#x000A;*(float*)var_addr=tmp;&#x000A;}&#x000A;\n\
 </code_block>\n\
 </code_block_list> \n\
 </template_data>\n\
 </op>\n\
</op_list>\n\
 </operation>\n\
<dependence>i2c:002</dependence>\n\
</device_entity>\n\
</device_description>\n\
<IO_description>\n\
<bus>\n\
 <io_i2c_entity type=i2c lid=001>\n\
<description/>\n\
</io_i2c_entity>\n\
 <io_i2c_entity type=i2c lid=002>\n\
<description/>\n\
</io_i2c_entity>\n\
<io_1553b_entity type=1553b lid=001>\n\
<description/>\n\
</io_1553b_entity>\n\
<io_uart_entity type=uart lid=007>\n\
<description/>\n\
</io_uart_entity>\n\
</bus>\n\
<device_io>\n\
<io_da_entity type=ad lid=002>\n\
<description/>\n\
</io_da_entity>\n\
</device_io>\n\
<RT>\n\
<io_RT_entity type=RT lid=02>\n\
<description/>\n\
<tranData_description>\n\
<send_priority>\n\
<device lid=001>11</device>\n\
</send_priority>\n\
<send_blockSize>\n\
<device lid=001>100</device>\n\
</send_blockSize>\n\
<receive_priority>\n\
<device lid=001>22</device>\n\
</receive_priority>\n\
<receive_blockSize>\n\
<device lid=001>100</device>\n\
</receive_blockSize>\n\
</tranData_description>\n\
</io_RT_entity>\n\
<io_RT_entity type=RT lid=04>\n\
<description/>\n\
<tranData_description>\n\
<send_priority>\n\
<device lid=002>11</device>\n\
</send_priority>\n\
<send_blockSize>\n\
<device lid=002>100</device>\n\
</send_blockSize>\n\
<receive_priority>\n\
<device lid=002>22</device>\n\
</receive_priority>\n\
<receive_blockSize>\n\
<device lid=002>100</device>\n\
</receive_blockSize>\n\
</tranData_description>\n\
</io_RT_entity>\n\
</RT>\n\
</IO_description>\n\
<config_description>\n\
<io_i2c_config lid=001>\n\
<parent>RT:02</parent>\n\
 </io_i2c_config>\n\
<io_i2c_config lid=002>\n\
<parent>RT:02</parent>\n\
</io_i2c_config>\n\
<io_RT_config lid=02>\n\
<parent>1553b:001</parent>\n\
</io_RT_config>\n\
<io_1553b_config lid=001>\n\
<parent>ROOT</parent>\n\
</io_1553b_config>\n\
<io_uart_config lid=007>\n\
<parent>RT:04</parent>\n\
</io_uart_config>\n\
<io_RT_config lid=04>\n\
<parent>1553b:001</parent>\n\
</io_RT_config>\n\
<io_da_config lid=002>\n\
<parent>ROOT</parent>\n\
</io_da_config>\n\
</config_description>\n\
</machine>\n";

#endif
