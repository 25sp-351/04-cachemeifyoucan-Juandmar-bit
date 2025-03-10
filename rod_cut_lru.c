#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#define NUM_FILES 4

void rod_cut(int rod_cut) {
    int length, value;
    const char files[NUM_FILES] = {"test2.txt", "test3.txt", "test4.txt"};

    FILE *file[NUM_FILES];
    for (int xx = 0; xx < NUM_FILES; xx++) {
        file[xx] = fopen(files[xx], "r");
        if (files[xx] == NULL) {
            printf("No file found.\n", files[xx]);
            return 1;
        } 
    }

    for (int yy = 0; yy < NUM_FILES; yy++) {
        while (fscanf(file, "%d, %d", &length, &value) == 2) {
    
            while (length <= rod_cut) {
                rod_cut -= length;
            }
        }
    }
}

int calculateTotalValue(PieceInfo* pieces, int pieceCount) {
    int totalValue = 0;
    for (int i = 0; i < pieceCount; i++) {
        totalValue += pieces[i].value * pieces[i].counter;
    }
    return totalValue;
}

void printResults(PieceInfo* pieces, int pieceCount, int remainder, int totalValue) {
    
    for (int i = 0; i < pieceCount; i++) {
        printf("%d @ %d = %d\n", pieces[i].counter, pieces[i].length, pieces[i].value * pieces[i].counter);
    }
    printf("Remainder: %d\n", remainder);
    printf("Total Value: %d\n\n", totalValue);
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        return 1;
    }
    
    char *endptr;
    errno = 0;
    int supplied_rod_length = strtol(argv[1], &endptr, 10);

    if (errno == ERANGE) {
        printf("Number out of range.\n");
    }

    if (endptr == argv[1] || *endptr != '\0') {
        printf("Error: Invalid number format.\n");
    }
    
    rod_cut(supplied_rod_length);

    return 0;
}
