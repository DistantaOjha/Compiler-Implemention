
%{

#define YYERROR_VERBOSE

/* same as import statements in Java */
#include <map>           // for C++ Hash Map
#include <string>        // for C++ string
#include <iostream>      // for C++ output to screen
#include <stdlib.h>
#include <deque>
#include "ast.cpp"
#include "ByteCodeVisitor.cpp"
using namespace std;

 
/* the look-up table: associates variable names (strings/keys) with their values (numbers) */
map<string, int>  variables;
ExprNode* matchComp;

/*
 * yylex -- this function will be created externally for us for reading
 *          the tokens based on the scanner description in calc.l
 */
extern int yylex();

/* defined in scanner (calc.l) */
extern int line_num;     // from Scanner -- our variable for tracking current line
extern char* yytext;     // from Scanner -- default variable for latest token found

/* yyerror -- error reporting function; we create this one (see below) */
void yyerror(const char* msg);
 
%}

/* connect Scanner and Parser: mention the union structure (i.e. the mailbox) from calc.l */
%union
{
    int        number;
    string     *text;
    ParseNode* parsenode;
    ExprNode* 	exprnode;
    StmntNode* stmntnode;
    ClassNode* classnode;
    ClassListNode* classlistnode;
    ProcedureNode* procnode;
    StmntListNode* stmntlistnode;
    ParamListNode* paramlistnode;
    ProcDefListNode* proclistnode;
    ProcCallNode* procallnode;
    ArgListNode* arglistnode;
    IdNode* idnode;
    ProgramNode* programnode;
    FieldDefListNode* datalistnode;
    FieldDefNode* datanode;


    // may add additional fields here if needed by Parser non-terminals
}

/* associate each token's identifier/signal from calc.l with field/type in the union structure */
%token <number> NUM
%token <text>   STR
%token <number>   _if_
%token <number>   _while_
%token <number>   _for_
%token <number>   _in_
%token <number>   _by_
%token <number>   _def_
%token <number>   _return_
%token <number>   _end_
%token <number>   _gen_
%token <number>   _yield_
%token <number>   _match_
%token <number>   _class_
%token <number>   _from_
%token <text>   ID


/*
 * associate each non-terminal in the grammar with field/type in the "mailbox"/union.
 * Only when $$, $1, $2, etc. used for non-terminal, so need for EXPR, but not for ASSIGN, LINE, etc.
 */
%type <exprnode>  EXPR
%type <exprnode>  TERM
%type <exprnode>  FACTOR
%type <programnode> PROGRAM
%type <classnode>   CLASS
%type <classlistnode> CLASS_LIST
%type <stmntlistnode> STMNT_LIST
%type <stmntlistnode> MATCH
%type <stmntlistnode> MATCHBODY
%type <stmntnode> STMNT
%type <procnode> PROC_DEF
%type <procnode> GEN_DEF
%type <stmntnode> GEN_INIT
%type <stmntnode> YIELD
%type <procallnode> PROC_CALL
%type <stmntnode> ASSIGN
%type <stmntnode> VARDEC
%type <stmntnode> IF
%type <stmntnode> WHILE
%type <stmntnode> FOR
%type <stmntnode> RETURN
%type <arglistnode> ARG_LIST
%type <arglistnode> NEMPTY_ARG_LIST
%type <paramlistnode> PARAM_LIST
%type <paramlistnode> NEMPTY_PARAM_LIST
%type <proclistnode> PROCLIST
%type <datalistnode> DATALIST
%type <datanode> DATADEF
%type <idnode> IDS
%%

/* The Mini Python Grammar */
PROGRAM:		CLASS_LIST  {
								$$ = new ProgramNode($1);
								ByteCodeVisitor* visitor = new ByteCodeVisitor();
								visitor->visit($$);
							}
;

CLASS_LIST:		  CLASS	 		{
									$$ = new ClassListNode();
									$$->insert($1);
								}

				| CLASS '\n' CLASS_LIST	{
											$$ = $3;
											$$->insert($1);
										}
;


CLASS:        _class_ IDS ':' '\n' PROCLIST _end_ '\n' 					{	
																			$$ = new ClassNode($2, new FieldDefListNode(), $5);
																		}
														
		    | _class_ IDS ':' '\n' _end_ '\n'           				{
																			$$ = new ClassNode($2, new FieldDefListNode() ,new ProcDefListNode());
																		}
														
		    | _class_ IDS ':' '\n' DATALIST '\n' _end_  '\n' 			{
		    																$$ = new ClassNode($2, $5, new ProcDefListNode());
		    															}
		    											
		    | _class_ IDS ':' '\n' DATALIST '\n' PROCLIST _end_  '\n' 	{
		    																$$ = new ClassNode($2, $5, $7);
		    													 	  	}
		    
;

PROCLIST:	   	  PROC_DEF '\n' 			{ 
												$$ = new ProcDefListNode();
												$$->insert($1);
											}

				| GEN_DEF '\n'  			{
										 		$$ = new ProcDefListNode();
										 		$$->insert($1);
											}
											
			    | PROC_DEF '\n' PROCLIST 	{
			    								$$ = $3;
												$$->insert($1);
			    							}
			    								
			    | GEN_DEF '\n' PROCLIST	    {
			    								$$ = $3;
												$$->insert($1);
											}
;

DATALIST:        DATADEF	   	   			{ 
												$$ = new FieldDefListNode();
												$$->insert($1);
											}

			    								
			    | DATADEF DATALIST	    	{
			    								$$ = $2;
												$$->insert($1);
											}
;


DATADEF :         _def_ IDS '=' EXPR  '\n' 	{
												$$ = new FieldDefNode($2,$4);
											}

STMNT_LIST:		  STMNT STMNT_LIST 			{
												$$ = $2;
												$$->insert($1);
											}
				
				| STMNT						{
												$$ = new StmntListNode();
												$$->insert($1);
											}
				
				| MATCH '\n' STMNT_LIST  	{
												$$ = $3;
												deque<StmntNode*> matStmntList = $1->stmnt_list;
												for(int i= matStmntList.size()-1; i>=0; i--){
													$$->insert(matStmntList[i]);
												}	
										 	}
										 
				| MATCH '\n'				{
												$$= $1;
											}
					
;

				
STMNT:					
				  ASSIGN '\n'				{$$ = $1;}
				
				| GEN_INIT '\n'				{$$ = $1;}
				
				| YIELD '\n'				{$$ = $1;}
				
				| RETURN '\n'				{$$ = $1;}
			
				| IF '\n'					{$$ = $1;}
			
				| WHILE '\n'				{$$ = $1;}
				
				| FOR '\n'              	{$$ = $1;}
				
				| PROC_CALL '\n'	    	{$$ = $1;}
						
				| VARDEC '\n'				{$$ = $1;}				
;



MATCH:        _match_ EXPR {matchComp = $2;} ':' '\n' MATCHBODY _end_ { $$ = $6;} 
;


MATCHBODY:   	  EXPR ':' '\n' STMNT_LIST	{
												BinExprNode* compareZero = new BinExprNode($1,matchComp,'-'); 
												IfNode* ifnode = new IfNode(compareZero, $4);
												$$ = new StmntListNode();
												$$->insert(ifnode);											
											}

			    | EXPR ':' '\n' STMNT_LIST '\n' MATCHBODY {		    											
			    											 BinExprNode* compareZero = new BinExprNode($1,matchComp,'-'); 
															 IfNode* ifnode = new IfNode(compareZero, $4);
			    											 $$= $6;
			    											 $$->insert(ifnode);
			    										  }
;



GEN_DEF:		_gen_ IDS '(' PARAM_LIST ')' ':' '\n' STMNT_LIST _end_ '\n'  {
																				$$ = new GenDefNode($2, $4, $8);
																			 }
;


GEN_INIT:		_gen_ IDS '=' IDS '(' ARG_LIST ')' 						{
																			$$ = new GenInitNode($2,$4, $6);
																		}
;

YIELD: 		_yield_ EXPR												{
																			$$ = new YieldNode($2);
																		}
;



PROC_DEF:		_def_ IDS '(' PARAM_LIST ')' ':' '\n' STMNT_LIST _end_ '\n'  {
																				$$ = new ProcDefNode($2, $4, $8);
																			}
;

ASSIGN:       	IDS '=' EXPR            								{
																			$$ = new VarAssignNode($1, $3);
																		}
;

RETURN: 		_return_ EXPR											{
																			$$ = new ReturnNode($2);
																		}
;	

IF:				_if_ EXPR ':' '\n' STMNT_LIST _end_ 					{
																			$$ = new IfNode($2, $5);
																		}
;

WHILE:  		_while_ EXPR ':' '\n' STMNT_LIST _end_ 					{
																			$$ = new WhileNode($2, $5);
																		}
;

FOR:   			_for_ IDS _in_ EXPR '~' EXPR _by_ EXPR ':' '\n' STMNT_LIST _end_ {
																					$$ = new ForLoopNode($2,$4,$6,$8,$11);
																				 }
;


PROC_CALL:		   IDS '(' ARG_LIST ')'  								{
																			$$ = new ProcCallNode($1, $3);
										 								}
										 								 
				| IDS _from_ IDS '(' ARG_LIST ')'						{
																			$$ = new ProcCallNode($1, $3, $5);
																		}
;



PARAM_LIST:		 /* Empty String */ 									{
																			$$= new ParamListNode();
																		}
				 
				 | NEMPTY_PARAM_LIST    								{$$= $1;}
;


NEMPTY_PARAM_LIST: 		 IDS            								{
																			$$ = new ParamListNode();
				 															$$->insert($1);
																		}
										
					   | IDS ',' NEMPTY_PARAM_LIST 						{
					   														$$ = $3;
				 															$$->insert($1);
					   													}
;

ARG_LIST:		   /* Empty String */ 									{
																			$$ = new ArgListNode();
																		}
				 
				 | NEMPTY_ARG_LIST    									{$$= $1;}
;


NEMPTY_ARG_LIST: 		EXPR											{
																			$$ = new ArgListNode();
				 															$$->insert($1);
																		}

					| EXPR  ',' NEMPTY_ARG_LIST							{
					 														$$ = $3;
					 														$$->insert($1);	
					 					 								}
;

EXPR:        EXPR '+' TERM          									{ $$ = new BinExprNode($1, $3, '+'); }

		   | EXPR '-' TERM          									{ $$ = new BinExprNode($1,$3, '-'); }

           | TERM          		 										{ $$ = $1;	}
;


TERM:        TERM '*' FACTOR											{ $$ = new BinExprNode($1,$3, '*'); }

		   | TERM '/' FACTOR											{ $$ = new BinExprNode($1,$3, '/'); }	

		   | FACTOR														{ $$ = $1; }
;


FACTOR:		 '(' EXPR ')'			 									{ $$ = $2; }
		    	
		    | NUM                 										{ $$ = new NumNode($1); }
            
            | IDS				  										{ $$ = $1; }
            
            | PROC_CALL           										{ $$ = $1; }
            
             	
            | '~' IDS													{ $$ = new GenInvokNode($2); }
            
;

VARDEC:	   		_def_ IDS '=' EXPR            							 {
																			$$ = new VarDefNode($2, $4);
																		 }
;

IDS:   ID   															{$$= new IdNode($1);}
;

%%

/* Main function to start the calculator (ignore this section) */

/*
 * yyerror is called when the expression typed by the user is not
 * recognized -- gives us a chance to offer a meaningful error message
 */
void yyerror(const char* msg)
{
    /* the scanner (calc.l) keeps track of the current line number (line_num) */
    cout << "Parser error on line " << line_num << ": " << msg << endl;
    cout << "Latest token: " << yytext << endl;
}


/* the main function where execution begins */
int main( int argc, char** argv ) {

    yyparse();         /* yyparse will be created for us */

    return 0;  
}
