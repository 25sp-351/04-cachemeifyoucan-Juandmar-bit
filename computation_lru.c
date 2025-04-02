#include <stdio.h>
#include <stdlib.h>
#include "LRU.h"
#include "computation_lru.h"

LRU cache[MAX_CACHE]; // Array to store the LFU pages

// return the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

ListOutput* storage_list(int n, int profit) {
    ListOutput *list = malloc(sizeof(ListOutput));
    if (!list) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    list->max_value = profit;

    list->count = calloc(n, sizeof(int));
    if (!list->count) {
        fprintf(stderr, "Memory allocation failed\n");
        free(list);
        exit(EXIT_FAILURE);
    }
    return list;
}

ListOutput* max_profit(int L, List pieces[], int n) {

    LRU *cached = get_cache(L);
    if (cached != NULL) {
        ListOutput *copy = storage_list(n, cached->max_value);
        for (int xx = 0; xx < n; xx++) {
            if (cached->values[xx].count != NULL)
                copy->count[xx] = *(cached->values[xx].count);
        }
        return copy;
    }

    if (L == 0){
        return storage_list(n, 0);
    }

    ListOutput *best = storage_list(n, 0);
    for (int xx = 0; xx < n; xx++) {
        if (pieces[xx].length <= L) {
            ListOutput *temp = max_profit(L - pieces[xx].length, pieces, n);
            int current_profit = temp->max_value + pieces[xx].value;

            if (current_profit > best->max_value) {
                free(best->count);
                free(best);

                best = storage_list(n, current_profit);
                for (int yy = 0; yy < n; yy++)
                    best->count[yy] = temp->count[yy];
                best->count[xx]++;
            }

            free(temp->count);
            free(temp);
        }
    }

    LRU entry;
    entry.key = L;
    entry.max_value = best->max_value;
    entry.last_accessed = 1;

    for (int xx = 0; xx < n; xx++) {
        entry.values[xx].length = pieces[xx].length;
        entry.values[xx].value = pieces[xx].value;
        entry.values[xx].count = malloc(sizeof(int));
        *(entry.values[xx].count) = best->count[xx];
    }

    put_in_cache(entry, n);

    return best;
}