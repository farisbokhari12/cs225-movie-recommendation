EXENAME = finalproj
COMMON = fileParser.o graph.o dfs.o dijkstra.o pagerank.o
OBJS = main.o $(COMMON)
TEST_OBJS = catch/catchmain.o tests/tests.o $(COMMON)

OBJDIR = .objs

SHELL:=/bin/bash

CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -Wall -Wextra -pedantic
#CXXFLAGS += -g -O0
#CXXFLAGS += -O3
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm -fuse-ld=lld

DEBUG = false

ifeq ($(DEBUG), true)
	CXXFLAGS += -g -O0
else
	CXXFLAGS += -O3 -flto
	LDFLAGS += -flto
endif

# Custom Clang version enforcement Makefile rule:
ccred=$(shell echo -e "\033[0;31m")
ccyellow=$(shell echo -e "\033[0;33m")
ccend=$(shell echo -e "\033[0m")

IS_EWS=$(shell hostname | grep "ews.illinois.edu")
IS_CORRECT_CLANG=$(shell clang -v 2>&1 | grep "version 6")
ifneq ($(strip $(IS_EWS)),)
ifeq ($(strip $(IS_CORRECT_CLANG)),)
CLANG_VERSION_MSG = $(error $(ccred) On EWS, please run 'module load llvm/6.0.1' first when running CS225 assignments. $(ccend))
endif
else
CLANG_VERSION_MSG = $(warning $(ccyellow) Looks like you are not on EWS. Be sure to test on EWS before the deadline. $(ccend))
endif

.PHONY: all test clean output_msg remake

all : output_msg $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME): $(addprefix $(OBJDIR)/,$(OBJS))
	$(LD) $(LDFLAGS) $^ -o $(EXENAME)

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< -o $@

test: output_msg $(addprefix $(OBJDIR)/,$(TEST_OBJS))
	$(LD) $(LDFLAGS) $(addprefix $(OBJDIR)/,$(TEST_OBJS)) -o $@

clean:
	-rm -rf $(OBJDIR) $(EXENAME) test

remake: clean all
