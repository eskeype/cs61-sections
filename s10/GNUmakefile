PROGRAMS = fork_1 fork_2 fork_3
all: $(PROGRAMS)

include ../common/rules.mk

%.o: %.c $(BUILDSTAMP)
	$(call run,$(CC) $(CFLAGS) $(DEPCFLAGS) -o $@ -c,COMPILE,$<)

$(PROGRAMS): %: %.o
	$(call run,$(CC) $(CFLAGS) -o $@ $^ -lpthread,LINK $@)

clean:
	$(call run,rm -f $(PROGRAMS) *.o *.dSYM *.core,CLEAN)

.PHONY: all clean
