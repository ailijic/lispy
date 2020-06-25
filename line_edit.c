
#include <assert.h>

#include "line_edit.h"

#ifdef _WIN32
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNUSED(x) ((void)((x)))

static char* readline(const char prompt[1]) {
  assert(prompt != NULL);
  static char buffer[2048];

  int status;
  status = fputs(prompt, stdout);
  assert(status >= 0);
  assert(sizeof(buffer) <= INT_MAX);
  int len = (int)sizeof(buffer);
  char* ret = fgets(buffer, len, stdin);
  if (ret == NULL) {
    return NULL;
  } else {
    size_t input_len = strlen(buffer);
    char* cpy = malloc(input_len + 1);
    assert(cpy != NULL);
    strcpy(cpy, buffer);

    // Get rid of the newline at the end of the buffer
    cpy[input_len] = '\0';
    return cpy;
  }
}

static void add_history(const char* unused) { UNUSED(unused); }

#else  // Compile for linux
#include <editline/readline.h>
#endif

const char* getInput(const char prompt[1]) {
  assert(prompt != NULL);

  const char* ret = readline(prompt);
  return ret;
}

void addToHistory(const char input[1]) {
  assert(input != NULL);

  add_history(input);
}
