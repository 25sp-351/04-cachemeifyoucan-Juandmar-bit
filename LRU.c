#include <stdio.h>
#include <stdlib.h>
#include "LRU.h"

LRU cache[MAX_CACHE]; // Array to store the LFU pages
int cache_size = 0; // Number of elements in the cache
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
            printf("[LRU] Cache HIT for rod length %d (last_used: %d)\n", key, cache[xx].last_accessed);
            cache[xx].last_accessed = access_counter++;
            return &cache[xx];
        }
    }
    printf("[LRU] Cache MISS for rod length %d\n", key);
    return NULL;  
}

void put_in_cache(LRU entry, int n) {
    entry.last_accessed = access_counter++;

    // Check if already in cache
    for (int i = 0; i < cache_size; i++) {
        if (cache[i].key == entry.key) {
            free_existing_entry(i);  // if needed
            printf("[LRU] Updating existing cache entry for %d\n", entry.key);
            free_existing_entry(i);
            cache[i] = entry;
            return;
        }
    }

    // If not full, add
    if (cache_size < MAX_CACHE) {
        printf("[LRU] Inserting new entry for %d\n", entry.key);
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
    printf("[LRU] Cache FULL: Replacing LRU entry (key: %d, last_used: %d) with new key %d\n",
           cache[lru_index].key, cache[lru_index].last_accessed, entry.key);


    free_existing_entry(lru_index);  // if needed
    cache[lru_index] = entry;
}