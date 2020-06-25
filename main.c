#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "line_edit.h"
#include "parse.h"

// #define ssizeof(type) ((intptr_t)(sizeof((type))))

static const bool FN_SUCCESS = false;
static const bool FN_FAILURE = true;

__attribute__((nonnull)) static void freeInput(const char input[]) {
  assert(input != NULL);

  void* free_me = NULL;
  memcpy(&free_me, &input, sizeof(void*));
  free(free_me);
  input = NULL;
}

__attribute__((nonnull)) static bool echoInput(const char str[]) {
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
  Parse parse;
  Parse* parser = Parse_ctor(&parse);
  for (;;) {
    const char* input = getInput("lispy> ");
    if (input == NULL) {
      break;
    }

    addToHistory(input);

    status = echoInput(input);
    assert(status == FN_SUCCESS);

    Parse_andPrint(parser, input);

    freeInput(input);
  }

  puts("\nExiting...");
  Parse_dtor(parser);
  return 0;
}
