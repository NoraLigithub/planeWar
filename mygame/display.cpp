#include"display.h"
void SetPos(COORD a)// set cursor  
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(out, a);
}
void SetPos(int x, int y){
	COORD a = { x, y };
	SetPos(a);
}
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void setrow(int x_left, int x_right, int y){
	if (x_left < 0 || x_right < 0 || y < 0 || x_left > x_right) { SetPos(1, 60); cout << "横线界限有误!"; return; }
	SetPos(x_left, y);
	for (int i = x_left; i <= x_right; i++)
		cout << '-';
}
void setline(int x, int y_up, int y_down){
	if (x < 0 || y_up < 0 || y_down < 0 || y_up > y_down){ SetPos(1, 60); cout << "竖线界限有误！"; return; }
	for (int i = y_up; i <= y_down; i++){
		SetPos(x, i);
		cout << '|';
	}
}

void game_info(int score){
	SetPos(BOARD_X2 + 5, BOARD_Y2 / 2);
	cout << "得分：";
	printf("%2d", score);
}

//画飞机，擦飞机，x,y是飞机中心点的坐标
void draw_plane(int x,int y){
	//SetPos(x, y - 2); cout << '|';
	SetPos(x, y - 1); cout << "|";
	SetPos(x - 2, y); cout << "==|==";
	SetPos(x - 1, y + 1); cout << "|-|";
}
void erase_plane(int x, int y){
	SetPos(x, y - 1); cout << " ";
	SetPos(x - 2, y); cout << "     ";
	SetPos(x - 1, y + 1); cout << "   ";
}

//画敌人，擦敌人
void draw_enemy(int x, int y){
	SetPos(x - 1 , y); cout << "\\|/";
	SetPos(x, y + 1); cout << "|";
}
void erase_enemy(int x, int y){
	SetPos(x - 1, y); cout << " "<<" "<<" ";
	SetPos(x, y + 1); cout << " ";
}

void draw_ballet(int x,int y){
	SetPos(x, y );
	cout << '^';
}
void erase_ballet(int x, int y){
	SetPos(x, y);
	cout << ' ';
}
void draw_over(){
	system("cls");
	SetPos(30, 10);
	cout << 'g';Sleep(200);
	cout << 'a'; Sleep(200);
	cout << 'm'; Sleep(200);
	cout << 'e'; Sleep(200);
	cout << ' '; Sleep(200);
	cout << 'o'; Sleep(200);
	cout << 'v'; Sleep(200);
	cout << 'e'; Sleep(200);
	cout << 'r'; Sleep(200);
	SetPos(25, 11);
	cout << "是否继续？是（y），否（n）";
	SetPos(25, 12);
}