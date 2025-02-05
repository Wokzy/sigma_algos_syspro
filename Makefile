cxx = g++
ld = g++
include_dir = ./
cflags = -std=c++20 -O2 -fno-stack-limit -I$(include_dir)#-lpthread -mavx512f
# ldflags = -lm -lc# -lcrypto -lssl

all: mini_1 mini_2 mini_3

mini_1 : mini_1.cpp
	$(cxx) $^ $(cflags) -o $@

mini_2 : mini_2.cpp
	$(cxx) $^ $(cflags) -o $@

mini_3 : mini_3.cpp
	$(cxx) $^ $(cflags) -o $@
