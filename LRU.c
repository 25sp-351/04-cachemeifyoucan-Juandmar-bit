#include <stdio.h>
#include "LRU.h"

#define SIZE 3  // Memory capacity
int pages[SIZE];  // Memory to store pages

CacheLRU cache[SIZE];  // Cache to store pages
int size = 0;
int current_time = 0;

CacheLRU* find_entry(int key) {
    for (int xx = 0; xx < size; xx++) {
        if (cache[xx].key == key) {
            return &cache[xx];
        }
    }
    return NULL;

}

int find_LRU_index() {
    int min_index = 0;
    for (int xx = 1; xx < size; xx++) {
        if (cache[xx].timestamp < cache[min_index].timestamp) {
            min_index = xx;
        }
    }
    return min_index;
}

void new_entry(int key, int length, int price) {
    current_time++;
    if (size != NULL) {
        cache[size].key = key;
        //cache[size].length = length;
        //cache[size].price = price;
        //cache[size].counter = 1;
        cache[size].timestamp = current_time;
        size++;
    }
    else {
        int min_index = find_LRU_index();
        cache[min_index].key = key;
        //cache[min_index].length = length;
        //cache[min_index].price = price;
        //cache[min_index].counter = 1;
        cache[min_index].timestamp = current_time;
    }
}

int is_in_memory(int ref_page) {
    for (int xx = 0; xx < SIZE; xx++) {
        if (pages[xx] == ref_page) {
            return xx; 
        }
    }
    return -1; 
}

void fill_memory() {
    for (int xx = 0; xx < SIZE; xx++) {
        pages[xx] = 0;
    }
}

void print_pages() {
    printf("Pages: ");
    for (int j = 0; j < SIZE; j++) {
        if (pages[j] != -1) 
            printf("%d ", pages[j]);
        else
            printf("- ");
    }
    printf("\n");
}

void hit(int page_index) {
    // Page hit: Move the found page to the end (most recently used)
    int temp = pages[page_index];
    for (int yy = page_index; yy < SIZE - 1; yy++) {
        pages[yy] = pages[yy + 1];
    }
    pages[SIZE - 1] = temp;
}

void fault (int ref_page) {
    // Page fault: If memory is full, remove the least recently used page
    for (int yy = 0; yy < SIZE - 1; yy++) {
        pages[yy] = pages[yy + 1];
    }
    pages[SIZE - 1] = ref_page;
}

void lru(int array[], int size) {
    int faults = 0, hits = 0;
    fill_memory();

    // Iterate over the reference string
    for (int xx = 0; xx < size; xx++) {
        int ref_page = array[xx];
        int page_index = is_in_memory(ref_page);

        if (page_index != -1) {  
            hit(page_index);
            hits++;
        } 
        else { 
            faults++;
            fault (ref_page);
        }
        print_pages();
    }

    printf("Page Faults: %d\n", faults);
    printf("Page Hits: %d\n", hits);
}


