
// ================================================================
// ordered_dither.c - Threshold program.
//
// Written by: Mateusz Zmijewski
// =====================================================================

#include "IP.h"
#include <ctime>
using namespace std;

// function prototype
void ordered_dither(imageP, int,double, imageP);
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
		cerr << "Usage: ordered_dither infile number outfile\n";
		exit(1);
	}

	// read input image (I1) and reserve space for output (I2)
	I1 = IP_readImage(argv[1]);
	I2 = NEWIMAGE;

	// read lower and upper thresholds
	levels  = atoi(argv[2]);
	
	gamma = atof(argv[3]);
	ordered_dither(I1,levels,gamma,I2);
	
	IP_saveImage(I2,argv[4]);

	// threshold image and save result in file


	// free up image structures/memory
	IP_freeImage(I1);
	IP_freeImage(I2);

	return 1;
}

int getMatrix(int size){







	return 1;

}



void
ordered_dither(imageP I1, int m, double gamma, imageP I2)
{
	int	 i, total;
	double gam;
	uchar	*in, *out;
	int quant = (int)(256/(m*m));
	int lut[256];

	int val = quant/2;
	gam = gamma;

	
	// total number of pixels in image
	total = I1->width * I1->height;

	// init I2 dimensions and buffer
	I2->width  = I1->width;
	I2->height = I1->height;
	I2->image  = (uchar *) malloc(total);
	
	if(I2->image == NULL) {
		cerr << "ordered_dithering: Insufficient memory\n";
		exit(1);
	}


	in  = I1->image;	// input  image buffer
	out = I2->image;	// output image buffer


	

	int h = I1->height;
	int w = I1->width;


	int h2 = h*m;
	int w2 = w*m;
	



	int dither2[] = {0,2,3,1};

	int dither3[] ={6,8,4,
					1,0,3,
					5,2,7};

	int dither4[] = { 0, 8, 2, 10,
					 12, 4, 14, 6,
					 3, 11, 1,  9,
					 15, 7, 13, 5};

	
	int dither8[] = {  0, 48, 12, 60, 3, 51, 15, 63, 
						32, 16, 44, 28, 35, 19, 47, 31, 
						8, 56, 4, 52, 11, 59, 7, 55, 
						40, 24, 36, 20, 43, 27, 39, 23, 
						2, 50, 14, 62, 1, 49, 13, 61, 
						34, 18, 46, 30, 33, 17, 45, 29, 
						10, 58, 6, 54, 9, 57, 5, 53, 
						42, 26, 38, 22, 41, 25, 37, 21 };


	int outi =0;
	int outj =0;

	I2->width = w;
	I2->height = h;


	for(int i=0; i<256; i++){

		lut[i] = val * (int) (i/val);
		lut[i] = 256*pow((double)lut[i]/256,1.0/gam);

	}
	int i2,j2;


	if(m==2){
			for(int i=0; i<h; i++){
		
		for(int j=0; j<w; j++){

				i2 = i % m; // dither matrix index
				j2 = j % m; // dither matrix index
				// threshold pixel using dither value Dij
				
				out[i*w+j] = (lut[in[i*w+j]]/(m*m) > dither2[i2*m+j2])? 255 : 0;
			}
		
		}
	}
	else if(m==3){
			for(int i=0; i<h; i++){
		
		for(int j=0; j<w; j++){

				i2 = i % m; // dither matrix index
				j2 = j % m; // dither matrix index
				// threshold pixel using dither value Dij
				
				out[i*w+j] = (lut[in[i*w+j]]/(m*m) > dither3[i2*m+j2])? 255 : 0;
			}
		
		}

	}
	else if(m==4){

			for(int i=0; i<h; i++){
		
		for(int j=0; j<w; j++){

				i2 = i % m; // dither matrix index
				j2 = j % m; // dither matrix index
				// threshold pixel using dither value Dij
				
				out[i*w+j] = (lut[in[i*w+j]]/(m*m) > dither4[i2*m+j2])? 255 : 0;
			}
		
		}


	}else if(m==8){

			for(int i=0; i<h; i++){
		
		for(int j=0; j<w; j++){

				i2 = i % m; // dither matrix index
				j2 = j % m; // dither matrix index
				// threshold pixel using dither value Dij
				
				out[i*w+j] = (lut[in[i*w+j]]/(m*m) > dither8[i2*m+j2])? 255 : 0;
			}
		
		}

	}
	

	}