#include "common.h"
#define BOARD_X1 1
#define BOARD_Y1 1
#define BOARD_X2 50
#define BOARD_Y2 23
#define END_X 70
//x横坐标，y纵坐标

//设置光标位置
void SetPos(COORD a);
void SetPos(int x, int y);

//隐藏光标
void HideCursor();

//显示横边
void setrow(int x_left, int x_right, int y);
//显示竖边
void setline(int x, int y_up, int y_down);

//显示得分称号
void game_info(int score);

//画飞机，擦除飞机
void draw_plane(int x, int y);
void erase_plane(int x, int y);
//画敌机,擦除敌机
void draw_enemy(int x, int y);
void erase_enemy(int x, int y);

void draw_ballet(int x,int y);
void erase_ballet(int x, int y);

//游戏失败
void draw_over();
