#include "s21_tools.h"
#include <stdlib.h>

int is_valid_pointer(void *a) {
    return (a != NULL) ? SUCCESS : FAILURE;
}

int is_valid_size(matrix_t *a) {
    return (a -> rows > 0 && a -> columns > 0) ? SUCCESS : FAILURE;
}

int is_valid_matrix(matrix_t *a) {
    return (is_valid_pointer(a) == SUCCESS && is_valid_size(a) == SUCCESS) ? SUCCESS : FAILURE;
}

int sum_and_sub(matrix_t *A, matrix_t *B, matrix_t *result, char operation) {
    int return_code = 0;
    if (is_valid_matrix(A) == SUCCESS && is_valid_matrix(B) == SUCCESS &&
                                    is_valid_pointer(result) == SUCCESS) {
        if (A -> rows == B -> rows && A -> columns == B -> columns) {
            return_code = s21_create_matrix(A -> rows, A -> columns, result);
            if (return_code == 0) {
                for (int i = 0; i < A -> rows; i++) {
                    for (int j = 0; j < A -> columns; j++) {
                        double temp = 0;
                        switch (operation) {
                        case '+':
                            temp = A -> matrix[i][j] + B -> matrix[i][j];
                            break;
                        case '-':
                            temp = A -> matrix[i][j] - B -> matrix[i][j];
                        default:
                            break;
                        }
                        result -> matrix[i][j] = temp;
                    }
                }
            }
        } else {
            return_code = 2;
        }
    } else {
        return_code = 1;
    }
    return return_code;
}
