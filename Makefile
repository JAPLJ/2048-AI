CC=clang++
CFLAGS=-c -Wall -std=c++11 -stdlib=libc++
LDFLAGS=

SRCS=main.cpp xorshift.cpp grid.cpp montecarlo.cpp
OBJS=$(SRCS:.cpp=.o)
EXECUTABLE=2048

all: $(SRCS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
