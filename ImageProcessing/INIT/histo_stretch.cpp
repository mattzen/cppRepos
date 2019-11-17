
// ================================================================
// histo_stretch.c - Histogram stretching program.
// Written by Mateusz Zmijewski
// =====================================================================

#include "IP.h"

using namespace std;

// function prototype
void histo_stretch(imageP, imageP,int,int);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// main:
//

int
main(int argc, char** argv)
{
	int	t1,t2;
	imageP	I1, I2;

	// error checking: proper usage
	if(argc != 5) {
		cerr << "Usage: histo_stretch infile t1 t2 outfile\n";
		exit(1);
	}

	// read input image (I1) and reserve space for output (I2)
	I1 = IP_readImage(argv[1]);
	I2 = NEWIMAGE;

	// read t1,t2
	t1  = atoi(argv[2]);
	t2  = atoi(argv[3]);
	
	histo_stretch(I1,I2,t1,t2);
	
	IP_saveImage(I2,argv[4]);


	// free up image structures/memory
	IP_freeImage(I1);
	IP_freeImage(I2);

	return 1;
}




// histo_stretch:

void
histo_stretch(imageP I1,imageP I2,int t1, int t2)
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
		cerr << "histo_stretch: Insufficient memory\n";
		exit(1);
	}
	
	//for negative t1,t2
	if(t1<0){
	
		for(i =0;i<256;i++)
		{	//assign first non zero frequency to t1
			if(lut[i]>0)
				t1=i;
		}
	
	}
	if(t2<0){
	
		for(i =255;i>0;i--)
		{	//assign last non zero frequency to t2
			if(lut[i]>0)
				t2=i;
		}
	
	}


	// init lookup table
	for(i=0; i<=t1 ; i++) lut[i] = (255*(0-t1))/(t2-t1);
	for(; i<=t2 ; i++) lut[i] =(255*(i-t1))/(t2-t1);
	for(; i<256 ; i++) lut[i] = (255*(255-t1))/(t2-t1);
		


	in  = I1->image;	// input  image buffer
	out = I2->image;	// output image buffer
	for(i=0; i<total; i++) out[i] = lut[ in[i] ];
}
