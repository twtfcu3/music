#ifndef __music_plane__
#define __music_plane__
#include <iostream>
#include <string>
#include <map>
using namespace std;
#include "./music_item.cpp"
typedef class music_plane : public GUI<music_plane,sdl_widget>
{
	public:
		music_plane();
		music_plane(const char*,int,int,int,int,Uint32);
		int init();
		int init(const char*,int,int,int,int,Uint32);
		int sysevent(SDL_Event*);
		static int view_event(sdl_view*,SDL_Event*);
	public:
		int update_list();
		int save_list();
	protected:
		sdl_view _list;
		sdl_button _update;		
		music_play_button _play;
}*music_plane_ptr;
music_plane::music_plane()
	:
		GUI<music_plane,sdl_widget>()
{
	init();
}
music_plane::music_plane(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
	:
		GUI<music_plane,sdl_widget>()
{
	init(ptitle,px,py,pw,ph,pflag);
}
int music_plane::init()
{
	if(sdl_widget::init())return -1;
	return 0;
}
int music_plane::init(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
{
	SDL_Rect rt;
	int i;
	if(sdl_widget::init(ptitle,px,py,pw,ph,pflag))return -1;
	_list.init("",0,64,pw,ph-64*3,1);
	_update.init("",0,0,64,64,1);
	_play.init("",0,ph-64,64,64,1);
	for(i=0;i<8;i++)
	{
		rt.x = i*64;
		rt.y = ph-64;
		rt.w = 64;
		rt.h = 64;
		icon(i,1)->blit_surface(NULL,this,&rt);	
	}
	icon(update_button_xy)->blit_surface(NULL,_update.killfocus_page(),NULL);
	icon(update_button_xy)->blit_surface(NULL,_update.release_page(),NULL);
	icon(update_button_xy)->blit_surface(NULL,_update.press_page(),NULL);
	icon(update_button_xy)->blit_surface(NULL,&_update,NULL);
	add<sdl_view>(&_list);
	add<sdl_button>(&_update);
	add<music_play_button>(&_play);
	_list.event(view_event);
	_update.color_key(1,0xff0000);
	_list.color_key(1,0x00);
	color_key(1,0x00);
	color_key(1,0xff0000);
	return 0;
}
int music_plane::sysevent(SDL_Event*e)
{
	switch(e->type)
	{
		case SDL_MOUSEMOTION:
			_parent->event(e);
		break;
		case SDL_USEREVENT:
			switch(e->user.code)
			{
				case sdlgui_button_click:
					if(e->user.data1 == &_update)update_list();
					else
					{
						cout<<_select_music->music_path<<endl;
					}
				break;
			}
		break;
		default:
		break;
	}
	return sdl_widget::sysevent(e);
}
int music_plane::view_event(sdl_view* v,SDL_Event*e)
{
	v->parent()->event(e);
	return 0;
}
int music_plane::update_list()
{
	_list.view.destroy(0);
	int i=0;
	map<string,string>::iterator iter;
	for(iter=music_list.begin();iter!=music_list.end();iter++)
	{
		_list.add<music_item>(iter->first.c_str(),0,i*64,_rect.w,64,1);		
		cout<<iter->first<<endl;
		i++;
	}
}
#endif //__music_plane__

