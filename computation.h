#ifndef COMPUTATION_H
#define COMPUTATION_H

typedef struct {
    int remaining;
    int max_value;
    int *count; 
} ListOutput;

// Define a struct for items.
typedef struct {
    int length;
    int value;
} List;

int max(int a, int b);
ListOutput* storage_list(int n, int profit);
ListOutput* max_profit(int L, List pieces[], int n);
void display_cache(ListOutput *list, int n);

#endif