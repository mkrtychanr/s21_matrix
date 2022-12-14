#include "check_s21_linear_algebra.h"

START_TEST(test_s21_transpose_matrix) {
    matrix_t a;
    matrix_t result;
    matrix_t expected;
    int return_code = 0;
    s21_create_matrix(3, 2, &a);
    s21_create_matrix(2, 3, &expected);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            a.matrix[i][j] = i * 2 + j + 1;
        }
    }
    expected.matrix[0][0] = 1;
    expected.matrix[0][1] = 3;
    expected.matrix[0][2] = 5;
    expected.matrix[1][0] = 2;
    expected.matrix[1][1] = 4;
    expected.matrix[1][2] = 6;
    return_code = s21_transpose(&a, &result);
    ck_assert_int_eq(return_code, 0);
    return_code = s21_eq_matrix(&result, &expected);
    ck_assert_int_eq(return_code, SUCCESS);
    return_code = s21_transpose(NULL, &result);
    ck_assert_int_eq(return_code, 1);
    return_code = s21_transpose(&a, NULL);
    ck_assert_int_eq(return_code, 1);
}
END_TEST

START_TEST(test_s21_determinant) {
    matrix_t a;
    double result = 0;
    int return_code = 0;
    s21_create_matrix(3, 3, &a);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            a.matrix[i][j] = i * 3 + j + 1;
        }
    }
    return_code = s21_determinant(&a, &result);
    ck_assert_int_eq(return_code, 0);
    ck_assert_double_eq(result, 0);
    a.rows = 2;
    return_code = s21_determinant(&a, &result);
    ck_assert_int_eq(return_code, 2);
    a.rows = 3;
    return_code = s21_determinant(NULL, &result);
    ck_assert_int_eq(return_code, 1);
    return_code = s21_determinant(&a, NULL);
    ck_assert_int_eq(return_code, 1);
    s21_remove_matrix(&a);
    s21_create_matrix(1, 1, &a);
    a.matrix[0][0] = 1;
    return_code = s21_determinant(&a, &result);
    ck_assert_int_eq(return_code, 0);
    ck_assert_double_eq(result, 1);
}
END_TEST

START_TEST(test_s21_calc_complements) {
    matrix_t a;
    matrix_t result;
    matrix_t expected;
    int return_code = 0;
    s21_create_matrix(3, 3, &a);
    s21_create_matrix(3, 3, &expected);
    a.matrix[0][0] = 1;
    a.matrix[0][1] = 2;
    a.matrix[0][2] = 3;
    a.matrix[1][0] = 0;
    a.matrix[1][1] = 4;
    a.matrix[1][2] = 2;
    a.matrix[2][0] = 5;
    a.matrix[2][1] = 2;
    a.matrix[2][2] = 1;
    expected.matrix[0][0] = 0;
    expected.matrix[0][1] = 10;
    expected.matrix[0][2] = -20;
    expected.matrix[1][0] = 4;
    expected.matrix[1][1] = -14;
    expected.matrix[1][2] = 8;
    expected.matrix[2][0] = -8;
    expected.matrix[2][1] = -2;
    expected.matrix[2][2] = 4;
    return_code = s21_calc_complements(&a, &result);
    ck_assert_int_eq(return_code, 0);
    return_code = s21_eq_matrix(&result, &expected);
    ck_assert_int_eq(return_code, SUCCESS);
    s21_remove_matrix(&a);
    s21_remove_matrix(&result);
    s21_create_matrix(1, 1, &a);
    s21_create_matrix(1, 1, &result);
    a.matrix[0][0] = 1;
    return_code = s21_calc_complements(&a, &result);
    ck_assert_int_eq(return_code, 0);
    ck_assert_int_eq(result.matrix[0][0], 1);
    a.rows = 2;
    return_code = s21_calc_complements(&a, &result);
    ck_assert_int_eq(return_code, 2);
    a.rows = 1;
    return_code = s21_calc_complements(NULL, &result);
    ck_assert_int_eq(return_code, 1);
    return_code = s21_calc_complements(&a, NULL);
    ck_assert_int_eq(return_code, 1);
    s21_remove_matrix(&a);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
}
END_TEST

//      2  5  7
// A =  6  3  4
//      5 -2 -3


START_TEST(test_s21_inverse_matrix) {
    matrix_t a;
    matrix_t result;
    matrix_t expected;
    int return_code = 0;
    s21_create_matrix(3, 3, &a);
    s21_create_matrix(3, 3, &expected);
    a.matrix[0][0] = 2;
    a.matrix[0][1] = 5;
    a.matrix[0][2] = 7;
    a.matrix[1][0] = 6;
    a.matrix[1][1] = 3;
    a.matrix[1][2] = 4;
    a.matrix[2][0] = 5;
    a.matrix[2][1] = -2;
    a.matrix[2][2] = -3;
    expected.matrix[0][0] = 1;
    expected.matrix[0][1] = -1;
    expected.matrix[0][2] = 1;
    expected.matrix[1][0] = -38;
    expected.matrix[1][1] = 41;
    expected.matrix[1][2] = -34;
    expected.matrix[2][0] = 27;
    expected.matrix[2][1] = -29;
    expected.matrix[2][2] = 24;
    return_code = s21_inverse_matrix(&a, &result);
    ck_assert_int_eq(return_code, 0);
    return_code = s21_eq_matrix(&result, &expected);
    ck_assert_int_eq(return_code, SUCCESS);
    a.rows = 4;
    return_code = s21_inverse_matrix(&a, &result);
    ck_assert_int_eq(return_code, 2);
    a.rows = 3;
    return_code = s21_inverse_matrix(NULL, &result);
    ck_assert_int_eq(return_code, 1);
    return_code = s21_inverse_matrix(&a, NULL);
    ck_assert_int_eq(return_code, 1);
    s21_remove_matrix(&a);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
    s21_create_matrix(3, 3, &a);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            a.matrix[i][j] = i * 3 + j + 1;
        }
    }
    return_code = s21_inverse_matrix(&a, &result);
    ck_assert_int_eq(return_code, 2);
}

//         -1   1  -1
// М^T. =  38 -41  34
//        -27  29 -24

Suite *s21_linear_algebra(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("sum, sub, mul by number and mul by matrix, divide");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_transpose_matrix);
  tcase_add_test(tc_core, test_s21_determinant);
  tcase_add_test(tc_core, test_s21_calc_complements);
  tcase_add_test(tc_core, test_s21_inverse_matrix);

  suite_add_tcase(s, tc_core);

  return s;
}

int test_linear_algebra() {
  int no_failed = 0;

  Suite *s;
  SRunner *runner;

  s = s21_linear_algebra();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return no_failed;
}
