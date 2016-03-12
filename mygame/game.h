#define random(x) (rand()%x)
#define MAX_ENEMY 20
#define MAX_BALLET 40
#include "display.h"


class point{
public:
	point(){};
	point(int a, int b) :x(a), y(b){};
	int x, y;
	
	//飞机移动，内联
	void shift(char com){
		switch (com){
		case 'w':y--; break;
		case 'a':x--; break;
		case 's':y++; break;
		case 'd':x++; break;
		}
	}
};

class Enemy :public point{
	int cout; //用于计算飞机是否移动
public:
	int e_speed;
	bool vacant;
	Enemy(){ cout = 0; e_speed = 1; vacant = 0; }
	Enemy(int speed,int x,int y):point(x,y){ cout = 0; e_speed = speed; vacant = 0; }
	void move(){
		cout = (cout + 1) % e_speed;
		if (cout == 0) {
			y++;
		}
	}
};
class Ballet : public point{
public:
	bool vacant;
	Ballet() :vacant(false){}
};
//原计划用于显示，现抛弃
/*class GameSpace{
	friend class GameControl;
	char **space;
	int row_size, line_size;
public:
	GameSpace(int R, int L) :row_size(R), line_size(L){
		space = new char*[row_size];
		for (int i = 0; i < row_size; i++)
			space[i] = new char[line_size];
	}
	~GameSpace(){
		for (int i = 0; i < row_size; i++)
			delete[]space[i];
		delete[]space;
	}
	void Initial_board(point left_up, int board_row, int board_line);
	void Print_screen();
};
*/
//核心控制
class GameControl{
	//GameSpace g;
	bool over; //表示是否结束游戏
	point plane;
	Enemy enemy[MAX_ENEMY];
	Ballet ballet[MAX_BALLET];
	int speed;
	int enemy_count;
	int score;
public:
	GameControl(){ enemy_count = 0; score = 0; }
	void Shift_plane(char ch);//飞机移动
	void Command_control(); //检测命令
	bool test_boarder(int& x, int& y);//检查飞机是否到达边界
	int Enemy_appear(); //出现一架敌机
	void Enemy_move(); //敌机按速度移动
	bool plane_enmemy_col(int e_x,int e_y, int p_x, int p_y);//检查飞机与敌机是否碰撞
	void ballet_appear();//子弹出现
	void ballet_move(); //子弹移动
	bool ballet_enemy_col(int b_x, int b_y, int& m);
	void Game_run();
	void Game_over();
};
//需要一个敌机的链表，可以增加敌机，删除敌机
