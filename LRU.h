#ifndef LRU_H
#define LRU_H

#define MAX_CACHE 100
#define MAX_PIECES 10

typedef struct {
    int length;
    int value;
    int *count;
} Values;

typedef struct {
    int key;
    Values values[MAX_PIECES];
    int max_value;
    int last_accessed; 
} LRU;

LRU *get_cache(int key);
void put_in_cache(LRU entry, int n);
void free_existing_entry(int index);

#endif