PROGRAMS = \
	test-add-1 $(patsubst %.s,test-%,$(wildcard add-[2-9].s)) \
	test-udiv-1 $(patsubst %.s,test-%,$(wildcard udiv-[2-9].s)) \
	test-max-1 $(patsubst %.s,test-%,$(wildcard max-[2-9].s)) \
	test-factorial-1 $(patsubst %.s,test-%,$(wildcard factorial-[2-9].s)) \
	test-swap-1 $(patsubst %.s,test-%,$(wildcard swap-[2-9].s)) \
	test-bzero8-1 $(patsubst %.s,test-%,$(wildcard bzero8-[2-9].s)) \
	test-traverse-1 $(patsubst %.s,test-%,$(wildcard traverse-[2-9].s))
all: $(PROGRAMS)

O = 1
include ../common/rules.mk

%-1.s: %.c $(BUILDSTAMP)
	@ARGS=$$(grep '^//!' $< | sed 's/.*! *//'); \
	  CFLAGS="$(filter-out -g,$(CFLAGS))"; \
	  if test -z "$$ARGS"; then ARGS="$(O)"; fi; \
	  $(call xrun,$(CC) $$CFLAGS $$ARGS -o $@ -S $<,COMPILE -S $$ARGS $< > $@) && { $(call cleanasm,$@); }

%.s.o: %.s $(BUILDSTAMP)
	@$(call xrun,$(CC) $(O) -o $@ -c $<,ASSEMBLE $<)

%.o: %.c $(BUILDSTAMP)
	@$(call xrun,$(CC) $(CFLAGS) $(O) $(DEPCFLAGS) -o $@ -c $<,COMPILE $<)

test-%-1: test-%.o %-1.s.o
	@$(call xrun,$(CC) $(CFLAGS) $(O) -o $@ $^,LINK $^ > $@)

test-%-2: test-%.o %-2.s.o
	@$(call xrun,$(CC) $(CFLAGS) $(O) -o $@ $^,LINK $^ > $@)

test-%-3: test-%.o %-3.s.o
	@$(call xrun,$(CC) $(CFLAGS) $(O) -o $@ $^,LINK $^ > $@)

test-%-4: test-%.o %-4.s.o
	@$(call xrun,$(CC) $(CFLAGS) $(O) -o $@ $^,LINK $^ > $@)

test-%-5: test-%.o %-5.s.o
	@$(call xrun,$(CC) $(CFLAGS) $(O) -o $@ $^,LINK $^ > $@)

test-%-6: test-%.o %-6.s.o
	@$(call xrun,$(CC) $(CFLAGS) $(O) -o $@ $^,LINK $^ > $@)


.PRECIOUS: %-1.s
.PRECIOUS: %.s.o

clean:
	rm -f *.o *-1.s *-1.s.o $(PROGRAMS) *.unsafe *.safe *.core
	rm -rf $(DEPSDIR) *.dSYM

.PHONY: all clean
