RM = rm -f
CC = gcc
CFLAGS = -Wall -Wextra -Wno-sign-compare -Wno-type-limits -std=c99 -Iinclude -O3 -g2
AS = fasm
ASFLAGS =
LD = gcc
LDFLAGS =
LIBS =
AR = ar
ARFLAGS = rcs

LIBOBJECTS = $(patsubst %.c,%.o,$(wildcard lib/*.c)) $(patsubst %.asm,%.o,$(wildcard lib/*.asm))
TESTS = $(patsubst tests/%,test_%,$(wildcard tests/*))

.PHONY: all clean

all: $(TESTS)

libreflection.a: $(LIBOBJECTS)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c include/reflection-typestr.h
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.asm
	$(AS) $(ASFLAGS) $< $@

include/reflection-typestr.h:
	./generate-typestr.rb > include/reflection-typestr.h

define TEST_template =
$(1): $$(patsubst %.c,%.o,$$(wildcard tests/$$(patsubst test_%,%,$(1))/*.c)) libreflection.a
	$$(LD) $$(LDFLAGS) -o $$@ $$^ $$(LIBS)
endef

$(foreach test,$(TESTS),$(eval $(call TEST_template,$(test))))

clean:
	$(RM) test.o libreflection.a $(TESTS) $(wildcard tests/*/*.o) $(LIBOBJECTS) test
