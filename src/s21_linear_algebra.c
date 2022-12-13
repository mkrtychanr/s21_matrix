#include "s21_matrix.h"
#include "s21_tools.h"
#include <stdlib.h>

int s21_transpose(matrix_t *A, matrix_t *result) {
    int return_code = 0;
    if (is_valid_matrix(A) == SUCCESS && is_valid_pointer(result) == SUCCESS) {
        s21_create_matrix(A -> columns, A -> rows, result);
        for (int i = 0; i < A -> rows; i++) {
            for (int j = 0; j < A -> columns; j++) {
                result -> matrix[j][i] = A -> matrix[i][j];
            }
        }
    } else {
        return_code = 1;
    }
    return return_code;
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

int s21_calc_complements(matrix_t *A, matrix_t *result) {
    int return_code = 0;
    if (is_valid_matrix(A) && is_valid_pointer(result)) {
        if (A -> rows == A -> columns) {
            s21_create_matrix(A -> rows, A -> rows, result);
            fill_matrix_with_minors(A, result);
        } else {
            return_code = 2;
        }
    } else {
        return_code = 1;
    }
    return return_code;
}