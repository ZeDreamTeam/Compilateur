%{
#include <stdlib.h>
#include <stdio.h>
#include "toolsPLZ.h"
//#define MAXDECL 10

extern int line;
void yyerror(char const  *err) {
  fprintf(stderr, "\n%s, line : %d\n",err, line); 
  exit(-1);
}

%}
%union {
  int nombre;
  char* string;
  struct VarInit* vinit;
  struct VarInitTable* vinitTable;
}
 
%token tMAIN tPARO tPARC tACCO tACCC tINSTREND
%token tCONST tINTDECL tEQEQ tVIRG
%token tINF tSUP tADD tSUB tSTAR tDIV tPERC tEQ
%token tIF tELSE
%token tInt
%token tVar
%token tPRINTF

%right tEQ
%left tADD tSUB
%left tSTAR tDIV tPERC


%start Start
%%

Start: tINTDECL tMAIN tPARO tPARC tACCO Body  tACCC {printf("Everything works");};
Body: DeclBlock | DeclBlock BodySuite | BodySuite;

DeclBlock: Decl
  | Decl DeclBlock;
Decl: tINTDECL DeclSuite {assignTypeInSymboleTable(INT); printTableSymbole();}
  | tCONST tINTDECL DeclSuite{assignTypeInSymboleTable(CONST_INT); printTableSymbole();};

DeclSuite:SingleDecl tINSTREND {  }
  | SingleDecl tVIRG DeclSuite 
    {
    } 
SingleDecl: tVar {  addSymbole($1,-1, 0);} 
  | tVar tEQ AffectRight { addSymbole($1,-1,1);};


BodySuite:OperationVariable 
  | OperationVariable BodySuite
  | StructCondBlock
  | StructCondBlock BodySuite
  | StructPrint;


OperationVariable: tVar tEQ AffectRight tINSTREND { symbolInit($1); printTableSymbole(); };

AffectRight: tVar | tInt
  | AffectRight Operation AffectRight
  | tPARO AffectRight tPARC;

Operation: tADD | tSUB | tSTAR | tDIV | tPERC;

StructCondBlock: IfBlock | IfElseBlock;

IfBlock: tIF tPARO Cond tPARC tACCO Body tACCC;

IfElseBlock: IfBlock tELSE tACCO Body tACCC;

Cond: AffectRight OperateurCondition AffectRight;

OperateurCondition: tINF | tSUP | tEQEQ;

StructPrint: tPRINTF tPARO tVar tPARC tINSTREND;
