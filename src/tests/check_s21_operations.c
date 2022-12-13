#include "check_s21_operations.h"


START_TEST(test_s21_sum_matrix) {
    matrix_t a;
    matrix_t b;
    matrix_t result;
    matrix_t expected;
    int return_code = 0;
    s21_create_matrix(2, 2, &a);
    s21_create_matrix(2, 2, &b);
    s21_create_matrix(2, 2, &expected);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.columns; j++) {
            expected.matrix[i][j] = a.matrix[i][j] + b.matrix[i][j];
        }
    }
    return_code = s21_sum_matrix(&a, &b, &result);
    ck_assert_int_eq(return_code, 0);
    return_code = s21_eq_matrix(&result, &expected);
    ck_assert_int_eq(return_code, SUCCESS);
    s21_remove_matrix(&a);
    s21_remove_matrix(&b);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
    
}
END_TEST

START_TEST(test_s21_sub_matrix) {
  matrix_t a;
  matrix_t b;
  matrix_t result;
  matrix_t expected;
  int return_code = 0;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  s21_create_matrix(2, 2, &expected);
  for (int i = 0; i < a.rows; i++) {
      for (int j = 0; j < a.columns; j++) {
          expected.matrix[i][j] = a.matrix[i][j] - b.matrix[i][j];
      }
  }
  return_code = s21_sub_matrix(&a, &b, &result);
  ck_assert_int_eq(return_code, 0);
  return_code = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(return_code, SUCCESS);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected); 
}
END_TEST

START_TEST (test_sum_and_sub) {
  matrix_t a;
  matrix_t b;
  matrix_t result;
  int return_code = 0;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  s21_create_matrix(2, 2, &result);
  sum_and_sub(&a, NULL, &result, '0');
  sum_and_sub(NULL, &b, &result, '0');
  sum_and_sub(&a, &b, &result, '0');
  sum_and_sub(&a, &b, NULL, '0');
  a.rows = 4;
  return_code = sum_and_sub(&a, &b, &result, '0');
  ck_assert_int_eq(return_code, 2);
  a.rows = 2;
  a.columns = 4;
  return_code = sum_and_sub(&b, &a, &result, '0');
  ck_assert_int_eq(return_code, 2);
  a.columns = 2;
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_mult_number) {
  matrix_t a;
  matrix_t result;
  matrix_t expected;
  double number = 0;
  int return_code = 0;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &result);
  s21_create_matrix(2, 2, &expected);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      a.matrix[i][i] = i * 2 + j + 1;
      expected.matrix[i][i] = (i * 2 + j + 1) * 2;
    }
  }
  number = 2;
  return_code = s21_mult_number(&a, number, &result);
  ck_assert_int_eq(return_code, 0);
  return_code = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(return_code, SUCCESS);
  return_code = s21_mult_number(NULL, number, &result);
  ck_assert_int_eq(return_code, 1);
  return_code = s21_mult_number(&a, number, NULL);
  ck_assert_int_eq(return_code, 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_s21_mult_matrix) {
  matrix_t a;
  matrix_t b;
  matrix_t result;
  matrix_t expected;
  int return_code = 0;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  s21_create_matrix(2, 2, &result);
  s21_create_matrix(2, 2, &expected);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      double temp = i * 2 + j + 1;
      a.matrix[i][j] = temp;
      b.matrix[i][j] = temp;
    }
  }
  expected.matrix[0][0] = 7;
  expected.matrix[0][1] = 10;
  expected.matrix[1][0] = 15;
  expected.matrix[1][1] = 22;
  return_code = s21_mult_matrix(&a, &b, &result);
  ck_assert_int_eq(return_code, 0);
  return_code = s21_eq_matrix(&result, &expected);
  ck_assert_int_eq(return_code, SUCCESS);
  a.columns = 3;
  return_code = s21_mult_matrix(&a, &b, &result);
  ck_assert_int_eq(return_code, 2);
  a.columns = 2;
  return_code = s21_mult_matrix(NULL, &b, &result);
  ck_assert_int_eq(return_code, 1);
  return_code = s21_mult_matrix(&a, NULL, &result);
  ck_assert_int_eq(return_code, 1);
  return_code = s21_mult_matrix(&a, &b, NULL);
  ck_assert_int_eq(return_code, 1);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST


Suite *s21_operations(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("sum, sub, mul by number and mul by matrix, divide");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_sum_matrix);
  tcase_add_test(tc_core, test_s21_sub_matrix);
  tcase_add_test(tc_core, test_sum_and_sub);
  tcase_add_test(tc_core, test_s21_mult_number);
  tcase_add_test(tc_core, test_s21_mult_matrix);
  suite_add_tcase(s, tc_core);

  return s;
}

int test_operations() {
  int no_failed = 0;

  Suite *s;
  SRunner *runner;

  s = s21_operations();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return no_failed;
}
