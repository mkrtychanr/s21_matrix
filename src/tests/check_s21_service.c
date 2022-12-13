#include "check_s21_service.h"


START_TEST(test_s21_create_matrix) {
    matrix_t a;
    int result = 0;
    result = s21_create_matrix(3, 3, NULL);
    ck_assert_int_eq(result, 1);
    s21_remove_matrix(NULL);
    result = s21_create_matrix(3, 3, &a);
    ck_assert_int_eq(result, 0);
    if (result == 0) {
        s21_remove_matrix(&a);
    }
    result = s21_create_matrix(0, 3, &a);
    ck_assert_int_eq(result, 1);
    if (result == 0) {
        s21_remove_matrix(&a);
    }
    result = s21_create_matrix(0, 0, &a);
    ck_assert_int_eq(result, 1);
    if (result == 0) {
        s21_remove_matrix(&a);
    }
    result = s21_create_matrix(3, 0, &a);
    ck_assert_int_eq(result, 1);
    if (result == 0) {
        s21_remove_matrix(&a);
    }
    result = s21_create_matrix(-1, 5, &a);
    ck_assert_int_eq(result, 1);
    if (result == 0) {
        s21_remove_matrix(&a);
    }
    result = s21_create_matrix(5, -1, &a);
    ck_assert_int_eq(result, 1);
    if (result == 0) {
        s21_remove_matrix(&a);
    }
    result = s21_create_matrix(-1, -1, &a);
    ck_assert_int_eq(result, 1);
    if (result == 0) {
        s21_remove_matrix(&a);
    }

}
END_TEST

START_TEST(test_s21_eq_matrix){
    matrix_t a;
    matrix_t b;
    int result = 0;
    s21_create_matrix(3, 3, &a);
    s21_create_matrix(3, 3, &b);
    result = s21_eq_matrix(&a, &b);
    ck_assert_int_eq(result, SUCCESS);
    a.matrix[0][0] = 5;
    result = s21_eq_matrix(&a, &b);
    ck_assert_int_eq(result, FAILURE);
    s21_remove_matrix(&a);
    s21_remove_matrix(&b);
    s21_create_matrix(3, 3, &a);
    result = s21_eq_matrix(NULL, &a);
    ck_assert_int_eq(result, FAILURE);
    result = s21_eq_matrix(&a, NULL);
    ck_assert_int_eq(result, FAILURE);
    s21_create_matrix(3, 3, &b);
    b.rows = 0;
    result = s21_eq_matrix(&a, &b);
    ck_assert_int_eq(result, FAILURE);
}
END_TEST

Suite *s21_service(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("create, delete and eq matrix_t");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_create_matrix);
  tcase_add_test(tc_core, test_s21_eq_matrix);
  suite_add_tcase(s, tc_core);

  return s;
}

int test_service() {
  int no_failed = 0;

  Suite *s;
  SRunner *runner;

  s = s21_service();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return no_failed;
}
