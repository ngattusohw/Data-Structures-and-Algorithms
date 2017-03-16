/*
 * I pledge my honor that I have abided by the steven's honor system
 *	Nick Gattuso
 * 
 * 11-16-2016
 */
package Lab8;

/**
 * The Quicksort class implements the Quicksort sorting algorithm to sort an array of ints
 * @author Nick Gattuso
 *
 */
public class Quicksort {
	public static String NAME = "Nick Gattuso";
	
	/**
	 * sort method calls the quickSort method to sort the array based on the order
	 * @param arr int[] to be sorted
	 * @param order A string that specifies how the array will be sorted
	 * @return int[]
	 */
	public int[] sort(int[] arr, String order){
		if(arr==null || order==null){
			throw new IllegalArgumentException("One of the parameters are null");
		}
		if(arr.length<2){
			return arr;
		}
		int temp;
		if(order.equals("asc")){
			//calls the quicksort method
			quickSort(arr, 0, arr.length -1 );
			return arr;
		}else if(order.equals("desc")){
			//calls the quicksort method, and then copies arr backwards to get it into decreasing
			// 	order
			quickSort(arr, 0 , arr.length -1);
			int[] bla = new int[arr.length];
			int y=0;
			for(int x=arr.length-1; x>=0; x--){
				bla[y] = arr[x];
				y++;
			}
			return bla;
			
		}else{
			throw new IllegalArgumentException("Invalid order");
		}
	}
	
	/**
	 * The partition method splits up the array based on the given low and high values, and sorts
	 * 	it.
	 * @param arr int[] array to be partitioned
	 * @param low int , lower bound
	 * @param high int , upper bound
	 * @return int representation of the pivot value
	 */
	public int partition(int[] arr,int low, int high){
		int pivot = arr[low];
        while (low<=high){
            while (arr[low] < pivot){
                low++;
            }
            while (arr[high] > pivot){
                high--;
            }
            if (low <= high){
            	int tmp = arr[low]; 
            	arr[low] = arr[high]; 
            	arr[high] = tmp;

                low++;
                high--;
            }
        }
        
        return low;
	}
	
	/**
	 * the quickSort method handles the recursive calls to partition, and to itself.
	 * @param arr int[] to be sorted
	 * @param left int, lower bound
	 * @param right int, upper bound
	 */
	public void quickSort(int[] arr, int left, int right){
        if(left < right){
            int pivot = partition(arr, left, right);
            if(left<pivot - 1){
            	quickSort(arr,left,pivot-1);
            }
            if(right>left){
            	quickSort(arr,pivot,right);
            }
        }
	}
}
