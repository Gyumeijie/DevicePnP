target = test_package.o package.o control_data_stream.o control_traffic_light.o traffic_light.o \
		 data_stream.o handle_data_package.o xml_parse.o relevant_struct_def.o\
	address_map.o route_map.o config_1553.o

test_package : $(target)
	cc -o test_package $(target) -lmxml -lpthread
test_control_package.o : test_package.c ../../control_data_stream.h
	cc -c test_control_data_stream.c
test_package.o : ../../package.c ../../package.h
	cc -c ../../package.c
control_data_stream.o : ../../control_data_stream.c ../../control_data_stream.h
	cc -c ../../control_data_stream.c
control_traffic_light.o : ../../control_traffic_light.c ../../control_traffic_light.h
	cc -c ../../control_traffic_light.c
traffic_light.o : ../../traffic_light.c ../../traffic_light.h
	cc -c ../../traffic_light.c
data_stream.o : ../../data_stream.c ../../data_stream.h
	cc -c ../../data_stream.c
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
config_1553.o : ../../config_1553.c ../../config_1553.h ../../handle_data_package.h ../../control_traffic_light.h
	cc -c ../../config_1553.c
.PHONY : clean
clean:
	rm test_package $(target)
