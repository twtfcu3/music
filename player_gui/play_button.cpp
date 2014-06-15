#include <SDL2/SDL.h>
#include "../sdlgui/sdlgui.h"
#include "inc.cpp"
using namespace std;
#ifndef __play_button__
#define __play_button__
extern sdl_clip icon;
typedef class music_play_button : public GUI<music_play_button,sdl_button>
{
	public:
		music_play_button();
		music_play_button(const char*,int,int,int,int,Uint32);
		int init();
		int init(const char*,int,int,int,int,Uint32);
		int sysevent(SDL_Event*);
		int state();
		int state(int);
		int draw();
	protected:
		int _state;
}*music_play_button_ptr;
music_play_button::music_play_button()
	:
		GUI<music_play_button,sdl_button>()
{
	init();
}
music_play_button::music_play_button(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
	:
		GUI<music_play_button,sdl_button>()
{
	init(ptitle,px,py,pw,ph,pflag);
}
int music_play_button::init()
{
	if(sdl_button::init())return -1;
	_state = 0;
	return 0;
}
int music_play_button::init(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
{
	if(sdl_button::init(ptitle,px,py,pw,ph,pflag))return -1;
	color_key(1,0xff0000);
	return 0;
}
int music_play_button::sysevent(SDL_Event*e)
{
	switch(e->type)
	{
		case SDL_MOUSEMOTION:
			cout<<"play motion"<<endl;
		break;
		case SDL_MOUSEBUTTONDOWN:
			state((_state)?0:1);
		break;
		default:
			break;
	}
	return sdl_button::sysevent(e);
}
int music_play_button::state()
{
	return _state;
}
int music_play_button::state(int s)
{
	sdlsurface* tsur = _button_clip(0,0);
	_state = s&1;
	if(_state)
	{
		icon(icon_play)->blit_surface(NULL,tsur,NULL);
	}
	else
	{
		icon(icon_paush)->blit_surface(NULL,tsur,NULL);
	}
	tsur->blit_surface(NULL,_button_clip(1,0),NULL);
	tsur->blit_surface(NULL,_button_clip(2,0),NULL);
	return 0;
}
int music_play_button::draw()
{
	return	state(0);
}
#endif //__play_button__
