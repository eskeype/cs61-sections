PROGRAMS = memsetbench traversebench memset-1 memset-2 memset-3
all: $(PROGRAMS)

O = 1
include ../common/rules.mk

GPROF_CFLAGS := $(UNOPT_CFLAGS) -pg

%.o: %.c $(BUILDSTAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(O) $(DEPCFLAGS) -o $@ -c $<

memsets.o: %.o: %.c $(BUILDSTAMP)
	$(CC) $(CPPFLAGS) $(CFLAGS) -O1 -ffreestanding -fno-unroll-loops $(DEPCFLAGS) -o $@ -c $<

memsetbench: memsetbench.o memsets.o
	$(CC) $(CFLAGS) $(O) -o $@ $^

traversebench: traversebench.o
	$(CC) $(CFLAGS) $(O) -o $@ $^

memset-%: memset-%.o test-memset.c
	$(CC) $(CFLAGS) $(O) -o $@ $^

perf-%: memset-%
	sudo perf stat ./$<

gprof-%.o: %.c $(BUILDSTAMP)
	$(CC) $(GPROF_CFLAGS) $(O) $(DEPCFLAGS) -o $@ -c $<

gprof-%: gprof-memset-%.o test-memset.c
	$(CC) $(GPROF_CFLAGS) $(O) -o memset-$* $^
	./memset-$*
	gprof ./memset-$*

clean:
	rm -f *.out *.o $(PROGRAMS)
	rm -rf $(DEPSDIR) *.dSYM

.PHONY: all clean
.PRECIOUS: %.s
