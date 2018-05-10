// Example image reading and writing code for pnm file images.
// And dealing with multidimensional images.
// Written by David M. Chelberg
// last-modified: Mon Feb  6 21:15:24 2006

#ifndef PNM_H
#define PNM_H

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <cstdlib>

using std::string;
using std::ostream;
using std::istream;

// This is a VERY simple class
// A real image class should have more robust operators, and accessors
// instead of depending on using public everything.
// DMC last-modified: Mon Oct 18 16:35:07 2004
class Image {
public:
  Image();
  Image(size_t nrows, size_t ncols, size_t ndims=1);
  Image(const Image &in);

  ~Image();

  // does the actual constructing work.
  void construct(size_t nrows, size_t ncols, size_t ndims=1);
  // Clears an array
  void clear(unsigned char clear_val=0);
  // Copies one array into another
  void copy(const Image &in);

  unsigned char& operator()(const size_t row, const size_t col)
  {
    return (ar[row*cols+col]);
  }

  const unsigned char& operator()(const size_t row, const size_t col) const
  {
    return (ar[row*cols+col]);
  }

  unsigned char& operator()(const size_t row, const size_t col, const size_t index)
  {
    return (ar[row*cols*dims+col*dims+index]);
  }

  const unsigned char& operator()(const size_t row, const size_t col, const size_t index) const
  {
    return (ar[row*cols*dims+col*dims+index]);
  }
  unsigned char *ar;
  size_t rows;
  size_t cols;
  size_t dims;
  string comment;
};

// The following implement reading and writing PNM format files.
// The are rudimentary and do not check for many errors.
// Use the first one to read in an image, the second is mainly for internal purposes.
void OpenGraphicFile(istream& ins, Image &img);
void ReadGraphicFile(istream &ins, Image &img);
// You can use this one to write out an image.
void WritePNMFile(Image &img, const string &filename, const string &comment);
void WritePNM(Image &img, ostream &outs, const string &comment);
#endif
