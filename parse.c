
#include <assert.h>
#include <stdio.h>

#include "mpc.h"
#include "parse.h"

/*
static int numberOfNodes(mpc_ast_t* t) {
  assert(t != NULL);

  if (t->children_num <= 0) {
    return 1;
  } else {
    int total = 1;
    int len = t->children_num;
    for (int i = 0; i < len; i++) {
      total = total + numberOfNodes(t->children[i]);
    }
    return total;
  }
}
*/

Parse* Parse_ctor(Parse* parser) {
  assert(parser != NULL);

  // Create Parsers
  mpc_parser_t* Number = mpc_new("number");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expr = mpc_new("expr");
  mpc_parser_t* Lispy = mpc_new("lispy");

  // Define Return Object
  parser->Number = Number;
  parser->Operator = Operator;
  parser->Expr = Expr;
  parser->Lispy = Lispy;

  // Define the Language
  mpca_lang(MPCA_LANG_DEFAULT,
            "number   : /-?[0-9]+/ ; "
            "operator : '+' | '-' | '*' | '/' | '%' | '^' ;"
            "expr     : <number> | '(' <operator> <expr>+ ')' ; "
            "lispy    : /^/ <operator> <expr>+ /$/ ; ",
            Number, Operator, Expr, Lispy);

  return parser;
}

void Parse_dtor(Parse* t) {
  assert(t != NULL);

  mpc_cleanup(4, t->Number, t->Operator, t->Expr, t->Lispy);
}

mpc_ast_t* Parse_andPrint(const Parse* t, const char* input) {
  assert(t != NULL);
  assert(input != NULL);

  mpc_result_t r;
  if (mpc_parse("<stdin>", input, t->Lispy, &r)) {
    // On Success Print the AST
    // printf("Number of Nodes: %d\n", numberOfNodes(r.output));
    // mpc_ast_print(r.output);
    // mpc_ast_delete(r.output);
    return r.output;
  } else {
    // Otherwise Print the Error
    mpc_err_print(r.error);
    mpc_err_delete(r.error);
    return NULL;
  }
}
