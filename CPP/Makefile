# Makefile
#    compile every C/C++ source file into an executable

# Custom Command
CC := g++
GCC:= gcc
RM := rm -f

# Custom Options and Flags
OUTPUT_OPTION = -o $@
CFLAGS        += -Wall -DMACOS -D_DARWIN_C_SOURCE
CXXFLAGS      += -std=c++20
LDFLAGS       +=


# Depended Library that Already Existed
LDLIBS := # -lgmock

# File lists
sources := $(wildcard *.c, *.cpp)
TARGET := $(subst .c,.app,$(subst .cpp,.app,${sources}))

# Makefile targets
.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	$(RM) $(TARGET)

# Makefile rules
%.app: %.cpp
	$(CC) $(OUTPUT_OPTION) $(TARGET_ARCH) $(CFLAGS) $(CXXFLAGS) $^ $(LDFLAGS) $(LDLIBS) $(LOADLIBES)
%.app: %.c
	$(GCC) $(OUTPUT_OPTION) $(TARGET_ARCH) $(CFLAGS) $^ $(LDFLAGS) $(LDLIBS) $(LOADLIBES)
