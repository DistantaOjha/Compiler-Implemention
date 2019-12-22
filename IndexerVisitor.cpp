#ifndef INDEXERVISITOR_CPP_
#define INDEXERVISITOR_CPP_

#include <string>
#include <map>

#include "PoolEntry.cpp"
#include "Visitor.cpp"

class IndexerVisitor : public Visitor{

public:
	map<string, int> localVarIndex;

	void visit(IdNode* node) override {
		localVarIndex[*(node->name)] = localVarIndex.size();
	}

	void visit(StmntListNode* node) override {
		deque<StmntNode*> stmntlist = node->stmnt_list;
		for(StmntNode* stnode: stmntlist){
			stnode->accept(this);
		}
	}

	void visit(IfNode* node) override {
		node->stmnt_list->accept(this);

	}

	void visit(WhileNode* node) override {
		node->stmnt_list->accept(this);
	}

	void visit(ForLoopNode* node) override {
		node->varDefNode->accept(this);
		node->whileNode->accept(this);
	}

	void visit(ParamListNode* node)override {
		deque<IdNode*> IdList = node->params;
		for(IdNode* idnode: IdList){
			idnode->accept(this);
		}
	}

	void visit(ProcDefNode* node) override {
		node->param_list->accept(this);
		node->stmntlist->accept(this);
	}

	void visit(GenDefNode* node) override {
		node->param_list->accept(this);
		node->stmntlist->accept(this);
	}

	void visit(GenInitNode* node) override {
		node->idVar->accept(this);
	}

	void visit(VarDefNode* node) override {
		node->id->accept(this);
	}
};



#endif /* INDEXERVISITOR_CPP_ */
