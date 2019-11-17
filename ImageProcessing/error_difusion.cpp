
// ================================================================
// error_diffusion.c - Threshold program.
//
// Written by: Mateusz Zmijewski
// =====================================================================

#include "IP.h"
#include <ctime>
using namespace std;

// function prototype
void error_diffusion(imageP, int,int, imageP);
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
		cerr << "Usage: error_diffusion infile mtd serpend outfile\n";
		exit(1);
	}

	// read input image (I1) and reserve space for output (I2)
	I1 = IP_readImage(argv[1]);
	I2 = NEWIMAGE;

	// read lower and upper thresholds
	levels  = atoi(argv[2]);
	
	gamma = atof(argv[3]);
	error_diffusion(I1,levels,gamma,I2);
	
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
error_diffusion(imageP I1, int mtd, int serpend, imageP I2)
{
	int	 i, total;
	double gam;
	uchar	*in, *out;

	int lut[256];


	
	// total number of pixels in image
	total = I1->width * I1->height;

	// init I2 dimensions and buffer
	I2->width  = I1->width;
	I2->height = I1->height;
	I2->image  = (uchar *) malloc(total);
	
	if(I2->image == NULL) {
		cerr << "error_diffusion: Insufficient memory\n";
		exit(1);
	}
	



	in  = I1->image;	// input  image buffer

	
	out = I2->image;	// output image buffer


	int h = I1->height;
	int w = I1->width;

	I2->width = w;
	I2->height = h;


	int buf[256*2+4];

	int i2,j2;
	int error;
	int vall;


	for(int i=0; i<total; i++)
		out[i] = in[i];


	for(int i=0; i<h-1; i++){
		
		for(int j=1; j<w-1; j++){
				


				vall = lut[out[i*w+j]];

		
				error = out[i*w+j]-vall*2;
			

				out[i*w+(j+1)] = out[ i*w+(j+1)] + (error*7/16.); 
				out[(i+1)*w+(j-1)] = out[(i+1)*w+(j-1)] + (error*3/16.); 
				out[(i+1)*w+j] = out[(i+1)*w+j] + (error*5/16.);  
				out[(i+1)*w+(j+1)] =out[(i+1)*w+(j+1)] + (error*1/16.);



			}


	}
		
		


	for(int i=0; i<total; i++)
	{
		if(lut[out[i]]==128)
			out[i] = 255;
		else
			out[i]=0;
	}

}




	

