
// ================================================================
// unordered_dither.c - Threshold program.
//
// Written by: Mateusz Zmijewski
// =====================================================================

#include "IP.h"
#include <ctime>
using namespace std;

// function prototype
void unordered_dither(imageP, int,double, imageP);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// main:
//
// Main routine to threshold image.
//
int
main(int argc, char** argv)
{
	int	levels;
	double gamma;
	imageP	I1, I2;

	// error checking: proper usage
	if(argc != 5) {
		cerr << "Usage: qrtz infile number outfile\n";
		exit(1);
	}

	// read input image (I1) and reserve space for output (I2)
	I1 = IP_readImage(argv[1]);
	I2 = NEWIMAGE;

	// read lower and upper thresholds
	levels  = atoi(argv[2]);
	
	gamma = atof(argv[3]);
	unordered_dither(I1,levels,gamma,I2);
	
	IP_saveImage(I2,argv[4]);

	// threshold image and save result in file


	// free up image structures/memory
	IP_freeImage(I1);
	IP_freeImage(I2);

	return 1;
}


void
unordered_dither(imageP I1, int levels, double gamma, imageP I2)
{
	int	 i, total;
	double gam;
	uchar	*in, *out, lut[256];
	int quant = (int)(256/levels);

	int val = quant/2;
	gam = gamma;

	
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
	



	int rando;

	for(i=0; i<256; i++)
	{
		//srand(time(NULL));
		rando = rand() % val;

		if(i%2 ==0){
			lut[i] = i+rando;
			if(lut[i] > 255)
				lut[i]=255;

		}else{
			
			lut[i] = i-rando;
			if(lut[i]<0)
				lut[i]=0;
		}

	}
	

	for(i=0; i<256 ; i++) {
	
		
		lut[i] = val * (int) (lut[i]/val);
		
	}


	// init lookup table

	
	// visit all input pixels and apply lut to threshold
	in  = I1->image;	// input  image buffer
	out = I2->image;	// output image buffer
	for(i=0; i<total; i++) out[i] = lut[ in[i] ];
}
