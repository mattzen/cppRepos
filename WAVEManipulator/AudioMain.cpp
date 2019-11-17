#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <math.h>

void reverseAudio(char* source, char* dest, long fsize){

		for(int i=0; i<46; i++)
			dest[i]=source[i];

		int maincount = 46;

		for(int i=fsize; i>46; i = i--){

			if(i>46){

				dest[maincount++] = source[i];

			}

		}
}

bool isFormatCorrect(char* buffer){

	if(buffer[0] == 'R' && buffer[8] == 'W' && buffer[36] == 'd')
		return true;
	else
		return false;

}

int getIntfromBuffer(char* buffer, int offset){

		int *test = (int*)(buffer+offset); //convert chunk of bytes oif character from a wav file to an int for later manipulation
		//char size[10];
		//for(int i=0; i<10; i++)
			//size[i] = '\0';
		int chunkSize = *test;
//		sprintf(size, "%d", chunkSize);
		//int b;
		//b = atoi(size);

		return chunkSize;

}

int getIntBIG(char* buffer, int offset){

		//int *test = (int*)(buffer+offset); //alternative to the below function buff2,a

		int a;
		char buff2[4];
		buff2[0] = buffer[4];
		buff2[1] = buffer[5];
		buff2[2] = buffer[6];
		buff2[3] = buffer[7];
		memcpy(&a, buff2, sizeof(buff2));
		/////////////////////////////////////////this or above

		char _hex[2];

		sprintf(_hex,"%x", *(buff2+1)); //access individual characters withing buffer and treanslate to hex buffer

		char buff[4]; //if want BIG-endian just reverse the order manually of bytes and then cast either as int *test2 = (int*)(buff);
					 // or memcpy(&a, buff2, sizeof(buff2));

		buff[3] = buffer[offset];
		buff[2] = buffer[offset+1];
		buff[1] = buffer[offset+2];
		buff[0] = buffer[offset+3];

		int *test2 = (int*)(buff);




		return *test2;

}

int getShortfromBuffer(char* buffer, int offset){



		short *test = (short*)(buffer+offset); //convert chunk of bytes oif character from a wav file to an int for later manipulation
		char size[5];
		for(int i=0; i<5; i++)
			size[i] = '\0';
		short chunkSize = *test;
		sprintf(size, "%d", chunkSize);
		short b;
		b = atoi(size);

		return b;


}

struct waveheader{ //40 bytes wav structure riff+rmf chunks and id of data chunk("data" keyword) for experimentation

	char	chunkID[4];
	int		chunkSize;
	char	format[4];
	char	subchunk1ID[4];
	int		subchunk1Size;
	short	audioFormat;
	short	numberChannels;
	int		sampleRate;
	int		byteRate;
	short	blockAlign;
	short	bitsperSample;
	char	subchunk2ID[4];

};

int temper(char* source, char* dest, long fsize){

    int i;
    int j = 0;
	
	double pi = 3.141592;

	printf("\n");
    printf("%lf",sin(1.25));


    float a = sin(1.25);


    printf("\n");
    printf("%d",sin(2*pi*285));
    printf("\n");
    printf("%d",sin(2*pi*0.25));
    printf("\n");
    printf("%d",sin(2*pi*0.30));
    printf("\n");
    printf("%d",sin(2*pi*0.50));
    printf("\n");
    printf("%d",sin(2*pi*0.70));
    printf("\n");
    printf("%d",sin(2*pi*0.75));
    printf("\n");
    printf("%d",sin(2*pi*0.80));
    printf("\n");







    for(i=0; i<46; i++){

        dest[i]=source[i];

    }

    for(i=46; i<80; i++){


    dest[i] = source[i];


    }



    int ctr=0;
    int crr2=0;

    for(i=80; i<fsize-1; i++){

    //increase multitude(sound) by varying temp
    int temp = (int)source[i];
    //printf("%d",sin( (2.0 * pi * 5) / 44100 * i ));
   // dest[i] = (short)sin( 2.0 * pi * i );


	 
	 //dest[i] = sin((pi*ctr)/(177152))*1000;
	 
	 dest[i] =sin( (2.0 * pi * 0.25) / 177152 * ctr )*10000;
	  ctr++;
	 


}


    

    return 0;


}

int cut(char* source, char* dest, short from, short to){

	int totalseconds = ((getIntfromBuffer(source,4))-36)/getIntfromBuffer(source,28); //total seconds calculated by dividing size data by byte rate


	if(to>from && from>0 && to < totalseconds){


	struct waveheader waveformat; //entire  wav header except for subchunk2Size
	int subchunk2Size=0;



	waveformat.chunkID[0] = 'R';						//wave file creation character by character, bytes by bytes
	waveformat.chunkID[1] = 'I';
	waveformat.chunkID[2] = 'F';
	waveformat.chunkID[3] = 'F';
	//strcpy(waveformat.chunkID,"RIFF"); alternative

	//waveformat.chunkSize  = (getIntfromBuffer(source,4));

	//waveformat.chunkSize = *((int*)(source+4)); //extracts little indian

	waveformat.chunkSize = (getIntBIG(source,4));

	waveformat.format[0]  = 'W';
	waveformat.format[1]  = 'A';
	waveformat.format[2]  = 'V';
	waveformat.format[3]  = 'E';
	waveformat.subchunk1ID[0] = 'f';
	waveformat.subchunk1ID[1] = 'm';
	waveformat.subchunk1ID[2] = 't';
	waveformat.subchunk1ID[3] = ' ';
	waveformat.subchunk1Size  =  getIntfromBuffer(source,16);
	waveformat.audioFormat    =  getShortfromBuffer(source,20);
	//waveformat.numberChannels =  getShortfromBuffer(source,22);
	waveformat.numberChannels = *((short*)(source+22));
	waveformat.sampleRate     =  getIntfromBuffer(source,24);
	waveformat.byteRate       =  getIntfromBuffer(source,28);
	waveformat.blockAlign     =  getShortfromBuffer(source,32);
	waveformat.bitsperSample  =  getShortfromBuffer(source,34);
	waveformat.subchunk2ID[0] = 'd';
	waveformat.subchunk2ID[1] = 'a';
	waveformat.subchunk2ID[2] = 't';
	waveformat.subchunk2ID[3] = 'a';


	int totalseconds = (waveformat.chunkSize-36)/waveformat.byteRate;
	waveformat.chunkSize = ((waveformat.chunkSize-36)/totalseconds)*(to-from);


	memcpy(dest, &waveformat, sizeof(waveformat));


	dest[40] = '\0';								//extract subchunk2size and convert to an int
	subchunk2Size = (getIntfromBuffer(source,41));
	int sizenew2 = subchunk2Size/totalseconds;
	subchunk2Size = sizenew2*(to-from);
	char temp[10];
	memcpy(temp, &subchunk2Size, sizeof(subchunk2Size));
	dest[41] = temp[0];
	dest[42] = temp[1];
	dest[43] = temp[2];
	dest[44] = temp[3];


	for(int i=waveformat.byteRate*from; i<(waveformat.byteRate*to)-45; i++) //cut correct chunk based on seconds entered into the program
		dest[i-(waveformat.byteRate*from)+45] = source[i+45];


	return waveformat.chunkSize+8; //return size of dest buffer size together with header
	}
	else
	{
		printf("%s", "wrong time intervals");
		return 0;
	}

}

int main(int argv, char** argvc)
{


	if(argv>2){

	FILE * pFile;
	FILE * pFile2;
    long lSize;
	char * buffer;
	char * buffer2;
    size_t result;


	struct waveheader waveformat; //entire  wav header except for subchunk2Size
	int subchunk2Size = 0; //remaining wavfile subchunk2Size



	 pFile =  fopen (argvc[1],"rb");
	 pFile2 = fopen (argvc[2] , "wb");


	  if (pFile!=NULL)
	  {

		  fseek (pFile , 0 , SEEK_END);
		  lSize = ftell (pFile);
		  rewind (pFile);
		  buffer  = (char*) malloc (sizeof(char)*lSize);
		  memset (buffer,'0',lSize);
		  result = fread (buffer,1,lSize,pFile);
		  if (result != lSize) {fputs ("Reading error",stderr); exit (3);}
		  if (!isFormatCorrect(buffer)) {
			  fputs ("File Format Error",stderr);
			  fclose (pFile);
			  fclose (pFile2);
			  free (buffer);
			  exit (3);
		  }


			 buffer2 = (char*) malloc (sizeof(char)*(lSize));
			 memset (buffer2,'0',(lSize));


			// if(argv==3){

			 // reverseAudio(buffer,buffer2,lSize);

			  //fwrite (buffer2 , 1 , lSize, pFile2 );


			// }
			if(argv==4){





                printf("right here");

               // buffer2 = "hello world";

             //   int size = 0;

               temper(buffer,buffer2,lSize);

               fwrite (buffer2 , 1 , lSize, pFile2 );




			}

			 else if(argv == 5)
			 {


				int size = 0;
			    size = cut(buffer,buffer2,atoi(argvc[3]),atoi(argvc[4]));
			    fwrite (buffer2 , 1 , size, pFile2 );
			 }
			 else{

			 printf("%s", "wrong arguments");
	


			 }

			 fclose (pFile);
			 fclose (pFile2);
			 free (buffer);
			 free (buffer2);

	  }
	  else
		  printf("%s", "File not found");
	  }
	  else
	  {
		  printf("%s", "wrong arguments");
	  }

	return 0;
}
