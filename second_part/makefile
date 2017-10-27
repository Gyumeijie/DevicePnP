vpath %.c ./src/
vpath %.c ./src/app/
vpath %.c ./src/RT/
vpath %.h ./include/
vpath %.h ./include/app/
vpath %.h ./include/RT/

CCFLAGS = -I ./include -I ./include/app/ -I ./include/RT/ -DDEBUG
ENDFALGS = -lmxml -lpthread
CC = cc 
OBJ = main.o manage_transport_center.o app.o my_socket.o package.o \
		 control_package.o control_data_stream.o control_traffic_light.o traffic_light.o \
		 data_stream.o handle_data_package.o xml_parse.o relevant_struct_def.o \
		 address_map.o route_map.o config_1553.o handle_event.o event.o handle_event_func.o \
		 my_RT_socket.o RT_control.o 

main : $(OBJ)
	$(CC) -o main $(OBJ) $(ENDFALGS)
	mv *.o ./obj/
$(OBJ): %.o: %.c
	cc -c $(CCFLAGS) $< -o $@

.PHONY : clean
clean:
	rm main ./obj/*.o
