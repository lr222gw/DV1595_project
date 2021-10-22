CXX=cc
CXXFLAGS= -std=c++14 
BIN=prog
LIBFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lstdc++ -lm 

TARGET ?= ./bin/cowBingo
SRC_DIRS ?= ./MainProgram

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(addsuffix .o,$(basename $(SRCS)))
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@ $(LIBFLAGS)  $(LOADLIBES) $(LDLIBS) 
	
.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS)

-include $(DEPS)

