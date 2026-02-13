#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>

#define n 5

void merge_sort(int *array, int start, int end);
void merging(int *array, int start, int mid, int end);
void quicksort(int *array, int start, int end);
void quicksort_hoare(int *array, int start, int end);

int main(void) {

    int array[n] = {2, 3, 0, 4, 1};
    int temp;
    int position;
    int j;

    // Bubble sort:
    // for (int i = 0; i < n - 1; i++) {
    //     for (int j = 0; j < n-i-1; j++) {
    //         if (array[j+1] < array[j]) {
    //             temp = array[j+1];
    //             array[j+1] = array[j];
    //             array[j] = temp;
    //         }
    //     }       
    // }

    // for (int i = 0; i < n; i++) {
    //     if (i == n-1) break;
    //     position = i;
    //     while (position > 0 && array[position+1] < array[position]) {
    //         temp = array[position+1];
    //         array[position+1] = array[position];
    //         array[position] = temp;
    //         position--;
    //     }
    // }
    
    // Insertion sort:
    // for (int i = 1; i < n; i++) {
    //     j = i;
    //     temp = array[i];
    //     while (j>=0 && temp < array[j-1]) {            
    //         array[j] = array[j-1];  
    //         j--;
    //     }       
    //     array[j] = temp;
    // }

    // Selection sort:
    // for (int i = 0; i < n-1; i++) {
    //     temp = array[i];
    //     position = i;
    //     for (int j = i + 1; j < n; j++) {
    //         if (temp > array[j]) {
    //             temp = array[j];
    //             position = j;
    //         }
    //     }
    //     array[position] = array[i];
    //     array[i] = temp;
    // }

    // Merge sort:
    // int len = sizeof(array)/sizeof(array[0]);
    // merge_sort(array, 0, len-1);

    // Quicksort Lomuto:
    
    // quicksort(array, 0, (n-1));

    quicksort_hoare(array, 0, (n-1));

    for (int i = 0; i <= n-1; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}

void merge_sort(int *array, int start, int end) {
    int mid = start + (end - start)/2;
    if (start >= end) return;
    merge_sort(array, start, mid);
    merge_sort(array, mid+1, end);
    merging(array, start, mid, end);    
}

void merging(int *array, int start, int mid, int end) {
    int new_array[n];
    int i = 0;
    int j = start;
    int k = mid + 1;

    while (j <= mid && k <= end) {
        new_array[i++] = array[j] < array[k] ? array[j++] : array[k++];
    }
    while (j <= mid) {
        new_array[i++] = array[j++];
    }
    while (k <= end) {
        new_array[i++] = array[k++];
    }

    memcpy(&array[start], new_array, (end - start + 1) * sizeof(int));
}

void quicksort(int *array, int start, int end) {
    if (start >= end) return;

    int pivot = array[end];
    int position = start;
    int temp;
    for (int i = start; i <= end-1; i++) {
        if (array[i] < pivot) {
            temp = array[i];
            array[i] = array[position];
            array[position++] = temp;
        }
    }
    temp = array[position];
    array[position] = pivot;
    array[end] = temp;

    quicksort(array, start, position-1);
    quicksort(array, position+1, end);
}

void quicksort_hoare(int *array, int start, int end) {
    if (start >= end) return;

    int pivot = array[start];
    int position;
    int temp;
    // {2, 3, 0, 4, 1}
    // {1, 3, 0, 4, 2}
    // {1, 0, 3, 4, 2}
    // {0, 1, 3, 2, 4}
    // {0, 1, 2, 3, 4}
    int i = start;
    int j = end;
    while (true) {

        // while (i < end && array[i++] < pivot);
        // while (j > start && array[j--] > pivot);

        while (i < end && array[i] < pivot) {
            i++;
        }
        while (j > start && array[j] > pivot) {
            j--;
        }

        if (i < j) {
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
        else {
            position = j;
            break;
        }
        
    } 
    // position = j;

    // for (int i = start; i <= end; i++) {
    //     for (int j = end; j >= start; j--) {
    //         if (i >= j) {
    //             position = j;
    //             break;
    //         }
    //         if (array[i] >= pivot && array[j] <= pivot) {
    //             temp = array[i];
    //             array[i] = array[j];
    //             array[j] = temp;
    //         } 
    //     }
    // }    

    quicksort_hoare(array, start, position);
    quicksort_hoare(array, position+1, end);
}