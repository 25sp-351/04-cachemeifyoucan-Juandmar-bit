CC = clang
CFLAGS = -Wall -Wextra -g

EXEC_LFU = rod_cut_lfu
SRC_LFU = rod_cut_lfu.c computation_lfu.c LFU.c

EXEC_LRU = rod_cut_lru
SRC_LRU = rod_cut_lru.c computation_lru.c LRU.c

EXEC = $(EXEC_LFU) $(EXEC_LRU)

all: $(EXEC_LFU) $(EXEC_LRU)

$(EXEC_LFU): $(SRC_LFU)
		$(CC) $(CFLANGS) -o $(EXEC_LFU) $(SRC_LFU)
	
$(EXEC_LRU): $(SRC_LRU)
		$(CC) $(CFLANGS) -o $(EXEC_LRU) $(SRC_LRU)

rebuild: clean all

run: $(EXEC)
		@echo "Running ..."
		./$(EXEC_LFU) test.txt
		./$(EXEC_LRU) test.txt

clean: 
		rm -f $(EXEC)