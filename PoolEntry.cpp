#ifndef POOLENTRY_CPP_
#define POOLENTRY_CPP_
#include "byteio.h"
#include "bytecode.h"
#include <iomanip>
#include <map>
#include <vector>


using namespace std;


map<string, u4> accessFlagsMap = {
		{"ACC_PUBLIC" , 0x0001},
		{"ACC_PRIVATE" , 0x0002},
		{"ACC_PROTECTED", 0x0004,},
		{"ACC_STATIC", 0x0008},
		{"ACC_FINAL", 0x0010},
		{"ACC_SUPER", 0x0020},
		{"ACC_VOLATILE", 0x0040	},
		{"ACC_VARARGS", 0x0080},
		{"ACC_NATIVE", 0x0100},
		{"ACC_INTERFACE", 0x0200},
		{"ACC_ABSTRACT", 0x0400},
		{"ACC_STRICT", 0x0800},
		{"ACC_SYNTHETIC", 0x1000},
		{"ACC_ANNOTATION", 0x2000	},
		{"ACC_ENUM",0x4000}
};


struct PoolEntry{
	virtual void read(){}
	virtual void print(vector<PoolEntry*> pool) {}
	virtual string description(vector<PoolEntry*> pool){return "incomplete";}
	virtual void write(){}


	static u2 encodeAccessFlags(vector<string> accessFlags){
		u2 encoded = accessFlagsMap[accessFlags[0]];
		for(int i=1; i< accessFlags.size(); i++ ){
			encoded = encoded | accessFlagsMap[(accessFlags[i])];
		}
		return encoded;
	}

};

struct CONSTANT_Utf8_info: public PoolEntry  {
	const int tag= 1;
	u2 length;
	vector<u1> bytes;//u1 bytes[length];

	CONSTANT_Utf8_info(vector<PoolEntry*> &pool, string entryText):
		length(entryText.size()), 
		bytes(entryText.begin(), entryText.end())
	{
		pool.push_back(this);
	}

	void read() override {
		u2 length = byteio::read_u2(ios::in);
		bytes = byteio::read_n(length,ios::in);
	}

	void print(vector<PoolEntry*> pool) override{
		string str = description(pool);
		cout<<"utf8"<<std::setw(str.length()+19)<<str<<endl;;

	}

	string description(vector<PoolEntry*> pool) override {
		stringstream ss;
		for(unsigned int i = 0 ; i < bytes.size(); i++){
			ss << bytes[i];
		}
		return ss.str();
	}

	virtual void write() override {
		byteio::write_u1(tag);
		byteio::write_u2(bytes.size());
		byteio::write_n(bytes);
	}

};

struct CONSTANT_NameAndType_info: public PoolEntry  {
	const int tag = 12;
	u2 name_index;
	u2 descriptor_index;

	CONSTANT_NameAndType_info(vector<PoolEntry*> &pool, string methodName, string methodDescr){
		pool.push_back(this);
		new CONSTANT_Utf8_info(pool, methodName);
		name_index= pool.size();
		new CONSTANT_Utf8_info(pool, methodDescr);
		descriptor_index=pool.size();
	}


	void read() override {
		name_index = byteio::read_u2(ios::in);
		descriptor_index = byteio::read_u2(ios::in);
	}

	void print(vector<PoolEntry*> pool) override{
		cout<<"NameAndType"<<std::setw(13)<<"#"<< name_index<<":#"<<descriptor_index<<std::setw(14)<<"// "<< description(pool)<<endl;
	}

	string description(vector<PoolEntry*> pool) override {
		CONSTANT_Utf8_info* poolEntryName = static_cast<CONSTANT_Utf8_info*> (pool[name_index]);
		string name =  poolEntryName->description(pool);
		CONSTANT_Utf8_info* poolEntryDes = static_cast<CONSTANT_Utf8_info*> (pool[descriptor_index]);
		string descriptor = poolEntryDes->description(pool);
		return (name + ":" + descriptor);
	}

	virtual void write() override{
		byteio::write_u1(tag);
		byteio::write_u2(name_index);
		byteio::write_u2(descriptor_index);
	}
};


struct CONSTANT_Class_info: public PoolEntry {
	const int tag = 7;
	u2 name_index;

	CONSTANT_Class_info(vector<PoolEntry*> &pool, string className){
		pool.push_back(this);
		new CONSTANT_Utf8_info(pool, className);
		name_index= pool.size();
	}

	void read() override {
		name_index = byteio::read_u2(ios::in);
	}

	void print(vector<PoolEntry*> pool) override{
		cout<<"Class"<<std::setw(19)<<"#"<< name_index<<std::setw(18)<<"//"<< description(pool)<<endl;
	}

	string description(vector<PoolEntry*> pool) override {
		CONSTANT_Utf8_info* poolEntry = static_cast<CONSTANT_Utf8_info*> (pool[name_index]);
		return poolEntry->description(pool);
	}

	virtual void write() override{
		byteio::write_u1(tag); 
		byteio::write_u2(name_index);
	}

};

struct CONSTANT_Fieldref_info: public PoolEntry  {
	const int tag =9;
	u2 class_index;
	u2 name_and_type_index;

	CONSTANT_Fieldref_info(vector<PoolEntry*> &pool, u2 classIndex, string fieldName, string fieldDescr){
		pool.push_back(this);
		class_index= classIndex;
		new CONSTANT_NameAndType_info(pool, fieldName, fieldDescr);
		name_and_type_index= pool.size()-2;
	}


	void read() override {
		class_index = byteio::read_u2(ios::in);
		name_and_type_index = byteio::read_u2(ios::in);
	}

	void print(vector<PoolEntry*> pool) override{
		cout<<"Fieldref"<<std::setw(16)<<"#"<<class_index<<".#"<<name_and_type_index<<std::setw(15)<<std::setw(15)<<"// "<<description(pool)<<endl;
	}

	string description(vector<PoolEntry*> pool) override {
		CONSTANT_Class_info* classConstPool = static_cast<CONSTANT_Class_info*>(pool[class_index]);
		string classInfo = classConstPool->description(pool);
		CONSTANT_NameAndType_info* typeConstPool = static_cast<CONSTANT_NameAndType_info*>(pool[name_and_type_index]);
		string nameTypeInfo = typeConstPool->description(pool);
		return classInfo +"."+ nameTypeInfo;
	}

	virtual void write() override{
		byteio::write_u1(tag); //tag
		byteio::write_u2(class_index);  //class index
		byteio::write_u2(name_and_type_index);  //name and type index
	}

};

struct CONSTANT_Methodref_info: public PoolEntry  {
	const int tag = 10;
	u2 class_index;
	u2 name_and_type_index;


	CONSTANT_Methodref_info(vector<PoolEntry*> &pool, u2 classIndex, string methodName, string methodDescr){
		pool.push_back(this);
		class_index= classIndex;
		new CONSTANT_NameAndType_info(pool, methodName, methodDescr);
		name_and_type_index= pool.size()-2;
	}

	void read() override {
		class_index = byteio::read_u2(ios::in);
		name_and_type_index = byteio::read_u2(ios::in);
	}

	void print(vector<PoolEntry*> pool) override{
		cout<<"Methodref"<<std::setw(15)<<"#"<<class_index<<".#"<<name_and_type_index<<std::setw(15)<<"// "<<description(pool)<<endl;
	}

	string description(vector<PoolEntry*> pool) override {
		CONSTANT_Class_info* classConstPool = static_cast<CONSTANT_Class_info*>(pool[class_index]);
		string classInfo = classConstPool->description(pool);
		CONSTANT_NameAndType_info* typeConstPool = static_cast<CONSTANT_NameAndType_info*>(pool[name_and_type_index]);
		string nameTypeInfo = typeConstPool->description(pool);
		return classInfo +"." + nameTypeInfo;
	}

	virtual void write() override{
		byteio::write_u1(tag);
		byteio::write_u2(class_index);  //class index
		byteio::write_u2(name_and_type_index);  //name and type index
	}

};

struct CONSTANT_InterfaceMethodref_info: public PoolEntry  {
	const int tag = 11;
	u2 class_index;
	u2 name_and_type_index;

	CONSTANT_InterfaceMethodref_info(vector<PoolEntry*> &pool, u2 classIndex, string methodName, string methodDescr){
		pool.push_back(this);
		class_index= classIndex;
		new CONSTANT_NameAndType_info(pool, methodName, methodDescr);
		name_and_type_index= pool.size()-2;
	}

	void read() override {
		class_index = byteio::read_u2(ios::in);
		name_and_type_index = byteio::read_u2(ios::in);
	}

	void print(vector<PoolEntry*> pool) override{
		cout<<"Methodref"<<std::setw(15)<<"#"<<class_index<<".#"<<name_and_type_index<<std::setw(15)<<"// "<<description(pool)<<endl;
	}

	string description(vector<PoolEntry*> pool) override {
		CONSTANT_Class_info* classConstPool = static_cast<CONSTANT_Class_info*>(pool[class_index]);
		string classInfo = classConstPool->description(pool);
		CONSTANT_NameAndType_info* typeConstPool = static_cast<CONSTANT_NameAndType_info*>(pool[name_and_type_index]);
		string nameTypeInfo = typeConstPool->description(pool);
		return classInfo + "."+ nameTypeInfo;
	}

	virtual void write() override {
		byteio::write_u1(tag); //tag
		byteio::write_u2(class_index);  //class index
		byteio::write_u2(name_and_type_index);  //name and type index
	}

};

struct CONSTANT_String_info: public PoolEntry  {

	u2 string_index;

	CONSTANT_String_info (vector<PoolEntry*> &pool, string str){
		pool.push_back(this);
		new CONSTANT_Utf8_info(pool, str);
		string_index = pool.size();
	}

	void read() override {
		string_index = byteio::read_u2(ios::in);
	}

	void print(vector<PoolEntry*> pool) override{
		cout<<"String"<<std::setw(18)<<"#"<<string_index<<std::setw(18)<<"// "<<description(pool)<<endl;
	}

	string description(vector<PoolEntry*> pool) override {

		CONSTANT_Utf8_info* poolEntryDes = static_cast<CONSTANT_Utf8_info*> (pool[string_index-1]);
		string descriptor = poolEntryDes->description(pool);
		return descriptor;
	}

	virtual void write() override{
		byteio::write_u1(8); //tag
		byteio::write_u2(string_index); //str_index
	}

};

struct CONSTANT_Integer_info: public PoolEntry  {

	u4 bytes;

	CONSTANT_Integer_info(vector<PoolEntry*> &pool, unsigned int num) : bytes(num){
		pool.push_back(this);
	}

	void read() override {
		bytes = byteio::read_u4(ios::in);
	}

	void print(vector<PoolEntry*> pool) override{
		cout<<"Integer"<<std::setw(17)<<bytes<<endl;
	}

	string description(vector<PoolEntry*> pool) override {
		return "";
	}

	virtual void write() override {
		byteio::write_u1(3); //tag
		byteio::write_u4(bytes); //bytes
	}

};


struct attribute_info{
	u2 attribute_name_index;
	u4 attribute_length;
	vector<u1> info;//[attribute_length];

	attribute_info(){

	}

	attribute_info(u2 name_index, u2 length)
	:
		attribute_name_index(name_index),
		attribute_length(length)
	{

	}

	void read(){
		attribute_name_index = byteio::read_u2(ios::in);
		attribute_length = byteio::read_u4(ios::in);

		for(int i= 0 ; i < attribute_length; i++){
			u1 one= (byteio::read_u1(ios::in));
			info.push_back(one);
		}
	}

	void write(){
		byteio::write_u2(attribute_name_index);
		byteio::write_u4(attribute_length);
		byteio::write_n(info);
	}


	void print(vector<PoolEntry*> pool){
		//cout<<attribute_name_index<<endl;
		CONSTANT_Utf8_info* utfRepDes = static_cast<CONSTANT_Utf8_info*>  (pool[attribute_name_index]);
		string attribute_type= utfRepDes->description(pool);
		if(attribute_type=="Code"){
			u1* curr = (u1*) info.data();
			u2 maxStackSize = byteio::read_u2(curr);
			u2 maxLocalVariable = byteio::read_u2(curr);
			cout<<"stack=" << maxStackSize;
			cout<<", locals=" << maxStackSize<<endl;
			u4 codeLength = byteio::read_u4(curr);

			int counter= 0;

			for(int i= 0; i < codeLength; i++){
				u1 code = byteio::read_u1(curr);
				string instruction = bytecode::name(code);

				if(instruction!="nop"){
					cout<<"\t"<<counter<<":"<<instruction;
					int numArg = bytecode::args(code);
					if(instruction=="newarray" || instruction=="bipush"){
						cout<<"\t\t"<<(int)byteio::read_u1(curr);
					}
					else if(instruction=="sipush" || instruction=="iinc"){
						int index= byteio::read_u1(curr);
						int constant = byteio::read_u1(curr);
						cout<<"\t\t"<<constant;
					}
					else if(instruction=="multianewarray"){
						int index1= byteio::read_u1(curr);
						int index2 = byteio::read_u1(curr);
						int dim = byteio::read_u1(curr);
						cout<<"\t\t#"<<index1<<", "<<index2;
					}
					else{
						bool isPoolRef = bytecode::is_poolref(code);
						bool isJumpRef = bytecode::is_jumpref(code);
						bool isLocalRef = bytecode::is_localref(code);
						stringstream ss;
						string des="";
						ss<<"\t\t";
						if(isJumpRef){
							ss<<"~";
						}
						for(int j= 0; j < numArg; j++){
							int arg = byteio::read_u1(curr);
							if(arg!=0){
								if(isPoolRef){
									ss<<"#"<<arg;
									des = des + pool[arg]->description(pool);

								}
								else if(isLocalRef){
									ss<<":"<<arg;
								}
								else if(isJumpRef){
									ss<<arg;
								}

								else{
									ss<<""<<arg;
								}
							}
						}
						if(isPoolRef){
							cout<<ss.str()<<"\t//"<<des;
						}
						else {
							cout<<ss.str();
						}
					}
					counter= counter+ numArg+1;
					cout<<endl;
				}
			}
		}
	}

};



struct method_field_info{
	u2  access_flags;
	u2  name_index_mef;
	u2  descriptor_index_mef;
	u2  attributes_count;
	vector<attribute_info*> attributes;

	method_field_info(vector<PoolEntry*> &pool, CONSTANT_Methodref_info* methodrefinfo, vector<string> accessFlags){
		access_flags = PoolEntry::encodeAccessFlags(accessFlags);

		u2 nameAndTypeIndex= methodrefinfo->name_and_type_index;
		CONSTANT_NameAndType_info* nametype = static_cast<CONSTANT_NameAndType_info*>(pool[nameAndTypeIndex-1]);

		name_index_mef = nametype->name_index;
		descriptor_index_mef= nametype->descriptor_index;

		//cout<<"name type index"<< nameAndTypeIndex <<endl;
		//cout<<"name_index is: " << name_index_mef <<" " << "des_index" << descriptor_index_mef<<endl;

		attributes_count=1;
	}


	method_field_info(vector<PoolEntry*> &pool, CONSTANT_Fieldref_info* fieldrefinfo, vector<string> accessFlags){
		access_flags = PoolEntry::encodeAccessFlags(accessFlags);

		u2 nameAndTypeIndex= fieldrefinfo->name_and_type_index;
		CONSTANT_NameAndType_info* nametype = static_cast<CONSTANT_NameAndType_info*>(pool[nameAndTypeIndex-1]);

		name_index_mef = nametype->name_index;
		descriptor_index_mef= nametype->descriptor_index;

		//cout<<"name type index"<< nameAndTypeIndex <<endl;
		//cout<<"name_index is: " << name_index_mef <<" " << "des_index" << descriptor_index_mef<<endl;

		attributes_count=0;
	}




	void read(){
		access_flags = byteio::read_u2(ios::in);
		name_index_mef = byteio::read_u2(ios::in);
		descriptor_index_mef = byteio::read_u2(ios::in);
		attributes_count = byteio::read_u2(ios::in);

		for(int i=0; i< attributes_count; i++){
			attribute_info* attributeinfo = new attribute_info();
			attributeinfo->read();
			attributes.push_back(attributeinfo);
		}

	}

	void print(vector<PoolEntry*> pool){

	}

	void write(){
		//attributes_count=1;
		byteio::write_u2(access_flags); //accessflags
		byteio::write_u2(name_index_mef); //name index
		byteio::write_u2(descriptor_index_mef); //des index
		byteio::write_u2(attributes_count);
		for(attribute_info* attributeInfo: attributes){
			attributeInfo->write();
		}
	}
};


#endif /* POOLENTRY_CPP_ */
