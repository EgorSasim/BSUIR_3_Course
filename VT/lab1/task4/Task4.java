import java.util.*;
import java.lang.Math;
class Task4 {

	public static void main(String[] args) {
		int[] testArr = {100, 200, 1, 5, 28, 93};


		for (int i = 0; i < testArr.length; ++i) {
			if (isPrime(testArr[i])) {
				System.out.println(i);
			}
		}

	}


		public static boolean isPrime(int num) {
			if (num <= 1) {
				return false;
			}
			for (int i = 2; i <= num / 2; ++i) {
				if ( (num % 2) == 0 ) 
					return false;
			}
			return true;
		}
}
