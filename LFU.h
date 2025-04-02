#ifndef LFU_H
#define LFU_H
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
} LFU;

LFU *get_cache(int key);
void put_in_cache(LFU piece, int n);
void free_old();
int find_min_index();

#endif