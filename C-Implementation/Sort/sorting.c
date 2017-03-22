#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define NUM_REPEAT 20

int BinarySearch(char* a[], char* key, int low, int high);

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
    int x,y;
    char* temp;

    for(x=l+1;x<r;x++){
        temp=arr[x];

        //do binary search, we did this from class
        int low = 0, high=x,y;
        while(low<high){
            int mid = (high+low)/2;
            if(strcmp(temp,arr[mid]) <=0){
                high = mid;
            }else{
                low = mid+1;
            }
        }

        for(y=x;y>high;y--){
            arr[y] = arr[y - 1];
        }

        arr[high] = temp;
    }

}


/*
Helper method for quicksort
###Need to make sure to set the pivot point..
 */

int partition(char* arr[], int l, int r){
    char* pivot = arr[l]; //need to change the pivot point to be specified in qs+
    char* temp;
    int low = l;
    int high = r;

    while(1){
        //printf("%s\n", "Here");
        low++;
        while(low<r && strcmp(arr[low],pivot)<=0) { 
            low++;
        }
        high--;
        while(high>l && strcmp(arr[high],pivot) > 0){
            high--;
        }
        if (low < high) {
            temp = arr[low];
            arr[low] = arr[high];
            arr[high] = temp;
        }else{
            temp=arr[l];
            arr[l] = arr[high];
            arr[high] = temp;
            return (high);
        }
    }
}


/* Quicksort: same specification, but use the recursive quicksort algorithm.
 * Use a two-sided partition algorithm, as discussed in class.
 * You can use the one in the textbook, or some variation.
 */
void quicksort(char* arr[], int l, int r){
	if (l < r) {
        int s = partition(arr,l,r);
        quicksort(arr,l,s-1);
        quicksort(arr,s+1,r);
    }
}

int partitionPlus(char* arr[], int l, int r){
    char* it[] = {arr[l], arr[r-1],arr[(l+r)/2]};
    insertionsort(it, 0 ,3);


    char* pivot = it[1]; //need to change the pivot point to be specified in qs+
    char* temp;
    int low = l;
    int high = r;

    while(1){
        //printf("%s\n", "Here");
        low++;
        while(low<r && strcmp(arr[low],pivot)<=0) { 
            low++;
        }
        high--;
        while(high>l && strcmp(arr[high],pivot) > 0){
            high--;
        }
        if (low < high) {
            temp = arr[low];
            arr[low] = arr[high];
            arr[high] = temp;
        }else{
            temp=arr[l];
            arr[l] = arr[high];
            arr[high] = temp;
            return (high);
        }
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
		if (l < r) {
            int s = partitionPlus(arr,l,r);
            quicksortPlus(arr,l,s-1);
            quicksortPlus(arr,s+1,r);
        }
	}

	return;
}




/* Assume arr has length at least len.
 * For each of the three sort functions, run it 20 times on arr, and print the total time for each of the three functions.
 */ 
void compareSorts(char* arr[], int len){
    char* copy[len];
    /* save start time, repeatedly make a (shallow) copy of the array and sort it */ 

    clock_t begin, end;
    double time_spent;
    begin = clock();

    for (int j = 0; j < NUM_REPEAT; j++) {
        for (int i = 0; i < len; i++)
            copy[i] = arr[i];
        insertionsort(copy, 0, len);
    }

    /* stop timing and print duration */

    end = clock();
    time_spent = ((double)(end - begin)) / CLOCKS_PER_SEC;
    printf("Sorting alg is insertion sort; time spent on %i sorts is %f \n", 
        NUM_REPEAT, time_spent);


    //For quicksort
    /* save start time, repeatedly make a (shallow) copy of the array and sort it */ 

    begin = clock();

    for (int j = 0; j < NUM_REPEAT; j++) {
        for (int i = 0; i < len; i++)
            copy[i] = arr[i];
        quicksort(copy, 0, len);
    }

    /* stop timing and print duration */

    end = clock();
    time_spent = ((double)(end - begin)) / CLOCKS_PER_SEC;
    printf("Sorting alg is quicksort; time spent on %i sorts is %f \n", 
        NUM_REPEAT, time_spent);

    //For quicksortPLUS
    /* save start time, repeatedly make a (shallow) copy of the array and sort it */ 


    for (int j = 0; j < NUM_REPEAT; j++) {
        for (int i = 0; i < len; i++)
            copy[i] = arr[i];
        quicksortPlus(copy, 0, len);
    }

    /* stop timing and print duration */

    end = clock();
    time_spent = ((double)(end - begin)) / CLOCKS_PER_SEC;
    printf("Sorting alg is quicksortPlus; time spent on %i sorts is %f \n", 
        NUM_REPEAT, time_spent);
} 

