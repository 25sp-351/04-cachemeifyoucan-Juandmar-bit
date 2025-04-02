#include <stdio.h>
#include <stdlib.h>
#include "LFU.h"
#include "computation.h"
#define LIMIT_VALUES 10

int main(int argc, char *argv[]) {

    if (argc < 2) {
        exit(EXIT_FAILURE);
    }

    const char *file_name = argv[1];

    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    
    int length, value, size, rod_length;
    List list[LIMIT_VALUES];
    size = 0;

    while (fscanf(file, "%d, %d", &length, &value) == 2){
        if (size == LIMIT_VALUES) {
            fprintf(stderr, "Error: Maximum size exceeded\n");
            fclose(file);
            exit(EXIT_FAILURE);
        }
        list[size].length = length;
        list[size].value = value;
        size++;
    }
    while(1) {
        printf("Enter the length of the rod: (-1 to exit): ");
        scanf("%d", &rod_length);

        if (rod_length == -1) {
            break;
        }
       
        ListOutput *result = max_profit(rod_length, list, size);
    
        for (int i = 0; i < size; i++) {
            if(result->count[i] > 0){
                printf("%d @ %d = %d \n", result->count[i], list[i].length, list[i].value * result->count[i]);
            }
        }
        printf("Value: %d\n", result->max_value);
    }
    fclose(file);
    return 0;
}
