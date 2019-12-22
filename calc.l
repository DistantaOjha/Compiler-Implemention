
%{

/* same as import statements in Java */
#include <string>            // for C++ string       
#include <iostream>          // for C++ output to screen 
using namespace std;


/* the structure (mailbox) that contains the latest token */
union YYSTYPE
{
    int       number;      // for number tokens
    string*   text;        // for text tokens (var names, strings)
};


/* the mailbox object -- must be called yylval */
extern YYSTYPE yylval;


/* the identifiers/signals for each type of token -- our choice of names/values */
enum Signals
{
    NUM = 258,     		// to signal that number found in input       
    STR,           		// to signal that quoted string found in input
	_if_,			   	// to signal we have "if"
	_while_,		   	// to signal we have "while"
	_for_,				// to signal we have "for"
	_in_,				// to signal we have "in"
	_by_,				// to signal we have "by"
	_def_, 		   		// to signal we have function defination
	_return_,		   	// to signal we have return 	 
    _end_,           	// to signal we have end
    _gen_,
    _yield_,
    _match_,
    _class_,
    _from_,
    ID,            		// to signal that variable name found in input
};


/* keeps track of the number of lines typed */
int line_num = 1;

%}


/* Regular Expressions describing the tokens our calculator must recognize */

NUMBER       [1-9][0-9]*|0
COMMENT      ;[^\n]*           
STRING       '[^']*'
WHITESPACE   [ \t]+
IDENTIFIER   [a-zA-Z_][a-zA-Z0-9_]*            


/* ignore this */
%option noyywrap
%option nounput

/* to show debug messages */
/* %option debug */


%%             
"\n"         {
                  ++line_num;
                  return '\n';
             }

"+"          {
                  return '+';
             }
             
"-"          {
                  return '-';
             }
             
"["          {
				  return '[';
			 }			 

"]"          {
				  return ']';
			 }   

","          {
                  return ',';
             }             
             
"/"          {
                  return '/';
             }

"::"	 	 {
				 return _from_;
			 }	
                            
":"          {
                  return ':';
             }  

"*"          {
                  return '*';
             }

"="          {
                  return '=';
             }

"~"          {
                  return '~';
             }             
             
"("          {
                  return '(';
             }

")"          {
                  return ')';
             }
             
{NUMBER}     {
                  yylval.number = stoi(yytext);
                  return NUM;
             }
             
{STRING}     {
                  yylval.text = new string(yytext);
                  return STR;
             }
             
"if"		 {
				 return _if_;
			 }
			 
"while"		 {
				 return _while_;
			 }

"for"		 {
				return _for_;
			 }
			 
"in"		 {
				return _in_;
			 }
			 
"by"		 {
				 return _by_;
			 }

"def"		 {
				 return _def_;
			 }
			 
"return"	 {
				 return _return_;
			 }
			 
"end"		 {
				 return _end_;
			 }

"gen"		 {
				 return _gen_;
			 }
			 
"yield"		 {
				 return _yield_;
			 }

"match"		 {
				 return _match_;
			 }	
			 		 
"class"		 {
				 return _class_;
			 }

{IDENTIFIER} {
                  yylval.text = new string(yytext);
                  return ID;
             }

{WHITESPACE} {
                  /* do nothing, i.e. ignore all white spaces */
             }

{COMMENT}    {
                  /* do nothing, i.e. ignore comments */
             }

.	     	 { 
                  cout << "Scanner error on line " << line_num
                  << ": unexpected token " << yytext << endl;
                  return 0;
             }

%%
