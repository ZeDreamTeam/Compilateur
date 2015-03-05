%{
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "tableTemporaire.h"
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
  int addr;
}
 
%token tMAIN tPARO tPARC tACCO tACCC tINSTREND
%token tCONST tINTDECL tEQEQ tVIRG
%token tINF tSUP tADD tSUB tSTAR tDIV tPERC tEQ
%token tIF tELSE
%token <nombre>tInt
%token <string>tVar
%token tPRINTF

%type <addr>AffectRight

%right tEQ
%left tADD tSUB
%left tSTAR tDIV tPERC


%start Start
%%

Start: tINTDECL tMAIN tPARO tPARC tACCO Body  tACCC {printf("Everything works");};
Body: DeclBlock | DeclBlock BodySuite | BodySuite;

DeclBlock: Decl
  | Decl DeclBlock;
Decl: tINTDECL DeclSuite {assignTypeInSymboleTable(INT);}
  | tCONST tINTDECL DeclSuite{assignTypeInSymboleTable(CONST_INT);};

DeclSuite:SingleDecl tINSTREND
  | SingleDecl tVIRG DeclSuite; 
SingleDecl: tVar {  addSymbole($1,-1, 0);} 
  | tVar tEQ AffectRight {
     int addr = addSymbole($1,-1,1);
     printf("COP %d %d\n", addr, $3);
     tempPop();
  };


BodySuite:OperationVariable 
  | OperationVariable BodySuite
  | StructCondBlock
  | StructCondBlock BodySuite
  | StructPrint;


OperationVariable: tVar tEQ AffectRight tINSTREND { 
  symbolInit($1);
  int addrVar = getIndexWithVarName($1);
  printf("COP %d %d", addrVar, $3);
  tempPop();
  };

AffectRight: tVar {
    if(getIndexWithVarName($1)==-1) {
      char err[150];
      strcat(err, "Error using the var ");
      strcat(err, $1); 
      yyerror(err);
    } else {
      int affect = tempAdd();
      printf("COP %d %d\n", affect, getIndexWithVarName($1));
      $$ = affect;
    }
  }
  | tInt {
    int affect = tempAdd();
    printf("AFC %d %d\n", affect, $1);
    $$ = affect;
  }
  | AffectRight tADD AffectRight {
    printf("ADD %d %d %d\n",  $1, $1, $3);
    tempPop();
    $$ = $1;
    }
  | AffectRight tSUB AffectRight {
    printf("SOU %d %d %d\n", $1, $1, $3);
    tempPop(); 
    $$ = $1;
  }
  | AffectRight tSTAR AffectRight {
    printf("MUL %d %d %d\n", $1, $1, $3);
    tempPop();
    $$ = $1;
  }
  | AffectRight tDIV AffectRight{
    printf("DIV %d %d %d\n", $1, $1, $3);
    tempPop();
    $$ = $1;

  }
  | AffectRight tPERC AffectRight {
    printf("MOD %d %d %d\n", $1, $1, $3);
    tempPop();
    $$ = $1;
  }
  | tPARO AffectRight tPARC;

StructCondBlock: IfBlock | IfElseBlock;

IfBlock: tIF tPARO Cond tPARC tACCO NewContext Body QuitContext tACCC;

IfElseBlock: IfBlock tELSE tACCO NewContext Body QuitContext tACCC;

NewContext : {oneStepDeeper();} ;

QuitContext : {unDeep();} ;

Cond: AffectRight OperateurCondition AffectRight;

OperateurCondition: tINF | tSUP | tEQEQ;

StructPrint: tPRINTF tPARO tVar tPARC tINSTREND;
