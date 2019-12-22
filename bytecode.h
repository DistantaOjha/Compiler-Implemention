#ifndef BYTECODE_H_
#define BYTECODE_H_

#include <iostream>
#include <unordered_map>
#include <set>
#include <tuple>
#include <string>
#include <cstdlib>


/*
  The list of available functions follows. General usage:

  bytecode::function(parameters)     // always prefix with   bytecode::
  
  string name(u1 code)         // name of instruction
  int args(u1 code)            // number of args of instruction
  u1 code(string name)         // code of instruction
  bool is_poolref(u1 code)     // does it reference const pool
  bool is_jumpref(u1 code)     // does it cause jump
  bool is_localref(u1 code)    // does it reference local variable
 */


namespace bytecode {

  using u1 = unsigned char;

  // returns the name of the instruction
  // with the given bytecode
  std::string name(u1 code);

  // returns the number of arguments of the
  // instruction with the given bytecode
  int args(u1 code);

  // returns the opcode (hex value) of the instruction
  // with the given name
  u1 code(const std::string& code);

  // determines whether the instructions with the
  // given bytecode references the constant pool
  bool is_poolref(u1 code);
  
  // determines whether the instructions with the
  // given bytecode makes a jump to ne instruction
  bool is_jumpref(u1 code);

  // determines whether the instructions with the
  // given bytecode references a local variable
  bool is_localref(u1 code);

  // exceptions -- handle separately:
  // 1: newarray, bipush
  // 2: sipush, iinc
  // 3: multianewarray

  
  // ---------------------------------------
  // the bookkeeping section -- could ignore
  // ---------------------------------------

  // the bytecoed instructions with their names and number of arguments
  std::unordered_map<u1, std::tuple<std::string, int>> code2name_map = {
	{0x32, {"aaload", 0}},
	{0x53, {"aastore", 0}},
	{0x01, {"aconst_null", 0}},
	{0x19, {"aload", 1}},
	{0x2a, {"aload_0", 0}},
	{0x2b, {"aload_1", 0}},
	{0x2c, {"aload_2", 0}},
	{0x2d, {"aload_3", 0}},
	{0xbd, {"anewarray", 2}},
	{0xb0, {"areturn", 0}},
	{0xbe, {"arraylength", 0}},
	{0x3a, {"astore", 1}},
	{0x4b, {"astore_0", 0}},
	{0x4c, {"astore_1", 0}},
	{0x4d, {"astore_2", 0}},
	{0x4e, {"astore_3", 0}},
	{0xbf, {"athrow", 0}},
	{0x33, {"baload", 0}},
	{0x54, {"bastore", 0}},
	{0x10, {"bipush", 1}},
	{0xca, {"breakpoint", 0}},
	{0x34, {"caload", 0}},
	{0x55, {"castore", 0}},
	{0xc0, {"checkcast", 2}},
	{0x90, {"d2f", 0}},
	{0x8e, {"d2i", 0}},
	{0x8f, {"d2l", 0}},
	{0x63, {"dadd", 0}},
	{0x31, {"daload", 0}},
	{0x52, {"dastore", 0}},
	{0x98, {"dcmpg", 0}},
	{0x97, {"dcmpl", 0}},
	{0x0e, {"dconst_0", 0}},
	{0x0f, {"dconst_1", 0}},
	{0x6f, {"ddiv", 0}},
	{0x18, {"dload", 1}},
	{0x26, {"dload_0", 0}},
	{0x27, {"dload_1", 0}},
	{0x28, {"dload_2", 0}},
	{0x29, {"dload_3", 0}},
	{0x6b, {"dmul", 0}},
	{0x77, {"dneg", 0}},
	{0x73, {"drem", 0}},
	{0xaf, {"dreturn", 0}},
	{0x39, {"dstore", 1}},
	{0x47, {"dstore_0", 0}},
	{0x48, {"dstore_1", 0}},
	{0x49, {"dstore_2", 0}},
	{0x4a, {"dstore_3", 0}},
	{0x67, {"dsub", 0}},
	{0x59, {"dup", 0}},
	{0x5a, {"dup_x1", 0}},
	{0x5b, {"dup_x2", 0}},
	{0x5c, {"dup2", 0}},
	{0x5d, {"dup2_x1", 0}},
	{0x5e, {"dup2_x2", 0}},
	{0x8d, {"f2d", 0}},
	{0x8b, {"f2i", 0}},
	{0x8c, {"f2l", 0}},
	{0x62, {"fadd", 0}},
	{0x30, {"faload", 0}},
	{0x51, {"fastore", 0}},
	{0x96, {"fcmpg", 0}},
	{0x95, {"fcmpl", 0}},
	{0x0b, {"fconst_0", 0}},
	{0x0c, {"fconst_1", 0}},
	{0x0d, {"fconst_2", 0}},
	{0x6e, {"fdiv", 0}},
	{0x17, {"fload", 1}},
	{0x22, {"fload_0", 0}},
	{0x23, {"fload_1", 0}},
	{0x24, {"fload_2", 0}},
	{0x25, {"fload_3", 0}},
	{0x6a, {"fmul", 0}},
	{0x76, {"fneg", 0}},
	{0x72, {"frem", 0}},
	{0xae, {"freturn", 0}},
	{0x38, {"fstore", 1}},
	{0x43, {"fstore_0", 0}},
	{0x44, {"fstore_1", 0}},
	{0x45, {"fstore_2", 0}},
	{0x46, {"fstore_3", 0}},
	{0x66, {"fsub", 0}},
	{0xb4, {"getfield", 2}},
	{0xb2, {"getstatic", 2}},
	{0xa7, {"goto", 2}},
	{0xc8, {"goto_w", 4}},
	{0x91, {"i2b", 0}},
	{0x92, {"i2c", 0}},
	{0x87, {"i2d", 0}},
	{0x86, {"i2f", 0}},
	{0x85, {"i2l", 0}},
	{0x93, {"i2s", 0}},
	{0x60, {"iadd", 0}},
	{0x2e, {"iaload", 0}},
	{0x7e, {"iand", 0}},
	{0x4f, {"iastore", 0}},
	{0x02, {"iconst_m1", 0}},
	{0x03, {"iconst_0", 0}},
	{0x04, {"iconst_1", 0}},
	{0x05, {"iconst_2", 0}},
	{0x06, {"iconst_3", 0}},
	{0x07, {"iconst_4", 0}},
	{0x08, {"iconst_5", 0}},
	{0x6c, {"idiv", 0}},
	{0xa5, {"if_acmpeq", 2}},
	{0xa6, {"if_acmpne", 2}},
	{0x9f, {"if_icmpeq", 2}},
	{0xa2, {"if_icmpge", 2}},
	{0xa3, {"if_icmpgt", 2}},
	{0xa4, {"if_icmple", 2}},
	{0xa1, {"if_icmplt", 2}},
	{0xa0, {"if_icmpne", 2}},
	{0x99, {"ifeq", 2}},
	{0x9c, {"ifge", 2}},
	{0x9d, {"ifgt", 2}},
	{0x9e, {"ifle", 2}},
	{0x9b, {"iflt", 2}},
	{0x9a, {"ifne", 2}},
	{0xc7, {"ifnonnull", 2}},
	{0xc6, {"ifnull", 2}},
	{0x84, {"iinc", 2}},
	{0x15, {"iload", 1}},
	{0x1a, {"iload_0", 0}},
	{0x1b, {"iload_1", 0}},
	{0x1c, {"iload_2", 0}},
	{0x1d, {"iload_3", 0}},
	{0xfe, {"impdep1", 0}},
	{0xff, {"impdep2", 0}},
	{0x68, {"imul", 0}},
	{0x74, {"ineg", 0}},
	{0xc1, {"instanceof", 2}},
	{0xba, {"invokedynamic", 4}},
	{0xb9, {"invokeinterface", 4}},
	{0xb7, {"invokespecial", 2}},
	{0xb8, {"invokestatic", 2}},
	{0xb6, {"invokevirtual", 2}},
	{0x80, {"ior", 0}},
	{0x70, {"irem", 0}},
	{0xac, {"ireturn", 0}},
	{0x78, {"ishl", 0}},
	{0x7a, {"ishr", 0}},
	{0x36, {"istore", 1}},
	{0x3b, {"istore_0", 0}},
	{0x3c, {"istore_1", 0}},
	{0x3d, {"istore_2", 0}},
	{0x3e, {"istore_3", 0}},
	{0x64, {"isub", 0}},
	{0x7c, {"iushr", 0}},
	{0x82, {"ixor", 0}},
	{0xa8, {"jsr", 2}},
	{0xc9, {"jsr_w", 4}},
	{0x8a, {"l2d", 0}},
	{0x89, {"l2f", 0}},
	{0x88, {"l2i", 0}},
	{0x61, {"ladd", 0}},
	{0x2f, {"laload", 0}},
	{0x7f, {"land", 0}},
	{0x50, {"lastore", 0}},
	{0x94, {"lcmp", 0}},
	{0x09, {"lconst_0", 0}},
	{0x0a, {"lconst_1", 0}},
	{0x12, {"ldc", 1}},
	{0x13, {"ldc_w", 2}},
	{0x14, {"ldc2_w", 2}},
	{0x6d, {"ldiv", 0}},
	{0x16, {"lload", 1}},
	{0x1e, {"lload_0", 0}},
	{0x1f, {"lload_1", 0}},
	{0x20, {"lload_2", 0}},
	{0x21, {"lload_3", 0}},
	{0x69, {"lmul", 0}},
	{0x75, {"lneg", 0}},
	{0x81, {"lor", 0}},
	{0x71, {"lrem", 0}},
	{0xad, {"lreturn", 0}},
	{0x79, {"lshl", 0}},
	{0x7b, {"lshr", 0}},
	{0x37, {"lstore", 1}},
	{0x3f, {"lstore_0", 0}},
	{0x40, {"lstore_1", 0}},
	{0x41, {"lstore_2", 0}},
	{0x42, {"lstore_3", 0}},
	{0x65, {"lsub", 0}},
	{0x7d, {"lushr", 0}},
	{0x83, {"lxor", 0}},
	{0xc2, {"monitorenter", 0}},
	{0xc3, {"monitorexit", 0}},
	{0xc5, {"multianewarray", 3}},
	{0xbb, {"new", 2}},
	{0xbc, {"newarray", 1}},
	{0x00, {"nop", 0}},
	{0x57, {"pop", 0}},
	{0x58, {"pop2", 0}},
	{0xb5, {"putfield", 2}},
	{0xb3, {"putstatic", 2}},
	{0xa9, {"ret", 1}},
	{0xb1, {"return", 0}},
	{0x35, {"saload", 0}},
	{0x56, {"sastore", 0}},
	{0x11, {"sipush", 2}},
	{0x5f, {"swap", 0}},
  };

  std::unordered_map<string, u1> name2code_map = {
	{"aaload",	0x32},
	{"aastore",	0x53},
	{"aconst_null",	0x01},
	{"aload",	0x19},
	{"aload_0",	0x2a},
	{"aload_1",	0x2b},
	{"aload_2",	0x2c},
	{"aload_3",	0x2d},
	{"anewarray",	0xbd},
	{"areturn",	0xb0},
	{"arraylength",	0xbe},
	{"astore",	0x3a},
	{"astore_0",	0x4b},
	{"astore_1",	0x4c},
	{"astore_2",	0x4d},
	{"astore_3",	0x4e},
	{"athrow",	0xbf},
	{"baload",	0x33},
	{"bastore",	0x54},
	{"bipush",	0x10},
	{"breakpoint",	0xca},
	{"caload",	0x34},
	{"castore",	0x55},
	{"checkcast",	0xc0},
	{"d2f",		0x90},
	{"d2i",		0x8e},
	{"d2l",		0x8f},
	{"dadd",	0x63},
	{"daload",	0x31},
	{"dastore",	0x52},
	{"dcmpg",	0x98},
	{"dcmpl",	0x97},
	{"dconst_0",	0x0e},
	{"dconst_1",	0x0f},
	{"ddiv",	0x6f},
	{"dload",	0x18},
	{"dload_0",	0x26},
	{"dload_1",	0x27},
	{"dload_2",	0x28},
	{"dload_3",	0x29},
	{"dmul",	0x6b},
	{"dneg",	0x77},
	{"drem",	0x73},
	{"dreturn",	0xaf},
	{"dstore",	0x39},
	{"dstore_0",	0x47},
	{"dstore_1",	0x48},
	{"dstore_2",	0x49},
	{"dstore_3",	0x4a},
	{"dsub",	0x67},
	{"dup",		0x59},
	{"dup_x1",	0x5a},
	{"dup_x2",	0x5b},
	{"dup2",	0x5c},
	{"dup2_x1",	0x5d},
	{"dup2_x2",	0x5e},
	{"f2d",		0x8d},
	{"f2i",		0x8b},
	{"f2l",		0x8c},
	{"fadd",	0x62},
	{"faload",	0x30},
	{"fastore",	0x51},
	{"fcmpg",	0x96},
	{"fcmpl",	0x95},
	{"fconst_0",	0x0b},
	{"fconst_1",	0x0c},
	{"fconst_2",	0x0d},
	{"fdiv",	0x6e},
	{"fload",	0x17},
	{"fload_0",	0x22},
	{"fload_1",	0x23},
	{"fload_2",	0x24},
	{"fload_3",	0x25},
	{"fmul",	0x6a},
	{"fneg",	0x76},
	{"frem",	0x72},
	{"freturn",	0xae},
	{"fstore",	0x38},
	{"fstore_0",	0x43},
	{"fstore_1",	0x44},
	{"fstore_2",	0x45},
	{"fstore_3",	0x46},
	{"fsub",	0x66},
	{"getfield",	0xb4},
	{"getstatic",	0xb2},
	{"goto",	0xa7},
	{"goto_w",	0xc8},
	{"i2b",		0x91},
	{"i2c",		0x92},
	{"i2d",		0x87},
	{"i2f",		0x86},
	{"i2l",		0x85},
	{"i2s",		0x93},
	{"iadd",	0x60},
	{"iaload",	0x2e},
	{"iand",	0x7e},
	{"iastore",	0x4f},
	{"iconst_m1",	0x02},
	{"iconst_0",	0x03},
	{"iconst_1",	0x04},
	{"iconst_2",	0x05},
	{"iconst_3",	0x06},
	{"iconst_4",	0x07},
	{"iconst_5",	0x08},
	{"idiv",	0x6c},
	{"if_acmpeq",	0xa5},
	{"if_acmpne",	0xa6},
	{"if_icmpeq",	0x9f},
	{"if_icmpge",	0xa2},
	{"if_icmpgt",	0xa3},
	{"if_icmple",	0xa4},
	{"if_icmplt",	0xa1},
	{"if_icmpne",	0xa0},
	{"ifeq",	0x99},
	{"ifge",	0x9c},
	{"ifgt",	0x9d},
	{"ifle",	0x9e},
	{"iflt",	0x9b},
	{"ifne",	0x9a},
	{"ifnonnull",	0xc7},
	{"ifnull",	0xc6},
	{"iinc",	0x84},
	{"iload",	0x15},
	{"iload_0",	0x1a},
	{"iload_1",	0x1b},
	{"iload_2",	0x1c},
	{"iload_3",	0x1d},
	{"impdep1",	0xfe},
	{"impdep2",	0xff},
	{"imul",	0x68},
	{"ineg",	0x74},
	{"instanceof",	0xc1},
	{"invokedynamic",	0xba},
	{"invokeinterface",	0xb9},
	{"invokespecial",	0xb7},
	{"invokestatic",	0xb8},
	{"invokevirtual",	0xb6},
	{"ior",		0x80},
	{"irem",	0x70},
	{"ireturn",	0xac},
	{"ishl",	0x78},
	{"ishr",	0x7a},
	{"istore",	0x36},
	{"istore_0",	0x3b},
	{"istore_1",	0x3c},
	{"istore_2",	0x3d},
	{"istore_3",	0x3e},
	{"isub",	0x64},
	{"iushr",	0x7c},
	{"ixor",	0x82},
	{"jsr",		0xa8},
	{"jsr_w",	0xc9},
	{"l2d",		0x8a},
	{"l2f",		0x89},
	{"l2i",		0x88},
	{"ladd",	0x61},
	{"laload",	0x2f},
	{"land",	0x7f},
	{"lastore",	0x50},
	{"lcmp",	0x94},
	{"lconst_0",	0x09},
	{"lconst_1",	0x0a},
	{"ldc",		0x12},
	{"ldc_w",	0x13},
	{"ldc2_w",	0x14},
	{"ldiv",	0x6d},
	{"lload",	0x16},
	{"lload_0",	0x1e},
	{"lload_1",	0x1f},
	{"lload_2",	0x20},
	{"lload_3",	0x21},
	{"lmul",	0x69},
	{"lneg",	0x75},
	{"lor",		0x81},
	{"lrem",	0x71},
	{"lreturn",	0xad},
	{"lshl",	0x79},
	{"lshr",	0x7b},
	{"lstore",	0x37},
	{"lstore_0",	0x3f},
	{"lstore_1",	0x40},
	{"lstore_2",	0x41},
	{"lstore_3",	0x42},
	{"lsub",	0x65},
	{"lushr",	0x7d},
	{"lxor",	0x83},
	{"monitorenter",0xc2},
	{"monitorexit",	0xc3},
	{"multianewarray",0xc5},
	{"new",		0xbb},
	{"newarray",	0xbc},
	{"nop",		0x00},
	{"pop",		0x57},
	{"pop2",	0x58},
	{"putfield",	0xb5},
	{"putstatic",	0xb3},
	{"ret",		0xa9},
	{"return",	0xb1},
	{"saload",	0x35},
	{"sastore",	0x56},
	{"sipush",	0x11},
	{"swap",	0x5f},
  };
  
  std::string name(u1 code)
  {
    if (code2name_map.count(code) == 0) {
      std::cout << "invalid instruction code: "
		<< std::hex << int(code) << std::dec << std::endl;
      exit(1);
    }
    else {
      return std::get<0>(code2name_map[code]);
    }
  }

  u1 code(const std::string& name)
  {
    if (name2code_map.count(name) == 0) {
      std::cout << "invalid instruction name: " << name << std::endl;
      exit(1);
    }
    else {
      return name2code_map[name];
    }
  }

  int args(u1 code)
  {
    if (code2name_map.count(code) == 0) {
      std::cout << "invalid instruction code: "
		<< std::hex << int(code) << std::dec << std::endl;
      exit(1);
    }
    else {
      return std::get<1>(code2name_map[code]);
    }
  }

  bool is_poolref(u1 code)
  {
    const std::set<u1> instructions = {
	0xbd,  // anewarray
	0xc0,  // checkcast
	0xb4,  // getfield
	0xb2,  // getstatic
	0xc1,  // instanceof
	0xba,  // invokedynamic (4 bytes)
	0xb9,  // invokeinterface (4 bytes)
	0xb7,  // invokespecial
	0xb8,  // invokestatic
	0xb6,  // invokevirtual
	0x12,  // ldc
	0x13,  // ldc_w
	0x14,  // ldc2_w
	0xc5,  // multianewarray (3 bytes)
	0xbb,  // new
	0xb5,  // putfield
	0xb3,  // putstatic
    };

    return instructions.count(code) != 0;
  }

  bool is_jumpref(u1 code)
  {
    const std::set<u1> instructions = {
	0xc8,  // goto_w (4 bytes)
	0xa7,  // goto
	0xa5,  // if_acmpeq
	0xa6,  // if_acmpne
	0x9f,  // if_icmpeq
	0xa2,  // if_icmpge
	0xa3,  // if_icmpgt
	0xa4,  // if_icmple
	0xa1,  // if_icmplt
	0xa0,  // if_icmpne
	0x99,  // ifeq
	0x9c,  // ifge
	0x9d,  // ifgt
	0x9e,  // ifle
	0x9b,  // iflt
	0x9a,  // ifne
	0xc7,  // ifnonnull
	0xc6,  // ifnull
	0xa8,  // jsr
	0xc9,  // jsr_w (4 bytes)
    };

    return instructions.count(code) != 0;
  }

  bool is_localref(u1 code)
  {
    const std::set<u1> instructions = {
	0x19,  // aload
	0x3a,  // astore
	0x18,  // dload
	0x39,  // dstore
	0x17,  // fload
	0x38,  // fstore
	0x15,  // iload
	0x36,  // istore
	0x16,  // lload
	0x37,  // lstore
	0xa9,  // ret
    };

    return instructions.count(code) != 0;
  }
}

#endif
