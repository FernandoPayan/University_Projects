//
//   authors: Steve Tate, Owen Astrachan
//   Bitstream I/O routines.
//   Feb 4, 1993 -- srt
//   modified by ola to ensure bits written in "fifo" order
//   (thus can be read in different chunks than written and
//   get same bit stream
//
//   ported to C++ by Owen Astrachan 3/27/94

#include <iostream>
#include "bitops.h"

// bit stuff

// allows a specific bit to be masked from a number
// usage: bmask[k] has the rightmost k bits == 1, other bits 0
//
static int bmask[] = {0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff,
                      0x1ff, 0x3ff, 0x7ff, 0xfff, 0x1fff, 0x3fff, 0x7fff, 0xffff,
                      0x1ffff, 0x3ffff, 0x7ffff, 0xfffff, 0x1fffff, 0x3fffff,
                      0x7fffff, 0xffffff, 0x1ffffff, 0x3ffffff, 0x7ffffff,
                      0xfffffff, 0x1fffffff, 0x3fffffff, 0x7fffffff, (int)0xffffffff};

static int
    pickbit[] = {0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80,
                 0x100, 0x200, 0x400, 0x800, 0x1000, 0x2000, 0x4000, 0x8000,
                 0x10000, 0x20000, 0x40000, 0x80000, 0x1000000, 0x2000000};

int KthBit(int x, int k)
// postcondition: returns k-th bit of x
{
  return x & pickbit[k];
}

// output bit stream class

obstream::obstream()
// postcondition: unusable but initialized bit-stream object
{
  os = NULL;                // initialize to no stream
  outbuff = 0;              // nothing in buffer
  bitsToGo = BITS_PER_WORD; // bits to go before buffer filled
}

obstream::obstream(const char name[])
// postcondition : bitstream  bound to file specified by name
{
  os = new ofstream(name);
  outbuff = 0;
  bitsToGo = BITS_PER_WORD;
}

void obstream::Writebits(int value, int numbits)
// postconditin: rightmost numbits bits of value written (buffered)
{

  if (os == NULL)
  {
    return; // can't do anything with no stream
  }

  while (numbits >= bitsToGo)
  {
    //cout << "BITSTOGO: " << bitsToGo << endl;
    outbuff = (outbuff << bitsToGo) | (value >> (numbits - bitsToGo));
    os->put(outbuff);
    value &= bmask[numbits - bitsToGo];
    numbits -= bitsToGo;
    bitsToGo = BITS_PER_WORD;
    outbuff = 0;
  }

  if (numbits > 0)
  {
    outbuff = (outbuff << numbits) | value;
    bitsToGo -= numbits;
  }
}

void obstream::Flushbits()
// postcondition: unwritten (buffered) bits are flushed
{

  if (os == NULL)
  {
    return; // can't do anythign with no stream
  }

  if (bitsToGo != BITS_PER_WORD)
  {
    os->put((outbuff << bitsToGo));
    outbuff = 0;
    bitsToGo = BITS_PER_WORD;
  }
}

int obstream::Open(const char name[])
// postcondition: output bit stream set to file specified by name
//                any open bit-stream is closed (not flushed)
{
  if (os && os->good())
  {
    os->close();
    delete os;
  }
  os = new ofstream(name);
  outbuff = 0;
  bitsToGo = BITS_PER_WORD;
  return os && os->good();
}

obstream::~obstream()
// postcondition: close things up, free memory
{
  if (os)
  {
    Flushbits();
    os->close();
    delete os;
  }
}

void obstream::Close()
// postcondition: close the output bit stream
{
  Flushbits();
  if (os)
    os->close();
}

// input bit-stream class

ibstream::ibstream()
// postcondition: unusable but initialized bit-stream object
{
  is = NULL;
  Resetbits();
}

int ibstream::Open(const char name[])
// postcondition: input bit stream set to file specified by name
//                any open bit-stream is closed
{
  if (is && is->good())
  {
    is->close();
    delete is;
  }
  is = new ifstream(name);
  Resetbits();
  return is && is->good();
}

ibstream::ibstream(const char name[])
// postcondition: input bit-stream tied to file specified by name
{
  is = new ifstream(name);
  Resetbits();
}

ibstream::~ibstream()
// postcondition: close and free up memory
{
  if (is)
  {
    is->close();
    delete is;
  }
}

void ibstream::Close()
// postcondition: close the input bit stream
{
  if (is)
    is->close();
}

void ibstream::Resetbits()
// postcondition: no bits in input buffer, buffer cleared
{
  inbuff = inbbits = 0;
}

int ibstream::Readbits(int numbits)
// postcondition: numbits bits read (buffered)
//                and returned, EOF returned if read fails
{
  int retval = 0;

  if (is == NULL)
  {
    return EOF; // can't do anything with no stream
  }

  while (numbits > inbbits)
  {
    retval |= inbuff << (numbits - inbbits);
    numbits -= inbbits;
    if ((inbuff = is->get()) == EOF)
    {
      return (EOF);
    }
    inbbits = BITS_PER_WORD;
  }

  if (numbits > 0)
  {
    retval |= inbuff >> (inbbits - numbits);
    inbuff &= bmask[inbbits - numbits];
    inbbits -= numbits;
  }
  return retval;
}

void ibstream::Rewind()
{
  if (is)
  {
    is->seekg(0); // reset pointer to beginning of file
    is->clear();  // clear state (in particular if EOF encounted)
    Resetbits();
  }
}
