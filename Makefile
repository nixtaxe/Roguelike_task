PROJECT = roguelike
BUILD   = g++
MAKEDIR = mkdir
REMOVE = rm -rf

DBGFLAGS = -g
CFLAGS  = -c
#-I.\include
LDFLAGS = -lncurses

SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:%.cpp=%.o)
OUT_DIR = .
OUTPUT  = -o ./$(OUT_DIR)/$(PROJECT)
.PHONY: build debug clean

all: build clean

debug: CFLAGS += $(DBGFLAGS)
debug: build

build: $(PROJECT)

$(OUT_DIR):
	$(MAKEDIR) $(OUT_DIR)

$(PROJECT): $(OBJECTS)
	$(BUILD) $(OUTPUT) $(OBJECTS) $(LDFLAGS)

%.o: %.cpp
	$(BUILD) $(CFLAGS) $< -o $@

clean:
	$(REMOVE) *.o
