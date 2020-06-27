#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "mpc.h"

static long f80Toi64(long double a) {
  // Make it so that ans will round to the nearest num when converted to int
  a = (a >= 0.0L) ? (a + 0.5L) : (a - 0.5L);

  assert(a >= (LONG_MIN * 1.0L));
  assert(a <= (LONG_MAX * 1.0L));

  return (long)a;
}

long eval_op(long x, const char* str, long y) {
  char op = str[0];
  if (op == '+') {
    return x + y;
  } else if (op == '-') {
    return x - y;
  } else if (op == '*') {
    return x * y;
  } else if (op == '/') {
    assert(y != 0);
    return x / y;
  } else if (op == '%') {
    assert(y != 0);
    return x % y;
  } else if (op == '^') {
    long double ans = powl(x, y);
    return f80Toi64(ans);
  } else {
    const char* const min = "min";
    const size_t len = strlen(min);
    if (strncmp(str, min, len) == 0) {
      return (x < y) ? x : y;
    } else {
      assert(NULL && "Should never get here");
      return 0;
    }
  }
}

static long evalRecur(mpc_ast_t* t) {
  assert(t != NULL);

  // If tagged as a number return it directly
  if (strstr(t->tag, "number")) {
    char* endptr = NULL;

    assert(t->contents != NULL);
    assert(&endptr != NULL);
    long ret = strtol(t->contents, &endptr, 10);

    // Check that `strtol` is valid
    assert(t->contents[0] != '\0');
    assert(endptr[0] == '\0');

    return ret;
  }

  // Operator is always element `[1]`
  char* op = t->children[1]->contents;

  // Put the 3rd child in x
  long x = evalRecur(t->children[2]);

  // Iterate the remaining children and combine
  int i = 3;
  while (strstr(t->children[i]->tag, "expr")) {
    x = eval_op(x, op, evalRecur(t->children[i]));
    i++;
  }

  // mpc_ast_delete(t);
  return x;
}

long eval(mpc_ast_t* t) {
  long ret = evalRecur(t);
  mpc_ast_delete(t);
  return ret;
}
