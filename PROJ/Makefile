# Makefile for SYSTEM SECURITY Project
#

# Intermediate target lists.
obj = $(addprefix out/,array.o list.o map.o memprofile.o global.o subst.o)

# Variables for build settings.
includes = -I.
ifeq ($(shell uname -s), Darwin)
	cflags = $(includes) -std=c99
else
	cflags = $(includes) -std=c99 -D _BSD_SOURCE -D _GNU_SOURCE
endif
cc = cc $(cflags)

# Primary targets.
all: $(obj) proj

proj: proj.c  $(obj)
	$(cc)  proj.c -g -o proj -lreadline $(obj)

clean:
	rm -rf out rm proj

# Internal rules; meant to only be used indirectly by the above rules.

out:
	mkdir -p out

out/global.o : ed2/global.c ed2/global.h | out
	$(cc) -o $@ -c $<

out/subst.o : ed2/subst.c ed2/subst.h | out
	$(cc) -o $@ -c $<

out/%.o : ed2/cstructs/%.c ed2/cstructs/%.h | out
	$(cc) -o $@ -c $<

# Listing this special-name rule prevents the deletion of intermediate files.
.SECONDARY:

