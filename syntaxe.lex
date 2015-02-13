%{
  #include "y.tab.h"
  int fail=0;
%}

VARNAME ([a-zA-Z]+[0-9_]*)*
INTEGER [0-9]*
SPACE [ \t]*
%x COMMENT

%%

"/*" {BEGIN COMMENT;}
<COMMENT>"*/" {BEGIN INITIAL;}
<COMMENT>"\n" {}
<COMMENT>. {}
int { return tINTDECL;}
main {return tMAIN;}
const {return tCONST;}
"{" {return tACCO;}
"}" {return tACCC;}
"<" {return tINF;}
">" {return tSUP;}
"+" {return tADD;}
"-" {return tSUB;}
"*" {return tSTAR;}
"/" {return tDIV;}
"%" {return tPERC;}
"(" {return tPARO;}
")" {return tPARC;}
"," {return tVIRG;}
"==" {return tEQEQ;}
"=" {return tEQ;}
"printf" {return tPRINTF;}
";" {return tINSTREND;}
"\n" {printf("\n");}
"//" {printf("tCOMM");}
"if" {return tIF;}
"else" {return tELSE;}
{SPACE} {printf("%s",yytext);}
{INTEGER} {return tInt;}
{VARNAME} {return tVar;}

. { fail++;} 

%%
int main() {
  yyparse();
  printf("Nombre de tokens non matché : %d\n", fail);
}
