VPATH = src/  src/utility  src/drivers  test/ 

CPPFLAGS = -I include/ -I include/utility -I include/drivers --std=c99  -DDEBUG

TEST_DEVICE_OPEN_OBJ  = test_device_open.o driver.o driver_register.o \
					   driver_bind.o driver_loaders.o dev_t.o hashstr.o \
					   init.o device.o driver_match.o config_info_collect.o \
					   load_xml.o gyroscope_match.o  gyroscope_driver.o \
					   device_register.o XmlParser.o analogsunsensor.o \
					   device_open.o gyroscope.o analogsunsensor_match.o \
                       analogsunsensor_driver.o adda_operation.o error_report.o
                  

test_device_open: $(TEST_DEVICE_OPEN_OBJ)
	gcc -g $^ -lmxml -lpthread -o $@
	rm -f *.o
	mv $@ ./test
