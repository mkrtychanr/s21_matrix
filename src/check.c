#include "tests/check_s21_service.h"

int main() {
  int no_failed = 0;

  no_failed |= test_service();

  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
