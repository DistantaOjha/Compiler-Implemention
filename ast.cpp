#ifndef AST_CPP_
#define AST_CPP_

#include <string>
#include <deque>

#include "Visitor.cpp"

using namespace std;

struct ParseNode {

	ParseNode(){}

	virtual void accept(Visitor* visitor)=0;
};


struct ExprNode :public ParseNode{

	virtual void accept(Visitor* visitor) override=0;

};


struct ProcedureNode :public ParseNode{

	virtual void accept(Visitor* visitor) override=0;

};


struct BinExprNode: public ExprNode{

	ExprNode* lexpr;
	ExprNode* rexpr;
	char oper;

	BinExprNode(ExprNode* l, ExprNode* r, char o ): lexpr(l), rexpr(r), oper(o){}

	virtual void accept(Visitor* visitor) override
	{
	    visitor->visit(this);
	}

};


struct IdNode : public ExprNode{

	string* name;

	IdNode(string* str): name(str){}


	virtual void accept(Visitor* visitor) override
	{
	    visitor->visit(this);
	}

};



struct NumNode : public ExprNode{

	int num;

	NumNode(int n): num(n){}

	virtual void accept(Visitor* visitor) override
	{
	    visitor->visit(this);
	}

};

struct StmntNode: public ParseNode{

	virtual void accept(Visitor* visitor) override
	{
	    visitor->visit(this);
	}

};

struct StmntListNode: public ParseNode {

	deque<StmntNode*> stmnt_list;

	StmntListNode(){

	}

	StmntListNode(deque<StmntNode*>stlist): stmnt_list(stlist) {}

	void insert(StmntNode* node){
		stmnt_list.push_front(node);
	}

	void insert_back(StmntNode* node){
		stmnt_list.push_back(node);
	}

	virtual void accept(Visitor* visitor) override
	{
	    visitor->visit(this);
	}
};

struct FieldDefNode :public StmntNode{

	IdNode* id;
	ExprNode* expr;

	FieldDefNode(IdNode* i, ExprNode* expre): id(i), expr(expre){}

	virtual void accept(Visitor* visitor) override
	{
		visitor->visit(this);
	}
};

struct FieldDefListNode :public ParseNode {

	deque<FieldDefNode*> fields;

	FieldDefListNode(){}

	void insert(FieldDefNode* node){
		fields.push_front(node);
	}

	virtual void accept(Visitor* visitor) override
	{
	    visitor->visit(this);
	}

};


struct ProcDefNode :public ProcedureNode{

	IdNode* id;
	ParamListNode* param_list;
	StmntListNode* stmntlist;

	ProcDefNode(IdNode* i, ParamListNode* l, StmntListNode* stlist): id(i), param_list(l), stmntlist(stlist)
	{}

	virtual void accept(Visitor* visitor) override
	{
	    visitor->visit(this);
	}

};



struct ProcDefListNode :public ParseNode {

	deque<ProcedureNode*> procedures;

	ProcDefListNode(){}

	void insert(ProcedureNode* node){
		procedures.push_front(node);
	}

	virtual void accept(Visitor* visitor) override
	{
	    visitor->visit(this);
	}

};


struct ClassNode : public ParseNode{

	IdNode* className;
	FieldDefListNode* fieldlist;
	ProcDefListNode* procedureList;

	ClassNode(IdNode* classname, FieldDefListNode* field_list, ProcDefListNode* proc_list):
		className(classname),
		fieldlist(field_list),
		procedureList(proc_list)
		{}

	virtual void accept(Visitor* visitor) override
	{
	    visitor->visit(this);
	}
};

struct ClassListNode :public ParseNode {

	deque<ClassNode*> classes;

	ClassListNode(){}

	void insert(ClassNode* node){
		classes.push_front(node);
	}

	virtual void accept(Visitor* visitor) override
	{
	    visitor->visit(this);
	}
};

struct ProgramNode : public ParseNode{

	ClassListNode* classlist;

	ProgramNode(ClassListNode* classlst): classlist(classlst){}


	virtual void accept(Visitor* visitor) override
	{
	    visitor->visit(this);
	}
};


struct IfNode: public StmntNode{

	ExprNode* expr;
	StmntListNode* stmnt_list;

	IfNode(ExprNode* e, StmntListNode* l): expr(e), stmnt_list(l){}

	virtual void accept(Visitor* visitor) override
	{
	    visitor->visit(this);
	}
};


struct GenDefNode :public ProcedureNode{

	IdNode* id;
	ParamListNode* param_list;
	StmntListNode* stmntlist;

	GenDefNode(IdNode* i, ParamListNode* l, StmntListNode* stlist): id(i), param_list(l), stmntlist(stlist)
	{}

	virtual void accept(Visitor* visitor) override
	{
	    visitor->visit(this);
	}

};




struct GenInitNode :public StmntNode{

	IdNode* idVar;
	IdNode* idProc;
	ArgListNode* arg_list;

	GenInitNode(IdNode* iVar, IdNode* iProc, ArgListNode* args): idVar(iVar), idProc(iProc), arg_list(args)
	{}

	virtual void accept(Visitor* visitor) override
	{
	    visitor->visit(this);
	}

};


struct GenInvokNode :public ExprNode{

	IdNode* id;

	GenInvokNode(IdNode* i): id(i)
	{}

	virtual void accept(Visitor* visitor) override
	{
	    visitor->visit(this);
	}

};


struct YieldNode : public StmntNode{

	ExprNode* expr;

	YieldNode(ExprNode* e): expr(e){}

	virtual void accept(Visitor* visitor) override
	{
	    visitor->visit(this);
	}
};


struct VarAssignNode :public StmntNode{

	IdNode* id;
	ExprNode* expr;


	VarAssignNode(IdNode* i, ExprNode* expre): id(i), expr(expre){}

	virtual void accept(Visitor* visitor) override
	{
		visitor->visit(this);
	}
};


struct WhileNode : public StmntNode {

	ExprNode* expr;
	StmntListNode* stmnt_list;

	WhileNode(ExprNode* e, StmntListNode* l): expr(e), stmnt_list(l){}

	virtual void accept(Visitor* visitor) override
	{
	    visitor->visit(this);
	}
};

struct VarDefNode :public StmntNode{

	IdNode* id;
	ExprNode* expr;

	VarDefNode(IdNode* i, ExprNode* expre): id(i), expr(expre){}

	virtual void accept(Visitor* visitor) override
	{
		visitor->visit(this);
	}
};

struct ForLoopNode : public StmntNode {

	VarDefNode* varDefNode;
	WhileNode* whileNode;

	ForLoopNode(IdNode* control, ExprNode* min, ExprNode* max, ExprNode* step, StmntListNode* stmntlist){

		varDefNode = new VarDefNode(control, min);

		//while loop expr condition
		BinExprNode* expr = new BinExprNode(max, control,'-');  //max - (control) !=0

		//auto increment at the end of the loop
		BinExprNode* incre_expr = new BinExprNode(control, step,'+');
		VarAssignNode* varAssign = new VarAssignNode(control, incre_expr); //control = control + step
		stmntlist->insert_back(varAssign);

		// construction while loop from for loop
		whileNode = new WhileNode(expr, stmntlist);
	}

	virtual void accept(Visitor* visitor) override
	{
	    visitor->visit(this);
	}
};

struct ParamListNode :public StmntNode {

	deque<IdNode*> params;

	ParamListNode(){}

	void insert(IdNode* node){
		params.push_front(node);
	}

	virtual void accept(Visitor* visitor) override
	{
	    visitor->visit(this);
	}

};

struct ArgListNode :public StmntNode {

	deque<ExprNode*> args;

	ArgListNode(){}

	void insert(ExprNode* node){
		args.push_front(node);
	}

	virtual void accept(Visitor* visitor) override
	{
	    visitor->visit(this);
	}

};

struct ProcCallNode :public StmntNode, public ExprNode{

	IdNode* classid;
	IdNode* id;
	ArgListNode* arg_list;

	ProcCallNode(IdNode* i, ArgListNode* args): classid(nullptr), id(i), arg_list(args){}

	ProcCallNode(IdNode* classID, IdNode* i, ArgListNode* args): classid(classID), id(i), arg_list(args) {}

	virtual void accept(Visitor* visitor) override
	{
	    visitor->visit(this);
	}
};

struct ReturnNode : public StmntNode{

	ExprNode* expr;

	ReturnNode(ExprNode* e): expr(e){}

	virtual void accept(Visitor* visitor) override
	{
	    visitor->visit(this);
	}

};

#endif
