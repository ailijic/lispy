#ifndef PARSE_H
#define PARSE_H

typedef struct Parse {
  void* Number;
  void* Operator;
  void* Expr;
  void* Lispy;
} Parse;

Parse* Parse_ctor(Parse* t);
__attribute__((nonnull)) void Parse_andPrint(const Parse* t, const char* input);
void Parse_dtor(Parse* t);

#endif  // PARSE_H
