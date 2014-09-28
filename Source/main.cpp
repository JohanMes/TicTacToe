#include "JohanEngine\Renderer.h"
#include "JohanEngine\Dialogs.h"
#include "Movement.h"
#include "Listeners.h"
#include "TicTacToe.h"
#include "resource.h"

void CreateKeys() {
	ui->AddKey(new Key(VK_F1,Help));
	ui->AddKey(new Key(VK_F2,ToggleFullscreen));
	ui->AddKey(new Key(VK_F11,ToggleOptions));	
	ui->AddKey(new Key(VK_F12,ToggleConsole));
	
	ui->OnMouseDown = OnMouseDown;
}

void InitGame() {
	CreateKeys();
		
	// Geen tooltip aub
	renderer->ShowTooltip(0);
	
	// Maak spellogica
	game = new TicTacToe();
	
	// Create centered main menu
	mainmenu = new Window(10,10,100,100,"");
	
	// Create score labels
	crossscore = new Label(10,10,80,20,"Cross score: 0",true);
	mainmenu->AddChild(crossscore);
	
	circlescore = new Label(10,35,80,20,"Circle score: 0",true);
	mainmenu->AddChild(circlescore);
	
	// Create start button
	Button* startbutton = new Button(10,60,80,30,"Start game");
	startbutton->OnClick = LoadScene;
	mainmenu->AddChild(startbutton);
	
	// Show to the player
	ui->AddComponent(mainmenu);
	mainmenu->Show(1);
	
	// Simulate first run
	LoadScene(startbutton);
}

void DeleteGame() {
	delete game;
}

// This is where Windows sends user input messages
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	
	// send message to 3D interface
	ui->OnMessage(hwnd,Message,wParam,lParam);
	
	// Perform more handling
	switch(Message) {
		case WM_DESTROY: {
			PostQuitMessage(0); // we are asked to close: kill main thread
			break;
		}
		default: {
			return DefWindowProc(hwnd, Message, wParam, lParam);
		}
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEXA wc = {0};
	MSG Msg = {0};

	// Create a window with these properties
	wc.cbSize        = sizeof(WNDCLASSEX);
	wc.lpfnWndProc   = WndProc;
	wc.hInstance     = hInstance;
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wc.lpszClassName = "WindowClass";
	wc.hIcon         = LoadIcon(hInstance,"A"); // laad projecticoon
	wc.hIconSm       = LoadIcon(hInstance,"A");
	
	// Say hi to Windows
	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
	
	// Set up a window with 1024x768 usable pixels
	RECT result = {0,0,1024,768};
	AdjustWindowRect(&result,WS_VISIBLE|WS_OVERLAPPEDWINDOW,false);

	// Create a window with a border and 'client rect' of 1024x768
	hwnd = CreateWindow("WindowClass","Tic-Tac-Toe",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, // x
		CW_USEDEFAULT, // y
		result.right - result.left, // width
		result.bottom - result.top, // height
		NULL,NULL,hInstance,NULL);
	if(hwnd == NULL) {
		MessageBox(NULL,"Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
	
	// Init render loop
	InitEngine();
	
	// Prepare game world
	InitGame();
	
	// Handle user input. If done, render a frame. Goto 1
	while(Msg.message != WM_QUIT) {
		while(PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
		
		if(!renderer->paused) {
			renderer->Begin(false);
			renderer->DrawScene(scene);
			renderer->End();
		} else {
			Sleep(100);
		}
	}
	
	// Ruim zooi op
	DeleteGame();
	
	// Render loop stopped due to Alt+F4 etc? Delete everything
	DeleteEngine();

	return Msg.wParam;
}
