#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>

#define n 6

typedef struct {
    int first_occ;
    int last_occ;
} Search;

void merge_sort(int *array, int start, int end);
void merging(int *array, int start, int mid, int end);
void quicksort(int *array, int start, int end);
void quicksort_hoare(int *array, int start, int end);
int linear_search(int *array, int key);
int binary_search_iterative(int *array, int key);
Search binary_search_recursive(int *array, int key, int start, int end);

int main(void) {

    int array[n] = {5, 2, 8, 1, 9, 9};
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

    int key = 9;
    // int key_pos = linear_search(array, key);
    // int key_pos = binary_search_iterative(array, key);
    Search result_main = binary_search_recursive(array, key, 0, (n-1));

    printf("first: %d last: %d\n", result_main.first_occ, result_main.last_occ);

    // for (int i = 0; i <= n-1; i++) {
    //     printf("%d ", array[i]);
    // }
    // printf("\n");

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
    int i = start;
    int j = end;
    while (true) {
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
            i++;
            j--;
        }
        else {
            position = j;
            break;
        }        
    } 

    quicksort_hoare(array, start, position);
    quicksort_hoare(array, position+1, end);
}

int linear_search(int *array, int key) {
    for (int i = 0; i < n; i++) {
        if (array[i] == key) {
            return i;
        }
    }
    return -1;
}

int binary_search_iterative(int *array, int key) {
    int mid;
    int low = 0;
    int high = n;

    while (low <= high) {
        mid = (high-low)/2+low;
        if (key < array[mid]) high = mid-1;
        if (key > array[mid]) low = mid+1;
        if (key == array[mid]) return mid;
    }

    return -1;
}

Search binary_search_recursive(int *array, int key, int start, int end) {
    Search result;
    // {1, 2, 5, 8, 9, 9}
    // int mid = (end-start)/2 + start;
    if (start >= end) {
        // if (key == array[start]) return start;
        if (key == array[start]) {
            result.last_occ = start;
            printf("last_occ: %d\n", result.last_occ);
        }
        else result.last_occ = result.first_occ;
        return result;
    }    
    int mid = (end-start)/2 + start;
    // printf("%d\n", mid);
    if (key == array[mid]) {
        result.first_occ = mid;
        printf("first_occ: %d\n", result.first_occ);
        binary_search_recursive(array, key, (mid+1), end); 
        binary_search_recursive(array, key, start, (mid-1));
    }
    if (key < array[mid]) binary_search_recursive(array, key, start, (mid-1));
    if (key > array[mid]) binary_search_recursive(array, key, (mid+1), end);    
    // binary_search_recursive(array, key, start, end);   
}