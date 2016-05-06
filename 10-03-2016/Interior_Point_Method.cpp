#include <bits/stdc++.h>

using namespace std;

void MatInverse(double Br[][10], double Br_inv[][10], int n)
{
	int r=0,i,j,k, m=1;
	double B[n][n], B_inv[n][n], e[n][1], c[n][1], eta[n][1], Er[n][n];
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			if(i==j)
				B[i][j]=1;
			else
				B[i][j]=0;
		}

	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			B_inv[i][j]=B[i][j];

	while(r!=-1)
	{
		r=-1;
		/*find which column is not equal*/
		for(j=0;j<n;j++)
		{
			for(i=0;i<n;i++)
			{
				if(B[i][j]!=Br[i][j])
				{
					r=j;
					break;
				}
			}
			if(r!=-1)
				break;
		}
		if(r==-1)
			continue;
		memset(c,0,sizeof(c));
		for(i=0;i<n;i++)
			c[i][0]=Br[i][r];
		/*found which column is not equal*/
		/*Finding the matrix E*/
		for(i=0;i<n;i++)
		{
			for(j=0;j<1;j++)
			{
				e[i][j]=0;
				for(k=0;k<n;k++)
				{
					e[i][j] += B_inv[i][k] * c[k][j];
				}
			}
		}

		for(i=0;i<n;i++)
			eta[i][0] = -1*e[i][0]/e[r][0];

		eta[r][0] /= -1*e[r][0];
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
			{
				if(i!=j)
					Er[i][j]=0;
				else
					Er[i][j]=1;
			}

		for(i=0;i<n;i++)
			Er[i][r]=eta[i][0];
		/*Developed the matrix Er */

		for(i=0; i<n;i++)
		{
			for(j=0; j<n; j++)
			{
				Br_inv[i][j]=0;
				for(k=0;k<n;k++)
				{
					Br_inv[i][j] += Er[i][k] * B_inv[k][j];
				}
			}
		}


		for(i=0;i<n;i++)
			B[i][r]=Br[i][r];
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				B_inv[i][j]=Br_inv[i][j];

	}
}

void multiplication(double a[][10], double b[][10], double mult[][10],int r1,int c1,int r2,int c2)
{
    int i,j,k;
    for(i=0; i<r1; ++i)
	    for(j=0; j<c2; ++j)
	    {
	       mult[i][j]=0;
	    }

    for(i=0; i<r1; ++i)
	    for(j=0; j<c2; ++j)
		    for(k=0; k<c1; ++k)
		    {
		        mult[i][j]+=a[i][k]*b[k][j];
		    }
}

int main()
{
	/*INPUTS START*/

	int n,m,i,j, i1=0, i2=0, i3=0, ik;
	cout<<"Enter the number of variables and the number of equations"<<endl;
	cin>>n>>m;
	double A1[10][10];
	int index=n;
	cout<<"Enter the elements of the Coefficient Matrix along with 1 for less than, 2 for greater than, 3 for equality constraints: "<<endl;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n+1;j++)
		{
			cin>>A1[i][j];
			if(j==n)
			{
				if(A1[i][j]==1)
					i1 += 1;
				else if(A1[i][j]==2)
					i2 += 1;
				else if(A1[i][j]==3)
					i3 += 1;
			}
		}
	}
	int N=n+i1+i3+2*i2;
	vector<int> pos;
	double A[10][10], D[10][10], eps=0.00001, alpha=0.5, B[10][10], C[10][10], vars[10][10];
	memset(C,0,sizeof(C));
	memset(D,0,sizeof(D));
	memset(A,0,sizeof(A));
	memset(vars,0,sizeof(vars));
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			A[i][j]=A1[i][j];

	for(i=0;i<m;i++)
	{
		if(A1[i][n]==1)
		{
			A[i][index]=1;
			index+=1;
		}
		else if(A1[i][n]==2)
		{
			A[i][index]=-1;
			A[i][index+1]=1;
			index+=2;
			pos.push_back(index-1);
		}
		else if(A1[i][n]==3)
		{
			A[i][index]=1;
			index+=1;
			pos.push_back(index-1);
		}
	}

	cout<<"Enter the coefficients of the variables in the objective function"<<endl;
	for(i=0;i<n;i++)
		cin>>C[i][0];
	cout<<"Enter the value to the right of the inequality"<<endl;
	for(i=0;i<m;i++)
		cin>>B[i][0];
	
	for(i=0;i<n;i++)
		vars[i][0]=0.0005;
	
	index=n;

	for(i=0;i<N;i++)
	{
		cout<<"Enter the value of variable "<<i+1<<": ";
		cin>>vars[i][0];
		cout<<endl;
	}
	cout<<"Iteration 0: ";
	for(i=0;i<N;i++)
		cout<<vars[i][0]<<" ";
	cout<<endl;
	/*INPUTS END*/
	while(1)
	{
		for(i=0;i<N;i++)
			D[i][i]=vars[i][0];

		double A_bar[10][10],A_barT[10][10], C_bar[10][10], P[10][10], Cp[10][10], X_bar[10][10], vars_1[10][10], interim_1[10][10], interim_2[10][10], interim_3[10][10], interim_4[10][10], vars_2[10][10];
		

		multiplication(A, D, A_bar, m, N, N, N);
		for(i=0;i<N;i++)
		{
			for(j=0;j<m;j++)
			{
				A_barT[i][j]=A_bar[j][i];
			}
		}
		multiplication(D, C, C_bar, N, N, N, 1);
		multiplication(A_bar, A_barT, interim_1, m, N, N, m);
		MatInverse(interim_1, interim_2, m);
		multiplication(A_barT, interim_2, interim_3, N, m, m, m);
		multiplication(interim_3, A_bar, interim_4, N, m, m, N);
		

		for(i=0;i<N;i++)
			for(j=0;j<N;j++)
			{
				if(i==j)
					P[i][j] = 1 - interim_4[i][j];
				else
					P[i][j] = -1 * interim_4[i][j];
			}

		multiplication(P, C_bar, Cp, N, N, N, 1);

		double v=-10000;
		for(i=0;i<N;i++)
		{
			if(Cp[i][0]<0 & abs(Cp[i][0])>v)
				v=abs(Cp[i][0]);
		}
		for(i=0;i<N;i++)
			X_bar[i][0]=1+((alpha*Cp[i][0])/v);

		double diff[N];
		multiplication(D, X_bar, vars_1, N, N, N, 1);
		for (i=0;i<N;i++)
			diff[i] = abs(vars[i][0] - vars_1[i][0]);
		double xm=*min_element(diff, diff+n);

		cout<<"Iteration "<<ik+1<<" :";

		for(i=0;i<N;i++)
		{
			vars[i][0]=vars_1[i][0];
			cout<<vars_1[i][0]<<" ";
		}
		cout<<endl;
		ik+=1;
		if(xm<eps)
			break;
	}
	int f=1;
	for(i=0;i<pos.size();i++)
	{
		if(vars[pos[i]][0]>=eps*10)
		{
			f=0;break;
		}
	}
	f=1;
	if(f)
	{
		double val=0.0;
		for(i=0;i<N;i++)
			val += C[i][0]*vars[i][0];
		cout<<"The optimal value is: "<<val<<endl;
		cout<<"The value of the variable of the optimal solution are: "<<endl;
		for(i=0;i<N;i++)
			cout<<" x"<<i+1<<" = "<<vars[i][0];
		cout<<endl;
	}
	else
		cout<<"The solution is infeasible"<<endl;
	return 0;
}