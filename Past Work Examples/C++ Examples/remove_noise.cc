// Very simple program showing how to use image code.
// And command line arguments.
// Written by Prof. David Chelberg
// last-modified: Tue Nov 28 14:15:51 2017

/*
	Modified by: Mark Brown
	Date: 12/8/2017
	Description: Takes in arguments for different sized images and finds the median (n value)
		of the surrounding pixels to set as the centre pixel.
*/

#include "pnm.h"
#include <iostream>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

// Parse the input arguments to the program.
// Check many error conditions
// return the values for rank and neighborhood_size
void parseargs(int argc, char **argv,
	       double &rank, int &neighborhood_size)
{
  // Defaults
  rank = 0.5;
  neighborhood_size = 5;
  // I.e. if no extra arguments it will go with the defaults.

  for (size_t i=0; i<argc; ++i) {
    // Parse rank argument
    if (string(argv[i]) == "-r") {
      if (i+1 < argc) {
	++i;
	char *end=argv[i];
	rank=strtod(argv[i], &end);
	if (*end != '\0') {
	  cerr << "Error in threshhold argument '" << argv[i] << "'" << endl;
	  exit(EXIT_FAILURE);
	}
      } else {
	cerr << "No threshhold argument given." << endl;
	exit(EXIT_FAILURE);
      }
    } else if (string(argv[i]) == "-n") {
      // Parse neighborhood_size argument
      if (i+1 < argc) {
	++i;
	char *end=argv[i];
	neighborhood_size=strtod(argv[i], &end);
	if (*end != '\0') {
	  cerr << "Error in neighborhood_size argument '" << argv[i] << "'" << endl;
	  exit(EXIT_FAILURE);
	}
      } else {
	cerr << "No neighborhood_size argument given." << endl;
	exit(EXIT_FAILURE);
      }
    } 
  }
}

// This function actually processes an input image to produce an
// output image that has more noise.
Image process_image(Image test, double rank, int neighborhood_size)
{
	/* All changes are done here. Below I take in the neighborhood_size provided by the user. Then
		divide it (integer division) as to provide a floor item for the surrounding pixels. After this
		I use the variable 'n' to find the median (or what ever the variable is provided by the user) 
		and returns the median pixel for that particular pixel. */
		
		
	int variable_floor = neighborhood_size / 2;
	double median_pixel;
  // Create an output image equal in size to the input image.
  Image test1(test.rows, test.cols, test.dims);
  // Proceesing the input image
  for(size_t row = variable_floor; row < test.rows - variable_floor; ++row) {
    for (size_t col = variable_floor; col< test.cols - variable_floor; ++col) {
		//insert here the average of them all
		for(int vari = 0-variable_floor; vari = variable_floor; vari++){
			for(int varj = 0-variable_floor; varj = variable_floor; varj++){
				 median_pixel += test(vari, varj);
			}
		}	
	test1(row, col) = median_pixel /(neighborhood_size * neighborhood_size);
    }
  }
  return(test1);
}

// Reads in an image from standard input, writes a noise added image
// to standard output
// Example call: addnoise < foo.pgm > out.pgm
// Example call with args: addnoise -t 0.95 -a 0.2 < foo.pgm > out.pgm
//
int main (int argc, char **argv)
{
  double rank;  // median rank between all the surrounding pixels
  int neighborhood_size;  // number of the nXn size neighbouring the primary pixel
  parseargs(argc, argv, rank, neighborhood_size);
  Image test;
  OpenGraphicFile(cin, test);

  Image test1 = process_image(test, rank, neighborhood_size);

  // If you want a comment in the output file:
  WritePNM(test1, cout, "Noise reduced image");

  // If you don't want any comments in the output file:
  //WritePNM(test1, cout, "");
  return(EXIT_SUCCESS);
}
