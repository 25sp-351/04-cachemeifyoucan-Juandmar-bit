#ifndef LFU_CACHE_H
#define LFU_CACHE_H

typedef struct {
    int key;
    int value; 
    int frequency;
} LFU_CACHE;

void shift_elements(int index_to_delete);
int find_min_index();
void new_entry(int key, int value);
void update_values(int key, int value);
void lfu(int numbers[][2], int length);

#endif