#ifndef __music_item__
#define __music_item__
#include <iostream>
#include <string>
#include <map>
#include "../sdlgui/sdlgui.h"
#include "./inc.cpp"
using namespace std;
class music_item;
music_item *_select_music=NULL;
typedef class music_item : public GUI<music_item,sdl_button>
{
	public:
		music_item();
		music_item(const char*,int,int,int,int,Uint32);
		int init();
		int init(const char*,int,int,int,int,Uint32);
		int state();
		int state(int);
		int sysevent(SDL_Event*);
		int draw();
	protected:
		int _state;
	public:
		string music_path;
}*music_item_ptr;
music_item::music_item()
	:
		GUI<music_item,sdl_button>()
{
	init();
}
music_item::music_item(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
	:
		GUI<music_item,sdl_button>()
{
	init();
	init(ptitle,px,py,pw,ph,pflag);
}
int music_item::init()
{
	if(sdl_button::init())return -1;
	return 0;
}
int music_item::init(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
{
	int loc;
	music_path.assign(ptitle);
	_text_color = 0xffffff;
	loc = music_path.rfind("//",music_path.length());
	if(sdl_button::init(music_path.substr(loc+2,music_path.length()-loc).c_str(),px,py,pw,ph,pflag))return -1;
	_state = 0;
	return 0;
}
int music_item::draw()
{
	state(0);
	color_key(1,0);
	color_key(1,0xff0000);
	return 0;
}
int music_item::sysevent(SDL_Event*e)
{
	switch(e->type)
	{
		case SDL_MOUSEBUTTONUP:
			if(_select_music)
			{
				_select_music->state(0);
			}
			_select_music = this;
			state(1);
		break;
		default:
		break;
	}
	return sdl_button::sysevent(e);
}
int music_item::state()
{
	return _state;
}
int music_item::state(int s)
{
	_state = s&1;
	switch(_state)
	{
		case 1:
			icon(music_listen_xy)->blit_surface(NULL,release_page(),NULL);
			icon(music_listen_xy)->blit_surface(NULL,press_page(),NULL);
			icon(music_listen_xy)->blit_surface(NULL,this,NULL);
		break;
		case 0:
			icon(file_type_music_xy)->blit_surface(NULL,release_page(),NULL);
			icon(file_type_music_xy)->blit_surface(NULL,press_page(),NULL);
			icon(file_type_music_xy)->blit_surface(NULL,this,NULL);
		break;
	}
}
#endif //__music_item__
