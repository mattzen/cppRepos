
// ================================================================
// blur.c - Threshold program.
//
// Written by: Mateusz Zmijewski
// =====================================================================

#include "IP.h"
#include <ctime>
using namespace std;

// function prototype
void blur(imageP, int,int, imageP);
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
		cerr << "Usage: blur infile xsz ysz outfile\n";
		exit(1);
	}

	// read input image (I1) and reserve space for output (I2)
	I1 = IP_readImage(argv[1]);
	I2 = NEWIMAGE;

	// read lower and upper thresholds
	levels  = atoi(argv[2]);
	
	gamma = atof(argv[3]);
	blur(I1,levels,gamma,I2);
	
	IP_saveImage(I2,argv[4]);

	// threshold image and save result in file


	// free up image structures/memory
	IP_freeImage(I1);
	IP_freeImage(I2);

	return 1;
}

void copyrow(int row, uchar *buf, uchar *in,int width, int neigh){


	for(int i=0; i<neigh; i++){
		buf[i]=in[row*width+i];
		buf[width+neigh+i]=in[row*width+width-i];
	}


	for(int i=0; i<width; i++)
		buf[i+neigh]=in[row*width+i];


}
void copycol(int col, uchar *buf, uchar *in,int height, int neigh){


	for(int i=0; i<neigh; i++){

		buf[i]=in[i*height+col];
		buf[height+i+neigh]=in[col*height+height-i];
	}


	for(int i=0; i<height; i++)
		buf[i+neigh]=in[i*height+col];


}


void
blur(imageP I1, int xsz, int ysz, imageP I2)
{
	int	 i, total;
	double gam;
	uchar	*in,*in2, *out,*out2;

	int lut[256];



	
	// total number of pixels in image
	total = I1->width * I1->height;

	// init I2 dimensions and buffer
	I2->width  = I1->width;
	I2->height = I1->height;
	I2->image  = (uchar *) malloc(total);

	out = (uchar *) malloc(total);

	in2 = (uchar *) malloc(total);

	if(I2->image == NULL) {
		cerr << "thr: Insufficient memory\n";
		exit(1);
	}
	
	

	in  = I1->image;	// input  image buffer
	out2 = I2->image;	// output image buffer


	int h = I1->height;
	int w = I1->width;

	I2->width = w;
	I2->height = h;

	
	for(int i=0; i<total; i++)
		in2[i] = in[i];
	
	int coef1=xsz;
	int coef2=ysz;


	int neigh = (coef1-1)/2;

	uchar *temprow = (uchar*)malloc(w+(neigh*2));


	int sum=0;

	//for rows
	for(int i=0; i<h; i++)
	{
			
		copyrow(i,temprow, in, w,neigh);

		for(int j=0; j<w; j++){
			sum=0;
			for(int k=0; k<coef1; k++){
				sum += temprow[j+k];
			}

			out[i*w+j] = sum/coef1;
		

		}

	}
	
	neigh=(coef2-1)/2;
	temprow = (uchar*)malloc(h+(neigh*2));



	//for columns
		for(int i=0; i<w; i++)
		{
		
			copycol(i,temprow, out, h,neigh);

			for(int j=0; j<h; j++){
				sum=0;
				for(int k=0; k<coef2; k++)
					sum += temprow[j+k];

				out2[j*h+i]=sum/coef2;
			
				
			}

		}



	
	
		
	
		

}

		
		

	

