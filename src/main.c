#include "test_decimal.h"

int main(void) {
  Suite *pS = test_decimal();
  SRunner *sr = srunner_create(pS);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
  return 0;
}
