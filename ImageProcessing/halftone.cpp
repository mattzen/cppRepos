
// ================================================================
// halftone.c - Threshold program.
//
// Written by: Mateusz Zmijewski
// =====================================================================

#include "IP.h"
#include <ctime>
using namespace std;

// function prototype
void halftone(imageP, int,double, imageP);
int getMatrix(int);
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
		cerr << "Usage: halftone infile number,gamma, outfile\n";
		exit(1);
	}

	// read input image (I1) and reserve space for output (I2)
	I1 = IP_readImage(argv[1]);
	I2 = NEWIMAGE;

	// read lower and upper thresholds
	levels  = atoi(argv[2]);
	
	gamma = atof(argv[3]);
	halftone(I1,levels,gamma,I2);
	
	IP_saveImage(I2,argv[4]);

	// threshold image and save result in file


	// free up image structures/memory
	IP_freeImage(I1);
	IP_freeImage(I2);

	return 1;
}



void
halftone(imageP I1, int m, double gamma, imageP I2)
{
	int	 i, total;
	double gam;
	uchar	*in, *out;
	int quant = (int)(256/(m*m));
	int lut[256];

	int val = quant/2;
	gam = gamma;
	int si = m;
	
	// total number of pixels in image
	total = I1->width * I1->height;

	// init I2 dimensions and buffer
	I2->width  = I1->width;
	I2->height = I1->height;
	I2->image  = (uchar *) malloc(total*m*m);
	
	if(I2->image == NULL) {
		cerr << "halftone: Insufficient memory\n";
		exit(1);
	}


	in  = I1->image;	// input  image buffer

	
	out = I2->image;	// output image buffer



	int spiral[] ={73,74,75, 76, 77, 78,79, 80, 81,82,
					72,43,44, 45, 46, 47, 48, 49,50,83,
					71, 42,21,	22,	23,	24,	25,26,51,84,
					70,41,20,	7,	8,	9,	10,27,52,85,
					69,40,19,	6,	1,	2,	11,28,53,86,
					68,39,18,	5,	4,	3,	12,29,54,87,
					67,38,17,	16,	15,	14,	13,30,55,88,
					66,37,36 ,35, 34, 33, 32,31, 56, 89,
					65,64,63, 62, 61, 60, 59,58, 57,90,
					100,99,98,97, 96, 95, 94, 93, 92 ,91};

	int h = I1->height;
	int w = I1->width;
	int j;


	int h2 = h*m;
	int w2 = w*m;

	int outi =0;
	int outj =0;

	I2->width =w2;
	I2->height = h2;


	for(int i=0; i<256; i++){

		lut[i] = val * (int) (i/val);
		lut[i] = 256*pow((double)i/256,1.0/gam);
	}


	for(int i=0; i<h; i++){
		outi=i*m;
		
		for(int j=0; j<w; j++){
		outj=j*m;

			for(int k=0; k<m; k++){


				for(int l=0; l<m; l++){


					out[((outi+k)*w*m+(outj+l))] = (lut[in[i*w+j]]/(m*m) * spiral[k*m+l]);


				}


			}

		}
			

	}
	
}
