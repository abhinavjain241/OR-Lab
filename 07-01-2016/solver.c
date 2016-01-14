/*
	Abhinav Jain
	13MA20004
	Date: 07-01-2016
	Max:/ Min = Z = C^T X
    Subject to AX= b
    X >= 0
*/
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <math.h>

void swap(double **, int, int, int);
int calculateRank(double **, int, int);
void printMatrix(double **, int, int);
void getMatrix(double **, int, int);
double** augmentMatrices(double **, double **, int, int);
long long C(int , int);

int main() {
	/* Get Objective Function Z */
	int n;	//Number of variables
	int m;	//Number of equations
	int i, j; // Dummy variables
	printf("Enter number of variables in the system:\n");
	scanf("%d", &n);
	printf("Enter number of equations in the system\n");
	scanf("%d", &m);
	assert(n > m); // Number of variables should be more than the constraints
	int nbasic = n - m; // Number of non-basic variables 
	// Coefficient matrix
	double **A = (double **)malloc(m * sizeof(double *));
	for(i = 0; i < m; i++)
		A[i] = (double *)malloc(n * sizeof(double));
	// Output matrix (Y - values)
	double **B = (double **)malloc(m * sizeof(double *));
	for(i = 0; i < m; i++)
		B[i] = (double *)malloc(sizeof(double));
	printf("Enter coefficients of constraints equations in matrix form:");
	getMatrix(A, m, n); // Get A
	printf("Enter the right side values of the equations:");
	getMatrix(B, m, 1); // Get B
	float *C = augmentMatrices(A, B, m, n); // Make (A | b)
	if (calculateRank(A, m, n) == calculateRank(C, m, n))
		printf("\nConsistent system!");
	else {
		printf("\nNo solution!")
		exit(0);
	}
	// Number of possible cases or basic solutions
	long long basic_sols = C(n, m);
	// Solution matrix containing basic solutions to the problem
	double **solution = (double **)malloc(m * sizeof(double *));
	for(i = 0; i < m; i++)
		solution[i] = (double *)malloc(basic_sols * sizeof(double));
	// Free dynamically allocated memory 
	free(A);
	free(B);
	free(C);
}

double** augmentMatrices(double **A, double **b, int m, int n) {
	int i, j;
	double **result = (double **)malloc(m * sizeof(double *));
	for(i = 0; i < m; i++)
		result[i] = (double *)malloc((n + 1) * sizeof(double));
	for(i = 0; i < m; i++) {
		for(j = 0; j < n; j++)
			result[i][j] = A[i][j];
	}
	for(i = 0; i < m; i++)
		result[i][n] = b[i][0];
	return result;
}

void swap(double **A, int r1, int r2, int cols)
{
	int i;
    for(i = 0; i < cols; i++) {
        double temp = A[r1][i];
        A[r1][i] = A[r2][i];
        A[r2][i] = temp;
    }
}

int calculateRank(double **A, int rows, int cols){
	int i, j, k;
	for(i = 0; i < cols; i++) {
		// printMatrix(A, rows, cols);
		if(fabs(A[i][i]) != 0.00)
			for(j = 0; j < rows; j++)
				if(j != i) {
					/* Make all the elements above and below the current principal
                 diagonal element zero */
                double ratio = (double) A[j][i] / A[i][i];
                for(k = 0; k < cols; k++)
                    A[j][k] -= ratio * A[i][k];
				}
				else
					printf("\n");
		else
			for(j = i + 1; j < rows; j++)
				if(A[j][i] != 0) {
					swap(A, i, j, cols);
					break;
				}

			if(j == rows){
				--cols;
                for(j = 0; j < rows; j++)
                    A[j][i] = A[j][cols];
			}
			--i;
	}
	return cols;
}

void printMatrix(double **A, int rows, int cols) {	
	int i, j;
	for(i = 0; i < rows; i++) {
		printf("\n");
		for(j = 0; j < cols; j++)
			printf("%lf ", A[i][j]);
	}
}

void getMatrix(double **A, int rows, int cols) {
	int i, j;
	for(i = 0; i < rows; i++)
		for(j = 0; j < cols; j++)
			scanf("%lf", &A[i][j]);
}

long long C(int n, int r) {
    if(r > n / 2) r = n - r; // because C(n, r) == C(n, n - r)
    long long ans = 1;
    int i;
    for(i = 1; i <= r; i++) {
        ans *= n - r + i;
        ans /= i;
    }
    return ans;
}

