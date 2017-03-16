/*
 * I pledge my honor that I have abided by the steven's honor system
 *	Nick Gattuso
 * 
 * 11-16-2016
 */

package Lab8;

/**
 * The InsertionSort class implements the InsertionSort algorithm to sort an array
 * @author Nick Gattuso
 *
 */
public class InsertionSort {
	public static String NAME = "Nick Gattuso";
	
	/**
	 * The sort method sorts the method depending on the order (ascending or descending)
	 * @param arr int[] to be sorted
	 * @param order A string, states if order is asc or des
	 * @return
	 */
	public int[] sort(int[] arr, String order){
		if(arr==null || order==null){
			throw new IllegalArgumentException("Parameter(s) null");
		}
		if(arr.length<2){
			return arr;
		}
		int temp;
		if(order.equals("asc")){
			for(int i=1;i<arr.length;i++){	
				temp=arr[i];	
				int pos=i;
				while((pos >0)	&&	(arr[pos-1]>temp)){
					arr[pos]=arr[pos-1];
					pos--;
				}
				arr[pos]=temp;	
			}
		}else if(order.equals("desc")){
			for(int i=1;i<arr.length;i++){
				temp=arr[i];	
				int pos=i;	
				while((pos >0)	&&	(arr[pos-1]<temp)){
					arr[pos]=arr[pos-1];
					pos--;
				}
				arr[pos]=temp;	
			}
		}else{
			throw new IllegalArgumentException("Invalid order");
		}
		
		return arr;
	}
}
