#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char** split_string(char*);

void swap(int *a, int *b)
{
    if (a == b) return;
    printf("a : %d, b: %d\n", *a, *b);
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
    printf("a : %d, b: %d\n", *a, *b);
}
void display(int *arr, int num)
{
    int i;
    for (i = 0; i < num; i++) {
        printf("%ld ", (long)arr[i]);
    }
    
}
int partition(int *arr, int low, int high)
{
    int i, j;
    long pivot;
    i = low - 1;
    pivot = arr [high];
    for ( j = low; j < high ; j++) {
        if (arr[j] > pivot) {
            swap(&arr[++i], &arr[j]);
        }
    }
    
    swap(&arr[i+1], &arr[high]);
    return (i + 1);
}
void quick_sort(int *arr, int low, int high)
{
    int pi;
    if ( low < high) {
        pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

// Complete the marcsCakewalk function below.
long marcsCakewalk(int calorie_count, int* calorie) {
    int i;
    long miles = 0;
    quick_sort(calorie, 0, calorie_count - 1);
	display(calorie, calorie_count);    
    for (i = 0; i < calorie_count; i++) {
        miles = miles + (calorie[i] << i);
    }
    return miles;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* n_endptr;
    char* n_str = readline();
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char** calorie_temp = split_string(readline());

    int* calorie = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        char* calorie_item_endptr;
        char* calorie_item_str = *(calorie_temp + i);
        int calorie_item = strtol(calorie_item_str, &calorie_item_endptr, 10);

        if (calorie_item_endptr == calorie_item_str || *calorie_item_endptr != '\0') { exit(EXIT_FAILURE); }

        *(calorie + i) = calorie_item;
    }

    int calorie_count = n;

    long result = marcsCakewalk(calorie_count, calorie);

    fprintf(fptr, "%ld\n", result);

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) { break; }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { break; }

        size_t new_length = alloc_length << 1;
        data = realloc(data, new_length);

        if (!data) { break; }

        alloc_length = new_length;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }

    data = realloc(data, data_length);

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);
        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

