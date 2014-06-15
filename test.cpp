#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "sdlgui/sdlgui.h"
#include "player_gui/play_button.cpp"
#include "player_gui/file_item.cpp"
#include "player_gui/back_button.cpp"
#include "player_gui/file_plane.cpp"
#include "player_gui/music_item.cpp"
#include "player_gui/music_plane.cpp"
using namespace std;
file_plane_ptr file=NULL;
music_plane_ptr music=NULL;
int plane_step=0;
Sint32 plane_move_f=1;
SDL_TimerID timer=0;
int frame_event(sdl_frame* obj,SDL_Event*e)
{
	switch(e->type)
	{
		case SDL_MOUSEMOTION:
			switch(e->motion.state)
			{
				case 1:
					plane_move_f = e->motion.xrel;
					plane_move_f /= abs(plane_move_f);
					plane_step = 0;
					timer = obj->add_timer(100);
				break;
			}
		break;
		case SDL_USEREVENT:
			switch(e->user.code)
			{
				case sdlgui_button_click:
					exit(0);
				break;
				case sdlgui_event_timer:
					plane_step +=plane_step+1;
					if(timer&&music)					
					{
						music->pos_x(music->pos_x()+plane_move_f*plane_step);
						if(abs(music->pos_x())>music->width())
						{
							SDL_RemoveTimer(timer);
							timer = 0;
							music->pos_x(music->width()*plane_move_f);
							file->pos_x(0);
						}
					}
					if(timer&&file)
					{
						file->pos_x(file->pos_x()+plane_move_f*plane_step);
						if(abs(file->pos_x())>file->width())
						{
							SDL_RemoveTimer(timer);
							timer = 0;
							file->pos_x(file->width()*plane_move_f);
							music->pos_x(0);
						}
					}
				break;
			}
		break;
	}
}
int main(int argc, char * argv[])
{
	Mix_Init(MIX_INIT_MP3);
	int i;
	sdlsurface bg;
	sdl_button* _close;
	icon.img_load("icon/icons.bmp");
	icon.clip(64,64);
	sdl_frame f("music player",100,100,400,600,SDL_WINDOW_SHOWN);	
	bg.img_load("icon/backgroup.jpg");
	bg.blit_surface(NULL,&f,NULL);
	file = f.add<file_plane>("",400,0,400,600,1);
	music= f.add<music_plane>("",0,0,400,600,1);
	_close = f.add<sdl_button>("",400-64,0,64,64,1);
	icon(close_button_xy)->blit_surface(NULL,_close->killfocus_page(),NULL);
	icon(close_button_xy)->blit_surface(NULL,_close->release_page(),NULL);
	icon(close_button_xy)->blit_surface(NULL,_close->press_page(),NULL);
	icon(close_button_xy)->blit_surface(NULL,_close,NULL);
	_close->color_key(1,0xff0000);
	f.event(frame_event);
	f.run();
	Mix_Quit();
	return 0;
}
