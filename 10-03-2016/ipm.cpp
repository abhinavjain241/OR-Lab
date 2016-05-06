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

void setIdentity(double b[][SIZE], int row) {
	int i ,j;
	for (i = 0 ; i < row ; i++)
		for (j = 0 ; j < row; j++){
			if(i == j){
				b[i][j] = 1;
			}
			else
				b[i][j] = 0;
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
	double A_init[SIZE][SIZE], E[SIZE],  
	int m, n, i, j, extra = 0;
	std::cout << "Enter the no of equations" << std::endl;
	cin >> m;
	std::cout << "Enter the no of variables" << std::endl;
	cin >> n;
	std::cout << "Enter the coefficients of the matrix" << std::endl;
	getMat(A_init, m, n); // Get an m x n matrix of coefficients A_init
	cout << "Enter signs of the constraint equations (<= 0, = 1, >= 2):";
	for(i = 0; i < m; i++) {
		cin >> E[i];
		if(E[i] == 0 || E[i] == 1)
			extra++;
		else if(E[i] == 2)
			extra += 2;
	}
	getVector(E, m); // Get equality/inequality type (0, 1, or 2) in a column
	// Now maximum number of additional variables, i.e N - n can be 2 * m, so n + 2m is the maximum column dimension of the basic variable matrix (Basis)
	double B[m][2*m + n + 1];
	// Initialize Basis Matrix here - B of size m x (2 * m + n) and make all entries zero
	for(i = 0; i < m; i++) {
		for(j = 0; j < extra; j++)
			B[i][j] = 0;
	}
	// Loop through column vector E and according to the sign of equality, populate B with 1, or -1 accordingly
	for(i = 0, j = 0; i < m; i++) {
		if(E[i] == 0 || E[i] == 1) {
			B[i][j++] = 1;
		} else if (E[i] == 2) {
			B[i][j++] = 1;
			B[i][j++] = -1;
		}
	}
	augmentMat(A_init, B, A, m, N); // Create new matrix A which is a m x N matrix containing basic variables (artificial + slack)
	// Get initial guess - either manually or through code, call it D (N x 1) matrix
	diagonalize(D); //Form a N X N matrix 
	getVector(C, n); // Get objective function coefficients (for only n variables right now)
	// Iterate from n to N and set C[i] to 0, since the coefficients of basic variables in objective function is zero
	multiMat(A_bar, A, D, m, N); // Get A_bar
	multiMat(C_bar, D, C)  // Get C_bar
	setIdentity(I, N); // Form identity matrix I (N X N)
	transpose(A_bar, A_bar_t, m, N); // take transpose of m x N matrix
	multiMat(X, A_bar, A_bar_t);
	inverse(X, Y, m, m); // calculate inverse of m x m matrix
	multiMat(temp_1, A_bar_t, Y);
	multiMat(temp_2, temp_1, A_bar);
	subtract(P, I, temp_2, N, N);
	multiMat(C_p, P, C_bar); // C_p is N x 1 matrix
	// iterate over C_p and find minimum, lets say v, get fabs(v)
	setVector(ones, N, 1); // form column vector (N x 1) with all 1's
	add(L_bar, ones, (alpha/fabs(v)) * C_p, N, 1);
	// Computer D * X_bar
	// Terminate the process if |X_j(k+1) - X_j(k)| <  epsilon  for all j
	return 0;
}