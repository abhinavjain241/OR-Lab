**Problem 1.**  
Max: Z = 2x<sub>1</sub> + 3x<sub>2</sub> + x<sub>3</sub>
         x<sub>1</sub> + x<sub>2</sub> + x<sub>3</sub>  <= 40
         2x<sub>1</sub> + x<sub>2</sub> -x<sub>3</sub>  >= 10
          -x<sub>2</sub> +x<sub>3</sub>      >= 10
     x<sub>1</sub>, x<sub>2</sub>, x<sub>3</sub> >= 0

**Problem 2.**  
Max: Z = 2x<sub>1</sub> + 3x<sub>2</sub> + x<sub>3</sub>
         x<sub>1</sub> + x<sub>2</sub> + x<sub>3</sub>  <= 40
         2x<sub>1</sub> +x<sub>2</sub> -x<sub>3</sub>   >= 10
          -x<sub>2</sub> +x<sub>3</sub>       = 10
     x<sub>1</sub>, x<sub>2</sub>, x<sub>3</sub> >= 0


Solved Example:
---------------

**PHASE I: LP Problem for Example 1 (P1)**

- Formulate an artificial objective function consisting of two artificial variables.

**A<sub>f</sub>=  x<sub>7</sub> +x<sub>8</sub>**
Min: A<sub>f</sub> = x<sub>7</sub> + x<sub>8</sub>
i.e. Max: -A<sub>f</sub> =  - x<sub>7</sub> -x<sub>8</sub>

**Phase I LP Problem:**

**Max: -A<sub>f</sub> =  - x<sub>7</sub> -x<sub>8</sub>**
Subject to:
    x<sub>1</sub> + x<sub>2</sub> +x<sub>3</sub>   +x<sub>4</sub> = 40
         2x<sub>1</sub> +x<sub>2</sub> -x<sub>3</sub>  -x<sub>5</sub> + x<sub>7</sub> = 10
          -x<sub>2</sub> +x<sub>3</sub>     -x<sub>6</sub> + x<sub>8</sub>    = 10
     x<sub>1</sub>, x<sub>2</sub>, x<sub>3</sub>, x<sub>4</sub>, x<sub>5</sub>, x<sub>6</sub> >= 0
     x<sub>7</sub>, x<sub>8</sub> >= 0  (Artificial Variables)

- Solve the Phase-I LP problem. As soon as artificial objective function becomes zero, 
terminate Phase I process. Then go to Phase II. If it is not possible to make all the artificial variables zero in Phase I, then the problem is infeasible.
- In Phase II  use the Original Objective function and the last Tableau of Phase-I.
- Drop the columns of artificial variables which are zero.
- With respect to Original Objective function find the indicator row elements.
- Then proceed with the steps of Simplex method to find the optimal solution.

**Note: Always Use Condensed form of the Simplex Tableau.**