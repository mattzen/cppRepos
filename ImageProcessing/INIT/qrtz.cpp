
// ================================================================
// qrtz.c - quantization program.
// Written by: Mateusz Zmijewski
// =====================================================================

#include "IP.h"

using namespace std;

// function prototype
void quantz(imageP, int, imageP);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// main:
int
main(int argc, char** argv)
{
	int	levels;
	imageP	I1, I2;

	// error checking: proper usage
	if(argc != 4) {
		cerr << "Usage: qrtz infile number outfile\n";
		exit(1);
	}

	// read input image (I1) and reserve space for output (I2)
	I1 = IP_readImage(argv[1]);
	I2 = NEWIMAGE;

	// read lower and upper thresholds
	levels  = atoi(argv[2]);
	
	
	quantz(I1,levels,I2);
	
	IP_saveImage(I2,argv[3]);

	// threshold image and save result in file


	// free up image structures/memory
	IP_freeImage(I1);
	IP_freeImage(I2);

	return 1;
}



// qrtz:

void
quantz(imageP I1, int levels,imageP I2)
{
	int	 i, total;
	uchar	*in, *out, lut[256];
	int quant = (int)(256/levels);
	int val = quant/2;

	
	// total number of pixels in image
	total = I1->width * I1->height;

	// init I2 dimensions and buffer
	I2->width  = I1->width;
	I2->height = I1->height;
	I2->image  = (uchar *) malloc(total);
	
	if(I2->image == NULL) {
		cerr << "thr: Insufficient memory\n";
		exit(1);
	}
	



	// init lookup table
	for(i=0; i<256 ; i++) {
	
		
		lut[i] = val * (int) (i/val);
		
	}
	
	// visit all input pixels and apply lut to threshold
	in  = I1->image;	// input  image buffer
	out = I2->image;	// output image buffer
	for(i=0; i<total; i++) out[i] = lut[ in[i] ];
}
