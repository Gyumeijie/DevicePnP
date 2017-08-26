VPATH = src/  src/utility test/ 

CPPFLAGS = -I include/ -I include/utility

TEST_HASHSTR_OBJ = test_hashstr.o hashstr.o

test_hashstr: $(TEST_HASHSTR_OBJ)
	gcc  $^ -o $@
	rm -f *.o
	mv $@ ./test
run_test_hashstr:
	./test/test_hashstr
