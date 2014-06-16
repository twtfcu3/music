#include <iostream>
#include <SDL2/SDL.h>
#include <io.h>
#include "../sdlgui/sdlgui.h"
#include "./back_button.cpp"
#include "./file_item.cpp"
#include "./inc.cpp"
#ifndef __file_plane__
#define __file_plane__
using namespace std;
typedef class file_plane : public GUI<file_plane,sdl_widget>
{
	public:
		file_plane();
		file_plane(const char*,int,int,int,int,Uint32);
		int init();
		int init(const char*,int,int,int,int,Uint32);
		int sysevent(SDL_Event*);
		int opendir(const char*);
	protected:
		static int view_event(sdl_view* obj,SDL_Event*);
	protected:
		back_button back;
		sdl_view _file_view;
		file_item* _current_item;
}*file_plane_ptr;
file_plane::file_plane()
	:
		GUI<file_plane,sdl_widget>()
{
	init();
}
file_plane::file_plane(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
	:
		GUI<file_plane,sdl_widget>()
{
	init(ptitle,px,py,pw,ph,pflag);
}
int file_plane::init()
{
	if(sdl_widget::init())return -1;
	return 0;
}
int file_plane::init(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
{
	if(sdl_widget::init(ptitle,px,py,pw,ph,pflag))return -1;
	back.init("",pw-64*2,0,64,64,1);
	add<back_button>(&back);
	_file_view.init("",0,64,pw,ph-64,1);
	_file_view.view.fill_rect(NULL,0xff0000);
	add<sdl_view>(&_file_view);
	_file_view.scroll(2);
	fill_rect(NULL,0xff0000);
	color_key(1,0xff0000);
	_file_view.event(file_plane::view_event);
	opendir("c:");
	return 0;
}
int file_plane::sysevent(SDL_Event*e)
{
	string music_path;
	map<string,string>::iterator iter;
	file_item_ptr item=NULL;
	_finddata_t f;
	int i,j=0;
	switch(e->type)
	{
		case SDL_USEREVENT:
			switch(e->user.code)
			{
				default:
				break;
				case sdlgui_button_click:
					if(e->user.data1==&back)
					{
						opendir(NULL);
					}
					else
					{
						item = (file_item_ptr)e->user.data1;
						if(item->_item_type == file_type_dir)
						{
							opendir(item->_file.c_str());
						}
						else
						{
							//合并文件路径
							music_path.assign(back.full_path());
							music_path.append(item->_file);
							switch(item->state())
							{
								case 0:
									//删除音乐
									music_list.erase(music_path);
								break;
								case 1:
									//加入音乐
									music_list.insert(pair<string,string>(music_path,music_path));
								break;
							}
						}
					}
				break;
			}
		break;
		case SDL_MOUSEMOTION:
			if(e->motion.y<64)_parent->event(e);
		break;
		default:
		break;
	}
	return sdl_widget::sysevent(e);
}
int file_plane::view_event(sdl_view* obj,SDL_Event*e)
{
	switch(e->type)
	{
		case SDL_USEREVENT:
			switch(e->user.code)
			{
				case sdlgui_button_click:
					obj->parent()->event(e);
				break;
			}
		break;
	}
}
int file_plane::opendir(const char* name=NULL)
{
	SDL_Rect rt;
	string _path_str;
	file_item_ptr item;
	_finddata_t f;
	int i,j=0;
	if(name==NULL)
	{
		back.back();
	}
	else
	{
		back.next(name);
	}
	_path_str.clear();
	_path_str.append(back.full_path());
	_path_str.append("*.*");
	i = _findfirst(_path_str.c_str(),&f);
	if(i==-1L)
	{
		return -1;
	}
	else
	{
		j=0;
		_file_view.view.destroy(0);
		_file_view.scroll(2.0,0.0);
		while(!_findnext(i,&f))
		{
			item = _file_view.view.add<file_item>(f.name,0,j*64,_rect.w,64,1);
			if(f.attrib == _A_SUBDIR)
			{
				item->_item_type = file_type_dir;
			}
			else
			{
				item->_item_type = file_type_music;
			}
			item->state(0);
			j++;
		}
		rt.h = 0;
		rt.y = -64*j;
		_file_view.view.size(width(),64*j);
		_file_view.scroll(2);
		_file_view.view.fill_rect(NULL,0xff0000);
		color_key(1,0xff0000);
	}
	return 0;
}
#endif //__file_plane__
