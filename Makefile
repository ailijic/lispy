prog=lispy
src=$(wildcard *.c)
obj=$(src:.c=.o)
dep=$(obj:.o=.d)

CC=clang
CFLAGS=-std=c2x -Og -ggdb -g3 -I. -Weverything
LDFLAGS=-ledit

all: $(prog)

$(prog): $(obj)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

-include $(dep)

%.d: %.c
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@

%.o: %.c %.h

.PHONY: clean cleandep
clean:
	-rm -f *.o $(prog)
cleandep:
	rm -f $(dep)
