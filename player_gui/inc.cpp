#include <map>
#include <iostream>
#include <SDL2/SDL.h>
#include "../sdlgui/sdlgui.h"
using namespace std;
#ifndef __ICN__
#define __ICN__
sdl_clip icon; 
map<string,string> music_list;
#define icon_play 0,0
#define icon_paush 1,0
//文件列表项目类型ID
const int file_type_dir = 0;
const int file_type_music= 1;
const int file_type_love= 2;
//文件目录图标坐标
#define file_type_dir_xy 5,0
//音乐图标坐标
#define file_type_music_xy 2,0
//喜欢的音乐图标坐标
#define file_type_love_xy 3,0
//正在听歌的音乐图标坐标
#define music_listen_xy 4,0
//返回上级目录按钮图片坐标
#define back_button_xy 7,0
//关闭按钮图片坐标
#define close_button_xy 8,0
//更新按钮图片坐标
#define update_button_xy 6,0
#endif//__ICN
