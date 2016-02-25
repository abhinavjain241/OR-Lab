#include <bits/stdc++.h>

using namespace std;

int indexofSmallestElement(double array[], int size) {
    int index = 0;
    cout<<endl;
    for(int i = 1; i < size; i++) {
        if(array[i] < array[index])
            index = i;
    }
    return index;
}

double find_replaced_element(double p, double q , double r, double s) {
	return (p*s - q*r)/p;
}

int check_equality(double vars[], double vars1[], int m) {
	int f=1;
	for (int i=0;i<m;i++) {
		for (int j=0;j<m;j++) {
			if (vars[i] != vars1[j]) {
			   f=0;
			   break;
			}
		}
	}
	return f;
}

int main()
{
	int n,m,choice,k=0, iterations=0;
	cout<<"Enter 1 to maximize and 0 to minimize"<<endl;
	cin>>choice;
	vector<pair<int,int> > elements;
	//*****************Inputs********************

	cout<<"Enter the number of equations and number of variables"<<endl;
	cin>>n>>m;
	int kk=m;
	double AA[n+1][m+1], BB[n+1][m+1], d, b[n], M=10000;
	int sign[n],k1=0,k2=0;
	cout<<"Enter the coefficients of the variables in the constraints"<<endl;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			cin>>AA[i][j];

	cout<<"Enter the matrix B along with 0 for less than, 1 for equality and 2 for greater than"<<endl;
	for(int i=0;i<n;i++)
		cin>>AA[i][m]>>sign[i];

	for(int i=0;i<n;i++) {
		if(sign[i]==2)
			sign[i]=0;
		else if (sign[i]==0)
			sign[i]=2;
	}
	for(int i=0;i<n;i++)
		if(sign[i]==1 || sign[i]==2)
			k1++;

	double A[n+1][m+1+k1],B[n+1][m+1+k1];
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			A[i][j]=AA[i][j];

	for(int i=0;i<n+1;i++)
		for(int j=m;j<m+k1;j++)
			A[i][j]=0;

	for (int i=0;i<n;i++)
		A[i][m+k1]=AA[i][m];

	for(int i=0;i<n;i++) {
		if(sign[i]) {
			A[i][k2+m]=-1;
			k2+=1;
		}
	}

	double vars[m];
	cout<<"Enter the coefficients of the varibles in the objective equation"<<endl;
	for(int i=0;i<m;i++)
		cin>>A[n][i];
	cout<<"Enter the value of d in the objective equation"<<endl;
	cin>>d;
	A[n][m+k1]=d;
	m = m + k1;

	if(choice)
		for(int i=0;i<=m;i++)
			A[n][i] *= -1;
	
	for (int i=0;i<=m;i++) {
		int s=0;
		for(int j=0;j<n;j++) {
			if(sign[j])
				s+=A[j][i];
		}
		A[n][i]-=1*s;
	}
	for(int i=0;i<n;i++) {
		for(int j=0;j<m+1;j++) {
			A[i][j]*=-1;
		}
		cout<<endl;
	}
	for(int i=0;i<n+1;i++) {
		for(int j=0;j<m+1;j++) {
			cout<<A[i][j]<<" ";
		}
		cout<<endl;
	}
	//*****************Inputs Over***************

	int x=1;
	while(1) {
		//double min_m=*min_element(A[n], A[n]+m);
		//cout<<min_m<<endl;
	//**************find the pivot element***************
		
		/*int pivot_c=indexofSmallestElement(A[n],m);
		for(int i=0;i<n;i++)
			b[i]=abs(A[i][m]/A[i][pivot_c]);
		int pivot_r=indexofSmallestElement(b,n);
		elements.push_back(make_pair(pivot_r, pivot_c));*/

		int cnt=0,pivot_r, pivot_c, check_2;
		double min_m=100000, mini=100000;
		for(int i=0;i<n;i++) {
			if(A[i][m]<min_m) {
				min_m=A[i][m];
				pivot_r=i;
			}
		}
		for(int i=0;i<m;i++) {
			if(A[n][i]>=0)
				cnt++;
		}
		if(min_m>0)
			break;
		if(cnt==0 and min_m>=0)
			break;
		for(int i=0;i<m;i++) {
			if(A[pivot_r][i]<0 && A[n][i] >=0) {
				if(mini>abs(A[n][i]/A[pivot_r][i])) {
					mini=abs(A[n][i]/A[pivot_r][i]);
					pivot_c=i;
				}
			}
		}
		//**************found pivot element*****************
		
		//***********Row and comlumn replacement************

		double pivot= A[pivot_r][pivot_c];
		for(int i=0;i<=m;i++)
			B[pivot_r][i] = A[pivot_r][i]/pivot;

		for(int i=0;i<=n;i++)
			B[i][pivot_c] = -1*A[i][pivot_c]/pivot;
		B[pivot_r][pivot_c] *= -1;
		B[pivot_r][pivot_c] /= pivot;

		//***********Row and column replaced***************

		//Rest of the matrix
		//Case 1 i<pivot_r, j<pivot_c:
		for(int i=0;i<=n;i++) {
			if(i==pivot_r)
				continue;
			for(int j=0; j<=m; j++) {
				if(j == pivot_c)
					continue;
				B[i][j]=find_replaced_element(A[pivot_r][pivot_c], A[i][pivot_c], A[pivot_r][j], A[i][j]);
			}
		}
		for(int i=0;i<=n;i++)
			for(int j=0;j<=m;j++)
				A[i][j]=B[i][j];
		memset(vars,0,sizeof(vars));
		for(int i=0; i<elements.size(); i++)
			vars[elements[i].second]=A[elements[i].first][m];
		if(A[n][m]>0)
			break;
		for(int i=0;i<n+1;i++) {
			for(int j=0;j<m+1;j++) {
				cout<<A[i][j]<<" ";
			}
			cout<<endl;
		}
	}
	if(abs(A[n][m])>M/10)
		cout<<"The problem is unbounded"<<endl;
	else {
		if(choice)
			cout<<"The maximum value of the equation is = "<<1*A[n][m]<<endl;
		else
			cout<<"The minimum value of the equation is = "<<-1*A[n][m]<<endl;	
	}
}