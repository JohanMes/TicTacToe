#ifndef LISTENER_INCLUDED
#define LISTENER_INCLUDED

void LoadScene(Component* sender);
void Help(void* data);
void ToggleFullscreen(void* data);
void ToggleConsole(void* data);
void ToggleOptions(void* data);
void OnButtonClick(Object* sender);
void OnMouseDown(WPARAM wParam,LPARAM lParam,bool handled);

#endif
