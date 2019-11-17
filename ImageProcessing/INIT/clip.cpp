
// ================================================================
// clip.c - Clipping program.
// Written by: Mateusz Zmijewski
// =====================================================================

#include "IP.h"

using namespace std;

// function prototype
void clip(imageP, imageP,int,int);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// main:
//
// Main routine
//
int
main(int argc, char** argv)
{
	int	t1,t2;
	imageP	I1, I2;

	// error checking: proper usage
	if(argc != 5) {
		cerr << "Usage: clip infile t1 t2 outfile\n";
		exit(1);
	}

	// read input image (I1) and reserve space for output (I2)
	I1 = IP_readImage(argv[1]);
	I2 = NEWIMAGE;

	// read t1, t2
	t1  = atoi(argv[2]);
	t2  = atoi(argv[3]);
	
	
	clip(I1,I2,t1,t2);
	
	IP_saveImage(I2,argv[4]);


	// free up image structures/memory
	IP_freeImage(I1);
	IP_freeImage(I2);

	return 1;
}




// clip:

void
clip(imageP I1,imageP I2,int t1, int t2)
{
	int	 i, total;
	uchar	*in, *out, lut[256];

	// total number of pixels in image
	total = I1->width * I1->height;

	// init I2 dimensions and buffer
	I2->width  = I1->width;
	I2->height = I1->height;
	I2->image  = (uchar *) malloc(total);
	
	if(I2->image == NULL) {
		cerr << "clip: Insufficient memory\n";
		exit(1);
	}
	

	// init lookup table
	for(i=0; i<=t1 ; i++) lut[i] = t1;
	for(; i<=t2 ; i++) lut[i] =i;
	for(; i<256 ; i++) lut[i] = t2;		

	in  = I1->image;	// input  image buffer
	out = I2->image;	// output image buffer
	for(i=0; i<total; i++) out[i] = lut[ in[i] ];
}
