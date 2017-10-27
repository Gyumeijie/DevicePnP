target = test_control_traffic_light.o control_traffic_light.o config_1553.o traffic_light.o handle_data_package.o xml_parse.o relevant_struct_def.o\
	address_map.o route_map.o handle_event.o handle_event_func.o event.o

test_control_traffic_light : $(target)
	cc -o test_control_traffic_light $(target) -lmxml -lpthread
test_control_traffic_light.o : test_control_traffic_light.c ../../control_traffic_light.h ../../route_map.h ../../config_1553.h
	cc -c test_control_traffic_light.c
control_traffic_light.o : ../../control_traffic_light.c ../../control_traffic_light.h
	cc -c ../../control_traffic_light.c
config_1553.o : ../../config_1553.c ../../config_1553.h
	cc -c ../../config_1553.c
traffic_light.o : ../../traffic_light.c ../../traffic_light.h
	cc -c ../../traffic_light.c
handle_data_package.o : ../../handle_data_package.c ../../handle_data_package.h
	cc -c ../../handle_data_package.c
xml_parse.o : ../../xml_parse.c ../../xml_parse.h
	cc -c ../../xml_parse.c
relevant_struct_def.o : ../../relevant_struct_def.c ../../relevant_struct_def.h
	cc -c ../../relevant_struct_def.c
address_map.o : ../../address_map.c ../../address_map.h
	cc -c ../../address_map.c
route_map.o : ../../route_map.c ../../route_map.h
	cc -c ../../route_map.c
handle_event.o : ../../handle_event.c ../../handle_event.h
	cc -c ../../handle_event.c
handle_event_func.o : ../../handle_event_func.c ../../handle_event_func.h
	cc -c ../../handle_event_func.c
event.o : ../../event.c ../../event.h
	cc -c ../../event.c
.PHONY : clean
clean:
	rm test_control_traffic_light $(target)
