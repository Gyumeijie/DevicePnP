VPATH = src/  src/utility test/ 

CPPFLAGS = -I include/ -I include/utility

TEST_HASHSTR_OBJ = test_hashstr.o hashstr.o

test_hashstr: $(TEST_HASHSTR_OBJ)
	gcc  $^ -o $@
	rm -f *.o
	mv $@ ./test
run_test_hashstr:
	./test/test_hashstr


TEST_DEVICE_REGISTER_OBJ = test_device_register.o hashstr.o device.o \
						   device_attrs.o device_register.o dev_t.o init.o
test_device_register: $(TEST_DEVICE_REGISTER_OBJ)
	gcc  $^ -o $@
	rm -f *.o
	mv $@ ./test
run_test_device_register:
	./test/test_device_register
