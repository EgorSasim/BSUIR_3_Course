import java.util.*;
import java.lang.Math;
class Task1 {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		System.out.println("Write 'x'");
		int x = sc.nextInt();
		System.out.println("Write 'y'");
		int y = sc.nextInt();

		int  res = (int)((1 + Math.pow(Math.sin(x + y), 2)) / (2 + Math.abs( x - (2*x)/(1 + Math.pow(x,2)*Math.pow(y,2))  )  ) + x); 
		
		System.out.print("The result is ");
		System.out.println(res);


	}
}
