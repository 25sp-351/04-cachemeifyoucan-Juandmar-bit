#ifndef LRU_H
#define LRU_H

#define MAX_VAL 2

#define MAX_CACHE 100
#define MAX_PIECES 10

typedef struct {
    int length;
    int value;
    int *count;
} Values;

typedef struct {
    int key;
    Values values[MAX_PIECES];
    int max_value;
    int frequency; 
} LRU;

typedef struct {
    int key;            // length of rod
    int values[MAX_VAL];// price of rod and number of times rod is cut
    int timestamp;      // time accessed
} CacheLRU;

int find_LUF_index();
void new_entry(int key, int length, int price);
void get_cache(int key);


#endif