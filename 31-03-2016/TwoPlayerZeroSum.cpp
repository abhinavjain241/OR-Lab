#include <bits/stdc++.h>

#define INF 99999
#define MAX 30
#define FOR(i, a, b, n) for(i = a; i < b; i = i + n)
#define FORe(i, a, b, n) for(i = a; i <= b; i = i + n)

using namespace std;

double mat[MAX][MAX];
double temp[MAX][MAX];
int eqn = 0, var = 0;
bool infinite, unbounded;

void printTableau(){
    static int no = 0;
    std::cout << "Tableau no." << (++no) << std::endl;
     for(int i = 0 ; i <= eqn ; i++) {
          for(int j = 0 ; j <= var; j++) {
               std::cout << fixed << setw(7) << setprecision(3) << std::setfill(' ') << mat[i][j] << " ";
          }
          std::cout << std::endl;
     }
     std::cout << std::endl;
}

void copyFromTemp(){
     for(int i = 0 ; i <=eqn ; i++){
          for(int j = 0 ; j <= var; j++){
               mat[i][j] = temp[i][j];
          }
     }
}

int getPivotRow(int pivotCol){
	int ind = -1;
	float currMin = 100000;
	for(int i = 0 ; i < eqn; i++){
	    if(mat[i][pivotCol] <= 0)
	        continue;
	    if((mat[i][var]/mat[i][pivotCol]) < currMin){
	        ind = i;
	        currMin = (mat[i][var]/mat[i][pivotCol]);
	    }
	}
	return ind;
}

int getMinFromLastRow(){
    int ind = -1;
    float currMin = 0;
    for(int i = 0 ; i < var ; i++){
          if(mat[eqn][i] > 0)
               continue;
          if(mat[eqn][i] == 0){
               infinite = true;
               return -1;
          }
          if(mat[eqn][i] < currMin){
               currMin = mat[eqn][i];
               ind = i;
         }
    }
    return ind;
}

int getPivotCol(int pivotRow){
     int ind = -1;
     float currMin = 100000;
     for(int i = 0 ; i < var; i++){
          if(mat[pivotRow][i] >= 0)
               continue;
          if(abs(mat[eqn][i]/mat[pivotRow][i]) < currMin){
               ind = i;
               currMin = abs(mat[eqn][i]/mat[pivotRow][i]);
           }
     }
     return ind;
}

int getMinFromLastCol(){
    int ind = -1;
    float currMin = 0;
    for(int i = 0 ; i < eqn ; i++){
          if(mat[i][var] > 0)
               continue;
          if(mat[i][var] == 0){
               infinite = true;
               return -1;
          }
          if(mat[i][var] < currMin){
               currMin = mat[i][var];
               ind = i;
         }
    }
    return ind;
}

void compute(){
	int pivotRow, pivotCol;
    while((pivotCol = getMinFromLastRow()) != -1){
    	printTableau();
      	if((pivotRow = getPivotRow(pivotCol)) == -1){
	           unbounded = true;
	           return;
	      }
	    for(int i = 0 ; i <= eqn ; i++) {
	    	for(int j = 0 ; j <= var; j++) {
	    		if(i == pivotRow && j == pivotCol)
	    			temp[i][j] = 1/mat[i][j];
	    		else if(i == pivotRow)
	    			temp[i][j] = (mat[i][j])/mat[pivotRow][pivotCol];
	    		else if(j == pivotCol)
	    			temp[i][j] = ((-1)*mat[i][j])/mat[pivotRow][pivotCol];
	    		else 
	    			temp[i][j] = ((mat[pivotRow][pivotCol]*mat[i][j]) - (mat[pivotRow][j]*mat[i][pivotCol]))/mat[pivotRow][pivotCol];
	           }
	       }
	       copyFromTemp();
	   }
	   printTableau();
}

void compute_dual(){
     int pivotRow, pivotCol;
     while((pivotRow = getMinFromLastCol()) != -1){
          printTableau();
          if((pivotCol = getPivotCol(pivotRow)) == -1){
               unbounded = true;
               return;
          }
          for(int i = 0 ; i <= eqn ; i++){
               for(int j = 0 ; j <= var; j++){
                    if(i == pivotRow && j == pivotCol)
                         temp[i][j] = 1/mat[i][j];
                    else if(i == pivotRow)
                         temp[i][j] = (mat[i][j])/mat[pivotRow][pivotCol];
                    else if(j == pivotCol)
                         temp[i][j] = ((-1)*mat[i][j])/mat[pivotRow][pivotCol];
                    else{
                        temp[i][j] = ((mat[pivotRow][pivotCol]*mat[i][j]) - (mat[pivotRow][j]*mat[i][pivotCol]))/mat[pivotRow][pivotCol];
                    }
               }
          }
          copyFromTemp();
     }
     printTableau();
}

int main(int argc, char const *argv[]) {
	int m, n; 	// m rows and n columns
	double A[MAX][MAX];
	std::cout << "Size of the matrix? (m, n):";
	std::cin >> m >> n;
	double min, max, gameValue;
	vector<double> minGain, maxLoss;
	std::cout << "Enter the payoff matrix" << std::endl;
	for (int i = 0; i < m; ++i) {
		min = INF;
		for (int j = 0; j < n; ++j) {
			std::cin >> A[i][j];
			// For given i
			if (A[i][j] < min) {
				min = A[i][j];
			}
		}
		minGain.push_back(min);
	}
	for (int j = 0; j < n; ++j) {
		max = -INF;
		for (int i = 0; i < m; ++i) {
			// For given j
			if (A[i][j] > max) {
				max = A[i][j];
			}
		}
		maxLoss.push_back(max);
	}
	double minimax = *min_element(maxLoss.begin(), maxLoss.end());
	double maximin = *max_element(minGain.begin(), minGain.end());
	std::cout << "Minimax value is " << minimax << std::endl;
	std::cout << "Maximin value is " << maximin << std::endl;
	assert(minimax >= maximin);
	if (minimax == maximin) {
		gameValue = minimax;
		std::cout << "The value of the game is:" << gameValue;
		exit(0);
	} else {
		std::cout << "The game is unstable. Proceeding on to solve using LPP method.";
	}
	//Set var and eqn to n and m respectively
	var = n;
	eqn = m;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			mat[i][j] = A[i][j];
		}
		mat[i][n] = 1;
	}
	for (int j = 0; j < n; ++j) {
		mat[m][j] = -1;
	}
	mat[m][n] = 0;
	std::cout << "Solving by Primal Simplex Method" << std::endl;
    compute();
    std::cout << "Game Value:" << (1/mat[m][n]) << std::endl << std::endl;
    //Solve for Player A using dual simplex method
    var = m;
    eqn = n;
    for (int i = 0; i < n; ++i) {
    	for (int j = 0; j < m; ++j) {
    		mat[i][j] = -A[j][i];
    	}
    	mat[i][m] = -1;
    }
    for (int j = 0; j < m; ++j) {
    	mat[n][j] = -1;
    }
    mat[n][m] = 0;
	std::cout << "Solving by Dual Simplex Method" << std::endl;
    compute_dual();
    std::cout << "Game Value:" << (1/mat[m][n]) << std::endl << std::endl;
	return 0;
}