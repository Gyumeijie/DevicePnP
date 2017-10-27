target = test_event.o handle_event.o handle_data_package.o handle_event_func.o event.o  xml_parse.o route_map.o relevant_struct_def.o

test_event : $(target)
	cc -o test_event $(target) -lmxml -lpthread
test_event.o : test_event.c ../../handle_event.h
	cc -c test_event.c
handle_event.o : ../../handle_event.c ../../handle_event.h
	cc -c ../../handle_event.c
handle_event_func.o : ../../handle_event_func.c ../../handle_event_func.h
	cc -c ../../handle_event_func.c
event.o : ../../event.c ../../event.h
	cc -c ../../event.c
handle_data_package.o : ../../handle_data_package.c ../../handle_data_package.h
	cc -c ../../handle_data_package.c
xml_parse.o : ../../xml_parse.c ../../xml_parse.h
	cc -c ../../xml_parse.c
route_map.o : ../../route_map.c ../../route_map.h
	cc -c ../../route_map.c
relevant_struct_def.o : ../../relevant_struct_def.c ../../relevant_struct_def.h
	cc -c ../../relevant_struct_def.c
.PHONY : clean
clean:
	rm test_event $(target)
