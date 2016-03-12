#include "game.h"



//返回1越界
bool GameControl::test_boarder(int& x, int& y){
	bool flag = 0;
	if (x < BOARD_X1 + 2) { x = BOARD_X1 + 2; flag = 1; }
	if (x > BOARD_X2 - 2) { x = BOARD_X2 - 2; flag = 1; }
	if (y < BOARD_Y1 + 2) { y = BOARD_Y1 + 2; flag = 1; }
	if (y > BOARD_Y2 - 2) { y = BOARD_Y2 - 2; flag = 1; }
	return flag;
}
bool GameControl::plane_enmemy_col(int e_x, int e_y, int p_x, int p_y){
	if ((abs(e_x - p_x) <= 1) && p_y <= e_y + 2 && p_y >= e_y - 1) return true;
	if ((abs(e_x - p_x) <= 2) && (p_y == e_y || p_y == e_y - 1) )return true;
	return false;
}
bool GameControl::ballet_enemy_col(int b_x, int b_y, int& m){
	bool flag = false;
	for (int i = 0; i < MAX_ENEMY; i++){
		if (enemy[i].vacant){
			if (enemy[i].x == b_x && (enemy[i].y == b_y || enemy[i].y == b_y - 1)){
				flag = true; enemy[i].vacant = false;
				erase_enemy(enemy[i].x, enemy[i].y);
				m = i; return flag;
			}
			else if (enemy[i].y == b_y && abs(enemy[i].x - b_x) <= 1) {
				flag = true; enemy[i].vacant = false;
				erase_enemy(enemy[i].x, enemy[i].y);
				m = i; return flag;
			}
		}
	}
	return flag;
}
void GameControl::Command_control(){
	if (_kbhit()){
		char ch = _getch();
		switch (ch){
		case 'w':case 'a':case 's':case 'd':
			erase_plane(plane.x, plane.y);
			Shift_plane(ch); break;
		case 'k':ballet_appear(); break;
		}
	}
}

//玩家控制飞机移动
void GameControl::Shift_plane(char ch){
	plane.shift(ch);
	point p(0, 0);
	//检测越界
	test_boarder(plane.x, plane.y);
	draw_plane(plane.x, plane.y);
}

//敌机移动
int GameControl::Enemy_appear(){
	for (int i = 0; i < MAX_ENEMY; i++){
		if (enemy[i].vacant == 0){
			enemy[i].vacant = 1;
			int pos = 0;
			//srand((int)time(0));
			pos = random(BOARD_X2 - BOARD_X1 - 4); //敌机出现的位置
			enemy[i].x = pos + 3;
			enemy[i].y = 1;
			draw_enemy(enemy[i].x, enemy[i].y);
			return i;
		}
	}
	return -1;
}
void GameControl::ballet_appear(){
	for (int i = 0; i < MAX_BALLET; i++){
		if (ballet[i].vacant == 0){
			ballet[i].vacant = 1;
			ballet[i].x = plane.x;
			ballet[i].y = plane.y-2;
			draw_ballet(ballet[i].x, ballet[i].y);
			break;
		}
	}
}
void GameControl::Enemy_move(){
	for (int m = 0; m < MAX_ENEMY; m++){
		if (enemy[m].vacant){
			erase_enemy(enemy[m].x, enemy[m].y);
			enemy[m].move(); //每一个飞机可以有个性化的速度，基准速度的几分之一
			//enemy[m].y++;//可修改使不同飞机速度不同，比如...
			//发生碰撞
			if (plane_enmemy_col(enemy[m].x, enemy[m].y, plane.x, plane.y)) {
				enemy[m].vacant = 0;
				over = 1;
			}
			//检测边界
			else if (enemy[m].y <= BOARD_Y2 - 2 && enemy[m].vacant)
				draw_enemy(enemy[m].x, enemy[m].y);
			else enemy[m].vacant = 0;
		}
 	}
}
void GameControl::ballet_move(){
	for (int m = 0; m < MAX_BALLET; m++){
		if (ballet[m].vacant){
			erase_ballet(ballet[m].x, ballet[m].y);
			ballet[m].y--;
			//draw_ballet(ballet[m].x, ballet[m].y);
			//发生碰撞
			int n = -1;
			if (ballet_enemy_col(ballet[m].x, ballet[m].y, n)) {
				ballet[m].vacant = 0;
				score++;
				game_info(score);
			}
			//检测边界
			else if (ballet[m].y >= BOARD_Y1 + 1)
				draw_ballet(ballet[m].x, ballet[m].y);
			else ballet[m].vacant = 0;
		}
	}
}
void GameControl::Game_run(){
    over = 0;
	while (!over){
		//游戏初始化
		system("cls");
		HideCursor();
		setrow(BOARD_X1, BOARD_X2, BOARD_Y2);
		setline(BOARD_X2, BOARD_Y1, BOARD_Y2);
		score = 0;
		game_info(score);
		plane.x = BOARD_X2 / 2; plane.y = BOARD_Y2 - 2;
		draw_plane(plane.x, plane.y);
		speed = 40;
		int flag_plane = 0;
		int flag_ballet = 0;
		int flag_appear = 0;
		//time_t t = time(NULL), t1;

		//游戏主循环
		while (true){
			Sleep(8);
			if (flag_plane == 0){
				int temp, temp1;
				//t = t1;
				if (flag_appear == 0) { temp = Enemy_appear(); }
				/*if (rand() % 3 == time(0) % 7 && (flag_appear == 0)){
					temp1 = Enemy_appear();
					//以下确保敌机不交叠,都产生了飞机
					if (temp != -1 && temp1 != -1){
						if (abs(enemy[temp1].x - enemy[temp].x) <= 2) {
							erase_enemy(enemy[temp1].x, enemy[temp1].x);
							enemy[temp1].vacant = false;
						}
					}
				}*/
				flag_appear++;
				if (flag_appear == 4) flag_appear = 0;
				Enemy_move();
			}
			flag_plane++;
			if (flag_plane == speed) flag_plane = 0;//该speed为基准速度
			if (flag_ballet == 0)
				ballet_move();
			flag_ballet++;
			if (flag_ballet == 5) flag_ballet = 0;
			if (over) {
				Game_over(); break;
			} //可以选择是否结束
			Command_control();
		}
	}
}
void GameControl::Game_over(){
	for (int i = 0; i < MAX_ENEMY; i++){
		enemy[i].vacant = 0;
	}
	for (int i = 0; i < MAX_BALLET; i++){
		ballet[i].vacant = 0;
	}
	score = 0;
	draw_over();
	char c = 'm';
	while (c != 'y'&&c != 'n'){
		HideCursor();
		c = _getch();
	}
	if (c == 'n')  {
		over = 1; exit(0);
	}
	else over = 0;
}