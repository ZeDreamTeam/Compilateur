%{
#include <stdio.h>
void yyerror(char const  *err) {
  fprintf(stderr, "%s\n",err); 
}
%} 
%token tMAIN tPARO tPARC tACCO tACCC tINSTREND
%token tCONST tINTDECL tEQEQ tVIRG
%token tINF tSUP tADD tSUB tSTAR tDIV tPERC tEQ
%token tIF tELSE
%token tInt tVar
%token tPRINTF
%start Start
%%

Start: tINTDECL tMAIN tPARO tPARC tACCO Body  tACCC {printf("Everything works");};
Body: DeclBlock | DeclBlock BodySuite;

DeclBlock: Decl
  | Decl DeclBlock;
Decl: tINTDECL DeclSuite
  | tCONST tINTDECL DeclSuite;

DeclSuite:SingleDecl tINSTREND
  | SingleDecl tVIRG DeclSuite;
SingleDecl: tVar
  | tVar tEQ tInt;


BodySuite:OperationVariable | OperationVariable BodySuite;


OperationVariable: tVar tEQ AffectRight tINSTREND;


AffectRight: tVar | tInt
  | tVar Operation AffectRight
  | tInt Operation AffectRight
  | tPARO AffectRight tPARC;

Operation: tADD | tSUB | tSTAR | tDIV | tPERC;
