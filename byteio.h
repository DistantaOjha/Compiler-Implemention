
#ifndef BYTEIO_H_
#define BYTEIO_H_

#include <ios>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


// convenient aliases for 1,2,4 byte types
using u1 = unsigned char;
using u2 = unsigned short;
using u4 = unsigned int;

/*
  The list of available functions follows. General usage:

  byteio::function(parameters)     // always prefix with   byteio::

  
  Writing Bytes
  -------------
  // attaches a stream to the writer -- must be called
  // before the writer can be used
  static void attach_out(ofstream& stream)

  // functions for writing 1,2,4,n bytes to the attached stream
  static void write_u1(u1 byte)
  static void write_u2(u2 word)
  static void write_u4(u4 quad)
  static void write_n(string str)
  static void write_n(vector bytes)

  // functions for writing 1,2,4,n bytes to the end of the given vector
  // [ the vector will be resized ]
  static void write_u1(vector<u1>& dest, u1 b)
  static void write_u2(vector<u1>& dest, u2 w)
  static void write_u4(vector<u1>& dest, u4 q)

  // functions for writing 1,2,4,n bytes to the end of the given vector
  // [ vector is not resized and cells are overwritten ]
  static void write_u1(int pos, vector<u1>& dest, u1 b)
  static void write_u2(int pos, vector<u1>& dest, u2 w)
  static void write_u4(int pos, vector<u1>& dest, u4 q)


  Reading Bytes
  -------------
  byteio::read_u1(ios::in)         // use file as source
  byteio::read_u1(curr_ptr)        // use pointer as source

  // attaches a stream to the reader -- must be called
  // before the reader can be used
  static void attach_in(ifstream& stream)

  // functions for reading 1,2,4,n bytes from the attached stream
  static u1 read_u1(ios_base::openmode)
  static u2 read_u2(ios_base::openmode)
  static u4 read_u4(ios_base::openmode)
  static vector<u1> read_n(int n, ios_base::openmode)

  // functions for reading 1,2,4,n bytes from the given pointer
  // the pointer will be advanced by the number of bytes read
  static u1 read_u1(u1*& ptr)
  static u2 read_u2(u1*& ptr)
  static u4 read_u4(u1*& ptr)

  // converts a collection of bytes to string
  static string to_string(const vector<u1>& bytes)
*/


class byteio
{
private:
  // the stream to read from -- must be attached first
  inline static ifstream* ifs = nullptr;

  // the stream to read from -- must be attached first
  inline static ofstream* ofs = nullptr;
  
public:
  // attaches the given stream to the reader
  static void attach_in(ifstream& stream)
  {
    ifs = &stream;
  }

  // attaches the given stream to the reader
  static void attach_out(ofstream& stream)
  {
    ofs = &stream;
  }

  // writes 1-byte value to the attached stream
  static void write_u1(u1 b)
  {
    ofs->write((const char*) &b, 1);
  }

  // writes 2-byte value to the attached stream
  static void write_u2(u2 b)
  {
    u1* ptr = (u1*) &b;
    write_u1(*(ptr+1));
    write_u1(*ptr);
  }

  // writes 4-byte value to the attached stream
  static void write_u4(u4 b)
  {
    u2* ptr = (u2*) &b;
    write_u2(*(ptr+1));
    write_u2(*ptr);
  }

  // writes the characters in the given string as bytes to the attached stream
  static void write_n(const std::string& str)
  {
    for (char ch : str) {
      write_u1(ch);
    }
  }

  // writes the bytes in the given vector to the attached stream
  static void write_n(const std::vector<u1>& bytes)
  {
    for (u1 b : bytes) {
      write_u1(b);
    }
  }

  // writes 1-byte value at the end of given destination vector
  // [the vector will be resized]
  static void write_u1(vector<u1>& dest, u1 b)
  {
    dest.push_back(b);
  }

  // writes 2-byte value at the end of given destination vector
  // [the vector will be resized]
  static void write_u2(vector<u1>& dest, u2 w)
  {
    u1* ptr = (u1*) &w;
    write_u1(dest, *(ptr+1));
    write_u1(dest, *ptr);
  }

  // writes 4-byte value at the end of given destination vector
  // [the vector will be resized]
  static void write_u4(vector<u1>& dest, u4 q)
  {
    u2* ptr = (u2*) &q;
    write_u2(dest, *(ptr+1));
    write_u2(dest, *ptr);
  }


  // writes 1-byte value at the end of given destination vector
  // [the vector will be resized]
  static void write_u1(int pos, vector<u1>& dest, u1 b)
  {
    dest[pos] = b;
  }

  // writes 2-byte value at the end of given destination vector
  // [the vector will be resized]
  static void write_u2(int pos, vector<u1>& dest, u2 w)
  {
    u1* ptr = (u1*) &w;
    write_u1(pos, dest, *(ptr+1));
    write_u1(pos+1, dest, *ptr);
  }

  // writes 4-byte value at the end of given destination vector
  // [the vector will be resized]
  static void write_u4(int pos, vector<u1>& dest, u4 q)
  {
    u2* ptr = (u2*) &q;
    write_u2(pos, dest, *(ptr+1));
    write_u2(pos+2, dest, *ptr);
  }


  // reads 1-byte value from the attached stream
  static u1 read_u1(ios_base::openmode)
  {
    u1 b = ifs->get();
    return b;
  }

  // reads 2-byte value from the attached stream
  static u2 read_u2(ios_base::openmode)
  {
    u1 b1 = read_u1(ios::in);    // read byte
    u1 b2 = read_u1(ios::in);    // read byte

    u2 w = b1;            // pack bytes into word
    w = (w << 8) | b2;
    return w;
  }

  // [another version] reads 2-byte value from the attached stream
  // static u2 read_u2(ios_base::openmode)
  // {
  //   u2 w;
  //   char* ptr = (char*) &w;
  //   ifs->get(*(ptr+1));
  //   ifs->get(*ptr);
  //   return w;
  // }

  // reads 4-byte value from the attached stream
  static u4 read_u4(ios_base::openmode)
  {
    u2 w1 = read_u2(ios::in);    // read word
    u2 w2 = read_u2(ios::in);    // read word

    u4 q = w1;            // pack words into quad
    q = (q << 16) | w2;
    return q;
  }

  // reads n bytes from the attached stream
  static vector<u1> read_n(int n, ios_base::openmode)
  {
    vector<u1> bytes(n);
    for (int i = 0; i < n; ++i) {
      bytes[i] = read_u1(ios::in);
    }
    return bytes;
  }

  // reads 1-byte value from the given source pointer
  // [the pointer will be moved 1 byte ahead]
  static u1 read_u1(u1*& ptr)
  {
    u1 b = *ptr;
    ++ptr;
    return b;
  }

  // reads 2-byte value from the given source pointer
  // [the pointer will be moved 2 bytes ahead]
  static u2 read_u2(u1*& ptr)
  {
    u1 b1 = read_u1(ptr);
    u1 b2 = read_u1(ptr);

    u2 w = b1;
    w = (w << 8) | b2;
    return w;
  }
  
  // reads 4-byte value from the given source pointer
  // [the pointer will be moved 4 bytes ahead]
  static u4 read_u4(u1*& ptr)
  {
    u2 w1 = read_u2(ptr);
    u2 w2 = read_u2(ptr);
    
    u4 q = w1;
    q = (q << 16) | w2;
    return q;
  }

  // converts a collection of bytes into a string
  // [useful for printing]
  static string to_string(const vector<u1>& bytes)
  {
    string str = "";
    for (u1 b : bytes) {
      str += b;
    }
    return str;
  }
};

#endif
