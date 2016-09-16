OBJ 	= main.o snake.o highscore.o
TARGET	= snake
LINK	= gcc
CC		= gcc
CFLAGS	= -march=native -O2 -pipe -fomit-frame-pointer
LFLAGS	= -lncurses
#~ WARNLEVEL= -Wall -pedantic
WARNLEVEL= -Wall

all: $(TARGET)

%.o: %.c
	$(CC) -c $(WARNLEVEL) $(CFLAGS) $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(LFLAGS) -o $(TARGET) $(OBJ)

clean:
	rm *.o $(TARGET)
