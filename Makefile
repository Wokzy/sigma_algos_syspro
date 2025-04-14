cc = gcc
cxx = g++
ld = g++
include_dir = ./
cflags = -std=c99 -O3 -fno-stack-limit
cxxflags = -std=c++20 -O2 -fno-stack-limit# -I$(include_dir)#-lpthread -mavx512f
# ldflags = -lm -lc# -lcrypto -lssl

all: mini_1 mini_2 mini_3 mini_4 mini_5 mini_6 mini_7 mini_8 mini_9 mini_10 mini_11 mini_12 mini_13 mini_14 mini_15 mini_16 mini_17 mini_18 mini_20 mini_21 mini_22 mini_23 mini_24 mini_25

mini_1 : mini_1.cpp
	$(cxx) $^ $(cxxflags) -o $@

mini_2 : mini_2.cpp
	$(cxx) $^ $(cxxflags) -o $@

mini_3 : mini_3.cpp
	$(cxx) $^ $(cxxflags) -o $@

mini_4 : mini_4.cpp
	$(cxx) $^ $(cxxflags) -o $@

mini_5 : mini_5.cpp
	$(cxx) $^ $(cxxflags) -o $@

mini_6 : mini_6.cpp
	$(cxx) $^ $(cxxflags) -o $@

mini_7 : mini_7.cpp
	$(cxx) $^ $(cxxflags) -o $@

mini_8 : mini_8.cpp
	$(cxx) $^ $(cxxflags) -o mini_8
	$(cxx) $^ $(cxxflags) -o mini_8_basic
	$(cxx) $^ $(cxxflags) -D SHTRASSEN -o mini_8_shtrassen

mini_9 : mini_9.cpp
	$(cxx) $^ $(cxxflags) -o $@

mini_10 : mini_10.cpp
	$(cxx) $^ $(cxxflags) -o $@

mini_11 : mini_11.cpp
	$(cxx) $^ $(cxxflags) -o $@

mini_12 : mini_12.c
	$(cc) $^ $(cflags) -o $@

mini_13 : mini_13.cpp
	$(cxx) $^ $(cxxflags) -o $@

mini_14 : mini_14.cpp
	$(cxx) $^ $(cxxflags) -o $@

mini_15 : mini_15.cpp
	$(cxx) $^ $(cxxflags) -o $@

mini_16 : mini_16.cpp
	$(cxx) $^ $(cxxflags) -o $@

mini_17 : mini_17.cpp
	$(cxx) $^ $(cxxflags) -o $@

mini_18 : mini_18.cpp
	$(cxx) $^ $(cxxflags) -o $@

mini_20 : mini_20.cpp
	$(cxx) $^ $(cxxflags) -o $@

mini_21 : mini_21.cpp
	$(cxx) $^ $(cxxflags) -o $@

mini_22 : mini_22.cpp
	$(cxx) $^ $(cxxflags) -o $@

mini_23 : mini_23.cpp
	$(cxx) $^ $(cxxflags) -o $@

mini_24 : mini_24.cpp
	$(cxx) $^ $(cxxflags) -o $@

mini_25 : mini_25.cpp
	$(cxx) $^ $(cxxflags) -o $@
