#include "s21_matrix.h"
#include "s21_tools.h"
#include <stdlib.h>
#include <math.h>

int s21_transpose(matrix_t *A, matrix_t *result) {
    int return_code = 0;
    if (is_valid_matrix(A) == SUCCESS && is_valid_pointer(result) == SUCCESS) {
        return_code = s21_create_matrix(A -> columns, A -> rows, result);
        if (return_code == 0) {
            for (int i = 0; i < A -> rows; i++) {
                for (int j = 0; j < A -> columns; j++) {
                    result -> matrix[j][i] = A -> matrix[i][j];
                }
            }
        }
    } else {
        return_code = 1;
    }
    return return_code;
}

void new_pointer(double **a, double *b) {
    *a = b;
}

double det(double **a, int n) {
    if (n == 1) {
        return a[0][0];
    }
    if (n == 2) {
        return a[0][0] * a[1][1] - a[0][1] * a[1][0];
    }
    int number = 0;
    double sum = 0;
    double **temp = malloc((n-1) * sizeof(double*));
    for (int i = 0; i < n; i++) {
        number = 0;
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            new_pointer(&temp[number++], a[j]);
        }
        sum +=  pow(-1, i + n - 1) * a[i][n-1] * det(temp, n - 1);
    }
    free(temp);
    return sum;
}

int s21_determinant(matrix_t *A, double *result) {
    int return_code = 0;
    if (is_valid_matrix(A) && is_valid_pointer(result)) {
        if (A -> rows == A -> columns) {
            *result = det(A -> matrix, A -> rows);
        } else {
            return_code = 2;
        }
    } else {
        return_code = 1;
    }
    return return_code;
}
