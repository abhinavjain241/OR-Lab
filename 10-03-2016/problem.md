Write a code for IPM ( Interior point method ) for solving a most general
LPP which has a maximum type objective function, m1 no. of <= type constraints, m2 no. of >= type constraints, m3  no. of equality type of constraints and n no. of non-negative decision variables. It is also assumed the the problem is feasible and has a optimal solution. Numerical examples will be provided later.

You may write the code for the LPP given below:

  Max:  Z=  c1 x1 + c2 x2 + c3 x3 +c4 x4
   subject  to
                a11 x1 + a12 x2 + a13 x3 + a14 x4  <= b1
                a21 x1 + a22 x2 + a23 x3 + a24 x4  >= b2
                a31 x1 + a32 x2 + a33 x3 + a34 x4   = b3
                x1, x2, x3, x4  >= 0     where    b1,b2,b3 > 0.

In this LPP n= 4, m = 3 (m1 = 1, m2 = 1, m3 = 1, m = m1 + m2 + m3 = 3)

(Include slack, surplus and artificial  variables and find a trial solution for the system of linear equations AX= b where all the variables are +ve set k = 1 Iter No)

Terminate the process if |X_j(k+1) - X_j(k)| <  epsilon  for all j

j = 1, 2, 3,   .... N  (   k = 1, 2, 3, 4, ......,  k= Iter. no )

N= Total number of variables including slack surplus and artificial variables
Let epsilon = 0.0001
    alpha = 0.5, 0 < alpha < 1

For Max type t = 1 and for Min type t = -1
You may use the product form of inverse in your code.