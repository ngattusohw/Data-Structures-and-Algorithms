#include <stdlib.h>
#include <stdio.h>


/* Insertion sort
 *
 * Sort an array segment, in place:
 * Assume 0 <= l <= r and arr has length at least r.
 * Assume the elements of arr point to null-terminated strings.
 * Permute the elements, in place, to put them in non-decreasing order,
 * using strcmp for comparison.
 * 
 * Use the insertion sort algorithm, with binary search to find the insertion point.
 */
void insertionsort(char* arr[], int l, int r){
    //use strcmp for comparisons
    



}

/*
Helper method for quicksort
###Need to make sure to set the pivot point..
 */

int partition(int arr[], int l, int r){
    int pivot = arr[l]; //need to change the pivot point to be specified in qs+
    int temp=0;
    int low = l-1;
    int high = r+1;

    while(1){
        low++;
        while(low<r && arr[low] < pivot){ 
            low++;
        }
        high--;
        while(high>l && arr[high] > pivot){
            high--;
        }
        if (low < high) {
            temp = arr[low];
            arr[low] = arr[high];
            arr[high] = temp;
        }else{
            return (high);
        }

    }
}


/* Quicksort: same specification, but use the recursive quicksort algorithm.
 * Use a two-sided partition algorithm, as discussed in class.
 * You can use the one in the textbook, or some variation.
 */
void quicksort(char* arr[], int l, int r){
	if (l+1 < r) {
        int s = partition(arr,l,r);
        quicksort(arr,l,s);
        quicksort(arr,s+1,r);
    }
}


/* QuicksortPlus: same specification, but use the following form of recursive quicksort:
 * 
 * If r - l <= 10, use insertionsort.
 * Otherwise, use quicksort, choosing the pivot element as the median value of 
 * arr[l], arr[r-1], and arr[(l+r)/2].
 */
void quicksortPlus(char* arr[], int l, int r){
	if(r-l <=10){
		insertionsort(arr, l, r);
	}else{
		quicksort(arr, l , r);
	}

	return;
}


/* Assume arr has length at least len.
 * For each of the three sort functions, run it 20 times on arr, and print the total time for each of the three functions.
 */ 
void compareSorts(char* arr[], int len);




