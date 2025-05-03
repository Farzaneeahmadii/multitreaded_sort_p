#include <pthread.h>
#include <stdio.h>

#define SIZE 10

int arr[SIZE] = {23, 42, 4, 16, 8, 15, 9, 55, 0, 34};
int sorted[SIZE];

void bubble_sort(int* array, int size) {
    for (int i = 0; i < size-1; i++)
        for (int j = 0; j < size-1-i; j++)
            if (array[j] > array[j+1]) {
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
}

void* sort_first_half(void* arg) {
    bubble_sort(arr, SIZE/2);
    pthread_exit(NULL);
}

void* sort_second_half(void* arg) {
    bubble_sort(arr + SIZE/2, SIZE/2);
    pthread_exit(NULL);
}

void* merge_halves(void* arg) {
    int i = 0, j = SIZE/2, k = 0;
    while (i < SIZE/2 && j < SIZE) {
        if (arr[i] < arr[j])
            sorted[k++] = arr[i++];
        else
            sorted[k++] = arr[j++];
    }
    while (i < SIZE/2)
        sorted[k++] = arr[i++];
    while (j < SIZE)
        sorted[k++] = arr[j++];
    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2, t3;

    pthread_create(&t1, NULL, sort_first_half, NULL);
    pthread_create(&t2, NULL, sort_second_half, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_create(&t3, NULL, merge_halves, NULL);
    pthread_join(t3, NULL);

    printf("Sorted array: ");
    for (int i = 0; i < SIZE; i++)
        printf("%d ", sorted[i]);
    printf("\n");

    return 0;
}
