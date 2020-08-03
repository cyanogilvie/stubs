#!/bin/sh -e

#TCLDIR=/home/cyan/local8.7_valgrind/lib
#FLAGS="--with-tcl=$TCLDIR --prefix=/tmp/stubs --exec-prefix=/tmp/stubs --enable-symbols=mem --enable-shared --enable-threads --enable-64bit"
#CFLAGS="-O0 -DPURIFY"
#TARGET="valgrind"

TCLDIR=/home/cyan/local8.7/lib
FLAGS="--with-tcl=$TCLDIR --prefix=/tmp/stubs --exec-prefix=/tmp/stubs --enable-symbols --enable-shared --enable-threads --enable-64bit"
CFLAGS="-O3 -march=native"
TARGET="test"

#TCLDIR=/home/cyan/local/lib
#FLAGS="--with-tcl=$TCLDIR --prefix=/tmp/stubs --exec-prefix=/tmp/stubs --enable-symbols --enable-shared --enable-threads --enable-64bit"
#CFLAGS="-O3 -march=native"
#TARGET="test"

export CFLAGS

test -e /tmp/stubs && rm -r /tmp/stubs

(
cd exa
autoconf &&
	./configure $FLAGS &&
	make genstubs clean all install

find /tmp/stubs -ls
cat /tmp/stubs/lib/exa0.1/exaConfig.sh
)

# Using exa's stubs, pointing at build location
(
cd exb
autoconf &&
	./configure $FLAGS --with-exa=../exa &&
	make clean all $TARGET
)

# Using exa's stubs, pointing at install location
(
cd exb
autoconf &&
	./configure $FLAGS --with-exa=/tmp/stubs/lib/exa0.1 &&
	make clean all $TARGET
)
