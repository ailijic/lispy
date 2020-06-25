#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "line_edit.h"

// #define ssizeof(type) ((intptr_t)(sizeof((type))))

static const bool FN_SUCCESS = false;
static const bool FN_FAILURE = true;

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

/*
static bool getInput(char buf[2], intptr_t buf_len) {
  assert(buf != NULL);
  assert(buf_len >= 2);
  assert(buf_len <= INT_MAX);

  int len = (int)buf_len;
  char* a = fgets(buf, len, stdin);

  if (a != NULL) {
    return FN_SUCCESS;
  } else {
    return FN_FAILURE;
  }
}
*/

/*
static bool displayPrompt(const char str[1]) {
  assert(str != NULL);

  int a = fputs(str, stdout);

  if (a >= 0) {
    return FN_SUCCESS;
  } else {
    return FN_FAILURE;
  }
}
*/

int main() {
  // static char input[2048];

  puts("Lispy Version 0.0.1");
  puts("Press Ctrl+d to Exit");

  bool status;
  for (;;) {
    // status = displayPrompt("lispy> ");
    // assert(status == FN_SUCCESS);
    const char* input = getInput("lispy> ");
    if (input == NULL) {
      break;
    }

    // Get Input
    // status = getInput(input, ssizeof(input));
    // if (status != FN_SUCCESS) {
    //   break;
    // }
    addToHistory(input);

    status = echoInput(input);
    assert(status == FN_SUCCESS);

    void* free_me = NULL;
    memcpy(&free_me, &input, sizeof(void*));
    free(free_me);
    input = NULL;
  }

  puts("\nExiting...");
  return 0;
}
