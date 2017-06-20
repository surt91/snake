OBJ 	= main.o snake.o highscore.o
TARGET	= snake
CFLAGS	= -march=native -O2 -pipe -fomit-frame-pointer
LFLAGS	= -lncurses
WARNLEVEL= -Wall

all: $(TARGET)

%.o: %.c
	$(CC) -c $(WARNLEVEL) $(CFLAGS) $< -o $@

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LFLAGS) 

clean:
	rm *.o $(TARGET)
