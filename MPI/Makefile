# Makefile for compiling and running MPI programs

CC = mpicc
CFLAGS = -Wall 

SRC_FILES = Day00/ex01.cc

SRCS = $(wildcard %.cc $(wildcard */*.cc))

OBJS = $(patsubst %.cc, $(BUILD_DIR)/%.o, $(SRCS))

BUILD_DIR = build

SUBDIRS := $(sort $(dir $(OBJS)))

$(shell mkdir -p $(SUBDIRS))

all: $(OBJS) 
	@echo "Usage: make run $(ARGS) [NP=<number of processes>]"

run: $(BUILD_DIR)
	mpiexec ./$(BUILD_DIR)/$(FILE)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.cc
	@$(CC) $(CFLAGS) -o $@ $<

clean:
	@rm -rf $(BUILD_DIR)
