package Lab8;

public class Tester {
	public static void main(String[] args){
		int[] first = {0,1};
		int[] second = new int[10];
		int[] third = new int[100];
		
		Quicksort sort = new Quicksort();
		
		for(int x=0;x<third.length;x++){
			int num = (int)(Math.random() * 200 + 1);
			third[x] = num;
		}
		
		sort.sort(third, "asc");
		for(int x=0; x<third.length;x++){
			System.out.print(third[x] + " , ");
		}
		
		
	}
}
