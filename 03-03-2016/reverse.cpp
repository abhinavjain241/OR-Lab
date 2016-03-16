#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <cmath> 

using namespace std;

#define SIZE 15

double a[SIZE][SIZE], b[SIZE][SIZE], c[SIZE][SIZE], temp[SIZE][SIZE], t[SIZE][SIZE], d[SIZE][SIZE], ans[SIZE][SIZE], B[SIZE], C[SIZE], CB[SIZE], Y[SIZE], T[SIZE][SIZE], XB[SIZE], aplha[SIZE], k[SIZE][SIZE];

void getMat(double a[][SIZE], int row , int col) {
	int i, j;
	std::cout << "Give the matrix entries" << std::endl;
	for (i = 0 ; i < row ; i++)
		for (j = 0 ; j < col ; j++)
			cin >> a[i][j];
}

void getVector(double a[], int row) {
	int i;
	std::cout << "Give the matrix entries" << std::endl;
	for (i = 0 ; i < row ; i++)
		cin >> a[i];
}

void setIdentity(double b[][SIZE], int row, int col) {
	int i ,j;
	for (i = 0 ; i < row ; i++)
		for (j = 0 ; j < col ; j++){
			if(i == j){
				b[i][j] = 1;
			}
			else
				b[i][j] = 0;
		}	
}

void printMatrix(double a[][SIZE], int row, int col){
	int i, j;
	for (i = 0; i < row; i++){
		std::cout << "\n";
		for (j = 0; j < col; j++)
			std::cout << a [i][j] << "\t";
	}
}

void multiMat(double a[][SIZE], double b[][SIZE], int row, int col){
	int i, j, k;
	double sum;
	for(i = 0; i < row; i++)
		for(j = 0; j < col; j++){
			sum  = 0;
			for(k = 0; k < col; k++){
				
				sum += a[i][k] * b[k][j];
			}
			ans[i][j] = sum;
		}

}
void check(double a[][SIZE], int row, int col){
	int i,j;
	double p;
	p = a[col][col];
	for(i = 0; i < row; i++){
		a[i][col] /= -1 * p;
	}
	a[col][col] = (double)1/(p);
}

void multi1(double a[][SIZE], double b[][SIZE], int row, int col, int j){
	int i, k;
	double sum;
	for(i = 0; i < row; i++){
		sum  = 0;
		for(k = 0; k < col; k++){
				
			sum += a[i][k] * b[k][j];
		}
		d[i][0] = sum;
	}
	for(i = 0; i < row; i++){
		b[i][j] = d[i][0];
	}
}

void reverse(double a[][SIZE], int row, int col){
	int i, j, m;
	for(i = 0; i < row; i++){
		temp[i][0] = a[i][0];
	}
	for(i = 0; i < row ; i++)
		for(j = 1; j < col; j++)
			temp[i][j] = b[i][j];

	check(temp, row, 0);

	for(i = 0; i < row ; i++)
			for(j =0; j < col; j++)
				c[i][j] = temp[i][j];
	for(m = 1; m < col; m++){
		for(i = 0; i < row ; i++)
			for(j =0; j < col; j++)
				t[i][j] = b[i][j];
		

		for(i = 0; i < row; i++){
			t[i][m] = a[i][m];
		}
		multi1(c, t, row, col, m);
		check(t, row, m);
		multiMat(t, c, row, col);
		for(i = 0; i < row ; i++)
			for(j =0; j < col; j++)
				temp[i][j] = t[i][j];

		for(i = 0; i < row ; i++)
			for(j =0; j < col; j++)
				c[i][j] = ans[i][j];
	}
	std::cout << "\n" << "The inverse of the Matrix:" << std::endl;
	printMatrix(ans, row, col);
}

void yValue(double b[SIZE], double a[][SIZE], int row, int col){
	int i, k;
	double sum;
	for(i = 0; i < row; i++){
		sum  = 0;
		for(k = 0; k < col; k++){
				
			sum += b[k] * a[k][i];
		}
		Y[i] = sum;
	}
}
double mul(double y[SIZE], double a[][SIZE],int row,int col){
	int i, j;
	double sum;
	for(i = 0; i < row; i++){
		sum  += y[i] * a[i][col];
	}
	return sum;
}

int entering(double y[SIZE], double a[][SIZE], double c[SIZE], int row, int col){
	int i, j, index = 0;
	double temp;
	double min = 0;
	bool t = false;
	for(i = 0; i < col; i++){
		temp = mul(y, a, row, i);
		temp = temp - c[i];
		if(temp < 0){
			t = true;
			if(temp < min){
				min = temp;
				index = i;
			}
		}
	}
	if(t)
		return index;
	else
		return -2;
}

void setXB(double a[][SIZE], double b[SIZE],int row,int col){
	int i, k;
	double sum;
	for(i = 0; i < row; i++){
		sum  = 0;
		for(k = 0; k < col; k++){
				
			sum += a[i][k] * b[k];
		}
		XB[i] = sum;
	}

}

void setAlpha(double a[][SIZE], double b[][SIZE],int row,int col){
	int i, k;
	double sum;
	for(i = 0; i < row; i++){
		sum  = 0;
		for(k = 0; k < row; k++){
				
			sum += a[i][k] * b[k][col];
		}
		aplha[i] = sum;
	}

}

int main(){
	int row, col, i, j,m, y;
	std::cout << "Enter the no of equations" << std::endl;
	cin >> row;
	std::cout << "Enter the no of variables" << std::endl;
	cin >> col;
	std::cout << "Enter the coefficients of the matrix" << std::endl;
	getMat(a, row, col);
	setIdentity(b, row, row);
	std::cout << "Enter the constants of the equations" << std::endl;
	getVector(B, row);
	std::cout << "Enter the coefficients and constant for the objective function" << std::endl;
	getVector(C, col);

	for(i = 0; i < row ; i++)
		for(j =0; j < row; j++)
			T[i][j] = b[i][j];

	for(i = 0; i < row; i++)
		CB[i] = 0;

	for(i = 0; i < row; i++)
			for(j = 0 ; j < row; j++)
				k[i][j] = T[i][j];

	setXB(T, B, row, row);
	while(entering(Y, a, C, row, col) >= 0){
		int enter, leave;
		double min = 999999, ratio;
		yValue(CB, T, row, row);
		enter = entering(Y, a, C, row, col);
		
		setAlpha(T, a, row, enter);
		for(i = 0; i < row; i++){
			if(aplha[i] != 0){
				ratio = XB[i] / aplha[i];
				if(ratio < min){
					min = ratio;
					leave = i;
				}

			}
		}
		
		for(i = 0; i < row; i++){
			k[i][leave] = a[i][enter];
		}
		
		reverse(k, row, row);
		for(i = 0; i < row; i++)
			for(j = 0 ; j < row; j++)
				T[i][j] = ans[i][j];

		for(i = 0; i < row; i++){
			if(i == leave){
				CB[i] = C[enter];
			}
		}
		C[enter] = 0;
		for(i = 0; i < row; i++){
			a[i][enter] = 0;
			if(i == enter)
				a[i][enter] = 1;
		}	
		setXB(T, B, row, row);

	}
	double solution = 0;
	for(i = 0; i < row; i++){
		solution += CB[i] * XB[i];
	}
	std::cout << "The solution of LPP : " << solution << std::endl;
}