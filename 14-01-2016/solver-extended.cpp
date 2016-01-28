/*
	Abhinav Jain
	13MA20004
	Date: 07-01-2016
	Max:/ Min = Z = C^T X
    Subject to AX= b || AX < b || AX > b
    X >= 0
*/
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <math.h>

void swap(double **, int, int, int);
int calculateRank(int, int);
void printMatrix(double **, int, int);
void getMatrix(double **, int, int);
double** augmentMatrices(double **, double **, int, int);
long long Comb(int , int);
void getMin(int, int);
void getMax(int, int);
void solve(int);

double d[10] = { 0 };
double copied[10][10], ans[10][10], z[10];

int main() {
	/* Get Objective Function Z */
	int n, m;	//Number of variables and number of equations
	int i, j; // Dummy variables
	int rank, rank_aug;
    int choice;
	printf("Enter number of variables in the system:\n");
	scanf("%d", &n);
    printf("Choose type of constraint system:\n1. AX = b\n.2 AX < b\n 3. AX > b\n");
    scanf("%d", &choice);
    switch(choice) {
        case 1:
            printf("Enter number of equations in the system\n");
            scanf("%d", &m);
        break;
        case 2:
            printf("Enter number of in-equations in the system\n");
            scanf("%d", &m);
            n += m; //Add slack variables
        break;
        case 3:
            printf("Enter number of in-equations in the system\n");
            scanf("%d", &m);
            n += m; //Add slack variables
        break;
        default:
        printf("Wrong choice");

    }
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
	for(i = 0 ; i < m; i++) {
		for(j = 0 ; j < n; j++){
	        	copied[i][j] = A[i][j];
		}
    	}
	rank = calculateRank(m, n);;
	double **C = augmentMatrices(A, B, m, n); // Make (A | b)
	for(i = 0 ; i < m; i++) {
		for(j = 0 ; j <= n; j++){
	        	copied[i][j] = C[i][j];
		}
    	}
	rank_aug = calculateRank(m, n + 1);
	printf("Rank of A is : %d \n", rank);
        printf("Rank of A | b is : %d \n", rank_aug);
	if(rank != rank_aug) {
    		printf("No solution!\n");
    		return 0;
    	}
	int mo = n - rank;
    int pw2 = (int)pow(2, n);
    int cnt1 = 0, v, solInd = 0, ind = 0;
    for(int i = 1 ; i < pw2 ; i++){
    	v = i;
    	cnt1 = 0;
    	while(v != 0){
    		cnt1 = cnt1 + v%2;
    		v = v/2;
    	}
    	if(cnt1 != (n - mo))
    		continue;
    	for(int k = 0 ; k < rank ; k++)
    	{
    		v = i;
    		ind = 0;
        	for(j = 0 ; j < n ; j++){
        		if(v%2 == 1){
        			copied[k][ind++] = C[k][j];
        		}
        		v = v/2;
        	}
        	copied[k][ind] = C[k][n];
        }
        if(calculateRank(cnt1, cnt1) != cnt1)
            continue;
        for(int k = 0 ; k < rank ; k++)
        {
            v = i;
            ind = 0;
            for(j = 0 ; j < n ; j++){
                if(v%2 == 1){
                    copied[k][ind++] = C[k][j];
                }
                v = v/2;
            }
            copied[k][ind] = C[k][n];
        }
        ind = 0;
        solve(n - mo);
        v = i;
    	for(j = 0 ; j < n ; j++){
    		if(v%2 == 1){
    			ans[solInd][j] = d[ind++];
    		}
    		else{
    			ans[solInd][j] = 0;
    		}
    		v = v/2;            
    	}
    	solInd++;
    }
    // Print Basic Feasible Solutions
    for(int k = 0 ; k < solInd ; k++){
        int check = 1;
        for(int l = 0 ; l < n ; l++){
            if(ans[k][l] < 0){
                check = 0;
                break;
            }
        }
        if(check != 1)
            continue;
        printf("One BFS is ");
        for(int l = 0 ; l < n ; l++){
            printf("%6.2f ", ans[k][l]);
        }
        printf("\n");
        
    }
    // Answers in ans[][]
    printf("Enter coefficients of each variable as in objective function\n");
    for(i = 0 ; i < n ; i++) {
        scanf("%lf",&z[i]);
    }    
    int bl = 0;
    printf("Enter 1 for maximum, 2 for minimum, 3 to get both \n");
    scanf("%d", &bl);
    if(bl & (1 << 1))
        getMin(solInd, n);
	if(bl&1)
        getMax(solInd, n);
	// Free dynamically allocated memory 
	free(A);
	free(B);
	free(C);
   return 0;
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

void swap(int r1, int r2, int cols) {
	int i;
    for(i = 0; i < cols; i++) {
        double temp = copied[r1][i];
        copied[r1][i] = copied[r2][i];
        copied[r2][i] = temp;
    }
}

int calculateRank(int R, int C) {
	int rank = C;
	for (int row = 0; row < rank; row++) {
		if (copied[row][row]) {
    		for (int col = 0; col < R; col++) {
    			if (col != row) {
    				double mult = (double)copied[col][row] / copied[row][row];
    				for (int i = 0; i < rank; i++)
    					copied[col][i] -= mult * copied[row][i];
    			}
    		}
		} else {
			bool reduce = true;
			for (int i = row + 1; i < R; i++) {
				if (copied[i][row]) {
					swap(row, i, rank);
					reduce = false;
					break ;
				}
			}
			if (reduce) {
				rank--;
				for (int i = 0; i < R; i ++)
					copied[i][row] = copied[i][rank];
			}
			row--;
		}
	}
	return rank;
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

long long Comb(int n, int r) {
    if(r > n / 2) r = n - r; // because C(n, r) == C(n, n - r)
    long long ans = 1;
    int i;
    for(i = 1; i <= r; i++) {
        ans *= n - r + i;
        ans /= i;
    }
    return ans;
}

void getMin(int solInd, int var) {
    double mnanswer = 999999.0, curr = 0;
    for(int k = 0 ; k < solInd ; k++) {
        int check = 1;
        curr = 0;
        for(int l = 0 ; l < var ; l++) {
            if(ans[k][l] < 0){
                check = 0;
                break;
            }
        }
        if(check != 1)
            continue;
        for(int l = 0 ; l < var ; l++) {
            curr = curr + ans[k][l] * z[l];
        }
        if(mnanswer > curr)
            mnanswer = curr;
    }
    printf("The minimum is %6.1f\n", mnanswer);
}

void getMax(int solInd, int var) {
    double mxanswer = 0.0, curr = 0;
    for(int k = 0 ; k < solInd ; k++) {
        int check = 1;
        curr = 0;
        for(int l = 0 ; l < var ; l++) {
            if(ans[k][l] < 0) {
                check = 0;
                break;
            }
        }
        if(check != 1)
            continue;
        for(int l = 0 ; l < var ; l++) {
            curr = curr + ans[k][l] * z[l];
        }
        if(mxanswer < curr)
            mxanswer = curr;
    }
    printf("The maximum is %6.1f\n", mxanswer);
}

void solve(int n) {
    double  c;
    int i, j, k;
    for(int i = 0 ; i < 10 ; i++)
    	d[i] = 0;
    for(k = 0 ; k < n - 1 ; k++)
        for(i = k ; i < n - 1 ; i++) {
            c = (copied[i + 1][k] / copied[k][k]);
            for(j = 0 ; j <= n ; j++)
                copied[i + 1][j] -= c * copied[k][j];
        }
    for(i = 0; i < n; i++) {
        for(j = 0; j <= n; j++)
            printf("%6.1f",copied[i][j]);
        printf("\n");
    }
    for(i = n - 1 ; i >= 0 ; i--) {
        c = 0;
        for( j = i ; j <= n - 1 ; j++)
            c = c + copied[i][j] * d[j];
        d[i] = (copied[i][n] - c) / copied[i][i];
    }
}
