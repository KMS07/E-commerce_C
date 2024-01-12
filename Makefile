CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Objects files to be generated 
OBJ = main.o skimplementation.o buyerimplementation.o

# Executable file name
EXEC = myprogram

# rule for generating the executable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

# Rule for compiling main.c
main.o: main.c buyer.h shopkeeper.h
	$(CC) $(CFLAGS) -c main.c

# Rule for compiling skimplementation.c
skimplementation.o: skimplementation.c shopkeeper.h
	$(CC) $(CFLAGS) -c skimplementation.c

buyerimplementation.o: buyerimplementation.c buyer.h
	$(CC) $(CFLAGS) -c buyerimplementation.c

# Clean rule to remove object files and executable
clean:
	rm -f $(EXEC) $(OBJ)