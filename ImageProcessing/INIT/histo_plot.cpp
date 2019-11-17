
// ================================================================
// histo_plot.c - Histogram plotting program.
// Written by: Mateusz Zmijewski
// =====================================================================

#include "IP.h"

using namespace std;

// function prototype
void histoplot(imageP, imageP, int);


// main:

int
main(int argc, char** argv)
{
	int	scale;
	imageP	I1, I2;

	// error checking: proper usage
	if(argc != 4) {
		cerr << "Usage: histoplot infile outfile scale\n";
		exit(1);
	}

	// read input image (I1) and reserve space for output (I2)
	I1 = IP_readImage(argv[1]);
	I2 = NEWIMAGE;

	// read scale value
	scale  = atoi(argv[3]);
	
	
	histoplot(I1,I2,scale);
	
	IP_saveImage(I2,argv[2]);


	// free up image structures/memory
	IP_freeImage(I1);
	IP_freeImage(I2);

	return 1;
}




// histo_plot:

void
histoplot(imageP I1,imageP I2, int s)
{
	int	 i, total,temp;
	uchar	*in, *out;
	int lut[256];

	// total number of pixels in image
	

	// init I2 dimensions and buffer
	I2->width  = 256;
	I2->height = 256;
	I2->image  = (uchar *) malloc(256*256);
	
	total = 256*256;

	if(I2->image == NULL) {
		cerr << "histoplot: Insufficient memory\n";
		exit(1);
	}
	
	in  = I1->image;	// input  image buffer
	out = I2->image;	// output image buffer

	for(i=0;i<256;i++) lut[i] = 0;
	
	// init lookup table
	for(i=0; i<total; i++) lut[(int)in[i]]++;
		
	for(i=0;i<30;i++) cout<<(int)lut[i]<<endl;

	int scale=1;
	
	if(s==0){
	scale = 2;
	}
	if(s==1){
	scale = 1;
	
	}
	
	for(int i=0;i<256;i++){
	
	lut[i] = (int)(lut[i])/scale;
	
	}
	
	for(int i=0; i<256*256;i++)
		out[i]=0;
	
	
	for(i=0;i<256;i++){ //for rows

	temp = (int)lut[i];

		if(temp>0){
		
			for(int j=255; j>255-temp && j>0 ;j--){ //for columns
			
				out[j*256+i] = 255;
			
			
			}
			
	
		}
	
	}
	
	
	
	

}
