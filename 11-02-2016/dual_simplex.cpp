/*
    Abhinav Jain
    13MA20004
    Date: 11-02-2016
    Max/Min: Z = C^T(X)
    Subject to AX >= b
    X >= 0
*/

/*
TODO: (Write Code)

- Take in number of variables
- Take in number of constraint (in)equations (<=, =, >= respectively)
- Take in objective function
- Convert constraints to equations
- Formulate min as max, otherwise let it be
- Now - Structure of condensed simplex tableau:
    
     ______________________________________________
    |       C_{n}|                                 |
    |C_{b}  B\NB |  x_{1}  x_{2}  x_{3} ..... x_{B}|
    |     x_{r}  |                                 |  <-- Check most -negative element in this column (Will decide the pRow)
    |   x_{r+1}  |                                 |
    |         .  |                                 |
    |         .  |                                 |
    |     x_{n}  |                                 |
    |______________________________________________|
                    z_{1}  z_{2}  z_{3} ...... z_{B}  <-- Take ratio of this row over the row decided

*/

int main(int argc, char const *argv[]) {
    
    return 0;
}