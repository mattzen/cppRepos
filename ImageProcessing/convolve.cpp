
// ================================================================
// unordered_dither.c - Threshold program.
//
// Written by: Mateusz Zmijewski
// =====================================================================

#include "IP.h"
#include <stdio.h>
#include <stdlib.h>
using namespace std;

// function prototype
void convolve(imageP, const char*, imageP);

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
	if(argc != 4) {
		cerr << "Usage: qrtz infile number outfile\n";
		exit(1);
	}

	// read input image (I1) and reserve space for output (I2)
	I1 = IP_readImage(argv[1]);
	I2 = NEWIMAGE;

	// read lower and upper thresholds

	
	const char *f= argv[2];

	convolve(I1,f,I2);
	
	IP_saveImage(I2,argv[3]);

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
convolve(imageP I1,const char *name, imageP I2)
{
	int	 i=0;
	int total;
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
		cerr << "convolve: Insufficient memory\n";
		exit(1);
	}
	
	

	in  = I1->image;	// input  image buffer
	out2 = I2->image;	// output image buffer





	

	int *buffer;
	int ctr =0;

	FILE* fil = fopen (name, "r");

	fscanf (fil, "%d", &i); 

    int matx = i;
	
	fscanf (fil, "%d", &i);  

	int maty = i;
		  
	int *kernel = (int *) malloc((matx*maty)*sizeof(int));

	 while (!feof (fil))
		{  
	
		  fscanf (fil, "%d", &i); 
		  kernel[ctr++]=i;
		  

		}
	   
	fclose (fil);     


	int neighx = (matx-1)/2;
	int neighy = (maty-1)/2;


	int h = I1->height;
	int w = I1->width;

	I2->width = w;
	I2->height = h;


	for(int i=0; i<total; i++){

		out2[i] = in[i];

	}


	int sum=0;


	//buffer 3x3

	for(int i=1; i<h-1; i++){

		
		for(int j=1; j<w-1; j++){

			 sum=0;
			


			for(int k=-neighx;k<neighx+1; k++){

				for(int l=-neighy; l<neighy+1;l++){

					sum+=out2[(i+k)* w+(j+l)] *kernel[(k+neighx)*maty+(l+neighy)];

				}



			}


			if(sum<0) sum=0;
			else if(sum>255) sum=255;

			out[i*w+j] = sum;
			

		}




	}



	for(int i=0; i<total;i++){


		out2[i]=out[i];
	}

	
		

}

		
		

	

