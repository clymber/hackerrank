# Makefile
#    compile every C/C++ source file into an executable

# Custom Command
CC	:= gcc# C Complier Command
CXX	:= c++# C++ Complier command
RM	:= rm -f

# Custom Options and Flags
CFLAGS	+= -Wall
CXXFLAGS += $(CFLAGS) -std=c++17
CPPFLAGS +=
LDFLAGS +=

# Depended Library that Already Existed
LDLIBS := # -lgmock

# File lists
sources := $(wildcard *.c *.cpp)
TARGET := $(subst .c,.app,$(subst .cpp,.app,${sources}))

# Makefile targets
.PHONY: all clean make_debug
all: $(TARGET)

clean:
	$(if $(wildcard $(TARGET)),$(RM) $(TARGET),)

make_debug:
	# Source files      # sources: $(sources)
	# Building targets  # TARGET: $(TARGET)
	# C complier        # CC: $(CC)
	# C compiler flags  # CFLAGS: $(CFLAGS)
	# C++ compiler      # CXX: $(CXX)
	# C++ compiler flags# CXXFLAGS: $(CXXFLAGS)
	# Linker options    # LDFLAGS: $(LDFLAGS)
	# Linking libraries # LDLIBS: $(LDLIBS)


# Makefile rules
%.app: %.cpp
	$(CXX) $^ $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o $@

%.app: %.c
	$(CC) $^ $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $@
