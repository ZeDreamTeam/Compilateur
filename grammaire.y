%{
#include <stdio.h>
#include "symbaleToble.h"

void yyerror(char const  *err) {
  fprintf(stderr, "%s\n",err); 
}

struct VarInit {
  char* var;
  int isInit;
} ;
%}
%union {
  int nombre;
  char* string;
  struct VarInit* vinit;
}
 
%token tMAIN tPARO tPARC tACCO tACCC tINSTREND
%token tCONST tINTDECL tEQEQ tVIRG
%token tINF tSUP tADD tSUB tSTAR tDIV tPERC tEQ
%token tIF tELSE
%token <nombre>tInt
%token <string>tVar
%token tPRINTF

%type <vinit>SingleDecl
%start Start
%%

Start: tINTDECL tMAIN tPARO tPARC tACCO Body  tACCC {printf("Everything works");};
Body: DeclBlock | DeclBlock BodySuite | BodySuite;

DeclBlock: Decl
  | Decl DeclBlock;
Decl: tINTDECL DeclSuite
  | tCONST tINTDECL DeclSuite;

DeclSuite:SingleDecl tINSTREND
  | SingleDecl tVIRG DeclSuite;
SingleDecl: tVar {  $$->var=$1;$$->isInit=0;  }
  | tVar tEQ AffectRight {}


BodySuite:OperationVariable 
  | OperationVariable BodySuite
  | StructCondBlock
  | StructCondBlock BodySuite
  | StructPrint;


OperationVariable: tVar tEQ AffectRight tINSTREND;

AffectRight: tVar | tInt
  | AffectRight Operation AffectRight
  | AffectRight Operation AffectRight
  | tPARO AffectRight tPARC;

Operation: tADD | tSUB | tSTAR | tDIV | tPERC;

StructCondBlock: IfBlock | IfElseBlock;

IfBlock: tIF tPARO Cond tPARC tACCO Body tACCC;

IfElseBlock: IfBlock tELSE tACCO Body tACCC;

Cond: AffectRight OperateurCondition AffectRight;

OperateurCondition: tINF | tSUP | tEQEQ;

StructPrint: tPRINTF tPARO tVar tPARC tINSTREND;
