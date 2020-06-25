
#include <assert.h>

#include "mpc.h"
#include "parse.h"

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
            "operator : '+' | '-' | '*' | '/' ; "
            "expr     : <number> | '(' <operator> <expr>+ ')' ; "
            "lispy    : /^/ <operator> <expr>+ /$/ ; ",
            Number, Operator, Expr, Lispy);

  return parser;
}

void Parse_dtor(Parse* t) {
  assert(t != NULL);

  mpc_cleanup(4, t->Number, t->Operator, t->Expr, t->Lispy);
}

void Parse_andPrint(const Parse* t, const char* input) {
  assert(t != NULL);
  assert(input != NULL);

  mpc_result_t r;
  if (mpc_parse("<stdin>", input, t->Lispy, &r)) {
    // On Success Print the AST
    mpc_ast_print(r.output);
    mpc_ast_delete(r.output);
  } else {
    // Otherwise Print the Error
    mpc_err_print(r.error);
    mpc_err_delete(r.error);
  }
}
