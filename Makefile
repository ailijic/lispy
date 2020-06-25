prog=lispy
src=$(wildcard *.c)
obj=$(src:.c=.o)
dep=$(obj:.o=.d)

sanitize=-fsanitize=undefined,alignment,bool,builtin,bounds,enum,$\
float-cast-overflow,float-divide-by-zero,function,$\
implicit-unsigned-integer-truncation,implicit-signed-integer-truncation,$\
implicit-integer-sign-change,integer-divide-by-zero,nonnull-attribute,null,$\
nullability-arg,nullability-assign,nullability-return,object-size,$\
pointer-overflow,return,returns-nonnull-attribute,shift,shift-base,shift-exponent,$\
signed-integer-overflow,unreachable,vla-bound

CC=clang
CFLAGS=-std=c2x -Og -ggdb -g3 -I. -Weverything $(sanitize)
LDFLAGS=-ledit -lm

all: $(prog)

$(prog): $(obj)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

-include $(dep)

mpc.o: mpc.c mpc.d mpc.h
	$(CC) -Og $(sanitize) -o $@ -c $< -Wall -Wextra -Wpedantic

%.d: %.c
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@

.PHONY: clean cleandep
clean:
	-rm -f *.o $(prog)
cleandep:
	rm -f $(dep)
