#include <bits/stdc++.h>

#define SIZE 20

void matrix_multiply(double A[][SIZE], double B[][SIZE], double result[][SIZE], int n) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; i++) {
			result[i][j] = 0;
			for(int k = 0; k < n; k++) {
				result[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}

void matrix_multiply_one_dimensional(double A[][SIZE], double B[], double result[], int m) {
	for(int i = 0; i < m; i++) {
		result[i] = 0;
		for (int j = 0; j < m; j++) {
			result[i] += A[i][j] * B[j];
		}
	}
}

void print_matrix(double A[][SIZE], int n) {
	for(int i = 0; i < n; i++) {
		std::cout << std::endl;
		for (int j = 0; j < n; j++) {
			std::cout << A[i][j] << " ";
		}
	}
}

int main(int argc, char const *argv[]) {
	double a[SIZE][SIZE], B[SIZE][SIZE], e[SIZE], C[SIZE], E[SIZE][SIZE], I[SIZE][SIZE];
	int n;
	std::cout << "Enter the size of the square matrix (n x n):";
	std::cin >> n;	
	// Populate Matrix
	for(int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout << "Enter element at position (" << i + 1 << "," << j + 1 << "):";
			std::cin >> a[i][j];
		}
	}
	print_matrix(a, n);
	//Form Identity Matrix I to start with
	for(int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j)
				I[i][j] = 1;
			else
				I[i][j] = 0;
		}
	}

	for(int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			B[i][j] = I[i][j];

	for(int j = 0; j < n; j++) {
		for(int i = 0; i < n; i++) 
			C[i] = a[i][j]; // Get Column Vector C
		matrix_multiply_one_dimensional(B, C, e, n);
		for(int i = 0; i < n; i++) {
			if(i == j)
				e[i] = 1 / e[i];
			else
				e[i] = -1 * (e[i] / e[j]);
		}
		// e ----> eta column vector
		for(int rows = 0; rows < n; rows++) {
			for(int cols = 0; cols < n; cols++) {
				if (cols == j) {
					E[rows][cols] = e[rows];
				}
				else
					E[rows][cols] = I[rows][cols];
			}
		}
		// Above code forms intermediate E matrix
		matrix_multiply(B, E, B, n);
	}
	return 0;
}