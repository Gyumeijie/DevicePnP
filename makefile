VPATH = src/  src/utility src/interpreter src/drivers  test/ 

CPPFLAGS = -I include/ -I include/utility -I include/drivers \
		   -I include/interpreter --std=c99  -DDEBUG

TEST_DEVICE_OPEN_OBJ  = test_device_open.o driver.o driver_register.o \
					   driver_bind.o driver_loaders.o dev_t.o hashstr.o \
					   init.o device.o driver_match.o config_info_collect.o \
					   load_xml.o gyroscope_match.o  gyroscope_driver.o \
					   device_register.o XmlParser.o analogsunsensor.o \
					   device_open.o gyroscope.o analogsunsensor_match.o \
					   magnetometer.o magnetometer_driver.o magnetometer_match.o \
					   magnetorquer.o magnetorquer_driver.o magnetorquer_match.o \
                       analogsunsensor_driver.o adda_operation.o error_report.o \
                       flywheel_driver.o flywheel.o flywheel_match.o \
					   parameter_package.o command_sequence_generate.o miscellaneous.o\
					   bytes_array_assembly.o driver_supported_interface.o\
					   flywheel_receive.o flywheel_set_speed.o flywheel_open.o\
					   magnetometer_getx.o magnetometer_gety.o magnetometer_getz.o\
					   magnetometer_open.o magnetometer_read_helper.o\
					   magnetometer_getxyz.o\
					   magnetorquer_open.o magnetorquer_setx.o magnetorquer_sety.o\
					   magnetorquer_setz.o magnetorquer_setxyz.o\
					   magnetorquer_write_helper.o\
                       analogsunsensor_open.o analogsunsensor_read.o\
                       analogsunsensor_read_helper.o\
					   gyroscope_open.o  gyroscope_getx.o  gyroscope_gety.o\
					   gyroscope_getz.o  gyroscope_getxyz.o\
                       gyroscope_read_helper.o gyroscope_write_helper.o\
                       fill_plain_struct.o fill_plain_array.o\
                       fill_register_array.o fill_command_sequence.o\
                       fill_bytes_array_assembly_scheme.o\
                       lex.o parser.o executor.o dependency.o relocation.o\
                       interpreter.o collect_code_block.o type_converter.o\
                       data_template_fetch.o\
                  

test_device_open: $(TEST_DEVICE_OPEN_OBJ)
	gcc -pedantic -W  -g $^ -lmxml -lpthread -o $@ 
	rm -f *.o
	mv $@ ./test
