
#include <assert.h>
#include <editline/readline.h>

#include "line_edit.h"

const char* getInput(const char prompt[1]) {
  assert(prompt != NULL);

  const char* ret = readline(prompt);
  return ret;
}

void addToHistory(const char input[1]) {
  assert(input != NULL);

  add_history(input);
}
