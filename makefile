VPATH = src/  src/utility  src/drivers  test/ 

CPPFLAGS = -I include/ -I include/utility -I include/drivers -DDEBUG

TEST_DRIVER_REGISTER_OBJ = test_driver_register.o driver.o driver_register.o \
						   driver_loaders.o dev_t.o hashstr.o init.o device.o \
						   driver_match.o xml_operation.o gyroscope_match.o \
						   gyroscope_driver.o analogsunsensor_driver.o \
						   analogsunsensor_match.o adda_operation.o

test_driver_register: $(TEST_DRIVER_REGISTER_OBJ)
	gcc  $^ -lmxml -lpthread -o $@
	rm -f *.o
	mv $@ ./test
