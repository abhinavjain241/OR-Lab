/*
    Abhinav Jain
    13MA20004
    Date: 28-01-2016
    Max: Z = C^T(X)
    X >= 0
*/

#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>

#define SIZE 15
#define M 99999.0

double a[SIZE][SIZE], b[SIZE][SIZE], temp[SIZE][SIZE], r[SIZE][SIZE];
int dc[SIZE];

void setMatrix(double [][SIZE], int &, int &, int []);
void getMatrix(double [][SIZE], int, int);
int check(double [][SIZE], int, int);
void printMatrix(double [][SIZE], int, int); 

int main(){
	int i, j, m, n, count;
	bool flag = true;
	int ob = 0;
	for(i = 0; i < SIZE; i++)
		dc[i] = 0;
	std::cout << "Enter the no of variables:" << std::endl;
 	scanf("%d", &n);
	std::cout << "Enter the no of equations:" << std::endl;
	scanf("%d", &m);
	count = n;
	std::cout << "Enter the coefficients of the matrix:" << std::endl;
	setMatrix(a, m, n, dc);
	std::cout << "Enter the constants of the equations:" << std::endl;
	getMatrix(b, m, 1);
	std::cout << "Enter the coefficients and constant for the objective function:" << std::endl;
	getMatrix(r, 1, n);
	std::cout << "Enter\n 1. Maximum\n2.Minimum\n" << std::endl;
	scanf("%d", &ob);
	for(i = 0; i < m; i++){
		for(j = 0; j < n; j++)	
			temp[i][j] = a[i][j];
	}
	for(i = 0; i < m; i++)
		temp[i][n] = b[i][0];
	for(i = 0; i <= n; i++){
		temp[m][i] = -r[0][i];
		for(j = 0; j < m; j++){
			if(dc[j] == 1){
				temp[m][i] -= (double)(M * temp[j][i]);
			}
		}	
	}
	printMatrix(temp, m + 1, n + 1);
	while(check(temp, m, n) >= 0) {
		int pRow, pCol;
		double pivot, min = 88888999.0;
		pCol = check(temp, m, n);
		for(j = 0; j < n; j++){
			if(temp[m][pCol] == temp[m][j]){
				for(i = 0; i < m; i++){
					if((double)(temp[i][n] / temp[i][j]) < min && (double)(temp[i][n] / temp[i][j]) > 0){
						min = (double)(temp[i][n] / temp[i][j]);
						pRow = i;
						pCol = j;
					}
				}
			}
		}
		pivot = temp[pRow][pCol];
		std::cout << "\nPivot element is :" << pivot << std::endl;
		for(i = 0; i < m + 1; i++){
			for(j = 0; j < n + 1; j++){
				if(i != pRow && j != pCol){
					temp[i][j] = temp[i][j] * pivot - temp[pRow][j] * temp[i][pCol];
					temp[i][j] /= pivot;
				}
			}
		}
		for(j = 0; j < n + 1; j++){
			if(j != pCol){
				temp[pRow][j] /= pivot;
			}
		}
		for(i = 0; i < m + 1; i++){
			if(i != pRow)
				temp[i][pCol] /= -pivot;
		}
		temp[pRow][pCol] = 1 / pivot;
		std::cout << "\nCurrent Simplex table is:" << std::endl;
		printMatrix(temp, m + 1, n + 1);
		for(i = 0; i < n; i++){
			if(temp[m][i] == 0){
				flag = false;
				break;
			}
		}
		if(flag == false)
			break;

	}
	if(flag)
		if(abs(temp[m][n]) >= M)
			std::cout << " No Solutions" << std::endl;
		else{
			if(ob == 2)
				std::cout << "\nMaximum Value of LPP is :" << -temp[m][n] << std::endl;
			else
				std::cout << "\nMaximum Value of LPP is :" << temp[m][n] << std::endl;
		}
	else
		std::cout << "\nInfinite Solutions" << std::endl;
		
}

void setMatrix(double a[][SIZE], int &row, int &col, int dc[SIZE]){
	int i, j, d, k;
	int c = col;
    for(i = 0; i < row; i++){
    	std::cout << "\nEnter 1. Ax <= b, 2. Ax >= b, 3. Ax = b" << std::endl;
    	scanf("%d", &d);
    	if(d == 1){
        	for(j = 0; j < c; j++)
            	scanf("%lf", &a[i][j]);
    	}
    	if(d == 3){
        	for(j = 0; j < c; j++)
            	scanf("%lf", &a[i][j]);
            dc[i] = 1;
    	}
    	if(d == 2){
    		for(j = 0; j < c; j++)
            	scanf("%lf", &a[i][j]);
            j = col;
            col += 1;
            for(k = 0; k < row; k++){
            	if(i == k){
            		a[k][j] = -1;
            		continue;
            	}
            	a[k][j] = 0;
            }
             dc[i] = 1;
    	}
    }
}

void getMatrix(double A[][SIZE], int rows, int cols) {
    int i, j;
    for(i = 0; i < rows; i++)
        for(j = 0; j < cols; j++)
            scanf("%lf", &A[i][j]);
}

int check(double a[][SIZE], int row, int col) {
	int i, j, index = 0;		
	double min = 0;
	bool t = false;
	for(j = 0; j < col; j++){
		if(a[row][j] < 0){
			t = true;
			if(a[row][j] < min){
				min = a[row][j];
				index = j;
			}
		}
	}
	if(t)
		return index;
	else
		return -2;

}

void printMatrix(double A[][SIZE], int rows, int cols) {  
    int i, j;
    for(i = 0; i < rows; i++) {
        printf("\n");
        for(j = 0; j < cols; j++)
            printf("%lf ", A[i][j]);
    }
}