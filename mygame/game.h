#define random(x) (rand()%x)
#define MAX_ENEMY 20
#define MAX_BALLET 40
#include "display.h"


class point{
public:
	point(){};
	point(int a, int b) :x(a), y(b){};
	int x, y;
	
	//�ɻ��ƶ�������
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
	int cout; //���ڼ���ɻ��Ƿ��ƶ�
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
//ԭ�ƻ�������ʾ��������
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
//���Ŀ���
class GameControl{
	//GameSpace g;
	bool over; //��ʾ�Ƿ������Ϸ
	point plane;
	Enemy enemy[MAX_ENEMY];
	Ballet ballet[MAX_BALLET];
	int speed;
	int enemy_count;
	int score;
public:
	GameControl(){ enemy_count = 0; score = 0; }
	void Shift_plane(char ch);//�ɻ��ƶ�
	void Command_control(); //�������
	bool test_boarder(int& x, int& y);//���ɻ��Ƿ񵽴�߽�
	int Enemy_appear(); //����һ�ܵл�
	void Enemy_move(); //�л����ٶ��ƶ�
	bool plane_enmemy_col(int e_x,int e_y, int p_x, int p_y);//���ɻ���л��Ƿ���ײ
	void ballet_appear();//�ӵ�����
	void ballet_move(); //�ӵ��ƶ�
	bool ballet_enemy_col(int b_x, int b_y, int& m);
	void Game_run();
	void Game_over();
};
//��Ҫһ���л��������������ӵл���ɾ���л�
