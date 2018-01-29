1. First change directory to 'scripts' and run `make` to comiple source code; 

2. Then change directory to 'test' and run `qemu-system-sparc -M leon3_generic -m 64M -kernel test_device_open -nographic`
to load object file into qemu simulator.
