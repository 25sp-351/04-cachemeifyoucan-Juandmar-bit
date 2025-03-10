#ifndef LRU_CACHE_H
#define LRU_CACHE_H

typedef struct {
    int key;            
    int value;
    //int timestamp;      
} LRU_CACHE;

int find_LUF_index();
void new_entry(int key, int length, int price);
void get_cache(int key);


#endif