/*
	Abhinav Jain
	13MA20004
	Date: 07-01-2016
*/
#include <stdio.h>
#include <malloc.h>
#include <assert.h>

void swap(float *, int, int, int);
int calculateRank(float *, int, int);
int printMatrix(float *, int, int);
int getMatrix(float *, int, int);

int main() {
	/* Get Objective Function Z */
	int n;	//Number of variables
	int m;	//Number of equations
	printf("Enter number of variables in the system:\n");
	scanf("%d", &n);
	printf("Enter number of equations in the system\n");
	scanf("%d", &m);
	assert(n > m); // Number of variables should be more than the constraints
	int nbasic = n - m;
	float *A = (float *)malloc(m * n * sizeof(float));
	float *B = (float *)malloc(m * sizeof(float));
	printf("Enter coefficients of constraints equations in matrix form:");
	getMatrix(A, m, n); // Get A
	printf("Enter the right side values of the equations:");
	getMatrix(B, m, 1); // Get B
	printf("Rank of matrix A is:\n");
	printf("%d", calculateRank(A, m, n));
	free(A);
	free(B);
}

void swap(float *A, int r1, int r2, int cols)
{
	int i;
    for(i = 0; i < cols; i++) {
        float temp = *(A + r1 * cols + i);
        *(A + r1 * cols + i) = *(A + r2 * cols + i);
		*(A + r2 * cols + i) = temp;
    }
}

int calculateRank(float *A, int rows, int cols){
	int i, j, k;
	for(i = 0; i < cols; i++) {
		printMatrix(A, rows, cols);
		if(*(A + i * cols + i))
			for(j = 0; j < rows; j++)
				if(j != i) {
					/* Make all the elements above and below the current principal
                 diagonal element zero */
                float ratio = (*(A + j * cols + i)/ *(A + i * cols + i));
                for(k = 0; k < cols; k++)
                    *(A + j * cols + k) -= ratio * (*(A + i * cols + k));
				}
				else
					printf("\n");
		else
			for(j = i + 1; j < rows; j++)
				if(*(A + j * cols + i)) {
					swap(A, i, j, cols);
					break;
				}

			if(j == rows){
				--cols;
                for(j = 0; j < rows; j++)
                    *(A + j * cols + i) = *(A + (j + 1) * cols);
			}
			--i;
	}
	return cols;
}

int printMatrix(float *A, int rows, int cols) {	
	int i, j;
	for(i = 0; i < rows; i++) {
		printf("\n");
		for(j = 0; j < cols; j++)
			printf("%f ", *(A + i * cols + j));
	}
}

int getMatrix(float *A, int rows, int cols) {
	int i, j;
	for(i = 0; i < rows; i++)
		for(j = 0; j < cols; j++)
			scanf("%f", (A + i * cols + j));
}