#include <stdio.h>
#include "lfu_cache.h"

#define CAPACITY 5 

LFU_CACHE pages[CAPACITY];
int SIZE = 0;

void shift_elements(int index_to_delete) {
    if (index_to_delete != -1) {
        for (int xx = index_to_delete; xx < CAPACITY; xx++) {
            pages[xx].key = pages[xx + 1].key;
            pages[xx].size = pages[xx + 1].size;
            pages[xx].value = pages[xx + 1].value;
            pages[xx].counter = pages[xx + 1].counter;
            pages[xx].frequency = pages[xx + 1].frequency;
        }
        SIZE--;  
    }
}

int find_min_index() {

    int min_index = 0; 

    for (int xx = 1; xx < CAPACITY; xx++) {
        if (pages[xx].frequency < pages[min_index].frequency) {
            min_index = xx;
        }
    }
    return min_index;
}

void new_entry(int key, int size, int value, int counter) {
    if (SIZE < CAPACITY) {
        pages[SIZE].key = key;
        pages[SIZE].size = size;
        pages[SIZE].value = value; 
        pages[SIZE].counter = counter;
        pages[SIZE].frequency = 1;
        SIZE++;  
    }
    else{  
        int min_index = find_min_index(); 
        shift_elements(min_index);
        pages[SIZE].key = key; 
        pages[SIZE].size = size; 
        pages[SIZE].value = value; 
        pages[SIZE].counter = counter;
        pages[SIZE].frequency = 1;
        SIZE++;

    }
}

void get_values(int key, int size, int value, int counter) {
    for (int xx = 0; xx < CAPACITY; xx++) {
        if (pages[xx].key == key) { 
            pages[xx].frequency += 1;
            return; 
        }
    }
    new_entry(key, size, value, counter);
}

void lfu (int rod_cut[][2], int length) {
    for (int xx = 0; xx < length; xx++) {
        
        update_values(rod_cut[xx][0], rod_cut[xx][1]);
    }
}

void print_cache () {
    for (int i = 0; i < CAPACITY; i++) {
        printf("%d, %d, %d\n", pages[i].key, pages[i].value, pages[i].frequency);
    }
}

int main () {
    /*int numbers[] = {3, 1, 2, 3, 3, 2, 4, 6, 7};
    int length = sizeof(numbers) / sizeof(numbers[0]);
    lfu(numbers, length);
    
    printf("Stored values and their counts:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("{%d, %d}\n", pages[i][0], pages[i][1]);
    }*/
    int rod_cut [10][2] = {{1, 22}, {2, 56}, {3, 9}, {4, 34}, {5, 54},  {1, 22}, {2, 56}, 
                            {6, 323}, {7, 3223}, {8, 34}};
    int length = sizeof(rod_cut) / sizeof(rod_cut[0]);
    lfu(rod_cut, length);
    print_cache();
}