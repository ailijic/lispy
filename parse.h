#ifndef PARSE_H
#define PARSE_H

typedef struct Parse {
  void* Number;
  void* Operator;
  void* Expr;
  void* Lispy;
} Parse;

struct mpc_ast_t;
typedef struct mpc_ast_t mpc_ast_t;

Parse* Parse_ctor(Parse* t);
mpc_ast_t* Parse_andPrint(const Parse* t, const char* input);
void Parse_dtor(Parse* t);

#endif  // PARSE_H
