/*
 * I pledge my honor that I have abided by the steven's honor system
 *	Nick Gattuso
 * 
 * 11-16-2016
 */

package Lab8;

/**
 * The SelectionSort class implements the selection sort algorithm to sort an array of integers.
 * @author Nick Gattuso
 *
 */
public class SelectionSort {
	public static String NAME = "Nick Gattuso";
	
	/**
	 * Checks the order (ascending or descending) and then sorts the array using the algorithm
	 * @param arr int[]
	 * @param order A string that states the order
	 * @return arr, a sorted array of ints
	 */
	public int[] sort(int[] arr, String order){
		if(arr==null || order==null){
			throw new IllegalArgumentException("Null parameters");
		}
		if(arr.length<2){
			return arr;
		}
		
		int temp;
		if(order.equals("asc")){
			for(int i=0;i <arr.length-1;i++){
				int smallest = arr.length-1;	
				//searches for the smallest and swaps
				for(int j=i;j<arr.length;j++){	
					if(arr[j]<arr[smallest]){	
						smallest=j;
					}	
				}	
				temp=arr[i];
				arr[i]=arr[smallest];
				arr[smallest]=temp;
			}
		}else if(order.equals("desc")){
			for(int i=0;i <arr.length-1;i++){
				int largest = arr.length-1;	
				//searches for the largest, and swaps
				for(int j=i;j<arr.length;j++){	
					if(arr[j]>arr[largest]){	
						largest=j;
					}	
				}	
				temp=arr[i];
				arr[i]=arr[largest];
				arr[largest]=temp;
			}
		}else{
			//if the string is invalid, throw an exception
			throw new IllegalArgumentException("Invalid order");
		}
		return arr;
	}
	
}
