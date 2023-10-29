#include <stdint.h>

/** EX: E4.0

Matrix arithmetic operations are commonly required in many
algorithms. In this exercise you are required to write four
functions which will implement some common matrix operations.

Specifically:
    matrix_sum()   - Matrix addition: A + B
    matrix_add()   - Scalar addition: A + k
    matrix_scale() - Scalar multiplication: A * k
    matrix_mul()   - Matrix multiplication: A * B

A matrix of dimensions m x n has m rows and n columns.
In C, this can be represented as a 2-dimensional array of the form:

    matrix[m][n]

When passing a matrix as an argument to a function,
a pointer to the first element of the array must be used.
This allows us to accommodate for different dimension matrices,
by supplying an additional argument containing the dimensions of
that matrix.

The dimensions of a matrix must be represented as a
pointer to a two-element array of unsigned 8-bit integers containing:
 - the number of rows in the first element
 - the number of columns in the second element

For this exercise:
 - Matrices are to be represented as 2-dimensional arrays of
   signed 16-bit integers.
 - Scalars are to be represented as signed 16-bit integers.

You must define prototypes for your functions in extension04.h so that they
may be called by external code. The implementation of each function should be
placed in extension04.c.

To test your functions, you may use the example code provided in main.c
and print matrices via the serial interface. main.c will be replaced
by our own test code on Gradescope.

For the following tasks, consider the 2 x 2 matrix A:

A = [ 1 2 ]
    [ 3 4 ]

and the 2 x 3 matrix B:

B = [ 1 2 3 ]
    [ 4 5 6 ]

*/

/** FUNCTION: matrix_sum() (Matrix Addition)

DESCRIPTION:

Computes the sum of two matrices of the same dimension, A and B,
by adding corresponding elements of A and B.

As this operation is element-wise, the resulting matrix will have
the same dimensions as A and B.

EXAMPLE:

B + B = [ 1 2 3 ] + [ 1 2 3 ]
        [ 4 5 6 ]   [ 4 5 6 ]

      = [ 1+1 2+2 3+3 ]
        [ 4+4 5+5 6+6 ]

      = [ 2  4  6 ]
        [ 8 10 12 ]

TASK: Write a function that computes the sum of two matrices.
ARGUMENTS: Arguments must be passed in the following order:
- matrix A
- dimensions of A or B
- matrix B
- result matrix
*/

/** CODE: Write your code for matrix_sum() below this line. */

void matrix_sum(int16_t **a, int16_t *d, int16_t **b, int16_t **r){
  // decode d into rows and colums
  // itterate over rows of a
      //iterate columns
      //add position to same position if matrix b
  // return result
  int16_t rows = d[0]; // first element of d
  int16_t cols = d[1]; // second element of d
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){
      r[i][j] = a[i][j] + b[i][j];
    }
  }
}

/** CODE: Write your code for matrix_sum() above this line. */

/** FUNCTION: matrix_add() (Scalar Addition)

DESCRIPTION:

Computes the sum of a matrix, A, and a scalar, k, by adding k to
each element of A.

As this operation is element-wise, the resulting matrix will have
the same dimensions as A.

EXAMPLE:

B + 1 = [ 1 2 3 ] + 1
        [ 4 5 6 ]

      = [ 1+1 2+1 3+1 ]
        [ 4+1 5+1 6+1 ]

      = [ 2 3 4 ]
        [ 5 6 7 ]

TASK: Write a function that computes the sum of matrix and a scalar.
ARGUMENTS: Arguments must be passed in the following order:
- matrix A
- dimensions of A
- scalar addend k
- result matrix
*/

/** CODE: Write your code for matrix_add() below this line. */

void matrix_add(int16_t **a, int16_t *d, int16_t k, int16_t **r){
  // decode d into rows and colums
  // itterate over rows of a
      //iterate columns
      //add position to same position if matrix b
  // return result
  int16_t rows = d[0]; // first element of d
  int16_t cols = d[1]; // second element of d
  int16_t result[rows][cols];
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){
      result[i][j] = a[i][j] + k;
    }
  }
  r = result;
}

/** CODE: Write your code for matrix_add() above this line. */

/** FUNCTION: matrix_scale() (Scalar Multiplication)

DESCRIPTION:

Computes the product of a matrix, A, and a scalar, k, by multiplying
each element of A by k.

As this operation is element-wise, the resulting matrix will have
the same dimensions as A.

EXAMPLE:

B * 2 = [ 1 2 3 ] * 2
        [ 4 5 6 ]

      = [ 1*2 2*2 3*2 ]
        [ 4*2 5*2 6*2 ]

      = [ 2  4  6 ]
        [ 8 10 12 ]

TASK: Write a function that computes the product of a matrix and a scalar.
ARGUMENTS: Arguments must be passed in the following order:
- matrix A
- dimensions of A
- scalar multiplicand k
- result matrix
*/

/** CODE: Write your code for matrix_scale() below this line. */

void matrix_scale(int16_t **a, int16_t *d, int16_t k, int16_t **r){
  // decode d into rows and colums
  // itterate over rows of a
      //iterate columns
      //add position to same position if matrix b
  // return result
  int16_t rows = d[0]; // first element of d
  int16_t cols = d[1]; // second element of d
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){
      r[i][j] = a[i][j] * k;
    }
  }
}

/** CODE: Write your code for matrix_scale() above this line. */

/** FUNCTION: matrix_mul() (Matrix Multiplication)

DESCRIPTION:

Computes the matrix product of the m x p matrix A and
p x n matrix B, by taking the dot product of the
rows in A and the columns in B.

The resulting matrix will have dimensions m x n.

EXAMPLE:

By treating the rows of A as row vectors, and the columns of B as column vectors,
we can identify the dot products required to compute A * B:

A = [ --a1-- ]
    [ --a2-- ]
    [   ...  ]

B = [ |  |  |      ]
    [ b1 b2 b3 ... ]
    [ |  |  |      ]

A * B = [ (a1 . b1) (a1 . b2) (a1 . b3) ... ]
        [ (a2 . b1) (a2 . b2) (a2 . b3) ... ]
        [    ...       ...       ...    ... ]

The dot product of a row vector and column vector is demonstrated below:

Consider the row vector a:

a = [ 1 2 ]

and the column vector b:

b = [ 1 ]
    [ 4 ]

The dot product of a and b is the sum of the element-wise products of a and b

a . b = 1*1 + 2*4
      = 1 + 8
      = 9

Therefore, by performing the dot product of each row vector in A with each column vector in B,
we can compute the matrix product of A and B:

A * B = [ 1 2 ] * [ 1 2 3 ]
        [ 3 4 ]   [ 4 5 6 ]

      = [ (1*1 + 2*4) (1*2 + 2*5) (1*3 + 2*6) ]
        [ (3*1 + 4*4) (3*2 + 4*5) (3*3 + 4*6) ]

      = [  9 12 15 ]
        [ 19 26 33 ]

Note that the inner dimensions of A and B (p) must be equal,
otherwise the dot product cannot be computed.

You do not need to perform any error handling for this,
and can assume that all tests use valid arguments.

TASK: Write a function that computes the product of two matrices.
ARGUMENTS: Arguments must be passed in the following order:
- matrix A
- dimensions of A
- matrix B
- dimensions of B
- result matrix
*/

/** CODE: Write your code for matrix_mul() below this line. */

void matrix_mul(int16_t **a, int16_t *da, int16_t **b, int16_t*db, int16_t **r){
  // decode d into rows and colums
  // itterate over rows of a
      //iterate columns
      //add position to same position if matrix b
  // return result
  int16_t rowsa = da[0]; // first element of da
  int16_t colsa = da[1]; // second element of da
  int16_t colsb = db[1]; // second element of db

  for (int i = 0; i < rowsa; i++){
    int p = 0;
    for (int j = 0; j < colsa; j++){
      for (int k = 0; k < colsb; k++){
        p += a[i][k] * b[k][j];
      }
      r[i][j] = p;
      p = 0;
    }
  }
}

/** CODE: Write your code for matrix_mul() above this line. */

/** RESOURCE: You can find many examples of these operations online. */
// https://online.stat.psu.edu/statprogram/reviews/matrix-algebra/arithmetic
