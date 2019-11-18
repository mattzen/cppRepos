#ifndef __SWORM__      // prevent infinite loops

#define __SWORM__

class Sworm{

public:

struct snakepart{
	int x,y;
	snakepart *nextpart;

};

	enum Direct{L_EFT,R_IGHT,U_P,D_OWN

};
	Sworm();
	void addPart(int a, int b);
	void printTest();
	void sMove(int a, int b);
	snakepart * ptr;
	Direct dir;
	int size;
	~Sworm();

};

#endif