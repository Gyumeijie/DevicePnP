VPATH = src/  src/utility  src/drivers  test/ 

CPPFLAGS = -I include/ -I include/utility -I include/drivers -DDEBUG

TEST_DEVICE_OPEN_OBJ = test_device_open.o driver.o driver_register.o \
					   driver_bind.o driver_loaders.o dev_t.o hashstr.o \
					   init.o device.o driver_match.o xml_operation.o \
					   gyroscope_match.o  gyroscope_driver.o \
					   analogsunsensor_driver.o analogsunsensor_match.o \
					   device_register.o device_attrs.o adda_operation.o \
					   device_open.o gyroscope.o analogsunsensor.o

test_device_open: $(TEST_DEVICE_OPEN_OBJ)
	gcc  $^ -lmxml -lpthread -o $@
	rm -f *.o
	mv $@ ./test
