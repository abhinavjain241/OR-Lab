#include <bits/stdc++.h>

using namespace std;

void getMat(double a[][SIZE], int row , int col) {
	int i, j;
	std::cout << "Give the matrix entries" << std::endl;
	for (i = 0 ; i < row ; i++)
		for (j = 0 ; j < col ; j++)
			cin >> a[i][j];
}

void getVector(double a[], int row) {
	int i;
	std::cout << "Give the column vector entries" << std::endl;
	for (i = 0 ; i < row ; i++)
		cin >> a[i];
}

void printMatrix(double a[][SIZE], int row, int col){
	int i, j;
	for (i = 0; i < row; i++){
		std::cout << "\n";
		for (j = 0; j < col; j++)
			std::cout << a[i][j] << "\t";
	}
}

void multiMat(double a[][SIZE], double b[][SIZE], double ans[][SIZE], int row, int col) {
	int i, j, k;
	double sum;
	for(i = 0; i < row; i++)
		for(j = 0; j < col; j++) {
			sum  = 0;
			for(k = 0; k < col; k++) {
				sum += a[i][k] * b[k][j];
			}
			ans[i][j] = sum;
		}
}

// double multiVec(double y[], double a[][SIZE], int row, int col) {
// 	// Multiply 1 X N vector with an N X 1 vector
// 	int i, j;
// 	double sum;
// 	for(i = 0; i < row; i++){
// 		sum += y[i] * a[i][col];
// 	}
// 	return sum;
// }

int main(int argc, char const *argv[]) {
	getMat(A_init, m, n); // Get an m x n matrix of coefficients A_init
	getVector(E, m); // Get equality/inequality type (0, 1, or 2) in a column
	// Now maximum number of additional variables, i.e N - n can be 2 * m, so n + 2m is the maximum column dimension of the basic variable matrix (Basis)
	// Initialize Basis Matrix here - B of size m x (2 * m + n) and make all entries zero
	// Loop through column vector E and according to the sign of equality, populate B with 1, or -1 accordingly
	augmentMat(A_init, B, A, m, N); // Create new matrix A which is a m x N matrix containing basic variables (artificial + slack)
	// Get initial guess - either manually or through code, call it D (N x 1) matrix
	diagonalize(D); //Form a N X N matrix 
	getVector(C, n); // Get objective function coefficients (for only n variables right now)
	// Iterate from n to N and set C[i] to 0, since the coefficients of basic variables in objective function is zero
	multiMat()
	return 0;
}