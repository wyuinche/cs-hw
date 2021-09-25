CC=gcc
CCFLAGS=

SRCS=cache-sim.c
TARGET=cache-sim

OBJS := $(patsubst %.c,%.o,$(SRCS))

all: $(TARGET)

%.o:%.c
	$(CC) $(CCFLAGS) $< -c -o $@

$(TARGET):$(OBJS)
	$(CC) $(CCFLAGS) $^ -o $@

.PHONY=clean
.PHONY=run

run:
	./$(TARGET) $(ARGS)

clean:
	rm -f $(OBJS) $(TARGET)
