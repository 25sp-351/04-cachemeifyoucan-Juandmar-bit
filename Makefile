CC = clang
CFLANGS = -Wall -Wextra -g
EXEC = rod_cut
SRC = rod_cut.c computation.c LFU.c

all: $(EXEC)

$(EXEC): $(SRC)
		$(CC) $(CFLANGS) -o $(EXEC) $(SRC)

rebuild: clean all

run: $(EXEC)
		@echo "Running ..."
		./$(EXEC) test.txt

clean: 
		rm -f $(EXEC)