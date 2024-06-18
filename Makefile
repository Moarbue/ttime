CC = clang
CFLAGS = -Wall -Wextra -O3
BIN=ttime
SRC=main.c

.PHONY: all clean

all: $(BIN)

$(BIN):
	$(CC) $(CFLAGS) -o $(BIN) $(SRC)

clean:
	rm -f $(BIN)
