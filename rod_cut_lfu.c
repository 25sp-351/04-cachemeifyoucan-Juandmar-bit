#include <stdio.h>
#include "cuts_data.h"

#define SIZE 100

Cut_Info data[SIZE]; 

void insert (int length, int value) {
    data->length = length;
    data->value = value;
    data->count++;
}

void check_if_double (int length, int value) {
    for (int xx = 0; xx < SIZE; xx++) {
        if (data[xx].length == length && data[xx].value == value) {
            data[xx].count++;
        }
        else {
            insert(length, value);
        }
    }
}

int calculate_total_value() {
    int totalValue = 0;
    for (int xx = 0; xx < SIZE; xx++) {
        totalValue += data[xx].value * data[xx].count;
    }
    return totalValue;
}
