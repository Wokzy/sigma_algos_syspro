cxx = g++
ld = g++
include_dir = ./
cflags = -std=c++20 -O2 -fno-stack-limit -I$(include_dir)#-lpthread -mavx512f
# ldflags = -lm -lc# -lcrypto -lssl

all: mini_1 mini_2 mini_3 mini_4 mini_5 mini_6 mini_7 mini_8 mini_9

mini_1 : mini_1.cpp
	$(cxx) $^ $(cflags) -o $@

mini_2 : mini_2.cpp
	$(cxx) $^ $(cflags) -o $@

mini_3 : mini_3.cpp
	$(cxx) $^ $(cflags) -o $@

mini_4 : mini_4.cpp
	$(cxx) $^ $(cflags) -o $@

mini_5 : mini_5.cpp
	$(cxx) $^ $(cflags) -o $@

mini_6 : mini_6.cpp
	$(cxx) $^ $(cflags) -o $@

mini_7 : mini_7.cpp
	$(cxx) $^ $(cflags) -o $@

mini_8 : mini_8.cpp
	$(cxx) $^ $(cflags) -o mini_8
	$(cxx) $^ $(cflags) -o mini_8_basic
	$(cxx) $^ $(cflags) -D SHTRASSEN -o mini_8_shtrassen

mini_9 : mini_9.cpp
	$(cxx) $^ $(cflags) -o $@
