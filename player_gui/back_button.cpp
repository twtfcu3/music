#include <SDL2/SDL.h>
#include "../sdlgui/sdlgui.h"
#include "inc.cpp"
#include <string>
#ifndef __back_button__
#define __back_button__
extern sdl_clip icon;
struct file_node_state
{
	char* full_path;
	file_node_state* child;
	file_node_state* parent;
	file_node_state();
	~file_node_state();
};
file_node_state::file_node_state()
{
	full_path = NULL;
	parent = NULL;
	child = NULL;
}
file_node_state::~file_node_state()
{
	delete full_path;
}
typedef class back_button : public GUI<back_button,sdl_button>
{
	public:
		back_button();
		back_button(const char*,int,int,int,int,Uint32);
		int init();
		int init(const char*,int,int,int,int,Uint32);
		int sysevent(SDL_Event*);
		int draw();
		int back();
		int next(const char*);
		const char* full_path();
	protected:
		file_node_state* _head,*_end;
		string _full_path;
}*back_button_ptr;
back_button::back_button()
	:
		GUI<back_button,sdl_button>()
{
	init();
}
back_button::back_button(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
	:
		GUI<back_button,sdl_button>()
{
	init(ptitle,px,py,pw,ph,pflag);
}
int back_button::init()
{
	if(sdl_button::init())return -1;
	_head = NULL;
	return 0;
}
int back_button::init(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
{
	if(sdl_button::init(ptitle,px,py,pw,ph,pflag))return -1;
	file_node_state* tnode;
	while(_head)
	{
		tnode = _head;
		_head = _head->child;
		delete tnode;
	}
	color_key(1,0xff0000);
	return 0;
}
int back_button::sysevent(SDL_Event*e)
{
	switch(e->type)
	{
		case SDL_MOUSEBUTTONDOWN:
			//back();
		break;
		default:
		break;
	}
	return sdl_button::sysevent(e);
}
int back_button::draw()
{
	sdlsurface *tsur = _button_clip(0,0);
	tsur->fill_rect(NULL,0xff0000);
	icon(back_button_xy)->blit_surface(NULL,tsur,NULL);
	tsur->blit_surface(NULL,_button_clip(1,0),NULL);
	tsur->blit_surface(NULL,_button_clip(2,0),NULL);
}
int back_button::back()
{
	int i = _full_path.rfind("//",_full_path.length()-3);
	if(i!=string::npos)
	{
		_full_path.assign(_full_path.substr(0,i+2));
	}
	return 0;
}
int back_button::next(const char* pname)
{
	_full_path.append(pname);
	_full_path.append("//");
	return 0;
}
const char* back_button::full_path()
{
	return _full_path.c_str();
}
#endif //__back_button__
