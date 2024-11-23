CC = gcc 
TARGET = $(basename $(SRC))
all:
	gcc -o $(TARGET) $(SRC)
allthread:
	gcc -o $(TARGET) $(SRC) -pthread
clean:
	rf -f $(TARGET)
