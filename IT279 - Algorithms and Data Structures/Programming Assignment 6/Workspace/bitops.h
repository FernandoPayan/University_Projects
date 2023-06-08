#ifndef _BITOPS_H
#define _BITOPS_H

//
// Author: Owen Astrachan
//         Based on code written by Steve Tate
//
// facilitates reading/writing in a "bits-at-a-time" fashion
// 
// ported to C++ on 3/27/94
//

#include <fstream>
using namespace std;

// # of bits-per-char
    
const int  BITS_PER_WORD  = 8;

// ALPH_SIZE should be 2^BITS_PER_WORD

const int  ALPH_SIZE  = 256;

extern int KthBit(int,int);

// operations on obstream
//
//  obstream()
//         constructs output bit-stream (in unusable form)
//         use name in constructor or use Open method to bind to a file
//    
//  obstream(const char name[])
//         constructs output bit-stream bound to file specified by parameter
//    
//  int  Open(const char name[])
//         sets output bit-stream to file specified by parameter
//         (previously open bit-stream closed)
//         returns 1 if open successful, else 0
//
// void Writebits(int value, int numbits)
//         writes rightmost # bits specified by second parameter
//         taken from the first parameter
//         (bits may be "buffered" for the next write)
//
//  void Flushbits()
//         writes any "left-over" (buffered) bits
//
//  void Close()
//         closes stream properly (flushes too).




// operations on ibstream
//
// ibstream()
//         constructs input bit-stream that is not usable
//         use name in constructor or Open method to bind to a file
//
// ibstream(const char name[])
//         construct input bit-stream bound to specified file
//
// int Open(const char name[])
//         bind input bit-stream to file specified
//         (previously open bit-stream closed)
//         returns 1 if open successful, else 0
//
// int Readbits(int)
//         reads number of bits specified by parameter and returns an
//         int representing this value
//         EXCEPTION: returns EOF if end-of-file encountered
//                    maximum number of bits that can be read is 32
//
//  void ResetBits()
//         effectively flushes bits buffered during read operations
//         so that subsequent reads start "from scratch"
//
//  void Rewind()
//         reset input bit-stream to beginning, clear it
//
//  void Close()
//         closes stream properly (flushes too).
//
// stand-alone function
//    
//   int KthBit(intx, int k)
//          returns the kth bit of the int x: rightmost bit is bit #1
//          EXCEPTION: error if k < 1 or k > 32
//
// specification: bits are read/written in the "same" order
// i.e., if 15 bits are written, then these bits will be read
// in the same order as written if 15 1-bit reads are issued.


class obstream 
{
 public:
  obstream();                      // default constructor
  obstream(const char name[]);        // bind to file specified by param
     ~obstream();

     int Open(const char name[]);         // set bit-stream to file
     void Writebits(int,int);          // value and # of bits to write
     void Flushbits();                 // flush bit-stream
     void Close();                     // wrap things up
 private:

     obstream(const obstream & os);    // disable pass-by-value
      
     ofstream * os;                    // stream for writing bits
     int outbuff;                      // buffer bits for output
     int bitsToGo;                     // # of 'left-over' bits for output 
};


class ibstream
{
 public:
  ibstream();                      // default constructor
  ibstream(const char name[]);        // bind to file specified by param
     virtual ~ibstream();

     int Open(const char name[]);        // set bit-stream to specified file
     int Readbits(int);               // # of bits to read
     void Resetbits();                // reset bits
     void Rewind();                   // rewind to beginning of input
     void Close();                    // wrap things up nicely
 private:

     ibstream(const ibstream & os);   // disable pass-by-value 
     ifstream * is;                   // stream for reading bits
     int inbuff;                      // buffer bits for input
     int inbbits;                     // used for buffering 
};


#endif

