#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "line_edit.h"

// #define ssizeof(type) ((intptr_t)(sizeof((type))))

static const bool FN_SUCCESS = false;
static const bool FN_FAILURE = true;

static void freeInput(const char* input) {
  assert(input != NULL);

  void* free_me = NULL;
  memcpy(&free_me, &input, sizeof(void*));
  free(free_me);
  input = NULL;
}

static bool echoInput(const char str[1]) {
  assert(str != NULL);

  int a = fputs("Echo: ", stdout);
  int b = fputs(str, stdout);
  int c = fputs("\n", stdout);

  if ((a >= 0) && (b >= 0) && (c >= 0)) {
    return FN_SUCCESS;
  } else {
    return FN_FAILURE;
  }
}

int main() {
  puts("Lispy Version 0.0.1");
  puts("Press Ctrl+d to Exit");

  bool status;
  for (;;) {
    const char* input = getInput("lispy> ");
    if (input == NULL) {
      break;
    }

    addToHistory(input);

    status = echoInput(input);
    assert(status == FN_SUCCESS);

    freeInput(input);
  }

  puts("\nExiting...");
  return 0;
}
