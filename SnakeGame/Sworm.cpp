#include <windows.h>
#include <string>


using std::string;

// Global variables
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

Sworm::Sworm()
{
	ptr = NULL;
	dir = R_IGHT;
	size = 0;
}


Sworm::~Sworm()
{

	delete ptr;//bad, needs revision

}


void Sworm::addPart(int x, int y)
{

	snakepart *temp1, *temp2;
	temp1 = new snakepart;
	temp1->x = x;
	temp1->y = y;
	temp1->nextpart = NULL;
	
	if(ptr==NULL)
		ptr= temp1;
	else
	{
		
		temp2=ptr;

		while(temp2->nextpart !=NULL)
		{
			temp2 = temp2->nextpart;
		}
		
		temp2->nextpart = temp1;

	}

		size++;

}

void Sworm::sMove(int x, int y)
{

	snakepart *temp12;
	int x1,y1;
	temp12 = ptr;
	temp12->x=x;
	temp12->y=y;

	while(temp12->nextpart != NULL)
	{

	
		x1 = temp12->nextpart->x;
		y1 = temp12->nextpart->y;

		temp12->nextpart->x = temp12->x;
		temp12->nextpart->y = temp12->y;
		temp12->x =x1;
		temp12->y =y1;


		temp12=temp12->nextpart; //move to the next part

	}

}

struct spawnPart{

	int x,y;

};
// The main window class name.j
static string szWindowClass = "win32app";


// The string that appears in the application's title bar.
static string szTitle = "Win32 Guided Tour Application";

Sworm Snake1;
int initx =70;
int inity =50;
int framectr =0;
HINSTANCE hInst;
bool totake = false;
bool run=true;
spawnPart p;


// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass.c_str();
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));


    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            "Call to RegisterClassEx failed!",
            "Win32 Guided Tour",
            NULL);

        return 1;
    }

    hInst = hInstance; // Store instance handle in our global variable

    // The parameters to CreateWindow explained:
    // szWindowClass: the name of the application
    // szTitle: the text that appears in the title bar
    // WS_OVERLAPPEDWINDOW: the type of window to create
    // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
    // 500, 100: initial size (width, length)
    // NULL: the parent of this window
    // NULL: this application does not have a menu bar
    // hInstance: the first parameter from WinMain
    // NULL: not used in this application
    HWND hWnd = CreateWindow(
        szWindowClass.c_str(),
		szTitle.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        400, 400,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        MessageBox(NULL,
            "Call to CreateWindow failed!",
            "Win32 Guided Tour",
            NULL);

        return 1;
    }

    // The parameters to ShowWindow explained:
    // hWnd: the value returned from CreateWindow
    // nCmdShow: the fourth parameter from WinMain
    ShowWindow(hWnd,
        nCmdShow);
    UpdateWindow(hWnd);

	//init snake

	Snake1.addPart(50,50);
	Snake1.addPart(60,50);
	Snake1.addPart(70,50);




    // Main message loop:
    MSG msg;

	GetMessage(&msg, NULL, 0, 0);

	while (msg.message != WM_QUIT)
	{
	
		if(PeekMessage(&msg, 0,0,0,PM_REMOVE))
	    {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
	    }
		else
		{
	
			if(run)
			{
			if(Snake1.dir == Sworm::Direct::R_IGHT)
			{
			initx=initx+10;
			Snake1.sMove(initx,inity);
			
			
			}
			else if(Snake1.dir == Sworm::Direct::L_EFT)
			{
			initx=initx-10;
			Snake1.sMove(initx,inity);
			}
			else if(Snake1.dir == Sworm::Direct::U_P)
			{
			inity = inity-10;
			Snake1.sMove(initx,inity);
			}
			else
			{
			inity =inity+10;
			Snake1.sMove(initx,inity);
			}
			
				if(initx == p.x && inity == p.y)
			{

				Snake1.addPart(p.x,p.y);
				totake=false;
			}
			//check if head touched special spawn
			}
				if(initx<20 || initx>320 || inity <20 || inity>320)
				{
					string lose= "You lose!";
					string cap = "Game Over!";
					initx = 70;
					inity = 50;
					run=false;
					MessageBox(NULL,lose.c_str(),cap.c_str(),NULL);
				}
		
					Sleep(200);
					InvalidateRect (hWnd, NULL, TRUE);
				

		}

	}



    return (int) msg.wParam;
	
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
	HBRUSH      NewBrush;
	
	//string message1 = wParam;
	
    switch (message)
	{
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        // Here your application is laid out.
        // For this introduction, we just print out "Hello, World!"
        // in the top left corner.
       /* TextOut(hdc,
            20, 20,
			greeting.c_str(), greeting.length());
*/
		for(int i=20; i<340; i=i+10)
		{
		MoveToEx(hdc, i, 20, NULL);
		LineTo(hdc, i, 330);
		MoveToEx(hdc, 330, i, NULL);
		LineTo(hdc, 20, i);
		}
		

		if(run)
		{

			Sworm::snakepart *temp;
			temp = Snake1.ptr;
			NewBrush = CreateSolidBrush(RGB(250, 25, 5));

			while(temp->nextpart !=NULL) //draw snake
			{

        		SelectObject(hdc, NewBrush);
			Rectangle(hdc,temp->x,temp->y,(temp->x)+10,(temp->y)+10);
			temp = temp->nextpart;
			}

		SelectObject(hdc, NewBrush);
		Rectangle(hdc,temp->x,temp->y,(temp->x)+10,(temp->y)+10);
		DeleteObject(NewBrush);

		
		if(totake)
		{
		

		SelectObject(hdc, NewBrush);
		Rectangle(hdc,p.x,p.y,(p.x)+10,(p.y)+10);
		DeleteObject(NewBrush);

		}
		else
		{
			p.x = initx+20;
			p.y = inity+20;

			totake=true;


		}
		}

    // End application-specific layout section.
        EndPaint(hWnd, &ps);

        break;

	case WM_KEYDOWN:

		switch (wParam) 
            { 
                case VK_LEFT: 
                    
              
					Snake1.dir = Sworm::Direct::L_EFT;
                     
                    break; 
 
                case VK_RIGHT: 
                    
					Snake1.dir = Sworm::Direct::R_IGHT;
                     
                    break; 
 
                case VK_UP: 
                    
					Snake1.dir = Sworm::Direct::U_P;
                     
                    break; 
 
                case VK_DOWN: 
                    
					Snake1.dir = Sworm::Direct::D_OWN;
                     
                    break; 
		}
		break;
		
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}
