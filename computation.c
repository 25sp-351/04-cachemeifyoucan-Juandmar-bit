#include <stdio.h>
#include <stdlib.h>
#include "LFU.h"
#include "computation.h"

LFU cache[MAX_CACHE]; // Array to store the LFU pages

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
   
    LFU *cached = get_cache(L);
    if (cached != NULL) {
        ListOutput *copy = storage_list(n, cached->max_value);
        for (int i = 0; i < n; i++) {
            if (cached->values[i].count != NULL)
                copy->count[i] = *(cached->values[i].count);
        }
        return copy;
    }

    // 2. Base case
    if (L == 0)
        return storage_list(n, 0);

    // 3. Recursive computation
    ListOutput *best = storage_list(n, 0);
    for (int i = 0; i < n; i++) {
        if (pieces[i].length <= L) {
            ListOutput *temp = max_profit(L - pieces[i].length, pieces, n);
            int current_profit = temp->max_value + pieces[i].value;

            if (current_profit > best->max_value) {
                free(best->count);
                free(best);

                best = storage_list(n, current_profit);
                for (int j = 0; j < n; j++)
                    best->count[j] = temp->count[j];
                best->count[i]++;
            }

            free(temp->count);
            free(temp);
        }
    }

    LFU entry;
    entry.key = L;
    entry.max_value = best->max_value;
    entry.frequency = 1;

    for (int i = 0; i < n; i++) {
        entry.values[i].length = pieces[i].length;
        entry.values[i].value = pieces[i].value;
        entry.values[i].count = malloc(sizeof(int));
        *(entry.values[i].count) = best->count[i];
    }

    put_in_cache(entry, n);

    return best;
}