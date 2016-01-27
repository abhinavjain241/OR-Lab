/*
    Abhinav Jain
    13MA20004
    Date: 21-01-2016
    Max: Z = C^T(X) + D
    Subject to AX <= b
    X >= 0
*/
#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <math.h>

#define SIZE 15

double d[SIZE] = { 0 };
double copied[SIZE][SIZE], ans[SIZE][SIZE], z[SIZE];
int x[SIZE]; // Swap Hash for upto SIZE variables

void swap(double **, int, int, int);
int calculateRank(int, int);
void printMatrix(double **, int, int);
void printStaticMatrix(double [][SIZE], int, int);
void getMatrix(double **, int, int);
double** augmentMatrices(double **, double **, int, int);
long long Comb(int , int);
void getMinimum(int, int);
void getMaximum(int, int);
void solve(int);
int checkNegative(double [][SIZE], int, int);

int main(){
    /* Get Objective Function Z */
    int n;  //Number of variables
    int m;  //Number of equations
    int i, j; // Dummy variables
    int rank, rank_aug;
    printf("Enter number of variables in the system:\n");
    scanf("%d", &n);
    printf("Enter number of in-equations in the system\n");
    scanf("%d", &m);
    // assert(n >= m); // Number of variables should be more than the constraints
    // Coefficient matrix [ m x n ]
    double **A = (double **)malloc(m * sizeof(double *));
    for(i = 0; i < m; i++)
        A[i] = (double *)malloc(n * sizeof(double));
    // Output matrix (Y - values) [ m x 1 ]
    double **B = (double **)malloc(m * sizeof(double *));
    for(i = 0; i < m; i++)
        B[i] = (double *)malloc(sizeof(double));
    printf("Enter coefficients of constraints equations in matrix form:");
    getMatrix(A, m, n); // Get A
    printf("Enter the right side values of the equations:");
    getMatrix(B, m, 1); // Get B
    for(i = 0 ; i < m; i++) {
        for(j = 0 ; j < n; j++){
                copied[i][j] = A[i][j];
        }
    }
    //Make Augmented Matrix and copy to static array
    double **Aug = augmentMatrices(A, B, m, n); // Make (A | b) [ m x (n + 1) ]
    for(i = 0 ; i < m; i++) {
        for(j = 0 ; j <= n; j++){
                copied[i][j] = Aug[i][j];
        }
    }
    // Objective Function Coefficients and Constant [ 1 x (n + 1) ]
    double **C = (double **)malloc((n + 1) * sizeof(double *));
    for(i = 0; i < m; i++)
        C[i] = (double *)malloc(sizeof(double));
    printf("Enter coefficients of objective function along with the constant:");
    getMatrix(C, n + 1, 1);
    // Add last row to the Simplex Tableau
    for(j = 0; j < n; j++){ // Last column will contain objective function
        copied[m][j] = -C[j][0];
    } 
    copied[m][n] = C[n][0];
    /* At this point, copied[][] contains the simplex tableau. */
    printf("Current State of Simplex Tableau:\n");
    printStaticMatrix(copied, m + 1, n + 1);
    while(checkNegative(copied, m + 1, n + 1) >= 0) {
        double min = 99999; int pRow = 0; double pivot = 0; bool infeasible = true;
        int pCol = checkNegative(copied, m + 1, n + 1);
        // std::cout << pCol << std::endl;
        for(i = 0; i < m; i++) {
            double ratio = copied[i][n] / copied[i][pCol];
            if(ratio >= 0) {
                infeasible = false;
                if (ratio < min) {
                    min = copied[i][n] / copied[i][pCol];
                    pRow = i;
                } 
            }
        }
        if(infeasible){
            printf("\nThere is no optimal solution to the given problem!\n");
            exit(0);
        }
        pivot = copied[pRow][pCol];
        printf("\nPivot element is at (%d, %d) and is equal to %lf.\n", pRow, pCol, pivot);
        for(i = 0; i < m + 1; i++) {
            for (j = 0; j < n + 1; j++) {
                if(i != pRow && j != pCol) {
                    copied[i][j] = pivot * copied[i][j] - copied[pRow][j] * copied[i][pCol];
                    copied[i][j] /= pivot;
                }
            }
        }
        x[pCol] = pRow; //Store position in Swap-Hash 
        for(j = 0; j < n + 1; j++) {
            if(j != pCol) 
                copied[pRow][j] /= pivot;
        }
        for(i = 0; i < m + 1; i++) {
            if(i != pRow) 
                copied[i][pCol] /= -pivot;
        }
        copied[pRow][pCol] = 1 / pivot;
        printf("\nCurrent State of Simplex Tableau:\n");
        printStaticMatrix(copied, m + 1, n + 1);
    }
    // Print Value of x(i)
    for(i = 0; i < n; i++) {
        printf("\nValue of x%d is %lf", i + 1, copied[x[i]][n]);
    } 
    printf("\nMaximum Value of LPP is: %lf\n", copied[m][n]);
}
 
void printMatrix(double **A, int rows, int cols) {  
    int i, j;
    for(i = 0; i < rows; i++) {
        printf("\n");
        for(j = 0; j < cols; j++)
            printf("%lf ", A[i][j]);
    }
}

void printStaticMatrix(double A[][SIZE], int rows, int cols) {  
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

int checkNegative(double A[][SIZE], int rows, int cols){
    double min = 0; bool flag = false; int min_index = 0;
    for(int i = rows - 1, j = 0; j < cols; j++) {
        if(A[i][j] < 0) {
            flag = true;
            if(A[i][j] < min) {
                min = A[i][j];
                min_index = j;
            }
        }
    }
    if(flag)
        return min_index;
    else
        return -1;  // If no number < 0 
}

