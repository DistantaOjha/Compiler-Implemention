
#ifndef BYTECODEVISITOR_CPP_
#define BYTECODEVISITOR_CPP_

#include <iostream>
#include <vector>
#include <utility>
#include "byteio.h"
#include "bytecode.h"
#include "IndexerVisitor.cpp"
#include "PoolEntry.cpp"

//#define REF

class ByteCodeVisitor :public Visitor{
public:

	const int thisClassIndex = 1;
	const int superClassIndex = 3;
	const int outFieldRef = 10;
	const int codeIndex = 5;
	const int printMethodRef = 14;
	const int systemClassIndex = 6;
	const int printStreamIndex = 8;
	const int scannerClassIndex =18;
	const int fieldInputStream = 20;
	const int scannerInitIndex = 24;
	const int nextIntMethodRef = 28;
	const int scannercloseMethodRef=32;
	int paramSize;

	//pool entries
	std::vector<PoolEntry*> pool;
	//methods
	std::vector<method_field_info*> methods;
	//fields
	std::vector<method_field_info*> fields;
	//method name and index in constant pool
	std::map<string, int> methodMap;
	//localIndex in local scopes of methods
	std::map<string, int> localIndex;
	//associates generator var name to corresponding gen method name and the number of args for invocations
	std::map<string, pair <string, int>> generatorNameArgs;
	//associates generator name with number of arraysize of that generator
	std::map<string, int> generatorArr;
	//associates class and index in constant pool;
	std::map<string, int> classMap;
	//associates field and index in the constant pool;
	std::map<string, int> fieldMap;


	void visit(ProgramNode* node) override {
		node->classlist->accept(this);
	}

	void visit(ClassListNode* node) override {
		deque<ClassNode*> classlist = node->classes;
		for(ClassNode*  singleClass: classlist){
			string className = *(singleClass->className->name);
			cout<<"Encoding class " <<className<<endl;
			ByteCodeVisitor* visitor = new ByteCodeVisitor();
			singleClass->accept(visitor);
		}
	}

	void visit (ClassNode* node) override {
		string className = *(node->className->name);

		new CONSTANT_Class_info( pool ,className);
		new CONSTANT_Class_info( pool ,"java/lang/Object");
		new CONSTANT_Utf8_info( pool, "Code");


		new CONSTANT_Class_info( pool ,"java/lang/System");
		new CONSTANT_Class_info( pool ,"java/io/PrintStream");
		new CONSTANT_Fieldref_info(pool, systemClassIndex, "out","Ljava/io/PrintStream;");
		new CONSTANT_Methodref_info(pool,printStreamIndex,"println","(I)V");

		new CONSTANT_Class_info( pool ,"java/util/Scanner");
		new CONSTANT_Fieldref_info(pool, systemClassIndex, "in","Ljava/io/InputStream;");
		new CONSTANT_Methodref_info(pool,scannerClassIndex,"<init>","(Ljava/io/InputStream;)V");
		new CONSTANT_Methodref_info(pool,scannerClassIndex,"nextInt","()I");
		new CONSTANT_Methodref_info(pool,scannerClassIndex,"close","()V");

		node->fieldlist->accept(this);
		node->procedureList->accept(this);

		std::ofstream ofs;
		ofs.open(className + ".class");
		byteio::attach_out(ofs);
		//magic number
		byteio::write_u4(0xCAFEBABE);
		//minor version
		byteio::write_u2(0);
		//major version
		byteio::write_u2(52);

		//const_pool_count
		byteio::write_u2(pool.size()+1);
		//const pool
		for(PoolEntry* element : pool){
			element->write();
		}

		std::vector<string> flags = {"ACC_PUBLIC"};
		byteio::write_u2(PoolEntry::encodeAccessFlags(flags)); //accessflag

		byteio::write_u2(thisClassIndex); //this class index in constpool
		byteio::write_u2(superClassIndex); // super class index in constpool

		byteio::write_u2(0); //interface count

		byteio::write_u2(fields.size()); //field count
		for(method_field_info* field : fields){
			field->write();
		}


		byteio::write_u2(methods.size()); //method count
		for(method_field_info* method : methods){
			method->write();
		}

		byteio::write_u2(0); //attribute count
		ofs.close();
	}

	void visit(FieldDefNode* node) override{
		string fieldName = *(node->id->name);
		string descr = "I";
		std::vector<string> flags = {"ACC_PUBLIC","ACC_STATIC"};

		CONSTANT_Fieldref_info* fieldReferen = new CONSTANT_Fieldref_info(pool,thisClassIndex,fieldName,descr);
		method_field_info* field = new method_field_info(pool, fieldReferen, flags);
		fieldMap[fieldName] = pool.size()-3 ; //-1 for nametype  -2 for utf
		fields.push_back(field);
	}

	void visit(FieldDefListNode* node) override{
		deque<FieldDefNode*> fieldlist = node->fields;
		for(FieldDefNode*  field: fieldlist){
			field->accept(this);
		}

		std::vector<string> flags = {"ACC_STATIC"};
		CONSTANT_Methodref_info* methodReferen = new CONSTANT_Methodref_info(pool,thisClassIndex,"<clinit>","()V");
		method_field_info* staticMethod = new method_field_info(pool, methodReferen, flags);
		methodMap["<clinit>"] = pool.size()-3 ;
		methods.push_back(staticMethod);
		attribute_info* attribute = new attribute_info(codeIndex, 100); //code // attribute length
		staticMethod->attributes.push_back(attribute);

//		//start info vector
		byteio::write_u2(attribute->info, 500); //stack
		byteio::write_u2(attribute->info, localIndex.size()); //locals
		byteio::write_u4(attribute->info, 50); //initial code length


		//Initialize all the fields here
		for(FieldDefNode*  field: fieldlist){
			field->expr->accept(this);
			byteio::write_u1(attribute->info, bytecode::code("putstatic"));
			string fieldName = *(field->id->name);
			byteio::write_u2(attribute->info, fieldMap[fieldName]);
		}

		byteio::write_u1(attribute->info, bytecode::code("return"));
		byteio::write_u2(attribute->info,0); //exception table length
		byteio::write_u2(attribute->info,0); //attributes_info count

		//size - stack size- max locals - code length - exception table length- info count
		int final_codelength = attribute->info.size()-2-2-4-2-2;
		//changing code length
		byteio::write_u4(4 ,attribute->info, final_codelength);
		attribute->attribute_length= attribute->info.size();
	}


	void visit(ProcDefListNode* node) override{
		deque<ProcedureNode*> proclist = node->procedures;
		for(ProcedureNode*  proc: proclist){
			proc->accept(this);
		}
	}

	void visit(BinExprNode* node) override {
		method_field_info* method = methods[methods.size()-1];
		attribute_info* attribute = method->attributes[0];
		char oper=node->oper;
		node->lexpr->accept(this);
		node->rexpr->accept(this);
		if(oper== '+'){
			byteio::write_u1(attribute->info, bytecode::code("iadd"));
		}
		else if (oper=='*'){
			byteio::write_u1(attribute->info, bytecode::code("imul"));
		}
		else if (oper == '/'){
			byteio::write_u1(attribute->info, bytecode::code("idiv"));
		}
		else if (oper == '-') {
			byteio::write_u1(attribute->info, bytecode::code("isub"));
		}
	}

	void visit(IdNode* node) override {
		method_field_info* method = methods[methods.size()-1];
		attribute_info* attribute = method->attributes[0];

		if ( localIndex.find(*(node->name)) == localIndex.end() ) {

			if ( fieldMap.find(*(node->name)) == fieldMap.end() ) {
				cout<<*(node->name)<<" --> Variable not defined"<<endl;
			}
			else {
				byteio::write_u1(attribute->info, bytecode::code("getstatic"));
				byteio::write_u2(attribute->info, fieldMap[*(node->name)]);
			}
		}
		else {
			byteio::write_u1(attribute->info, bytecode::code("iload"));
			byteio::write_u1(attribute->info, localIndex[*(node->name)]);
		}
	}

	void visit(NumNode* node) override {
		method_field_info* method = methods[methods.size()-1];
		attribute_info* attribute = method->attributes[0];
		byteio::write_u1(attribute->info, bytecode::code("bipush"));
		byteio::write_u1(attribute->info, node->num);
	}

	void visit(StmntListNode* node) override {
		deque<StmntNode*> stmntlist = node->stmnt_list;
		for(StmntNode* stnode: stmntlist){
			stnode->accept(this);
		}
	}

	void visit(IfNode* node) override {

		method_field_info* method = methods[methods.size()-1];
		attribute_info* attribute = method->attributes[0];


		node->expr->accept(this);

		int initialsize= attribute->info.size();

		byteio::write_u1(attribute->info, bytecode::code("ifne"));
		byteio::write_u2(attribute->info, 50);

		node->stmnt_list->accept(this);

		int finalsize = attribute->info.size();
		int offset =  finalsize - initialsize;

		byteio::write_u2(initialsize+1,attribute->info, offset);
	}

	void visit(WhileNode* node) override {
		method_field_info* method = methods[methods.size()-1];
		attribute_info* attribute = method->attributes[0];


		int beforeWhileIndex= attribute->info.size();
		node->expr->accept(this);

		int fromWhileIndex= attribute->info.size();
		byteio::write_u1(attribute->info,  bytecode::code("ifeq"));
		byteio::write_u2(attribute->info, 50);


		node->stmnt_list->accept(this);

		int afterWhileIndex = attribute->info.size();
		byteio::write_u1(attribute->info, bytecode::code("goto")); //goto begining
		byteio::write_u2(attribute->info, beforeWhileIndex- afterWhileIndex);


		int finalsize = attribute->info.size();
		int offset =  finalsize - fromWhileIndex;
		byteio::write_u2(fromWhileIndex+1,attribute->info, offset);
	}


	void visit(ForLoopNode* node) override{
		node->varDefNode->accept(this);
		node->whileNode->accept(this);
	}

	void visit(ProcDefNode* node) override {

		string methodName = *(node->id->name);

		string descr;
		std::vector<string> flags = {"ACC_PUBLIC","ACC_STATIC"};

		if(methodName=="main"){
			descr = "([Ljava/lang/String;)V";
		}
		else {
			descr = makeSignature(node);
		}

		IndexerVisitor* indexVisit = new IndexerVisitor();
		indexVisit->visit(node);
		localIndex=  indexVisit->localVarIndex;

		CONSTANT_Methodref_info* methodReferen = new CONSTANT_Methodref_info(pool,thisClassIndex,methodName,descr);
		method_field_info* method = new method_field_info(pool, methodReferen, flags);
		methodMap[methodName] = pool.size()-3 ; //-1 for nametype  -2 for utf

		methods.push_back(method);

		attribute_info* attribute = new attribute_info(codeIndex, 100); //code // attribute length
		method->attributes.push_back(attribute);

		//start info vector
		byteio::write_u2(attribute->info, 500); //stack
		byteio::write_u2(attribute->info, localIndex.size()); //locals
		byteio::write_u4(attribute->info, 50); //initial code length

		node->stmntlist->accept(this);

		if(methodName=="main"){
			byteio::write_u1(attribute->info, bytecode::code("return"));
		}

		byteio::write_u2(attribute->info,0); //exception table length
		byteio::write_u2(attribute->info,0); //attributes_info count

		//size - stack size- max locals - code length - exception table length- info count
		int final_codelength = attribute->info.size()-2-2-4-2-2;

		//changing code length
		byteio::write_u4(4 ,attribute->info, final_codelength);
		attribute->attribute_length= attribute->info.size();
	}


	string makeSignature(ProcDefNode* node){
		ParamListNode* param = node->param_list;
		paramSize = param->params.size();
		string des = "(";

		for(int i=0; i< paramSize; i++){
			des = des + "I";
		}
#ifndef REF
		des= des+ ")I";
#else
		//when ref is turned on
		des= des + ")[I";
#endif
		return des;
	}


	void visit(GenDefNode* node) override{
		string methodName = *(node->id->name);

		std::vector<string> flags = {"ACC_PUBLIC","ACC_STATIC"};
		string descr = makeSignature(node);
		IndexerVisitor* indexVisit = new IndexerVisitor();
		indexVisit->localVarIndex["<state>"] = 0;
		indexVisit->visit(node);
		indexVisit->localVarIndex["<retIndex>"] = indexVisit->localVarIndex.size();

		localIndex=  indexVisit->localVarIndex; // array at 0 , params 1,...k, locals k+1,...n

		CONSTANT_Methodref_info* methodReferen = new CONSTANT_Methodref_info(pool,thisClassIndex,methodName,descr);
		method_field_info* method = new method_field_info(pool, methodReferen, flags);
		methodMap[methodName] = pool.size()-3 ; //-1 for nametype  -2 for utf
		methods.push_back(method);


		attribute_info* attribute = new attribute_info(codeIndex, 100); //code // attribute length
		method->attributes.push_back(attribute);
		//start info vector
		byteio::write_u2(attribute->info, 500); //stack

		byteio::write_u2(attribute->info, localIndex.size()); //locals
		byteio::write_u4(attribute->info, 50); //initial code length


		byteio::write_u1(attribute->info, bytecode::code("aload_0"));
		int initialsize= attribute->info.size();
		byteio::write_u1(attribute->info, bytecode::code("ifnonnull"));
		byteio::write_u2(attribute->info, 99); //dummy value
		byteio::write_u1(attribute->info, bytecode::code("bipush"));

		//index arraySize-1 is result and arraySize-2 is ret index
		int arraySize = localIndex.size()+1; //X , params..., defs.. (ret) , result

		generatorArr[methodName] = arraySize;


		byteio::write_u1(attribute->info, arraySize); //arraysize

		byteio::write_u1(attribute->info, bytecode::code("newarray"));
		byteio::write_u1(attribute->info, 10); //int type
		byteio::write_u1(attribute->info, bytecode::code("astore_0")); //store array


		//put jump index into a local variable we have for ret
		int sipushIndex = attribute->info.size();
		byteio::write_u1(attribute->info, bytecode::code("sipush"));
		byteio::write_u2(attribute->info, 99); //dummy index
		byteio::write_u1(attribute->info, bytecode::code("istore"));
		byteio::write_u1(attribute->info, localIndex["<retIndex>"]);


		for(int i=1; i < arraySize-2; i++){ //go upto ret //stops at size-3
			//load array
			byteio::write_u1(attribute->info, bytecode::code("aload_0"));
			//put index to the stack
			byteio::write_u1(attribute->info, bytecode::code("bipush"));
			byteio::write_u1(attribute->info, i);
			//put local variable to stack
			if(i-1 < node->param_list->params.size()){
				byteio::write_u1(attribute->info, bytecode::code("iload"));
				byteio::write_u1(attribute->info, i); //dummy value
			}
			else {
				byteio::write_u1(attribute->info, bytecode::code("bipush"));
				byteio::write_u1(attribute->info, 0); //dummy value
			}
			//call iastore
			byteio::write_u1(attribute->info, bytecode::code("iastore"));
		}

		//put ret
		byteio::write_u1(attribute->info, bytecode::code("aload_0")); //load array
		byteio::write_u1(attribute->info, bytecode::code("bipush")); //index
		byteio::write_u1(attribute->info, arraySize-2);
		byteio::write_u1(attribute->info, bytecode::code("iload")); //value
		byteio::write_u1(attribute->info, localIndex["<retIndex>"]);
		byteio::write_u1(attribute->info, bytecode::code("iastore")); //store


		byteio::write_u1(attribute->info, bytecode::code("aload_0"));
		byteio::write_u1(attribute->info, bytecode::code("areturn"));

		int finalSize = attribute->info.size();
		//size - stack size - max locals - code length
		int offset =  finalSize - initialsize;
		byteio::write_u2(initialsize+1,attribute->info, offset);


		//array is not null then unload all the values and ret and then jump to the place
		for(int i= 1 ; i <= arraySize-2; i++){
			byteio::write_u1(attribute->info, bytecode::code("aload_0"));
			//put index to the stack
			byteio::write_u1(attribute->info, bytecode::code("bipush"));
			byteio::write_u1(attribute->info, i);
			//get the value onto the stack
			byteio::write_u1(attribute->info, bytecode::code("iaload"));
			//put the value to the local argument
			byteio::write_u1(attribute->info, bytecode::code("istore"));
			//get the index and put it in // we are assuming arguments are always variables
			byteio::write_u1(attribute->info, i);
		}

		//now jump
		byteio::write_u1(attribute->info, bytecode::code("ret"));
		byteio::write_u1(attribute->info, localIndex["<retIndex>"]);

		//changing value of ret
		finalSize = attribute->info.size();
		//cout<<"next time to jump is when array null: " << finalSize-2-2-4 << endl;
		byteio::write_u2(sipushIndex+1,attribute->info, finalSize-2-2-4);


		node->stmntlist->accept(this);

		byteio::write_u1(attribute->info, bytecode::code("aconst_null"));
		byteio::write_u1(attribute->info, bytecode::code("areturn"));

		byteio::write_u2(attribute->info,0); //exception table length
		byteio::write_u2(attribute->info,0); //attributes_info count
		//size - stack size- max locals - code length - exception table length- info count
		int final_codelength = attribute->info.size()-2-2-4-2-2;
		//changing code length
		byteio::write_u4(4 ,attribute->info, final_codelength);
		attribute->attribute_length= attribute->info.size();
	}


	void visit(YieldNode* node) override {

		method_field_info* method = methods[methods.size()-1];
		attribute_info* attribute = method->attributes[0];

		int arraySize = localIndex.size()+1;

		//put ret into variable
		int sipushIndex = attribute->info.size();
		byteio::write_u1(attribute->info, bytecode::code("sipush"));
		byteio::write_u2(attribute->info, 99); //dummy index
		byteio::write_u1(attribute->info, bytecode::code("istore"));
		byteio::write_u1(attribute->info, localIndex["<retIndex>"]);

		for(int i=1; i <= arraySize-2; i++){
			//load array
			byteio::write_u1(attribute->info, bytecode::code("aload_0"));
			//put index to the stack
			byteio::write_u1(attribute->info, bytecode::code("bipush"));
			byteio::write_u1(attribute->info, i);
			//put local variable to stack
			byteio::write_u1(attribute->info, bytecode::code("iload"));
			byteio::write_u1(attribute->info, i);
			//call iastore
			byteio::write_u1(attribute->info, bytecode::code("iastore"));
		}



		//put result into the stack
		byteio::write_u1(attribute->info, bytecode::code("aload_0")); //put result that will be left on stack
		byteio::write_u1(attribute->info, bytecode::code("bipush")); //put index to the stack
		byteio::write_u1(attribute->info, arraySize-1); //index done now call iastore
		node->expr->accept(this);
		byteio::write_u1(attribute->info, bytecode::code("iastore"));

		byteio::write_u1(attribute->info, bytecode::code("aload_0"));
		byteio::write_u1(attribute->info, bytecode::code("areturn")); //return array after storing

		//size - stack size - max locals - code length
		int finalSize = attribute->info.size()-2-2-4;
		//change the value of ret
		//cout<<"next time to jump is from yield is: " << finalSize << endl;
		byteio::write_u2(sipushIndex+1,attribute->info, finalSize);
	}

	string makeSignature(GenDefNode* node){
		ParamListNode* param = node->param_list;
		paramSize = param->params.size();
		string des = "([I";

		for(int i=0; i< paramSize; i++){
			des = des + "I";
		}
		des= des+ ")[I";
		return des;
	}


	void visit(GenInitNode* node) override{
		method_field_info* method = methods[methods.size()-1];
		attribute_info* attribute = method->attributes[0];

		string varName =  *(node->idVar->name);
		string genProcName =  *(node->idProc->name);
		int numArgs = node->arg_list->args.size();

		generatorNameArgs[varName]= make_pair(genProcName, numArgs);

		//put null for array
		byteio::write_u1(attribute->info, bytecode::code("aconst_null"));
		node->arg_list->accept(this);
		byteio::write_u1(attribute->info, bytecode::code("invokestatic"));
		byteio::write_u2(attribute->info, methodMap[genProcName]);
		byteio::write_u1(attribute->info, bytecode::code("astore"));
		byteio::write_u1(attribute->info, localIndex[varName]);
	}

	void visit(GenInvokNode* node) override {
		method_field_info* method = methods[methods.size()-1];
		attribute_info* attribute = method->attributes[0];

		string genVarName = *(node->id->name);

		string genProcName = generatorNameArgs[genVarName].first;
		int numArgs =  generatorNameArgs[genVarName].second;

		byteio::write_u1(attribute->info, bytecode::code("aload"));
		byteio::write_u1(attribute->info, localIndex[genVarName]);

		for(int i=0; i< numArgs; i++){ //we do not need arguments to invoke anymore so putting it as null
			byteio::write_u1(attribute->info, bytecode::code("iconst_0"));
		}

		//invoke the method
		byteio::write_u1(attribute->info, bytecode::code("invokestatic"));
		byteio::write_u2(attribute->info, methodMap[genProcName]);
		//store the returned array
		byteio::write_u1(attribute->info, bytecode::code("astore"));
		byteio::write_u1(attribute->info, localIndex[genVarName]);
		//get the result value

		byteio::write_u1(attribute->info, bytecode::code("aload"));
		byteio::write_u1(attribute->info, localIndex[genVarName]);

		byteio::write_u1(attribute->info, bytecode::code("bipush"));
		byteio::write_u1(attribute->info, generatorArr[genProcName]-1);
		//get the value onto the stack
		byteio::write_u1(attribute->info, bytecode::code("iaload"));
	}


	void visit(ArgListNode* node) override {
		deque<ExprNode*>  args= node->args;
		for(ExprNode* expr: args){
			expr->accept(this);
		}
	}

	void visit(ProcCallNode* node)override {
		method_field_info* method = methods[methods.size()-1];
		attribute_info* attribute = method->attributes[0];
		string procName = *(node->id->name);

		if(procName == "print"){
			byteio::write_u1(attribute->info, bytecode::code("getstatic"));
			byteio::write_u2(attribute->info, outFieldRef);
			node->arg_list->accept(this);
			byteio::write_u1(attribute->info, bytecode::code("invokevirtual"));
			byteio::write_u2(attribute->info, printMethodRef);
		}
		else if(procName == "readint"){

			//make scanner
			byteio::write_u1(attribute->info, bytecode::code("new"));
			byteio::write_u2(attribute->info, scannerClassIndex);

			byteio::write_u1(attribute->info, bytecode::code("dup"));
			byteio::write_u1(attribute->info, bytecode::code("getstatic"));
			byteio::write_u2(attribute->info, fieldInputStream);
			byteio::write_u1(attribute->info, bytecode::code("invokespecial"));
			byteio::write_u2(attribute->info, scannerInitIndex);

			//getvalue
			byteio::write_u1(attribute->info, bytecode::code("invokevirtual"));
			byteio::write_u2(attribute->info, nextIntMethodRef);

		}
		else {
			node->arg_list->accept(this);
			byteio::write_u1(attribute->info, bytecode::code("invokestatic"));
			if(node->classid==nullptr){
				byteio::write_u2(attribute->info, methodMap[procName]);
			}
			else {
				string className = *(node->classid->name);
				int classIndex;

				if(classMap.find(className) == classMap.end() ){
					new CONSTANT_Class_info( pool ,className);
					classIndex = pool.size()-1;
					classMap[className] = classIndex;
				}
				else {
					classIndex = classMap[className];
				}

				int methodIndex;
				if(methodMap.find(procName) == methodMap.end() ){
					int argSize = node->arg_list->args.size();
					string* descriptor = new string(argSize,'I');
					new CONSTANT_Methodref_info(pool, classIndex, procName, "("+*(descriptor)+")"+"I");
					methodIndex = pool.size()-3 ;
					methodMap[procName] = methodIndex ; //-1 for nametype  -2 for utf
				}
				else {
					methodIndex = methodMap[procName];
				}
				byteio::write_u2(attribute->info, methodMap[procName]);
			}

#ifdef REF
			visitProcCallRef(node, attribute);
#endif

		}
	}


	void visitProcCallRef(ProcCallNode* node, attribute_info* &attribute){
		//we have an array with [p1, p2, ... result] on stack to unload
		ArgListNode* arg_listnode = node->arg_list;

		for(int i = 0 ; i< arg_listnode->args.size(); i++){
			byteio::write_u1(attribute->info, bytecode::code("dup"));
			//put index to the stack
			byteio::write_u1(attribute->info, bytecode::code("bipush"));
			byteio::write_u1(attribute->info, i);
			//get the value onto the stack
			byteio::write_u1(attribute->info, bytecode::code("iaload"));
			//put the value to the local argument
			byteio::write_u1(attribute->info, bytecode::code("istore"));
			//get the index and put it in // we are assuming arguments are always variables
			IdNode* arg = static_cast<IdNode*> (arg_listnode->args.at(i));
			int localArgIndex= localIndex[*(arg->name)];
			byteio::write_u1(attribute->info, localArgIndex);
		}
		byteio::write_u1(attribute->info, bytecode::code("bipush"));
		byteio::write_u1(attribute->info, arg_listnode->args.size());
		//get the value onto the stack
		byteio::write_u1(attribute->info, bytecode::code("iaload"));
	}

	void visit(ReturnNode* node) override {

		method_field_info* method = methods[methods.size()-1];
		attribute_info* attribute = method->attributes[0];

		int nameType_index = (method->name_index_mef)-1;
		CONSTANT_NameAndType_info* ntinfo = static_cast<CONSTANT_NameAndType_info*>(pool[nameType_index-1]);
		CONSTANT_Utf8_info* utfin =  static_cast<CONSTANT_Utf8_info*>(pool[(ntinfo->name_index)-1]);
		string methodName = utfin->description(pool);

		//main method is not allowed return anything
		if(methodName != "main"){
#ifndef REF
			node->expr->accept(this);
			byteio::write_u1(attribute->info, bytecode::code("ireturn"));
#else
			visitReturnRef(node, attribute);
#endif
		}
		else {
			byteio::write_u1(attribute->info, bytecode::code("return"));
		}
	}

	void visitReturnRef(ReturnNode* node, attribute_info* &attribute){
		//if ref is turned on then load all the parameters to the array
		//make array
		byteio::write_u1(attribute->info, bytecode::code("bipush"));
		byteio::write_u1(attribute->info, paramSize+1);
		byteio::write_u1(attribute->info, bytecode::code("newarray"));
		byteio::write_u1(attribute->info, 10); //int type

		//put params into the array
		for(int i = 0; i < paramSize; i++){
			//load array
			byteio::write_u1(attribute->info, bytecode::code("dup"));
			//put index to the stack
			byteio::write_u1(attribute->info, bytecode::code("bipush"));
			byteio::write_u1(attribute->info, i);
			//put local variable to stack
			byteio::write_u1(attribute->info, bytecode::code("iload"));
			byteio::write_u1(attribute->info, i);
			//call iastore
			byteio::write_u1(attribute->info, bytecode::code("iastore"));
		}
		//put result into the array

		//dup the array
		byteio::write_u1(attribute->info, bytecode::code("dup"));

		//put index to the stack
		byteio::write_u1(attribute->info, bytecode::code("bipush"));
		byteio::write_u1(attribute->info, paramSize);

		// after this value to put will be left on the stack
		node->expr->accept(this);
		//put into the array
		byteio::write_u1(attribute->info, bytecode::code("iastore"));

		//return the array
		byteio::write_u1(attribute->info, bytecode::code("areturn"));
	}

	void visit(VarAssignNode* node) override {
		method_field_info* method = methods[methods.size()-1];
		attribute_info* attribute = method->attributes[0];

		node->expr->accept(this);
		if ( localIndex.find(*(node->id->name)) == localIndex.end() ) {

			if ( fieldMap.find(*(node->id->name)) == fieldMap.end() ) {
							cout<<*(node->id->name)<<" --> Variable not defined"<<endl;
			}
			else {
					byteio::write_u1(attribute->info, bytecode::code("putstatic"));
					byteio::write_u2(attribute->info, fieldMap[*(node->id->name)]);
			}
		}
		else {
			byteio::write_u1(attribute->info, bytecode::code("istore"));
			byteio::write_u1(attribute->info, localIndex[*(node->id->name)]);
		}
	}

	void visit(VarDefNode* node) override {
		method_field_info* method = methods[methods.size()-1];
		attribute_info* attribute = method->attributes[0];
		node->expr->accept(this);
		byteio::write_u1(attribute->info, bytecode::code("istore"));
		byteio::write_u1(attribute->info, localIndex[*(node->id->name)]);
	}
};

#endif /* BYTECODEVISITOR_CPP_ */
