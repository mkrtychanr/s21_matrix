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

Suite *s21_linear_algebra(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("sum, sub, mul by number and mul by matrix, divide");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_transpose_matrix);
  tcase_add_test(tc_core, test_s21_determinant);

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
