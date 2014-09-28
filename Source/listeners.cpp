#include "JohanEngine\Dialogs.h"
#include "JohanEngine\Renderer.h"
#include "Listeners.h"
#include "resource.h"

void LoadScene(Component* sender) {
	
	// laad omgeving
	scene->Load("TicTacToe.script");
	
	// Maak ground
	Object* ground = scene->objects->AddPlane("Ground","Ground.mtl",
		float3(0,0,0),0,10,2,4,NULL);
	ground->castshadows = false;
	
	// Maak zonlicht
	Dirlight* sun = new Dirlight(
		float3(-1,1.5,3),
		float3(1.4,1.4,1.2),
		true);
	sun->SetCastShadows(true);
	
	// En dan de rest, met OnClicks
	buttons[0][0] = new Object("Button00","TicButton.obj","Stone.mtl",float3(0,0,0),0,1);
	buttons[1][0] = new Object("Button10","TicButton.obj","Stone.mtl",float3(1,0,0),0,1);
	buttons[2][0] = new Object("Button20","TicButton.obj","Stone.mtl",float3(2,0,0),0,1);
	buttons[0][1] = new Object("Button01","TicButton.obj","Stone.mtl",float3(0,0,1),0,1);
	buttons[1][1] = new Object("Button11","TicButton.obj","Stone.mtl",float3(1,0,1),0,1);
	buttons[2][1] = new Object("Button21","TicButton.obj","Stone.mtl",float3(2,0,1),0,1);
	buttons[0][2] = new Object("Button02","TicButton.obj","Stone.mtl",float3(0,0,2),0,1);
	buttons[1][2] = new Object("Button12","TicButton.obj","Stone.mtl",float3(1,0,2),0,1);
	buttons[2][2] = new Object("Button22","TicButton.obj","Stone.mtl",float3(2,0,2),0,1);
	
	for(int i = 0;i < 3;i++) {
		for(int j = 0;j < 3;j++) {
			buttons[i][j]->OnClick = OnButtonClick;
		}
	}
	
	// Reset speelveld
	game->ResetField();
}

void ResetScene(Component* sender) {
	ui->RemoveComponent(sender->parent);
	LoadScene(NULL);
}
	
void Help(void* data) {
	new Messagebox("F1:Show this\nF2:Toggle fullscreen\nF11:Show options\nF12:Show console");
}

void ToggleFullscreen(void* data) {
	renderer->ToggleFullScreen();
}

void ToggleOptions(void* data) {
	OptionsDialog->Toggle();
}

void ToggleConsole(void* data) {
	ConsoleDialog->Toggle();
}

void WinBox(const char* text) {
	
	// Center window
	float2 windowsize = float2(100,100);
	float2 topleft = renderer->GetCenteringCorner(windowsize);
	
	// Gooi jezelf weg bij OK?
	Window* winner = new Window(topleft.x,topleft.y,windowsize.x,windowsize.y,text);
	Button* ok = new Button(5,20,windowsize.x-10,windowsize.y-25,"OK");
	ok->OnClick = ResetScene;
	winner->AddChild(ok);
	ui->AddComponent(winner);
	winner->Show(1);
}

void OnButtonClick(Object* sender) {
	
	// Which button is this?
	int x,y;
	if(sscanf(sender->GetName(),"Button%1d%1d",&x,&y) == 2) {
		
		// ignore invalid clicks
		if(game->field[x][y] != bsNone) {
			return; 
		}
		
		// Ignore clicks after game win
		if(game->gamewon) {
			return;
		}
		
		game->field[x][y] = game->currentplayer;
		switch(game->currentplayer) {
			case bsCircle: {
				new Object("ButtonProp","TicCircle.obj","WoodBoards.mtl",sender->GetTranslation(),0,1);
				break;
			}
			case bsCross: {
				new Object("ButtonProp","TicCross.obj","WoodBoards.mtl",sender->GetTranslation(),0,1);
				break;
			}
			default: {
				break;
			}
		}

		// Check if we have a winner
		ButtonState winner = game->GetWinner();
		switch(winner) {
			case bsCircle: {
				game->circlescore++;
				
				// Werk main menu bij
				char caption[128];
				sprintf(caption,"Circle score: %d",game->circlescore);
				circlescore->SetCaption(caption);
				WinBox("Circle wins!");				
				break;
			}
			case bsCross: {
				game->crossscore++;
				
				// Werk main menu bij
				char caption[128];
				sprintf(caption,"Cross score: %d",game->crossscore);
				crossscore->SetCaption(caption);
				WinBox("Cross wins!");
				break;
			}
			case bsDraw: {
				WinBox("Noone wins!"); // Sad			
				break;
			}
			case bsNone: {
				break;
			}
		}
		game->NextPlayer();
	}
}
void OnMouseDown(WPARAM wParam,LPARAM lParam,bool handled) {
	if(handled) {
		return;
	}
	
	float3 worldpos = camera->pos;
	float3 worlddir = renderer->GetPixelWorldRay(ui->mousepos).SetLength(1000); // reach 1000m
	Object* mouseobject = scene->IntersectScene(worldpos,worlddir).object;
	if(mouseobject && mouseobject->OnClick) {
		mouseobject->OnClick(mouseobject);
	}
}
