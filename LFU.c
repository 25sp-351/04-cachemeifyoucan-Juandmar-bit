#include <stdio.h>
#include <stdlib.h>
#include "LFU.h"

LFU cache[MAX_CACHE]; // Array to store the LFU pages
int cache_size = 0; // Number of elements in the cache

int find_min_index() {
    // Replace least frequently used
    int min_index = 0;
    for (int xx = 1; xx < cache_size; xx++) {
        if (cache[xx].frequency < cache[min_index].frequency)
            min_index = xx;
    }
    return min_index;
}

void free_old (int min_index) {
    // Free the old LFU page
    for (int xx = 0; xx < MAX_PIECES; xx++) {
        if (cache[min_index].values[xx].count != NULL) {
            free(cache[min_index].values[xx].count);
        }
    }
}

LFU* get_cache(int key) {
    // Check if the item is in the cache
    for (int xx = 0; xx < MAX_CACHE; xx++) {
        if (cache[xx].key == key) {
            cache[xx].frequency++;
            return &cache[xx];
            return &cache[xx];
        }
    }
    return NULL;  
}

void put_in_cache(LFU piece, int n) {
    // Check if already in cache
    for (int xx = 0; xx < cache_size; xx++) {
        if (cache[xx].key == piece.key) {
            // Free inner counts
            for (int j = 0; j < MAX_PIECES; j++) {
                if (cache[xx].values[j].count != NULL) {
                    free(cache[xx].values[j].count);
                    cache[xx].values[j].count = NULL;
                }
            }

            // Copy new piece
            cache[xx].key = piece.key;
            cache[xx].max_value = piece.max_value;
            cache[xx].frequency++;
            for (int j = 0; j < n; j++) {
                cache[xx].values[j].length = piece.values[j].length;
                cache[xx].values[j].value = piece.values[j].value;
                cache[xx].values[j].count = malloc(sizeof(int));
                *(cache[xx].values[j].count) = *(piece.values[j].count);
            }
            return;
        }
    }

    // Add if not full
    if (cache_size < MAX_CACHE) {
        piece.frequency = 1;
        LFU *dest = &cache[cache_size++];
        dest->key = piece.key;
        dest->max_value = piece.max_value;
        dest->frequency = piece.frequency;
        for (int xx = 0; xx < n; xx++) {
            dest->values[xx].length = piece.values[xx].length;
            dest->values[xx].value = piece.values[xx].value;
            dest->values[xx].count = malloc(sizeof(int));
            *(dest->values[xx].count) = *(piece.values[xx].count);
        }
        return;
    }

    int min_index = find_min_index();

    free_old(min_index);

    // Deep copy into evicted slot
    cache[min_index].key = piece.key;
    cache[min_index].max_value = piece.max_value;
    cache[min_index].frequency = 1;
    for (int xx = 0; xx < n; xx++) {
        cache[min_index].values[xx].length = piece.values[xx].length;
        cache[min_index].values[xx].value = piece.values[xx].value;
        cache[min_index].values[xx].count = malloc(sizeof(int));
        *(cache[min_index].values[xx].count) = *(piece.values[xx].count);
    }
}
