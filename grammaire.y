%{
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "tableTemporaire.h"
#include "jmpList.h"
extern int line;

int asmLine;
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

Start: tINTDECL tMAIN tPARO tPARC tACCO Body  tACCC {printf("Everything works. %d lines of ASM", asmLine);};
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
     asmLine++;
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
  asmLine++;
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
      asmLine++;
      $$ = affect;
    }
  }
  | tInt {
    int affect = tempAddST();
    fprintf(out, "AFC %d %d\n", affect, $1);
    asmLine++;
    $$ = affect;
  }
  | AffectRight tADD AffectRight {
    fprintf(out, "ADD %d %d %d\n",  $1, $1, $3);
    asmLine++;
    tempPopST();
    $$ = $1;
    }
  | AffectRight tSUB AffectRight {
    fprintf(out, "SOU %d %d %d\n", $1, $1, $3);
    asmLine++;
    tempPopST(); 
    $$ = $1;
  }
  | AffectRight tSTAR AffectRight {
    fprintf(out, "MUL %d %d %d\n", $1, $1, $3);
    asmLine++;
    tempPopST();
    $$ = $1;
  }
  | AffectRight tDIV AffectRight{
    fprintf(out, "DIV %d %d %d\n", $1, $1, $3);
    asmLine++;
    tempPopST();
    $$ = $1;

  }
  | AffectRight tPERC AffectRight {
    fprintf(out,"MOD %d %d %d\n", $1, $1, $3);
    asmLine++;
    tempPopST();
    $$ = $1;
  }
  | tPARO AffectRight tPARC { 
   $$ = $2; 
  };



StructBlock: IfBlock { updateJumpingJLFromBottom(asmLine); displayJL(); }
  | IfElseBlock 
  | WhileBlock;

WhileBlock: tWHILE tPARO AddJumpingLineWhile Cond AddStatementLineWhile tPARC tACCO NewContext Body JumpInconditWhile QuitContext tACCC;

IfBlock: tIF tPARO Cond JumpIf tPARC tACCO NewContext Body QuitContext tACCC ;

IfElseBlock: IfBlock JumpIncondit tELSE tACCO NewContext Body QuitContext tACCC JumpHere;

JumpIncondit: {
  fprintf(out, "JMP\n");
  updateJumpingJLFromBottom(asmLine+1);
  addStatementJL(asmLine);
  asmLine++;
  }
JumpInconditWhile: {
  fprintf(out, "JMP\n");
  updateStatementLineFromBottom(asmLine);
  asmLine++;
  updateJumpingJLFromBottom(asmLine);
  displayJL();
  printf("Should work\n");
}
JumpHere: { updateJumpingJL(asmLine);
 displayJL(); }

NewContext : {oneStepDeeperND();} ;

QuitContext : {unDeepND();} ;

JumpIf: {
  addStatementJL(asmLine-1);
  displayJL();
}

AddStatementLineWhile: {
  addStatementJL(asmLine-1);
}
AddJumpingLineWhile: {
//  addStatementJL(asmLine-1);
  addJumpingJL(asmLine);
  displayJL();
}

Cond: AffectRight tINF AffectRight {
    fprintf(out, "INF %d %d %d\n", $1, $1, $3);
    asmLine++;
    fprintf(out, "JMF %d\n", $1);
    asmLine++;
    tempPopST();
    $$=$1;
  }
  | AffectRight tSUP AffectRight {
    fprintf(out, "SUP %d %d %d\n", $1, $1, $3);
    asmLine++;
    fprintf(out, "JMF %d\n", $1);
    asmLine++;
    tempPopST();
    $$=$1;
  }
  | AffectRight tEQEQ AffectRight{
   fprintf(out, "EQU %d %d %d\n", $1, $1, $3);
   asmLine++;
   fprintf(out, "JMF %d\n", $1);
   asmLine++;
   tempPopST();
   $$=$1;
  };


StructPrint: tPRINTF tPARO tVar tPARC tINSTREND;

%%

void addJmps();

int main(int argc, char * argv[]) {
  int i=0;
  int init=-1;
  for(i=0;i<argc-1;i++) {
    if(strcmp("-f", argv[i])) {
      out=fopen("out/file.tmp", "w");
      init=0;
    }
  }
  if(init==-1) {
    out=stdout;
  }
  asmLine=1;
  yyparse();
  if(init==0) {
    fclose(out);
    printf("Starting to insert jmps\n");
    addJmps();

  }
}

void addJmps() {
  IfJmpList* jumpingList = getJmpList();
  int line=0;
  char buf[4096];
  char* res = buf;
  FILE* tmp = fopen("out/file.tmp", "r");
  FILE * out = fopen("out/file.asm", "w");
  while(res != NULL && jumpingList != NULL) {
    line++;
    int jmpLine = isThereAJump(line);
    //If we have to jump on this line
    if(jmpLine != -1) {
      char c;
      printf("Jmp on line %d", line);
      
      //If the line i is a jmp line, we write every chars until end of the line
      c = fgetc(tmp);
      while(c != '\n') {
        fprintf(out,"%c", c);
        c = fgetc(tmp);
      }
      //and then the line to jump to
      fprintf(out," %d\n", jmpLine);
      jumpingList = jumpingList->next;
    } else {
      //if it isn't a jumping line, just write the line from the file
      res = fgets(buf,sizeof(char)*4096,tmp);
      fprintf(out, "%s", buf);
    }
  }
  fclose(tmp);
  fclose(out);
}

