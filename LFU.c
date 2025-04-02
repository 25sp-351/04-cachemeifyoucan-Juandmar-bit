#include <stdio.h>
#include <stdlib.h>
#include "LFU.h"

LFU cache[MAX_CACHE]; // Array to store the LFU pages
int cache_size = 0; // Number of elements in the cache

int find_min_index() {
    // Replace least frequently used
    int min_index = 0;
    for (int i = 1; i < cache_size; i++) {
        if (cache[i].frequency < cache[min_index].frequency)
            min_index = i;
    }
    return min_index;
}

void free_old (int min_index) {
    // Free the old LFU page
    for (int j = 0; j < MAX_PIECES; j++) {
        if (cache[min_index].values[j].count != NULL) {
            free(cache[min_index].values[j].count);
        }
    }
}

LFU* get_cache(int key) {
    // Check if the item is in the cache
    for (int i = 0; i < MAX_CACHE; i++) {
        if (cache[i].key == key) {
            cache[i].frequency++;
            return &cache[i];
            return &cache[i];
        }
    }
    return NULL;  
}

void put_in_cache(LFU piece, int n) {
    // Check if already in cache
    for (int i = 0; i < cache_size; i++) {
        if (cache[i].key == piece.key) {
            // Free inner counts
            for (int j = 0; j < MAX_PIECES; j++) {
                if (cache[i].values[j].count != NULL) {
                    free(cache[i].values[j].count);
                    cache[i].values[j].count = NULL;
                }
            }

            // Copy new piece
            cache[i].key = piece.key;
            cache[i].max_value = piece.max_value;
            cache[i].frequency++;
            for (int j = 0; j < n; j++) {
                cache[i].values[j].length = piece.values[j].length;
                cache[i].values[j].value = piece.values[j].value;
                cache[i].values[j].count = malloc(sizeof(int));
                *(cache[i].values[j].count) = *(piece.values[j].count);
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
        for (int j = 0; j < n; j++) {
            dest->values[j].length = piece.values[j].length;
            dest->values[j].value = piece.values[j].value;
            dest->values[j].count = malloc(sizeof(int));
            *(dest->values[j].count) = *(piece.values[j].count);
        }
        return;
    }

    int min_index = find_min_index();

    free_old(min_index);

    // Deep copy into evicted slot
    cache[min_index].key = piece.key;
    cache[min_index].max_value = piece.max_value;
    cache[min_index].frequency = 1;
    for (int j = 0; j < n; j++) {
        cache[min_index].values[j].length = piece.values[j].length;
        cache[min_index].values[j].value = piece.values[j].value;
        cache[min_index].values[j].count = malloc(sizeof(int));
        *(cache[min_index].values[j].count) = *(piece.values[j].count);
    }
}
