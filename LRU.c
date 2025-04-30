#include <stdio.h>
#include <stdlib.h>
#include "LRU.h"

LRU cache[MAX_CACHE];
int cache_size = 0; 
int access_counter = 0;

void free_existing_entry(int index) {
    for (int j = 0; j < MAX_PIECES; j++) {
        if (cache[index].values[j].count != NULL) {
            free(cache[index].values[j].count);
            cache[index].values[j].count = NULL;
        }
    }
}

LRU* get_cache(int key) {
    // Check if the item is in the cache
    for (int xx = 0; xx < MAX_CACHE; xx++) {
        if (cache[xx].key == key) {
            cache[xx].last_accessed = access_counter++;
            return &cache[xx];
        }
    }
    return NULL;  
}

void put_in_cache(LRU entry, int n) {
    entry.last_accessed = access_counter++;

    // Check if already in cache
    for (int i = 0; i < cache_size; i++) {
        if (cache[i].key == entry.key) {
            free_existing_entry(i);
            cache[i] = entry;
            return;
        }
    }

    // If not full, add
    if (cache_size < MAX_CACHE) {
        cache[cache_size++] = entry;
        return;
    }

    // Find least recently used
    int lru_index = 0;
    for (int i = 1; i < cache_size; i++) {
        if (cache[i].last_accessed < cache[lru_index].last_accessed) {
            lru_index = i;
        }
    }
    cache[lru_index] = entry;
}