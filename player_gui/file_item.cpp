#include <SDL2/SDL.h>
#include "../sdlgui/sdlgui.h"
#include <string.h>
#include "inc.cpp"
using namespace std;
#ifndef __file_item__
#define __file_item__
typedef class file_item: public GUI<file_item,sdl_button>
{
	public:
		file_item();
		file_item(const char*,int,int,int,int,Uint32);
		int init();
		int init(const char*,int,int,int,int,Uint32);
		int sysevent(SDL_Event*);
		int state();
		int state(int);
		int draw();
		int item(const char*,int);
	public:
		int _state;
		int _item_type;
		string _file;
	protected:
}*file_item_ptr;
file_item::file_item()
:
GUI<file_item,sdl_button>()
{
	init();
}
file_item::file_item(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
{
	init(ptitle,px,py,pw,ph,pflag); 
}
int file_item::init()
{
	if(sdl_button::init())return -1;
	_state = 0;
	_item_type = file_type_dir;
	_text_rect.x = 70;
	return 0;
}
int file_item::init(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
{
	sdl_button::_text_color=0xffffff;
	if(sdl_button::init(ptitle,px,py,pw,ph,pflag))return -1;
	text(ptitle);
	_file.clear();
	_file.append(ptitle);
	color_key(1,0xff0000);
	return 0;
}
int file_item::sysevent(SDL_Event*e)
{
	switch(e->type)
	{
		case SDL_MOUSEBUTTONDOWN:
			state((_state)?0:1);
		break;
	}
	return sdl_button::sysevent(e);
}
int file_item::state()
{
	return _state;
}
int file_item::state(int p)
{
	sdlsurface* tsur = _button_clip(0,0);
	tsur->fill_rect(NULL,0xff0000);
	_state = p&1;
	switch(_item_type)
	{
		case file_type_dir:
			icon(file_type_dir_xy)->blit_surface(NULL,tsur,NULL);
			if(_state)
			{

			}
		break;
		default:
			if(_state)
			{
				icon(file_type_love_xy)->blit_surface(NULL,tsur,NULL);
			}
			else
			{
				icon(file_type_music_xy)->blit_surface(NULL,tsur,NULL);
			}
		break;
	}
	tsur->blit_surface(NULL,_button_clip(1,0),NULL);
	tsur->blit_surface(NULL,_button_clip(2,0),NULL);
	tsur->blit_surface(NULL,this,NULL);
	return 0;
}
int file_item::draw()
{
	state(0);
}
int file_item::item(const char* pfile,int ptype = file_type_dir)
{
	if(text(pfile))return -1;
	_item_type = ptype&3;
	state(0);
	return 0;
}
#endif //__file_item__
