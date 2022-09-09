import java.util.*;
import java.lang.Math;

class Task6 {
	
	public static double[][] matrix;

	public static void main(String[] args) {
		double[] testArr = {100.3, 200.5, 1.23, 5.75, 28.0, 93, 23.234, 4, 45.5};
		genMatrix(testArr.length);
		fillMatrix(testArr);
		showMatrix((int)Math.sqrt(testArr.length));
	}

	public static void genMatrix(int numsLength) {
		matrix = new double[(int)Math.sqrt(numsLength)][(int)Math.sqrt(numsLength)];
	}

	public static void fillMatrix(double[] nums) {
		for (int i = 0; i < Math.sqrt(nums.length); ++i) {
			for (int j = 0; j < Math.sqrt(nums.length); j++) {
				matrix[i][j] =nums[j + i * (int)Math.sqrt(nums.length)];
			}
		}
	}

	public static void showMatrix(int matrixSideSize) {
		for (int i = 0; i < matrixSideSize; ++i) {
			for (int j = 0; j < matrixSideSize; ++j) {

				System.out.print(matrix[i][j]);
				System.out.print("\t");
			}
				System.out.println();
		}
	}
}
