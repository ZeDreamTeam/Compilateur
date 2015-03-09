%{
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "tableTemporaire.h"

extern int line;
void yyerror(char const  *err) {
  fprintf(stderr, "\n%s, line : %d\n",err, line); 
  exit(-1);
}
 FILE* out;

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
%token tIF tELSE tWHILE
%token <nombre>tInt
%token <string>tVar
%token tPRINTF

%type <addr>AffectRight
%type <addr>Cond
%right tEQ
%left tADD tSUB
%left tSTAR tDIV tPERC


%start Start
%%

Start: tINTDECL tMAIN tPARO tPARC tACCO Body  tACCC {printf("Everything works");};
Body: DeclBlock | DeclBlock BodySuite | BodySuite;

DeclBlock: Decl
  | Decl DeclBlock;
Decl: tINTDECL DeclSuite {assignTypeInSymboleTableTT(INT);}
  | tCONST tINTDECL DeclSuite{assignTypeInSymboleTableTT(CONST_INT);};

DeclSuite:SingleDecl tINSTREND
  | SingleDecl tVIRG DeclSuite; 
SingleDecl: tVar {  addSymboleTT($1,-1, 0);} 
  | tVar tEQ AffectRight {
     int addr = addSymboleTT($1,-1,1);
     fprintf(out, "COP %d %d\n", addr, $3);
     tempPopST();
  };


BodySuite:OperationVariable 
  | OperationVariable BodySuite
  | StructBlock
  | StructBlock BodySuite
  | StructPrint;


OperationVariable: tVar tEQ AffectRight tINSTREND { 
  symbolInitST($1);
  int addrVar = getIndexWithVarNameST($1);
  fprintf(out, "COP %d %d\n", addrVar, $3);
  tempPopST();
  };

AffectRight: tVar {
    if(getIndexWithVarNameST($1)==-1) {
      char err[150];
      strcat(err, "Error using the var ");
      strcat(err, $1); 
      yyerror(err);
    } else {
      int affect = tempAddST();
      fprintf(out, "COP %d %d\n", affect, getIndexWithVarNameST($1));
      $$ = affect;
    }
  }
  | tInt {
    int affect = tempAddST();
    fprintf(out, "AFC %d %d\n", affect, $1);
    $$ = affect;
  }
  | AffectRight tADD AffectRight {
    fprintf(out, "ADD %d %d %d\n",  $1, $1, $3);
    tempPopST();
    $$ = $1;
    }
  | AffectRight tSUB AffectRight {
    fprintf(out, "SOU %d %d %d\n", $1, $1, $3);
    tempPopST(); 
    $$ = $1;
  }
  | AffectRight tSTAR AffectRight {
    fprintf(out, "MUL %d %d %d\n", $1, $1, $3);
    tempPopST();
    $$ = $1;
  }
  | AffectRight tDIV AffectRight{
    fprintf(out, "DIV %d %d %d\n", $1, $1, $3);
    tempPopST();
    $$ = $1;

  }
  | AffectRight tPERC AffectRight {
    fprintf(out,"MOD %d %d %d\n", $1, $1, $3);
    tempPopST();
    $$ = $1;
  }
  | tPARO AffectRight tPARC { 
   $$ = $2; 
  };



StructBlock: IfBlock
  | IfElseBlock 
  | WhileBlock;

WhileBlock: tWHILE tPARO Cond tPARC tACCO NewContext Body QuitContext tACCC;

IfBlock: tIF tPARO Cond tPARC tACCO NewContext Body QuitContext tACCC;

IfElseBlock: IfBlock tELSE tACCO NewContext Body QuitContext tACCC;

NewContext : {oneStepDeeperND();} ;

QuitContext : {unDeepND();} ;

Cond: AffectRight tINF AffectRight {
    fprintf(out, "INF %d %d %d\n", $1, $1, $3);
    fprintf(out, "JMF %d\n", $1);
    addStatementJL(line);  
    tempPopST();
    $$=$1;
  }
  | AffectRight tSUP AffectRight {
    fprintf(out, "SUP %d %d %d\n", $1, $1, $3);
    fprintf(out, "JMF %d\n", $1);
    addStatementJL(line);
    tempPopST();
    $$=$1;
  }
  | AffectRight tEQEQ AffectRight{
   fprintf(out, "EQU %d %d %d\n", $1, $1, $3);
   fprintf(out, "JMF %d\n", $1);
   tempPopST();
   $$=$1;
  };


StructPrint: tPRINTF tPARO tVar tPARC tINSTREND;

%%

int main(int argc, char * argv[]) {
  int i=0;
  int init=-1;
  for(i=0;i<argc-1;i++) {
    if(strcmp("-f", argv[i])) {
      out=fopen("out/file.asm", "w");
      init=0;
    }
  }
  if(init==-1) {
    out=stdout;
  }

  yyparse();
}

