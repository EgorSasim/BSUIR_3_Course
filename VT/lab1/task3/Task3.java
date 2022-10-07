import java.util.*;
import java.lang.Math;
class Task3 {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		System.out.println("Write 'a'");
		int a = sc.nextInt();
		System.out.println("Write 'b'");
		int b = sc.nextInt();
		System.out.println("Write step('h')");
		int h = sc.nextInt();

		System.out.println("TABLE:");

		for (int i = a; i <= b; i += h) {
			System.out.print(i);
			System.out.print("\t");
			System.out.print(Math.tan(i));
			System.out.println();
		}
	}
}
