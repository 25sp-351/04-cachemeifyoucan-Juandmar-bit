#include <stdio.h>
#include "lru_cache.h"

#define SIZE 5  // Memory capacity
LRU_CACHE pages[SIZE];  // Memory to store pages

/*LRU_CACHE cache[SIZE]; 
int size = 0;
int current_time = 0;

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
    printf("hello\n");
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
}*/

int is_in_memory(int key, int value) {
    for (int xx = 0; xx < SIZE; xx++) {
        if (pages[xx].key == key && pages[xx].value == value) {
            return xx; 
        }
    }
    return -1; 
}

void fill_memory() {
    for (int xx = 0; xx < SIZE; xx++) {
        pages[xx].key = 0;
        pages[xx].value = 0;
    }
}

void print_pages() {
    printf("Pages: \n");
    for (int xx = 0; xx < SIZE; xx++) {
        printf("%d, %d \n", pages[xx].key, pages[xx].value);  // Prints all elements, including -1
    }
    printf("\n");
}


void hit(int page_index) {
    // Page hit: Move the found page to the end (most recently used)
    int temp_key = pages[page_index].key;
    int temp_value = pages[page_index].value;
    for (int yy = page_index; yy < SIZE - 1; yy++) {
        pages[yy].key = pages[yy + 1].key;
        pages[yy].value = pages[yy + 1].value;
    }
    pages[SIZE - 1].key = temp_key;
    pages[SIZE - 1].value = temp_value;
}

void fault (int key, int value) {
    // Page fault: If memory is full, remove the least recently used page
    for (int yy = 0; yy < SIZE - 1; yy++) {
        pages[yy].key = pages[yy + 1].key;
        pages[yy].value = pages[yy + 1].value;
    }
    pages[SIZE - 1].key = key;
    pages[SIZE - 1].value = value;
}

void lru(int array[][2], int size) {
    int faults = 0, hits = 0;
    fill_memory();

    // Iterate over the reference string
    for (int xx = 0; xx < size; xx++) {
        int key = array[xx][0];
        int value = array[xx][1];
        int page_index = is_in_memory(key, value);

        if (page_index != -1) {  
            hit(page_index);
            hits++;
        } 
        else { 
            faults++;
            fault (key, value);
        }
    }
    print_pages();
    printf("Page Faults: %d\n", faults);
    printf("Page Hits: %d\n", hits);
}

int main() {
    // Reference string
    //int reference_string[] = {1, 2, 3, 4, 5, 1, 2, 6, 7, 1, 2, 8, 9, 10, 1, 11};
    //int n = sizeof(reference_string) / sizeof(reference_string[0]);

    //lru(reference_string, n);
    int reference_string[16][2] = {{1, 32}, {2, 45}, {3, 12}, {4, 45}, {5, 42}, {1, 32}, 
                                    {2, 45}, {6, 423}, {7, 343}, {1, 32}, {2, 45}, {8,54}, 
                                    {9,65}, {10, 43}, {1, 32}, {11, 342}};
    int n = sizeof(reference_string) / sizeof(reference_string[0]);

    lru(reference_string, n);

    return 0;
}