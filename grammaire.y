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
%token <string>tName
%token tPRINTF

%type <addr>AffectRight
%type <addr>Cond
%type <nombre>Args
%type <nombre> ArgsCalled
%type <nombre> SingleArgCalled

%type <string>SingleArg

%right tEQ
%left tADD tSUB
%left tSTAR tDIV tPERC


%start Start
%%


Start: Func Start | Func/*tINTDECL tMAIN tPARO tPARC tACCO Body  tACCC {printf("Everything works. %d lines of ASM", asmLine);};*/;
Func: tINTDECL tName NewContext tPARO Args tPARC {
  ftable_add($2,$5, asmLine);
  fprintf(out, ".%s:\n",$2);
  fprintf(out, "\tPUSH\tBP\n");
  fprintf(out, "\tMOV\tBP\tSP\n");
  asmLine+=3;
}
tACCO Body QuitContext tACCC {
    //ftable_add($2,$5, $8);
    //ftable_print();
    //fprintf(out, "\tMOV\tSP\tBP\n");
    fprintf(out, "\tPOP\tBP\n");
    fprintf(out, "\tPOP\tIP\n");
    asmLine+=2;
  }
  | tINTDECL tName NewContext tPARO tPARC {
    ftable_add($2,0,asmLine); 
    fprintf(out, ".%s:\n", $2);
    fprintf(out, "\tPUSH\tBP\n");
    fprintf(out, "\tMOV\tBP\t SP\n");
    asmLine+=3;
  }tACCO Body QuitContext tACCC {
    //ftable_add($2,0, $7);
    //ftable_print();
    fprintf(out, "\tPOP\tBP\n");
    fprintf(out, "\tPOP \tIP\n");
    asmLine+=2;
  };

Args: SingleArg tVIRG Args {
    $$ = 1 + $3;
    int addr = symboleAddST($1, 0, 1, -($$));
  } | SingleArg {
    $$ = 1;
    int addr = symboleAddST($1, 0, 1, -$$);
  } /*Returns the number of args */;

SingleArg: tINTDECL tName { 
    $$ = $2;
  } | tCONST tINTDECL tName {
    $$ = $3;
  };

Body: DeclBlock | DeclBlock BodySuite | BodySuite;

DeclBlock: Decl
  | Decl DeclBlock;
Decl: tINTDECL DeclSuite {assignTypeInSymboleTableTT(INT);}
  | tCONST tINTDECL DeclSuite{assignTypeInSymboleTableTT(CONST_INT);};

DeclSuite:SingleDecl tINSTREND
  | SingleDecl tVIRG DeclSuite; 
SingleDecl: tName {  addSymboleTT($1,-1, 0);} 
  | tName tEQ AffectRight {
     int addr = addSymboleTT($1,-1,1);
     fprintf(out, "\tCOP \t@%d \t@%d\n", addr, $3);
     asmLine++;
     tempPopST();
  };


BodySuite:OperationVariable 
  | OperationVariable BodySuite
  | StructBlock
  | StructBlock BodySuite
  | StructPrint
  | FuncCall;


OperationVariable: tName tEQ AffectRight tINSTREND { 
  symbolInitST($1);
  int addrVar = getIndexWithVarNameST($1);
  fprintf(out, "\tCOP \t@%d \t@%d\n", addrVar, $3);
  asmLine++;
  tempPopST();
  };

AffectRight: tName {
    int affect = tempAddST();
    fprintf(out, "\tCOP \t@%d \t@%d\n", affect, getIndexWithVarNameST($1));
    asmLine++;
    $$ = affect;
  }
  | tInt {
    int affect = tempAddST();
    fprintf(out, "\tAFC \t@%d \t%d\n", affect, $1);
    asmLine++;
    $$ = affect;
  }
  | AffectRight tADD AffectRight {
    fprintf(out, "\tADD \t@%d \t@%d \t@%d\n",  $1, $1, $3);
    asmLine++;
    tempPopST();
    $$ = $1;
    }
  | AffectRight tSUB AffectRight {
    fprintf(out, "\tSOU \t@%d \t@%d \t@%d\n", $1, $1, $3);
    asmLine++;
    tempPopST(); 
    $$ = $1;
  }
  | AffectRight tSTAR AffectRight {
    fprintf(out, "\tMUL \t@%d \t@%d \t@%d\n", $1, $1, $3);
    asmLine++;
    tempPopST();
    $$ = $1;
  }
  | AffectRight tDIV AffectRight{
    fprintf(out, "\tDIV \t@%d \t@%d \t@%d\n", $1, $1, $3);
    asmLine++;
    tempPopST();
    $$ = $1;

  }
  | AffectRight tPERC AffectRight {
    fprintf(out,"\tMOD \t@%d \t@%d \t@%d\n", $1, $1, $3);
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
  fprintf(out, "\tJMP \t\n");
  updateJumpingJLFromBottom(asmLine+1);
  addStatementJL(asmLine);
  asmLine++;
  }
JumpInconditWhile: {
  fprintf(out, "\tJMP \t\n");
  updateStatementLineFromBottom(asmLine);
  asmLine++;
  updateJumpingJLFromBottom(asmLine);
  displayJL();
}
JumpHere: { updateJumpingJL(asmLine);
 displayJL(); }

NewContext : { oneStepDeeperND(); } ;

QuitContext : { unDeepND(); } ;

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
    fprintf(out, "\tINF \t@%d \t@%d \t@%d\n", $1, $1, $3);
    asmLine++;
    fprintf(out, "\tJMF \t%d\n", $1);
    asmLine++;
    tempPopST();//Two temp vars are used when checking conditions
    tempPopST();
    $$=$1;
  }
  | AffectRight tSUP AffectRight {
    fprintf(out, "\tSUP \t@%d \t@%d \t@%d\n", $1, $1, $3);
    asmLine++;
    fprintf(out, "\tJMF \t%d\n", $1);
    asmLine++;
    tempPopST();
    tempPopST();
    $$=$1;
  }
  | AffectRight tEQEQ AffectRight{
   fprintf(out, "\tEQU \t@%d \t@%d \t@%d\n", $1, $1, $3);
   asmLine++;
   fprintf(out, "\tJMF \t%d\n", $1);
   asmLine++;
   tempPopST();
   tempPopST();
   $$=$1;
  };


FuncCall: tName tPARO tPARC tINSTREND { 
    int lineToJumpTo = ftable_exists($1, 0);
    fprintf(out, "\tPUSH \tIP\n");//PUSH @ret
    fprintf(out, "\tJMP \t%d\n", lineToJumpTo);
    asmLine+=2;
  } | tName tPARO ArgsCalled tPARC tINSTREND{
    printf("Looking for %s (%d args)\n", $1,$3);
    int lineToJumpTo = ftable_exists($1, $3);
    fprintf(out, "\tPUSH \tIP\n");//PUSH @ret
    fprintf(out, "\tJMP \t%d\n", lineToJumpTo);
  };

ArgsCalled: SingleArgCalled { $$ = $1; } | SingleArgCalled tVIRG ArgsCalled { $$ = $1 + $3; };
SingleArgCalled: AffectRight {
    fprintf(out, "\tPUSH \t%d\n", $1);
    asmLine+=2;
    $$ = 1;
    tempPopST();//A tmp var is used by AffectRight.
  };


StructPrint: tPRINTF tPARO tName tPARC tINSTREND;

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
  if(jumpingList == NULL) {
    while(res != NULL) {
      res = fgets(buf,sizeof(char)*4096,tmp);
      if(res > 0) {
        fprintf(out, "%s", buf);
      }
    }
  }
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

