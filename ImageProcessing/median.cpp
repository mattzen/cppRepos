
// ================================================================
// unordered_dither.c - Threshold program.
//
// Written by: Mateusz Zmijewski
// =====================================================================

#include "IP.h"
#include <ctime>
using namespace std;

// function prototype
void median(imageP, int,int, imageP);
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
		cerr << "Usage: qrtz infile number outfile\n";
		exit(1);
	}

	// read input image (I1) and reserve space for output (I2)
	I1 = IP_readImage(argv[1]);
	I2 = NEWIMAGE;

	// read lower and upper thresholds
	levels  = atoi(argv[2]);
	
	gamma = atof(argv[3]);
	median(I1,levels,gamma,I2);
	
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

int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

void
median(imageP I1, int sz, int avg, imageP I2)
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


	for(int i=0; i<total; i++){

		out2[i] = in[i];

	}

	

	int s = sz;

	int *temps = (int*)malloc((sz*sz)*sizeof(int));

	for(int i=0;i<sz*sz; i++)
		temps[i]=0;

	int neigh=(sz-1)/2;
	int sum=0;
	int ctr=0;
	int savg = 9+0/2
		;


	for(int i=1; i<h-1; i++){

		
		for(int j=1; j<w-1; j++){

			ctr=0;

				for(int k=-neigh;k<neigh+1; k++){

				for(int l=-neigh; l<neigh+1;l++){

					temps[ctr++] = out2[(i+k)* w+(j+l)];


				}

		}
				


			qsort(temps,sz*sz,sizeof(int),compare);
			
			savg = (sz*sz+avg)/2;
			out[i*w+j] = temps[savg];
			

		}




	}

	

			for(int i=0; i<total; i++){

			out2[i]=out[i];		

			}
			

		
	
		

}

		
		

	

