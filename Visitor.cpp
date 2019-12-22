#ifndef VISITOR_CPP_
#define VISITOR_CPP_

struct ParseNode;
struct ExprNode;
struct ProcedureNode;
struct BinExprNode;
struct IdNode;
struct NumNode;
struct StmntListNode;
struct IfNode;
struct WhileNode;
struct ForLoopNode;
struct ParamListNode;
struct ProcDefListNode;
struct ProcDefNode;
struct GenDefNode;
struct GenInitNode;
struct GenInvokNode;
struct YieldNode;
struct ArgListNode;
struct ProcCallNode;
struct ReturnNode;
struct VarAssignNode;
struct VarDefNode;
struct StmntNode;
struct ProgramNode;
struct ClassNode;
struct ClassListNode;
struct FieldDefNode;
struct FieldDefListNode;


class Visitor {

public:
	//virtual void visit(ParseNode* node)=0;
	//virtual void visit(ExprNode* node)=0;

	virtual void visit(ProgramNode* node){

	}

	virtual void visit(ClassNode* node){

	}

	virtual void visit(ClassListNode* node){

	}

	virtual void visit(BinExprNode* node){

	}

	virtual void visit(IdNode* node){

	}

	virtual void visit(NumNode* node){

	}

	virtual void visit(StmntListNode* node){

	}

	virtual void visit(IfNode* node){

	}

	virtual void visit(WhileNode* node){

	}

	virtual void visit(ForLoopNode* node){

	}

	virtual void visit(ParamListNode* node){

	}

	virtual void visit(FieldDefNode* node){

	}

	virtual void visit(FieldDefListNode* node){

	}

	virtual void visit(ProcDefListNode* node){

	}

	virtual void visit(ProcDefNode* node){

	}

	virtual void visit(GenDefNode* node){

	}

	virtual void visit(GenInitNode* node){

	}

	virtual void visit(GenInvokNode* node){

	}

	virtual void visit(YieldNode* node){

	}

	virtual void visit(ArgListNode* node){

	}

	virtual void visit(ProcCallNode* node){

	}

	virtual void visit(ReturnNode* node){

	}

	virtual void visit(VarAssignNode* node){

	}

	virtual void visit(VarDefNode* node){

	}

	virtual void visit(StmntNode* node){

	}

};
#endif
