#include "common.h"
#define BOARD_X1 1
#define BOARD_Y1 1
#define BOARD_X2 50
#define BOARD_Y2 23
#define END_X 70
//x�����꣬y������

//���ù��λ��
void SetPos(COORD a);
void SetPos(int x, int y);

//���ع��
void HideCursor();

//��ʾ���
void setrow(int x_left, int x_right, int y);
//��ʾ����
void setline(int x, int y_up, int y_down);

//��ʾ�÷ֳƺ�
void game_info(int score);

//���ɻ��������ɻ�
void draw_plane(int x, int y);
void erase_plane(int x, int y);
//���л�,�����л�
void draw_enemy(int x, int y);
void erase_enemy(int x, int y);

void draw_ballet(int x,int y);
void erase_ballet(int x, int y);

//��Ϸʧ��
void draw_over();
