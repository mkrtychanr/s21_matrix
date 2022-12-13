#include "tests/check_s21_service.h"
#include "tests/check_s21_operations.h"

int main() {
  int no_failed = 0;

  no_failed |= test_service();
  no_failed |= test_operations();

  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
