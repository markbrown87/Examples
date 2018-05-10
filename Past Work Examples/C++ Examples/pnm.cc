// Example image reading and writing code for pnm file images.
// Written by David M. Chelberg

// Some code originally written by Tom Ruch, substantially modified by
// Dr. Chelberg.

// last-modified: Mon Feb  6 21:14:40 2006
// dmc -- Added P6 image type.

#include "pnm.h"
#include <vector>

using namespace std;

// Simple image class

// Default constructor
Image::Image()
{
  rows=0;
  cols=0;
  dims=0;
  ar=NULL;
}

// Constructor
Image::Image(size_t nrows, size_t ncols, size_t ndims)
{
  construct(nrows, ncols, ndims);
}

// Copy constructor
Image::Image(const Image &in)
{
  // first allocate storage
  construct(in.rows, in.cols, in.dims);
  copy(in);
}

void Image::copy(const Image &in)
{
  // Check to be sure these are compatible arrays.
  assert(rows == in.rows);
  assert(cols == in.cols);
  assert(dims == in.dims);

  // Then copy data.
  for(size_t row=0; row < in.rows; ++row) {
    for (size_t col=0; col< in.cols; ++col) {
      for (size_t dim=0; dim< in.dims; ++dim) {
	(*this)(row,col,dim) = in(row,col,dim);
      }
    }
  }
}  

void Image::clear(unsigned char clear_val)
{
  // Initialize to zero.
  for (size_t row=0; row < rows; ++row) {
    for (size_t col=0; col < cols; ++col) {
      for (size_t dim=0; dim < dims;++dim){
	(*this)(row,col,dim)=clear_val;
      }
    }
  }    
}  

// Auxilliary helper function.
void Image::construct(size_t nrows, size_t ncols, size_t ndims)
{
  rows=nrows;
  cols=ncols;
  dims=ndims;
  // create array for image
  ar = (unsigned char *) new unsigned char*[rows*cols*dims];
  clear(0);
}

// Destructor clean up our mess :).
Image::~Image()
{
  if (!(ar==NULL)) {
    delete ar;
  }
}

//******************************************************************
//
//  Function: OpenGraphicFile
//
//  Purpose: to read the image size and all header info
//           Can read PNM format files, and also PPM format color
//           files.  
//
//  Parameters: ins      - the file stream to work with
//
//  Calls: getline, c_str, peek, ReadGraphicFile
//      
//  Date: 2/20/04
//  Modified: 2/6/06 to read PPM files.
//  
//  Comment: Should check for more error conditions to be more robust.
//
//******************************************************************
void OpenGraphicFile(istream& ins, Image &img)
{
  string line;

  // process the first line of the file
  getline(ins, line);
  bool color=false;
  if (line != "P5") {
    if (line != "P6") {
      cerr << "Error: Invalid file type.  (Expected pgm/p5, or ppm/p6)" << endl;
      exit(EXIT_FAILURE);
    } else {
      color = true;
    }
  }

  // Deal with comments
  while(ins.peek() == '#') { getline(ins, line); }

  ins >> img.cols >> img.rows;

  /*
  cout << "Image Size: " << img.rows << "x" << img.cols << endl;
  if (color) {
    cout << "Color Image" << endl;
  } else {
    cout << "Greyscale Image" << endl;
  }
  */
  getline(ins, line); // read extra whitespace that >> left behind
  getline(ins, line);

  if (line != "255") {
    cerr << "Error: Invalid color depth.  (Expected 255)" << endl;
    exit(EXIT_FAILURE);
  }

  //  cout << "Color Depth: 255" << endl;
  if (color) {
    img.construct(img.rows, img.cols, 3);
  } else {
    img.construct(img.rows, img.cols);
  }

  ReadGraphicFile(ins, img);
}

//******************************************************************
//
//  Function: ReadGraphicFile
//
//  Purpose: to read in the graphic file
//
//  Parameters: ins   - the file stream to read from
//              array - pointer to the array we're going to store it in
//
//  Calls: 
//      
//  Date: 2/20/04
//
//******************************************************************
void ReadGraphicFile(istream &ins, Image &img) 
{
  // get data into main array
  for(size_t i=0; i<img.rows; ++i) {
    for(size_t j=0; j<img.cols; ++j) {
      for (size_t k=0; k<img.dims; ++k) {
	img(i,j,k)= ins.get();
      }
    }
  }
}

//******************************************************************
//
//  Function: WritePNMFile
//
//  Purpose: writes a PNM image file from the array to the filename,
//           with a comment (if provided)
//  
//  Parameters: array - pointer to the image to write
//              filename - the filename to create
//              comment - the comment to write in the file                
//  
//  Calls: none
//  
//  Date: 1/30/03
//  Modified: Tue Feb  7 13:01:37 2006 to add P6 image type.
//
//  Comments: Should check for more error conditions to be robust.
//  
//******************************************************************
void WritePNMFile(Image &img, const string &filename, const string &comment) {
  ofstream outs;
  outs.open(filename.c_str());

  if (outs.fail()) {
    cerr << "Error: Can't open file for write: " << filename << endl;
    exit(EXIT_FAILURE);
  }

  WritePNM(img, outs, comment);
}

//******************************************************************
//
//  Function: WritePNMFile
//
//  Purpose: writes a PNM image file from the array to the filename,
//           with a comment (if provided)
//  
//  Parameters: array - pointer to the image to write
//              filename - the filename to create
//              comment - the comment to write in the file                
//  
//  Calls: none
//  
//  Date: 1/30/03
//  Modified: Tue Feb  7 13:01:37 2006 to add P6 image type.
//
//  Comments: Should check for more error conditions to be robust.
//  
//******************************************************************
void WritePNM(Image &img, ostream &outs, const string &comment) 
{
  unsigned char temp;

  // header
  if (img.dims == 3) {
    outs << "P6" << endl;
  } else if (img.dims == 1) {
    outs << "P5" << endl;
  } else {
    cerr << "Unknown image type passed to WritePNM" << endl;
    cerr << "Unknown image has " << img.dims << " dimensions!" << endl;
    exit(EXIT_FAILURE);
  }
  if (comment!="") {
    outs << "# This image was written by dmc's pnm writer based on Tom Ruch's code." << endl
	 << "# " << endl
	 << "# " << comment << endl;
  }
  outs << img.cols << " " << img.rows << endl << 255 << endl;

  // data
  for(size_t row=0; row < img.rows; ++row) {
    for(size_t col=0; col < img.cols; ++col) {
      for (size_t color=0; color<img.dims; ++color) {
	outs << img(row, col, color);
      }
    }
  }
  //  cout << "Successfully wrote file: " << filename << endl;
}
