DEBUG=0

CC=gcc

FLAGS=-pipe
CFLAGS=$(FLAGS)
LDFLAGS=$(FLAGS)
ifeq ($(DEBUG),1)
	FLAGS+=-g
	CFLAGS+=-Wall -g
else
	CFLAGS+=-O2
	LDFLAGS+=-s
endif
LIBS=

OBJS=rtl_reader.o

ADD_FLAGS=
ADD_CFLAGS=
ADD_LDFLAGS=
FLAGS+=$(ADD_FLAGS)
CFLAGS+=$(ADD_CFLAGS)
LDFLAGS+=$(ADD_LDFLAGS)

BIN=rtl_reader

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(BIN) $(LIBS)

clean:
	$(RM) $(OBJS) $(BIN)

.PHONY: clean
