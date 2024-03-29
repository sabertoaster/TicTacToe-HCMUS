﻿#include "Model.h"
#include <filesystem>
#include <fstream>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#include<chrono>
using namespace chrono;

auto start_time = system_clock::now();
auto end_time = system_clock::now();
auto elapsed_time = duration_cast<milliseconds>(end_time - start_time);
int check_play_ai = 0, save_I, save_J, check_save=0, milliseconds_as_int = 0;
Player::Player(int x, int y, int inputnumcell, int j, int i) {
	// x,y la toa do console // i tuong ung voi y // j tuong ung voi x
	initCoor.X = x;
	initCoor.Y = y;
	numcell = inputnumcell;
	this->i = i;
	this->j = j;
}
int Player::pow10(int _POINT, int b)
{
	int res = 1;
	while (b)
	{
		if (b % 2 == 1)
			res *= _POINT;
		_POINT *= _POINT;
		b /= 2;
	}
	return res;
}
int Player::cal(int n)
{
	if (n == 0)
		return 0;
	return pow10(10, n);
}
int Player::solve(int x, int y, int k)
{
	int tmp1 = x, tmp2 = y, cnt = 0, ans = 0;
	int cd = 0;
	for (int i = 1; i <= 6; i++)
	{
		x++;
		y--;
		if (_POINT[x][y] == k)
			cnt++;
		else
		{
			if (x<1 || x>numcell || y<1 || y>numcell)
				cd++;
			else if (_POINT[x][y] != 0)
				cd++;
			break;
		}
			
	}
	/*ans += cal(cnt+(k==2));
	cnt = 0;*/
	x = tmp1, y = tmp2;
	for (int i = 1; i <= 6; i++)
	{
		x--;
		y++;
		if (_POINT[x][y] == k)
			cnt++;
		else
		{
			if (x<1 || x>numcell || y<1 || y>numcell)
				cd++;
			else if (_POINT[x][y] != 0)
				cd++;
			break;
		}
		
	}
	if ((cd < 2 || cnt == 4))
		ans += cal(cnt + (k == 2));
	cnt = 0; cd = 0;
	// check 2
	x = tmp1, y = tmp2;
	for (int i = 1; i <= 6; i++)
	{
		x--;
		y--;
		if (_POINT[x][y] == k)
			cnt++;
		else
		{
			if (x<1 || x>numcell || y<1 || y>numcell)
				cd++;
			else if (_POINT[x][y] != 0)
				cd++;
			break;
		}
		
	}
	/*ans += cal(cnt + (k == 2));
	cnt = 0;*/
	x = tmp1, y = tmp2;
	for (int i = 1; i <= 6; i++)
	{
		x++;
		y++;
		if (_POINT[x][y] == k)
			cnt++;
		else
		{
			if (x<1 || x>numcell || y<1 || y>numcell)
				cd++;
			else if (_POINT[x][y] != 0)
				cd++;
			break;
		}
		
	}
	if ((cd < 2 || cnt == 4))
		ans += cal(cnt + (k == 2));
	cnt = 0; cd = 0;
	//check 3
	x = tmp1, y = tmp2;
	for (int i = 1; i <= 6; i++)
	{
		x--;
		//y--;
		if (_POINT[x][y] == k)
			cnt++;
		else
		{
			if (x<1 || x>numcell || y<1 || y>numcell)
				cd++;
			else if (_POINT[x][y] != 0)
				cd++;
			break;
		}
		
	}
	/*ans += cal(cnt + (k == 2));
	cnt = 0;*/
	x = tmp1, y = tmp2;
	for (int i = 1; i <= 6; i++)
	{
		x++;
		//y++;
		if (_POINT[x][y] == k)
			cnt++;
		else
		{
			if (x<1 || x>numcell || y<1 || y>numcell)
				cd++;
			else if (_POINT[x][y] != 0)
				cd++;
			break;
		}
		
	}
	if ((cd < 2 || cnt == 4))
		ans += cal(cnt + (k == 2));
	cnt = 0; cd = 0;
	// check 4;
	x = tmp1, y = tmp2;
	for (int i = 1; i <= 6; i++)
	{
		//x--;
		y--;
		if (_POINT[x][y] == k)
			cnt++;
		else
		{
			if (x<1 || x>numcell || y<1 || y>numcell)
				cd++;
			else if (_POINT[x][y] != 0)
				cd++;
			break;
		}
		
	}
	/*ans += cal(cnt + (k == 2));
	cnt = 0;*/
	x = tmp1, y = tmp2;
	for (int i = 1; i <= 6; i++)
	{
		//x++;
		y++;
		if (_POINT[x][y] == k)
			cnt++;
		else
		{
			if (x<1 || x>numcell || y<1 || y>numcell)
				cd++;
			else if (_POINT[x][y] != 0)
				cd++;
			break;
		}
	}
	if ((cd < 2 || cnt == 4))
		ans += cal(cnt + (k == 2));
	cnt = 0; cd = 0;
	return ans;
}
void Player::move()
{
	int check_up = 0, check_down = 0, check_right = 0, check_left = 0, check_enter = 0, cnt = 1, win = 1 ,check_undo=0,check_reundo=0;
	if (_kbhit())
	{
		char ch = _getch();
		ch = tolower(ch);
		if (ch == -32)
		{
			ch = _getch();
			if (ch == 72)
				check_up = 1;
			else if (ch == 80)
				check_down = 1;
			else if (ch == 75)
				check_left = 1;
			else if (ch == 77)
				check_right = 1;
		}
		else if (ch == 13)
			check_enter = 1;
		else if (ch == 'w')
			check_up = 1;
		else if (ch == 's')
			check_down = 1;
		else if (ch == 'd')
			check_right = 1;
		else if (ch == 'a')
			check_left = 1;
		else if (ch == 'z')
			check_undo = 1;
		else if (ch == 'y')
			check_reundo = 1;
		else if (ch == 'p')
		{
			check_save = 1;
			return;
		}
	}
	if (check_undo)
	{
		if (history.size() > 0)
		{
			if (BruteForce == 0 && Minimax == 0)
			{
				pair<int, int>his_xy = history.back();
				re_history.push_back(his_xy);
				history.pop_back();
				_POINT[his_xy.first][his_xy.second] = 0;
				current_player = 1 - current_player;
				GotoXY(initCoor.X + (his_xy.second - 1) * offSetX, initCoor.Y + (his_xy.first - 1) * offSetY);
				if (opt.darkMode == 1)
					changeFontColor(black, black);
				else
					changeFontColor(white, white);
				cout << " ";
				if (current_player == 1)
				{
					visualizer.printAvatar('X', 1); // Visualize O's turn
					visualizer.printAvatar('O', 0);
					
					visualizer.printAvatar('P', 1);
					visualizer.printAvatar('S', 0);
				}
				else
				{
					visualizer.printAvatar('X', 0); // Visualize X's turn
					visualizer.printAvatar('O', 1);
					
					visualizer.printAvatar('P', 0);
					visualizer.printAvatar('S', 1);
				}
				//GotoXY(initCoor.X + (j - 1) * offSetX, initCoor.Y + (i - 1) * offSetY);
			}
			else
			{
				pair<int, int>his_xy = history.back();
				re_history.push_back(his_xy);
				_POINT[his_xy.first][his_xy.second] = 0;
				history.pop_back();
				GotoXY(initCoor.X + (his_xy.second - 1) * offSetX, initCoor.Y + (his_xy.first - 1) * offSetY);
				if (opt.darkMode == 1)
					changeFontColor(black, black);
				else
					changeFontColor(white, white);
				cout << " ";
				his_xy = history.back();
				re_history.push_back(his_xy);
				_POINT[his_xy.first][his_xy.second] = 0;
				history.pop_back();
				GotoXY(initCoor.X + (his_xy.second - 1) * offSetX, initCoor.Y + (his_xy.first - 1) * offSetY);
				if (opt.darkMode == 1)
					changeFontColor(black, black);
				else
					changeFontColor(white, white);
				cout << " ";
				/*GotoXY(initCoor.X + (j - 1) * offSetX, initCoor.Y + (i - 1) * offSetY);*/
			}
			kt_undo = 1;
			check_undo = 0;
		}
	}
	if (check_reundo)
	{
		if (re_history.size() > 0)
		{
			if (BruteForce == 0 && Minimax == 0 )
			{
				pair<int, int>his_xy = re_history.back();
				history.push_back(his_xy);
				re_history.pop_back();
				GotoXY(initCoor.X + (his_xy.second - 1) * offSetX, initCoor.Y + (his_xy.first - 1) * offSetY);
				if (current_player == 1)
				{
					_POINT[his_xy.first][his_xy.second] = 1;
					draw_x();
					visualizer.printAvatar('X', 0); // Visualize X's turn
					visualizer.printAvatar('O', 1);
					visualizer.printAvatar('P', 0);
					visualizer.printAvatar('S', 1);
				}
				else
				{
					_POINT[his_xy.first][his_xy.second] = 2;
					draw_o();
					visualizer.printAvatar('X', 1); // Visualize O's turn
					visualizer.printAvatar('O', 0);
					visualizer.printAvatar('P', 1);
					visualizer.printAvatar('S', 0);
				}
				current_player = 1 - current_player;
			}
			else
			{
				pair<int, int>his_xy = re_history.back();
				history.push_back(his_xy);
				re_history.pop_back();
				GotoXY(initCoor.X + (his_xy.second - 1) * offSetX, initCoor.Y + (his_xy.first - 1) * offSetY);
				_POINT[his_xy.first][his_xy.second] = 1;
				draw_x();
				visualizer.printAvatar('X', 0); // Visualize X's turn
				visualizer.printAvatar('O', 1);
				visualizer.printAvatar('A', 1);
				visualizer.printAvatar('P', 0);

				his_xy = re_history.back();
				history.push_back(his_xy);
				re_history.pop_back();
				GotoXY(initCoor.X + (his_xy.second - 1) * offSetX, initCoor.Y + (his_xy.first - 1) * offSetY);
				_POINT[his_xy.first][his_xy.second] = 2;
				draw_o();

				visualizer.printAvatar('X', 1); // Visualize O's turn
				visualizer.printAvatar('O', 0);
				visualizer.printAvatar('A', 0);
				visualizer.printAvatar('P', 1);
				
			}
			check_reundo = 0;
		}
	}
	if (check_up || check_down || check_right || check_left)
	{
		PlaySound(TEXT("SOUND GAME CARO\\click\\click1.wav"), NULL, SND_ASYNC | opt.vfxFlag);
	}
	if (check_enter)
	{
		PlaySound(TEXT("SOUND GAME CARO\\click\\enter.wav"), NULL, SND_ASYNC | opt.vfxFlag);
	}
	if (check_enter == 1 && _POINT[i][j] != 0)
		check_enter = 0;
	if (i <= 1)
	{
		check_up = 0;
	}
	if (j <= 1)
	{
		check_left = 0;
	}
	if (j >= numcell)
	{
		check_right = 0;
	}
	if (i >= numcell)
	{
		check_down = 0;
	}
	// xu li check
	if (check_up)
	{
		i--;
		check_up = 0;
	}
	if (check_down)
	{
		i++;
		check_down = 0;
	}
	if (check_right)
	{
		j++;
		check_right = 0;
	}
	if (check_left)
	{
		j--;
		check_left = 0;
	}

	GotoXY(initCoor.X + (j - 1) * offSetX, initCoor.Y + (i - 1) * offSetY);
	if (BruteForce == 0 && Minimax == 0)
	{
		if (_POINT[i][j] == 0 && check_enter && !check_up && !check_down && !check_right && !check_left)
		{
			if (current_player == 1)
			{

				draw_x();
				visualizer.printAvatar('X', 0); // Visualize X's turn
				visualizer.printAvatar('O', 1);
				visualizer.printAvatar('S', 1);
				visualizer.printAvatar('P', 0);
				_POINT[i][j] = 1;
			}
			else
			{
				draw_o();
				visualizer.printAvatar('X', 1); // Visualize O's turn
				visualizer.printAvatar('O', 0);
				visualizer.printAvatar('S', 0);
				visualizer.printAvatar('P', 1);
				_POINT[i][j] = 2;
			}
			if (TimeMode == 1)
				start_time = system_clock::now();
			current_player = 1 - current_player;
			check_enter = 0;
			history.push_back({ i,j });
			if (kt_undo == 1)
			{
				kt_undo = 0;
				re_history.clear();
			}
		}
	}
	if (BruteForce == 1 || Minimax >= 1) 
	{
		if (current_player == 1)
		{
			if (_POINT[i][j] == 0 && check_enter && !check_up && !check_down && !check_right && !check_left)
			{
				draw_x();
				visualizer.printAvatar('X', 0); // Visualize X's turn
				visualizer.printAvatar('O', 1);
				visualizer.printAvatar('A', 1);
				visualizer.printAvatar('P', 0);
				_POINT[i][j] = 1;
				current_player = 1 - current_player;
				check_enter = 0;
				history.push_back({ i,j });
				if (kt_undo == 1)
				{
					kt_undo = 0;
					re_history.clear();
				}
			}
			
		}
		else if(BruteForce == 1)
		{
			// duyet het cac o trong bang 16x16 luu lai o co nuoc di toi uu
			pair<int, int>tmp = find_best_bruteforce();
			int tmpi = tmp.first, tmpj = tmp.second;
			_POINT[tmpi][tmpj] = 2;

			GotoXY(initCoor.X + (tmpj - 1) * offSetX, initCoor.Y + (tmpi - 1) * offSetY);
			draw_o();
			visualizer.printAvatar('X', 1); // Visualize O's turn
			visualizer.printAvatar('O', 0);
			visualizer.printAvatar('S', 0);
			visualizer.printAvatar('P', 1);

			current_player = 1 - current_player;
			check_enter = 0;
			GotoXY(initCoor.X + (j - 1) * offSetX, initCoor.Y + (i - 1) * offSetY);
			save_I = i; save_J = j;
			i = tmpi; j = tmpj;
			//check_play_ai = 1;
			history.push_back({ i,j });
			//PlaySound(TEXT("SOUND GAME CARO\\click\\enter.wav"), NULL, SND_ASYNC);
			type = check_win();
		}
		else
		{
			pair<int, int>tmp = find_best_move();
			int tmpi = tmp.first, tmpj = tmp.second;
			_POINT[tmpi][tmpj] = 2;
			GotoXY(initCoor.X + (tmpj - 1) * offSetX, initCoor.Y + (tmpi - 1) * offSetY);
			draw_o();
			visualizer.printAvatar('X', 1); // Visualize O's turn
			visualizer.printAvatar('O', 0);
			visualizer.printAvatar('A', 0);
			visualizer.printAvatar('P', 1);

			current_player = 1 - current_player;
			check_enter = 0;
			GotoXY(initCoor.X + (j - 1) * offSetX, initCoor.Y + (i - 1) * offSetY);
			save_I = i; save_J = j;
			i = tmpi; j = tmpj;
			//check_play_ai = 1;
			history.push_back({ i,j });
			PlaySound(TEXT("SOUND GAME CARO\\click\\enter.wav"), NULL, SND_ASYNC | opt.vfxFlag);
			type = check_win();
		}
	}

}
pair<int, int> Player::find_best_bruteforce()
{
	int  tmpi = 0, tmpj = 0; // tmpi , tmpj = i,j
	int ans = -1;   //tmpx, tmp initCoor.Y =initCoor.X,initCoor.Y;
	for (int _i = 1; _i <= 16; _i++)
	{
		for (int _j = 1; _j <= 16; _j++)
		{
			if (_POINT[_i][_j] != 0)
			{
				continue;
			}
			int tmp1 = solve(_i, _j, 1);
			int tmp2 = solve(_i, _j, 2);
			int tmp = tmp1 + tmp2;
			if (tmp2 >= cal(5))
			{
				tmp += cal(7);
			}
			if (tmp1 >= cal(4) && tmp2 < cal(5))
			{
				tmp += cal(6);
			}
			if (tmp1 >= cal(3) && tmp1 < cal(4) && tmp2 < cal(4))
			{
				tmp = cal(4) - 1;
			}
			if (ans < tmp)
			{
				ans = tmp;
				tmpi = _i, tmpj = _j;
			}
			else if (ans == tmp)
			{
				if (tmp1 > tmp2)
				{
					ans = tmp;
					tmpi = _i, tmpj = _j;
				}
			}
		}
	}
	return { tmpi,tmpj };
}
int Player::check_win()
{
	int x = i, y = j;
	int k = _POINT[i][j];
	if (k == 0)
		return 0;
	//check 1
	int tmp1 = x, tmp2 = y, cnt = 1;
	for (int i = 1; i <= 6; i++)
	{
		x++;
		y--;
		if (_POINT[x][y] == k)
			cnt++;
		else
			break;
	}
	x = tmp1, y = tmp2;
	for (int i = 1; i <= 6; i++)
	{
		x--;
		y++;
		if (_POINT[x][y] == k)
			cnt++;
		else
			break;
	}
	if (cnt >= 5)
		return 1;
	// check 2
	x = tmp1, y = tmp2, cnt = 1;
	for (int i = 1; i <= 6; i++)
	{
		x--;
		y--;
		if (_POINT[x][y] == k)
			cnt++;
		else
			break;
	}
	x = tmp1, y = tmp2;
	for (int i = 1; i <= 6; i++)
	{
		x++;
		y++;
		if (_POINT[x][y] == k)
			cnt++;
		else
			break;
	}
	if (cnt >= 5)
		return 1;
	//check 3
	x = tmp1, y = tmp2, cnt = 1;
	for (int i = 1; i <= 6; i++)
	{
		x--;
		//y--;
		if (_POINT[x][y] == k)
			cnt++;
		else
			break;
	}
	x = tmp1, y = tmp2;
	for (int i = 1; i <= 6; i++)
	{
		x++;
		//y++;
		if (_POINT[x][y] == k)
			cnt++;
		else
			break;
	}
	if (cnt >= 5)
		return 1;
	// check 4;
	x = tmp1, y = tmp2, cnt = 1;
	for (int i = 1; i <= 6; i++)
	{
		//x--;
		y--;
		if (_POINT[x][y] == k)
			cnt++;
		else
			break;
	}
	x = tmp1, y = tmp2;
	for (int i = 1; i <= 6; i++)
	{
		//x++;
		y++;
		if (_POINT[x][y] == k)
			cnt++;
		else
			break;
	}
	if (cnt >= 5)
		return 1;
	cnt = 0;
	for (int i = 1; i <= numcell; i++)
		for (int j = 1; j <= numcell; j++)
			if (_POINT[i][j] == 0)
				cnt++;
	if (cnt == 0)
		return 2;
	return 0;
}
void Player::draw_x() {
	// [Huy_Darkmode]
	if (opt.darkMode == 1)
		changeFontColor(black, pink);
	else
		changeFontColor(white, red);
	// [Huy_Darkmode]



	cout << "X";
}

void Player::draw_o()
{
	// [Huy_Darkmode]
	if (opt.darkMode == 1)
		changeFontColor(black, blue2);
	else
		changeFontColor(white, blue1);
	// [Huy_Darkmode]
	
	cout << "O";
}


int Player::check_huong()
{
	int x = i, y = j;
	int k = _POINT[i][j];
	//check 1
	int tmp1 = x, tmp2 = y, cnt = 1;
	for (int i = 1; i <= 6; i++)
	{
		x++;
		y--;
		if (_POINT[x][y] == k)
			cnt++;
		else
			break;
	}
	x = tmp1, y = tmp2;
	for (int i = 1; i <= 6; i++)
	{
		x--;
		y++;
		if (_POINT[x][y] == k)
			cnt++;
		else
			break;
	}
	if (cnt >= 5)
		return 1;
	// check 2
	x = tmp1, y = tmp2, cnt = 1;
	for (int i = 1; i <= 6; i++)
	{
		x--;
		y--;
		if (_POINT[x][y] == k)
			cnt++;
		else
			break;
	}
	x = tmp1, y = tmp2;
	for (int i = 1; i <= 6; i++)
	{
		x++;
		y++;
		if (_POINT[x][y] == k)
			cnt++;
		else
			break;
	}
	if (cnt >= 5)
		return 2;
	//check 3
	x = tmp1, y = tmp2, cnt = 1;
	for (int i = 1; i <= 6; i++)
	{
		x--;
		//y--;
		if (_POINT[x][y] == k)
			cnt++;
		else
			break;
	}
	x = tmp1, y = tmp2;
	for (int i = 1; i <= 6; i++)
	{
		x++;
		//y++;
		if (_POINT[x][y] == k)
			cnt++;
		else
			break;
	}
	if (cnt >= 5)
		return 3;
	// check 4;
	x = tmp1, y = tmp2, cnt = 1;
	for (int i = 1; i <= 6; i++)
	{
		//x--;
		y--;
		if (_POINT[x][y] == k)
			cnt++;
		else
			break;
	}
	x = tmp1, y = tmp2;
	for (int i = 1; i <= 6; i++)
	{
		//x++;
		y++;
		if (_POINT[x][y] == k)
			cnt++;
		else
			break;
	}
	if (cnt >= 5)
		return 4;
	return 0;
}
vector<pair<int, int>>Player::huong1()
{
	//check 1
	int x = i, y = j;
	int k = _POINT[i][j];
	//check 1
	vector<pair<int, int>>LIST_POS;
	LIST_POS.push_back({ x,y });
	int tmp1 = x, tmp2 = y, cnt = 1;
	for (int i = 1; i <= 6; i++)
	{
		x++;
		y--;
		if (_POINT[x][y] == k)
		{
			cnt++;
			LIST_POS.push_back({ x,y });
		}
		else
			break;
	}
	x = tmp1, y = tmp2;
	for (int i = 1; i <= 6; i++)
	{
		x--;
		y++;
		if (_POINT[x][y] == k)
		{
			cnt++;
			LIST_POS.push_back({ x,y });
		}
		else
			break;
	}
	return LIST_POS;
}
vector<pair<int, int>>Player::huong2()
{
	//check 1
	int x = i, y = j;
	int k = _POINT[i][j];
	//check 1
	vector<pair<int, int>>LIST_POS;
	LIST_POS.push_back({ x,y });
	int tmp1 = x, tmp2 = y, cnt = 1;
	for (int i = 1; i <= 6; i++)
	{
		x--;
		y--;
		if (_POINT[x][y] == k)
		{
			cnt++;
			LIST_POS.push_back({ x,y });
		}
		else
			break;
	}
	x = tmp1, y = tmp2;
	for (int i = 1; i <= 6; i++)
	{
		x++;
		y++;
		if (_POINT[x][y] == k)
		{
			cnt++;
			LIST_POS.push_back({ x,y });
		}
		else
			break;
	}
	return LIST_POS;
}
vector<pair<int, int>>Player::huong3()
{
	//check 1
	int x = i, y = j;
	int k = _POINT[i][j];
	//check 1
	vector<pair<int, int>>LIST_POS;
	LIST_POS.push_back({ x,y });
	int tmp1 = x, tmp2 = y, cnt = 1;
	for (int i = 1; i <= 6; i++)
	{
		x--;
		if (_POINT[x][y] == k)
		{
			cnt++;
			LIST_POS.push_back({ x,y });
		}
		else
			break;
	}
	x = tmp1, y = tmp2;
	for (int i = 1; i <= 6; i++)
	{
		x++;
		if (_POINT[x][y] == k)
		{
			cnt++;
			LIST_POS.push_back({ x,y });
		}
		else
			break;
	}
	return LIST_POS;
}
vector<pair<int, int>>Player::huong4()
{
	//check 1
	int x = i, y = j;
	int k = _POINT[i][j];
	//check 1
	vector<pair<int, int>>LIST_POS;
	LIST_POS.push_back({ x,y });
	int tmp1 = x, tmp2 = y, cnt = 1;
	for (int i = 1; i <= 6; i++)
	{
		y--;
		if (_POINT[x][y] == k)
		{
			cnt++;
			LIST_POS.push_back({ x,y });
		}
		else
			break;
	}
	x = tmp1, y = tmp2;
	for (int i = 1; i <= 6; i++)
	{
		y++;
		if (_POINT[x][y] == k)
		{
			cnt++;
			LIST_POS.push_back({ x,y });
		}
		else
			break;
	}
	return LIST_POS;
}
void Player::selectWinStreak() {
	int kind = check_huong();
	vector<pair<int, int>>tmp;
	if (kind == 1)
	{
		tmp = huong1();
	}
	else if (kind == 2)
	{
		tmp = huong2();
	}
	else if (kind == 3)
	{
		tmp = huong3();
	}
	else
	{
		tmp = huong4();
	}
	for (auto x : tmp)
	{
		COORD save = { x.second,x.first };
		winningCoord.push_back(save);
	}
}
void Player::load_board()
{
	// ve cac x o cua ban co to
	for (int i = 1; i <= numcell; i++)
	{
		for (int j = 1; j <= numcell; j++)
		{
			if (_POINT[i][j] == 1)
			{
				GotoXY(initCoor.X + (j - 1) * offSetX, initCoor.Y + (i - 1) * offSetY);
				draw_x();
			}
			else if (_POINT[i][j] == 2)
			{
				GotoXY(initCoor.X + (j - 1) * offSetX, initCoor.Y + (i - 1) * offSetY);
				draw_o();
			}
		}
	}
}
void Player::load_board_mini()
{
	// ham nay ve tran dau nho luc load game
	COORD initCoor_mini;
	initCoor_mini.X = 95;
	initCoor_mini.Y = 15;
	GotoXY(95, 13);
	if (Minimax == 1 || BruteForce == 1)
	{
		if (opt.darkMode == 1)
			changeFontColor(black, cyan);
		else
			changeFontColor(white, blue1);
		cout << "Play Mode: Bot";
	}
	else
	{
		if (opt.darkMode == 1)
			changeFontColor(black, pink);
		else
			changeFontColor(white, red);
		cout << "Play Mode: PVP";
	}
	for (int i = 1; i <= numcell; i++)
	{
		for (int j = 1; j <= numcell; j++)
		{
			if (_POINT[i][j] == 1)
			{
				GotoXY(initCoor_mini.X + (j - 1) * 2, initCoor_mini.Y + (i - 1) * 1);
				draw_x();
			}
			else if (_POINT[i][j] == 2)
			{
				GotoXY(initCoor_mini.X + (j - 1) * 2, initCoor_mini.Y + (i - 1) * 1);
				draw_o();
			}
			else
			{
				GotoXY(initCoor_mini.X + (j - 1) * 2, initCoor_mini.Y + (i - 1) * 1);
				/*changeFontColor(white, black);*/
				if (opt.darkMode == 1)
					changeFontColor(black, white);
				else
					changeFontColor(white, black);
				cout << ".";
			}
		}
	}
}

vector<string> Player::list_namesave()
{
	ifstream fi("file_game/name_saveload.txt");
	string name_saveload[100];
	int count_name = 1;
	while (getline(fi, name_saveload[count_name]))
	{
		count_name++;
	}
	vector<string>res;
	for (int i = 1; i < count_name; i++)
	{
		res.push_back(name_saveload[i]);
	}

	return res;
}
int Player::load_game()
{
	//interface

	DrawObject("Background");
	DrawObject("Border");
	DrawObject("Text_Border", 48, 120);
	GotoXY(48, 1);
	DrawObject("Saveload_Logo");
	DrawObject("CornerEsc");
	GotoXY(35, 10);
	DrawObject("Save_Board"); // [Saber]
	COORD boardPos;
	boardPos.X = 35;
	boardPos.Y = 10;

	COORD ptrInit = boardPos;
	ptrInit.X += 5;
	ptrInit.Y += 3;

	GotoXY(ptrInit.X, ptrInit.Y);
	cout << ">>";

	int offset = 3;

	int xconsole = boardPos.X + 10, yconsole = boardPos.Y + 3;
	vector<string> temp = list_namesave();
	int count_name = temp.size();
	if (count_name == 0)
	{
		bool _checkNotEnter = true, _checkEsc = false;
		while (_checkNotEnter) {
			if (_kbhit())
			{
				char ch = _getch();
				if (ch == 27)
				{
					_checkEsc = true;
					_checkNotEnter = false;
				}
			}
		}
		if (!_checkEsc) {
			return 1;
		}
		return 0;
	}
	int ptrId = 0, max_id = 7, current_max_id;
	int current_count = 6;
	
	current_max_id = min(count_name, max_id);
	for (int i = 0; i < current_max_id; i++)
	{
		GotoXY(xconsole, yconsole + offset * i);
		cout << i + 1 << ") " << temp[i];
	}

	//print_list_name();

	ifstream ci("file_game/" + temp[0]);
	ci >> BruteForce >> Minimax >> type >> current_player >> TimeMode >> set_time;
	for (int i = 1; i <= numcell; i++)
		for (int j = 1; j <= numcell; j++)
			ci >> _POINT[i][j];

	name_repeat_load = temp[0];
	ci.close();
	load_board_mini();
	bool _checkNotEnter = true, _checkEsc = false;
	while (_checkNotEnter) {
		if (_kbhit())
		{
			char ch = _getch();
			if (ch == 'a' || ch == 'w')
			{
				if (ptrId == 0 && current_count - 6 > 0)
				{
					current_count--;
					for (int i = 0; i < current_max_id; i++)
					{
						GotoXY(xconsole, yconsole + offset * i);
						cout << string(35, ' ');
					}
					for (int i = current_count - 6; i <= current_count; i++)
					{
						GotoXY(xconsole, yconsole + offset * (i - (current_count - 6)));
						cout << i + 1 << ") " << temp[i];
					}
					GotoXY(ptrInit.X, ptrInit.Y + ptrId * offset);
					cout << "  ";
					GotoXY(ptrInit.X, ptrInit.Y + ptrId * offset);
					if (opt.darkMode == 1)
						changeFontColor(black, white);
					else
						changeFontColor(white, black);
					cout << ">>";
				}
				GotoXY(ptrInit.X, ptrInit.Y + ptrId * offset);
				cout << "  ";
				ptrId = max(0, ptrId - 1);
				/*current_count = ptrId;*/
				GotoXY(ptrInit.X, ptrInit.Y + ptrId * offset);
				if (opt.darkMode == 1)
					changeFontColor(black, white);
				else
					changeFontColor(white, black);
				cout << ">>";
			}
			if (ch == 's' || ch == 'd')
			{
				if (ptrId == 6 && current_count + 1 < count_name)
				{
					current_count++;
					for (int i = 0; i < current_max_id; i++)
					{
						GotoXY(xconsole, yconsole + offset * i);
						cout << string(35, ' ');
					}
					for (int i = current_count - 6 ; i <= current_count; i++)
					{
						GotoXY(xconsole, yconsole + offset * (i- (current_count-6)));
						cout << i + 1 << ") " << temp[i];
					}
					GotoXY(ptrInit.X, ptrInit.Y + ptrId * offset);
					cout << "  ";
					//ptrId = max(0, ptrId - 1);
					GotoXY(ptrInit.X, ptrInit.Y + ptrId * offset);
					if (opt.darkMode == 1)
						changeFontColor(black, white);
					else
						changeFontColor(white, black);
					cout << ">>";
				}
				if (!(ptrId == 6 && current_count + 1 == count_name))
				{
					GotoXY(ptrInit.X, ptrInit.Y + ptrId * offset);
					cout << "  ";
					ptrId = min(max(current_max_id - 1, 0), ptrId + 1);
					//current_count = ptrId;
					GotoXY(ptrInit.X, ptrInit.Y + ptrId * offset);
					if (opt.darkMode == 1)
						changeFontColor(black, white);
					else
						changeFontColor(white, black);
					cout << ">>";
				}
			
			}
			if (ch == 13)
			{
				_checkNotEnter = false;
			}
			if (ch == 27)
			{
				_checkEsc = true;
				_checkNotEnter = false;
			}
			if (ch == 'x')//delete
			{
				if (count_name <= 0)
					continue;
				std::filesystem::remove("file_game/" + temp[current_count - 6 + ptrId]);
				name_repeat_load = temp[current_count - 6 + ptrId];
				update_namegame();
				for (int i = 0; i < current_max_id; i++)
				{
					GotoXY(xconsole, yconsole + offset * i);
					cout << string(35, ' ');
				}
				temp = list_namesave();
				count_name = temp.size();
				current_max_id = min(count_name, max_id);
				for (int i = 0; i < current_max_id; i++)
				{
					GotoXY(xconsole, yconsole + offset * i);
					cout << i + 1 << ") " << temp[i];
				}
				GotoXY(ptrInit.X, ptrInit.Y + ptrId * offset);
				cout << "  ";
				if(current_count>6)
					current_count--;
				if(ptrId == 6 && count_name >=7)
					ptrId = max(0, ptrId + 1);
				ptrId = max(0, ptrId - 1);
				GotoXY(ptrInit.X, ptrInit.Y + ptrId * offset);
				if (opt.darkMode == 1)
					changeFontColor(black, white);
				else
					changeFontColor(white, black);
				cout << ">>";
				if (count_name == 0) // ve lai bang mini
				{
					COORD initCoor_mini;
					initCoor_mini.X = 95;
					initCoor_mini.Y = 15;
					GotoXY(95, 13);
					if (opt.darkMode == 1)
						changeFontColor(black, cyan);
					else
						changeFontColor(white, blue1);
					cout << "                     ";
					for (int i = 1; i <= numcell; i++)
					{
						for (int j = 1; j <= numcell; j++)
						{
							
							GotoXY(initCoor_mini.X + (j - 1) * 2, initCoor_mini.Y + (i - 1) * 1);
							/*changeFontColor(white, black);*/
							if (opt.darkMode == 1)
								changeFontColor(black, white);
							else
								changeFontColor(white, black);
							cout << " ";
							
						}
					}
				}
			}
			if (count_name <= 0)
				continue;
			ifstream ci("file_game/" + temp[current_count-6+ptrId]);
			ci >> BruteForce >> Minimax >> type >> current_player>>TimeMode>>set_time;
			for (int i = 1; i <= numcell; i++)
				for (int j = 1; j <= numcell; j++)
					ci >> _POINT[i][j];

			name_repeat_load = temp[current_count - 6 + ptrId];
			ci.close();
			load_board_mini();
		}
	}
	
	if (!_checkEsc) {
		return 1;
	}	
	return 0;
}
void Player::update_namegame()
{

	ifstream fi("file_game/name_saveload.txt");
	string name_saveload[100];
	int count_name = 1;
	while (getline(fi, name_saveload[count_name]))
	{
		count_name++;
	}
	fi.close();
	ofstream fo_nsave("file_game/name_saveload.txt");
	for (int i = 1; i <= count_name; i++)
	{
		if (name_saveload[i] != name_repeat_load && name_saveload[i].size() != 0)
			fo_nsave << name_saveload[i] << "\n";
	}
	fo_nsave.close();
	std::filesystem::remove("file_game/" + name_repeat_load);
}
string check_name_save(string name_saveload,vector<string>temp)
{
	int check_space = 0;
	for (int i = 0; i < name_saveload.size(); i++)
		if (name_saveload[i] != ' ')
		{
			check_space = 1;
		}
	if (check_space == 0)
	{
		return "loi_all_space";
	}
	for (int i = 0; i < temp.size(); i++)
	{
		if (name_saveload == temp[i])
			return "loi_trung_ten";
	}
	return "ok";
}
void Player::save_game()
{
	vector<string> temp = list_namesave();
	if (check_saveload == 1) // neu nhu file duoc mo tu load thi se khong can nhap ten 
	{
		string name_saveload = name_repeat_load;   // gan ten bang ten luc load vao
		ofstream fo("file_game/" + name_saveload);

		// luu lai bang
		fo << BruteForce << " " << Minimax << " " << type << " " << current_player << " "<<TimeMode<<" "<<set_time<<'\n';
		for (int i = 1; i <= numcell; i++)
		{
			for (int j = 1; j <= numcell; j++)
				fo << _POINT[i][j] << " ";
			fo << "\n";
		}
		fo.close();
		ofstream fo_nsave("file_game/name_saveload.txt");

		// danh sach cac name file de load ra :))
		fo_nsave << name_saveload << '\n';
		for (int i = 0; i < temp.size(); i++)
			if(name_saveload!=temp[i])
				fo_nsave << temp[i] << "\n";
		fo_nsave.close();
		return;
	}
	// truong hop mo game PLAY 
	// can dat ten game

	//interface
	DrawObject("Background");
	DrawObject("Border");
	DrawObject("Text_Border", 48, 120);
	GotoXY(48, 1);
	DrawObject("Save_Logo");
	DrawObject("CornerEsc");
	COORD boardPos;
	boardPos.X = 35;
	boardPos.Y = 10;

	COORD ptrInit = boardPos;
	ptrInit.X += 5;
	ptrInit.Y += 3;

	GotoXY(ptrInit.X, ptrInit.Y);

	int offset = 3;

	int xconsole = boardPos.X + 10, yconsole = boardPos.Y + 3;
	int count_name = temp.size();
	int ptrId = 0, max_id = 7, current_max_id;

	current_max_id = min(count_name, max_id);
	for (int i = 0; i < current_max_id; i++)
	{
		GotoXY(xconsole, yconsole + offset * i);
		cout << i + 1 << ") " << temp[i];
	}

	GotoXY(35, 10);
	DrawObject("Save_Board"); // [Saber]
	///


	// cai bang nho luc load game 
	load_board_mini(); 
	int position_x_save = xconsole + 19 , position_y_save = yconsole + offset * 7 -1 ; //15
	GotoXY(xconsole, position_y_save);
	//


	cout << "Enter FILE's name: ";  // 20
	bool _checkNotEnter = true, _checkEsc = false;
	string name_saveload = "";
	while (_checkNotEnter) {
		if (_kbhit())
		{
			char ch = _getch();
			// chi cho luu nhung ki tu 
			if ((ch >= 'A' && ch <= 'Z') || (ch == ' ') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9'))
			{	
				if (name_saveload.size() <= 20)
				{
					name_saveload += ch;
					if (opt.darkMode == 1)
						changeFontColor(black, white);
					else
						changeFontColor(white, black);
					cout << ch;
				}
			}
			// nhan nut backspace 
			if (ch == 8)
			{
				if (name_saveload.size() >= 1)
				{
					
					name_saveload.erase(name_saveload.size() - 1, 1); //xoa di ki tu cuoi
					// xoa khoang trang
					GotoXY(position_x_save, position_y_save);
					if (opt.darkMode == 1)
						changeFontColor(black, black);
					else
						changeFontColor(white, white);
					cout << string(21,' ');
					if (opt.darkMode == 1)
						changeFontColor(black, white);
					else
						changeFontColor(white, black);
					GotoXY(position_x_save, position_y_save);
					// in ra lai name sau khi xoa ki tu cuoi
					cout << name_saveload;

					//lam nhu nay cho de xu li
				}
			}
			if (ch == 13) // khi nhan nut enter
			{
				string tmp = check_name_save(name_saveload, temp);// kiem tra cac truong hop
				if (tmp=="ok") //name thoa man khong van de :))
				{
					_checkNotEnter = false;
				}
				else // name co loi 
				{
					// xuong dong duoi nhap ten FILE va xoa cac ki tu
					GotoXY(xconsole, position_y_save+1);
					if (opt.darkMode == 1)
						changeFontColor(black, black);
					else
						changeFontColor(white, white);
					cout << string(35, ' ');
					if (opt.darkMode == 1)
						changeFontColor(black, pink);
					else
						changeFontColor(white, red);
					
					// tien hanh in cac loi
					GotoXY(xconsole, position_y_save + 1);
					if (tmp == "loi_all_space")
					{
						cout << "The file name cannot be empty!";	
					}
					else
					{
						cout << "The file name has been duplicated!";
					}
					
					// reset name de cho nhap lai day
					name_saveload = "";
					GotoXY(position_x_save, position_y_save);
					if (opt.darkMode == 1)
						changeFontColor(black, black);
					else
						changeFontColor(white, white);
					cout << string(21, ' ');
					GotoXY(position_x_save, position_y_save);
					if (opt.darkMode == 1)
						changeFontColor(black, white);
					else
						changeFontColor(white, black);
				}
			}
			if (ch == 27)
			{
				// nhan nut esc

				// choi tiep tuc tran dau dang do
				DrawObject("Background");
				DrawObject("Border");
				DrawObject("PlayerFrame"); // built-in coor for player frame
				GotoXY(52, 3);
				DrawObject("BoardCanvas");
				load_board();
				ShowConsoleCursor(true);
				if (type == 0)
				{
					play();
				}
				_checkEsc = true;
				_checkNotEnter = false;
			}
		}
	}

	// xoa cac khoang trang dau, chuan hoa name_save
	while (name_saveload.size() >= 1 && name_saveload[0] == ' ')
		name_saveload.erase(0, 1);

	//luu lai bang
	ofstream fo("file_game/" + name_saveload);
	fo << BruteForce << " " << Minimax << " " << type << " " << current_player << " "<<TimeMode<<" "<<set_time<<'\n';
	for (int i = 1; i <= numcell; i++)
	{
		for (int j = 1; j <= numcell; j++)
			fo << _POINT[i][j] << " ";
		fo << "\n";
	}
	fo.close();

	//in ra cac ten file luu trong name_saveload.txt
	ofstream fo_nsave("file_game/name_saveload.txt");
	fo_nsave << name_saveload << '\n';
	for (int i = 0; i < temp.size(); i++)
		fo_nsave << temp[i] << "\n";
	fo_nsave.close();

}
const string directoryPath = "./file_game";

void create_saved_games_folder() {
	if (!std::filesystem::exists(directoryPath)) {
		std::filesystem::create_directory(directoryPath);
		return;
	}
	else {
		return;
	}
}
/// <summary>
/// minimax area
/// </summary>

int winScore = INT_MAX;
int AttackPoint_List[] = { 0,16,670,11000,200000,200000 ,200000 ,200000 };
int DefendPoint_List[] = { 0,5,210,2700,45000,45000 ,45000 ,45000 };//
int BlockedAttackPoint_List[] = { 0,1,50, 440,200000,200000 ,200000 ,200000 }; //
int BlockedDefendPoint_List[] = { 0,1,5,290,45000,45000,45000 ,45000 };//,

vector<pair<int, int> > Player::area(int ex)
{
	vector<pair<int, int>>list_erea;
	int d[100][100];
	memset(d, 0, sizeof(d));
	for (pair<int, int>tmp : history)
	{
		int l1 = tmp.first - ex;
		int r1 = tmp.second - ex;
		int l2 = tmp.first + ex;
		int r2 = tmp.second + ex;
		if (l1 < 1)
			l1 = 1;
		if (r1 < 1)
			r1 = 1;
		if (l2 > numcell)
			l2 = numcell;
		if (r2 > numcell)
			r2 = numcell;
	
		for (int i = l1; i <= l2; i++)
		{
			for (int j = r1; j <= r2; j++)
			{
				if (i >= 1 && i <= numcell && j >= 1 && j <= numcell && _POINT[i][j] == 0 && d[i][j] == 0)
				{
					list_erea.push_back({ i,j });
					d[i][j] = 1;
				}
			}
		}
	}
	return list_erea;
}
int Player::AttackPoint_Horizontal(int nline,int ncolumn,int player)
{
	int res = 0;
	int phe_minh = 1;
	int phe_dich = 0;
	int tmp = 0;
	for (int cnt = 1; cnt < 7 && nline + cnt <= numcell + 1; cnt++)
	{
		if (_POINT[nline + cnt][ncolumn] == player)
		{
			phe_minh++;
		}
		else if (nline+cnt==numcell+1)
		{
			phe_dich++;
			break;
		}
		else if (_POINT[nline + cnt][ncolumn] == 0)
		{
			if (cnt == 1)
			{
				tmp++;
				continue;
			}
			break;
		}
		else
		{
			phe_dich++;
			break;
		}
	}
	// nguoc lai
	for (int cnt = 1; cnt < 7 && nline - cnt >=  0; cnt++)
	{
		if (_POINT[nline - cnt][ncolumn] == player)
		{
			phe_minh++;
		}
		else if (nline - cnt == 0)
		{
			phe_dich++;
			break;
		}
		else if (_POINT[nline - cnt][ncolumn] == 0)
		{
			if (cnt == 1)
			{
				tmp++;
				continue;
			}
			break;
		}
		else
		{
			phe_dich++;
			break;
		}
	}

	if (phe_dich == 2)
		return 0;
	if (phe_dich == 1)
	{
		res += BlockedAttackPoint_List[phe_minh];
	}
	else
	{
		res += AttackPoint_List[phe_minh];
	}
	return res;
}
int Player::AttackPoint_Vertical(int nline, int ncolumn, int player)
{
	int res = 0;
	int phe_minh = 1;
	int phe_dich = 0;
	int tmp = 0;
	for (int cnt = 1; cnt < 7 && nline + cnt <= numcell + 1; cnt++)
	{
		if (_POINT[nline ][ncolumn + cnt] == player)
		{
			phe_minh++;
		}
		else if (ncolumn + cnt == numcell + 1)
		{
			phe_dich++;
			break;
		}
		else if (_POINT[nline][ncolumn + cnt] == 0)
		{
			if (cnt == 1)
			{
				tmp++;
				continue;
			}
			break;
		}
		else
		{
			phe_dich++;
			break;
		}
	}
	// nguoc lai
	for (int cnt = 1; cnt < 7 && nline - cnt >= 0; cnt++)
	{
		if (_POINT[nline][ncolumn - cnt] == player)
		{
			phe_minh++;
		}
		else if (ncolumn - cnt == 0)
		{
			phe_dich++;
			break;
		}
		else if (_POINT[nline][ncolumn - cnt] == 0)
		{
			if (cnt == 1)
			{
				tmp++;
				continue;
			}
			break;
		}
		else
		{
			phe_dich++;
			break;
		}
	}
	if (phe_dich == 2)
		return 0;
	if (phe_dich == 1)
	{
		res += BlockedAttackPoint_List[phe_minh];
	}
	else
	{
		res += AttackPoint_List[phe_minh];
	}
	return res;
}
int Player::AttackPoint_Diagonal1(int nline, int ncolumn, int player)
{
	int res = 0;
	int phe_minh = 1;
	int phe_dich = 0;
	int tmp = 0;
	for (int cnt = 1; cnt < 7 && nline + cnt <= numcell + 1; cnt++)
	{
		if (_POINT[nline - cnt][ncolumn + cnt] == player)
		{
			phe_minh++;
		}
		else if (ncolumn + cnt == numcell + 1 || nline - cnt == 0)
		{
			phe_dich++;
			break;
		}
		else if (_POINT[nline - cnt][ncolumn + cnt] == 0)
		{
			if (cnt == 1)
			{
				tmp++;
				continue;
			}
			break;
		}
		else
		{
			phe_dich++;
			break;
		}
	}
	// nguoc lai
	for (int cnt = 1; cnt < 7 && nline - cnt >= 0; cnt++)
	{
		if (_POINT[nline +  cnt][ncolumn - cnt] == player)
		{
			phe_minh++;
		}
		else if (ncolumn - cnt == 0 || nline + cnt == numcell+1)
		{
			phe_dich++;
			break;
		}
		else if (_POINT[nline + cnt ][ncolumn - cnt] == 0)
		{
			if (cnt == 1)
			{
				tmp++;
				continue;
			}
			break;
		}
		else
		{
			phe_dich++;
			break;
		}
	}
	if (phe_dich == 2)
		return 0;
	if (phe_dich == 1)
	{
		res += BlockedAttackPoint_List[phe_minh];
	}
	else
	{
		res += AttackPoint_List[phe_minh];
	}
	return res;
}
int Player::AttackPoint_Diagonal2(int nline, int ncolumn, int player)
{
	int res = 0;
	int phe_minh = 1;
	int phe_dich = 0;
	int tmp = 0;
	for (int cnt = 1; cnt < 7 && nline + cnt <= numcell + 1; cnt++)
	{
		if (_POINT[nline - cnt][ncolumn - cnt] == player)
		{
			phe_minh++;
		}
		else if (ncolumn - cnt == 0 || nline - cnt == 0)
		{
			phe_dich++;
			break;
		}
		else if (_POINT[nline - cnt][ncolumn - cnt] == 0)
		{
			if (cnt == 1)
			{
				tmp++;
				continue;
			}
			break;
		}
		else
		{
			phe_dich++;
			break;
		}
	}
	// nguoc lai
	for (int cnt = 1; cnt < 7 && nline - cnt >= 0; cnt++)
	{
		if (_POINT[nline + cnt][ncolumn + cnt] == player)
		{
			phe_minh++;
		}
		else if (ncolumn + cnt == numcell + 1 || nline + cnt == numcell + 1)
		{
			phe_dich++;
			break;
		}
		else if (_POINT[nline + cnt][ncolumn + cnt] == 0)
		{
			if (cnt == 1)
			{
				tmp++;
				continue;
			}
			break;
		}
		else
		{
			phe_dich++;
			break;
		}
	}
	if (phe_dich == 2)
		return 0;
	if (phe_dich == 1)
	{
		res += BlockedAttackPoint_List[phe_minh];
	}
	else
	{
		res += AttackPoint_List[phe_minh];
	}
	return res;
}
int Player::DefendPoint_Horizontal(int nline,int ncolumn,int player)
{
	int res = 0;
	int phe_minh = 0;
	int phe_dich = 1;
	int tmp = 0;
	for (int cnt = 1; cnt < 7 && nline + cnt <= numcell + 1; cnt++)
	{
		if (_POINT[nline + cnt][ncolumn] == player)
		{
			phe_minh++;
			break;
		}
		else if (nline + cnt == numcell + 1)
		{
			phe_minh++;
			break;
		}
		else if (_POINT[nline + cnt][ncolumn] == 0)
		{
			if (cnt == 1)
			{
				tmp++;
				continue;
			}
			break;
		}
		else
		{
			phe_dich++;
		}
	}
	// nguoc lai
	for (int cnt = 1; cnt < 7 && nline - cnt >= 0; cnt++)
	{
		if (_POINT[nline - cnt][ncolumn] == player)
		{
			phe_minh++;
			break;
		}
		else if (nline - cnt == 0)
		{
			phe_minh++;
			break;
		}
		else if (_POINT[nline - cnt][ncolumn] == 0)
		{
			if (cnt == 1)
			{
				tmp++;
				continue;
			}
			break;
		}
		else
		{
			phe_dich++;
		}
	}
	if (phe_minh == 2)
		return 0;
	if (phe_minh == 1)
	{
		res +=BlockedDefendPoint_List[phe_dich];
	}
	else
	{
		res += DefendPoint_List[phe_dich];
	}
	return res;
}
int Player::DefendPoint_Vertical(int nline, int ncolumn, int player)
{
	int res = 0;
	int phe_minh = 0;
	int phe_dich = 1;
	int tmp = 0;
	for (int cnt = 1; cnt < 7 && nline + cnt <= numcell + 1; cnt++)
	{
		if (_POINT[nline][ncolumn + cnt] == player)
		{
			phe_minh++;
			break;
		}
		else if (ncolumn + cnt == numcell + 1)
		{
			phe_minh++;
			break;
		}
		else if (_POINT[nline][ncolumn + cnt ] == 0)
		{
			if (cnt == 1)
			{
				tmp++;
				continue;
			}
			break;
		}
		else
		{
			phe_dich++;
		}
	}
	// nguoc lai
	for (int cnt = 1; cnt < 7 && nline - cnt >= 0; cnt++)
	{
		if (_POINT[nline][ncolumn - cnt] == player)
		{
			phe_minh++;
			break;
		}
		else if (ncolumn - cnt == 0)
		{
			phe_minh++;
			break;
		}
		else if (_POINT[nline][ncolumn - cnt ] == 0)
		{
			if (cnt == 1)
			{
				tmp++;
				continue;
			}
			break;
		}
		else
		{
			phe_dich++;
		}
	}
	if (phe_minh == 2)
		return 0;
	if (phe_minh == 1)
	{
		res += BlockedDefendPoint_List[phe_dich];
	}
	else
	{
		res += DefendPoint_List[phe_dich];
	}
	return res;
}
int Player::DefendPoint_Diagonal1(int nline, int ncolumn, int player)
{
	int res = 0;
	int phe_minh = 0;
	int phe_dich = 1;
	int tmp = 0;
	for (int cnt = 1; cnt < 7 && nline + cnt <= numcell + 1; cnt++)
	{
		if (_POINT[nline - cnt ][ncolumn + cnt] == player)
		{
			phe_minh++;
			break;
		}
		else if (ncolumn + cnt == numcell + 1 || nline - cnt == 0)
		{
			phe_minh++;
			break;
		}
		else if (_POINT[nline - cnt ][ncolumn + cnt] == 0)
		{
			if (cnt == 1)
			{
				tmp++;
				continue;
			}
			break;
		}
		else
		{
			phe_dich++;
		}
	}
	// nguoc lai
	for (int cnt = 1; cnt < 7 && nline - cnt >= 0; cnt++)
	{
		if (_POINT[nline + cnt ][ncolumn - cnt] == player)
		{
			phe_minh++;
			break;
		}
		else if (ncolumn - cnt == 0 || ncolumn + cnt == numcell +1 )
		{
			phe_minh++;
			break;
		}
		else if (_POINT[nline + cnt ][ncolumn - cnt] == 0)
		{
			if (cnt == 1)
			{
				tmp++;
				continue;
			}
			break;
		}
		else
		{
			phe_dich++;
		}
	}
	if (phe_minh == 2)
		return 0;
	if (phe_minh == 1)
	{
		res += BlockedDefendPoint_List[phe_dich];
	}
	else
	{
		res += DefendPoint_List[phe_dich];
	}
	return res;
}
int Player::DefendPoint_Diagonal2(int nline, int ncolumn, int player)
{
	int res = 0;
	int phe_minh = 0;
	int phe_dich = 1;
	int tmp = 0;
	for (int cnt = 1; cnt < 7 && nline + cnt <= numcell + 1; cnt++)
	{
		if (_POINT[nline + cnt][ncolumn + cnt] == player)
		{
			phe_minh++;
			break;
		}
		else if (ncolumn + cnt == numcell + 1 || nline + cnt == numcell)
		{
			phe_minh++;
			break;
		}
		else if (_POINT[nline + cnt][ncolumn + cnt] == 0)
		{
			if (cnt == 1)
			{
				tmp++;
				continue;
			}
			break;
		}
		else
		{
			phe_dich++;
		}
	}
	// nguoc lai
	for (int cnt = 1; cnt < 7 && nline - cnt >= 0; cnt++)
	{
		if (_POINT[nline - cnt][ncolumn - cnt] == player)
		{
			phe_minh++;
			break;
		}
		else if (ncolumn - cnt == 0 || ncolumn - cnt == 0)
		{
			phe_minh++;
			break;
		}
		else if (_POINT[nline - cnt][ncolumn - cnt] == 0)
		{
			if (cnt == 1)
			{
				tmp++;
				continue;
			}
			break;
		}
		else
		{
			phe_dich++;
		}
	}
	if (phe_minh == 2)
		return 0;
	if (phe_minh == 1)
	{
		res += BlockedDefendPoint_List[phe_dich];
	}
	else
	{
		res += DefendPoint_List[phe_dich];
	}
	return res;
}

int Player::check_4_huong(int i,int j)
{
	int x = i, y = j;
	int k = _POINT[i][j];
	//check 1
	int tmp1 = x, tmp2 = y, cnt = 1;
	for (int i = 1; i <= 6; i++)
	{
		x++;
		y--;
		if (_POINT[x][y] == k)
			cnt++;
		else
			break;
	}
	x = tmp1, y = tmp2;
	for (int i = 1; i <= 6; i++)
	{
		x--;
		y++;
		if (_POINT[x][y] == k)
			cnt++;
		else
			break;
	}
	if (cnt >= 5)
		return 1;
	// check 2
	x = tmp1, y = tmp2, cnt = 1;
	for (int i = 1; i <= 6; i++)
	{
		x--;
		y--;
		if (_POINT[x][y] == k)
			cnt++;
		else
			break;
	}
	x = tmp1, y = tmp2;
	for (int i = 1; i <= 6; i++)
	{
		x++;
		y++;
		if (_POINT[x][y] == k)
			cnt++;
		else
			break;
	}
	if (cnt >= 5)
		return 2;
	//check 3
	x = tmp1, y = tmp2, cnt = 1;
	for (int i = 1; i <= 6; i++)
	{
		x--;
		//y--;
		if (_POINT[x][y] == k)
			cnt++;
		else
			break;
	}
	x = tmp1, y = tmp2;
	for (int i = 1; i <= 6; i++)
	{
		x++;
		//y++;
		if (_POINT[x][y] == k)
			cnt++;
		else
			break;
	}
	if (cnt >= 5)
		return 3;
	// check 4;
	x = tmp1, y = tmp2, cnt = 1;
	for (int i = 1; i <= 6; i++)
	{
		//x--;
		y--;
		if (_POINT[x][y] == k)
			cnt++;
		else
			break;
	}
	x = tmp1, y = tmp2;
	for (int i = 1; i <= 6; i++)
	{
		//x++;
		y++;
		if (_POINT[x][y] == k)
			cnt++;
		else
			break;
	}
	if (cnt >= 5)
		return 4;
	return 0;
}

int Player::cal_mark()
{
	int ans = 0;
	for (pair<int, int>tmp : history)
	{
		int attack = 0, defend = 0;
		//if (_POINT[tmp.first][tmp.second] != _POINT[tmp.first -1 ][tmp.second + 1])
		//{
		//	attack = attack + AttackPoint_Diagonal1(tmp.first, tmp.second, _POINT[tmp.first][tmp.second]);
		//	defend = defend + DefendPoint_Diagonal1(tmp.first, tmp.second, _POINT[tmp.first][tmp.second]);
		//}
		//	
		//if (_POINT[tmp.first][tmp.second] != _POINT[tmp.first - 1][tmp.second - 1])
		//{
		//	attack = attack + AttackPoint_Diagonal2(tmp.first, tmp.second, _POINT[tmp.first][tmp.second]);
		//	defend = defend + DefendPoint_Diagonal2(tmp.first, tmp.second, _POINT[tmp.first][tmp.second]);
		//}
		//	
		//if (_POINT[tmp.first][tmp.second] != _POINT[tmp.first - 1][tmp.second])
		//{
		//	attack = attack + AttackPoint_Horizontal(tmp.first, tmp.second, _POINT[tmp.first][tmp.second]);
		//	defend = defend + DefendPoint_Horizontal(tmp.first, tmp.second, _POINT[tmp.first][tmp.second]);
		//}	
		//if (_POINT[tmp.first][tmp.second] != _POINT[tmp.first][tmp.second - 1])
		//{
		//	attack = attack + AttackPoint_Vertical(tmp.first, tmp.second, _POINT[tmp.first][tmp.second]);
		//	defend = defend + DefendPoint_Vertical(tmp.first, tmp.second, _POINT[tmp.first][tmp.second]);
		//}

		attack = attack + AttackPoint_Diagonal1(tmp.first, tmp.second, _POINT[tmp.first][tmp.second]);
		defend = defend + DefendPoint_Diagonal1(tmp.first, tmp.second, _POINT[tmp.first][tmp.second]);
		attack = attack + AttackPoint_Diagonal2(tmp.first, tmp.second, _POINT[tmp.first][tmp.second]);
		defend = defend + DefendPoint_Diagonal2(tmp.first, tmp.second, _POINT[tmp.first][tmp.second]);
		attack = attack + AttackPoint_Horizontal(tmp.first, tmp.second, _POINT[tmp.first][tmp.second]);
		defend = defend + DefendPoint_Horizontal(tmp.first, tmp.second, _POINT[tmp.first][tmp.second]);
		attack = attack + AttackPoint_Vertical(tmp.first, tmp.second, _POINT[tmp.first][tmp.second]);
		defend = defend + DefendPoint_Vertical(tmp.first, tmp.second, _POINT[tmp.first][tmp.second]);

		if(_POINT[tmp.first][tmp.second]==2)
			ans += max(attack, defend);
		else
			ans -=	max(attack , defend);
	}
	return ans;
}

int Player::kt_win()
{
	for (pair<int, int>tmp : history)
	{
		if (check_4_huong(tmp.first, tmp.second))
			_POINT[tmp.first][tmp.second];
	}
	return 0;
}

int Player::minimax(int depth, int alpha, int beta, int minimax_player)
{
	int type_win = kt_win();
	if (type_win == 1)
		return -winScore;
	if(type_win == 2)
		return winScore;

	if (depth == 0)
	{
		return cal_mark();
	}
	if (minimax_player == 1)
	{
		int maxEval = INT_MIN;
		vector<pair<int, int>>area_list = area(1);
		for (int k=0;k<area_list.size();k++)
		{
			int i = area_list[k].first;
			int j = area_list[k].second;

			if (_POINT[i][j] != 0)
				continue;
			_POINT[i][j] = 2;
			history.push_back({ i,j });
			int eval = minimax(depth - 1, alpha, beta, 0);
			maxEval = max(maxEval, eval);
			alpha = max(alpha, eval);
			history.pop_back();
			_POINT[i][j] = 0;
			if (alpha >= beta)
				break;
			
		}
		return maxEval;
	}
	else
	{
		int minEval = INT_MAX;
		vector<pair<int, int>>area_list = area(1);
		for (int k = 0; k < area_list.size(); k++)
		{
			int i = area_list[k].first;
			int j = area_list[k].second;
			if (_POINT[i][j] != 0)
				continue;
			_POINT[i][j] = 1;
			history.push_back({ i,j });
			int eval = minimax(depth - 1, alpha, beta, 1);
			minEval = min(minEval, eval);
			beta = min(beta, eval);
			history.pop_back();
			_POINT[i][j] = 0;
			if (alpha >= beta)
				break;
		}
		return minEval;
	}
}

pair<int, int> Player::find_best_move()
{
	for (int i = 1; i <= numcell; i++)
	{
		for (int j = 1; j <= numcell; j++)
		{
			if (_POINT[i][j] != 0)
				continue;
			_POINT[i][j] = 2;
			if (check_4_huong(i, j))
				return { i,j };
			_POINT[i][j] = 0;
		}
	}
	for (int i = 1; i <= numcell; i++)
	{
		for (int j = 1; j <= numcell; j++)
		{
			if (_POINT[i][j] != 0)
				continue;
			_POINT[i][j] = 1;
			if (check_4_huong(i, j))
				return { i,j };
			_POINT[i][j] = 0;
		}
	}
	int ans = INT_MIN;
	pair<int, int>best_move;
	vector<pair<int, int>>area_list = area(1);
	for (int k = 0; k < area_list.size(); k++)
	{
		int i = area_list[k].first;
		int j = area_list[k].second;
		if (_POINT[i][j] == 0)
		{
			_POINT[i][j] = 2;
			history.push_back({ i,j });
			int tmp = minimax(Minimax, INT_MIN, INT_MAX, 0);
			history.pop_back();
			_POINT[i][j] = 0;
			if (tmp > ans)
			{
				ans = tmp;
				best_move = { i,j };
			}
		}
	}
	return best_move;
}

void Player:: init_time()
{
	int position = 52,position_y=37;
	GotoXY(position, position_y);
	position += 22;
	cout << "Enter time limit (s): ";
	set_time = 0;
	bool _checkNotEnter = true, _checkEsc = false;
	while (_checkNotEnter) {
		if (_kbhit())
		{
			char ch = _getch();
			// chi cho luu nhung ki tu 
			if ((ch >= '0' && ch <= '9'))
			{
				if (set_time < 100)
				{
					set_time = set_time * 10 + (ch - 48);

					GotoXY(position, position_y);
					if (opt.darkMode == 1)
						changeFontColor(black, white);
					else
						changeFontColor(white, black);
					cout << string(10, ' ');
					GotoXY(position, position_y);
					if (opt.darkMode == 1)
						changeFontColor(black, white);
					else
						changeFontColor(white, black);
					if (set_time > 0)
						cout << set_time;
				}
			}
			if (ch == 8)
			{
				if (set_time > 0)
				{
					set_time /= 10;
					GotoXY(position, position_y);
					if (opt.darkMode == 1)
						changeFontColor(black, white);
					else
						changeFontColor(white, black);
					cout << string(10, ' ');
					GotoXY(position, position_y);
					if (opt.darkMode == 1)
						changeFontColor(black, white);
					else
						changeFontColor(white, black);
					if (set_time > 0)
						cout << set_time;
				}
			}
			if (ch == 13)
			{
				if (set_time >=10)
					_checkNotEnter = false;
			}
		}
	}
	GotoXY(position-22, position_y);
	if (opt.darkMode == 1)
		changeFontColor(black, white);
	else
		changeFontColor(white, black);
	cout << string(30, ' ');
}
void Player::print_time()
{
	if (current_player == 1)
	{
		GotoXY(25, 15);
		if (opt.darkMode == 1)
			changeFontColor(black, white);
		else
			changeFontColor(white, black);
		cout << string(5, ' ');


		GotoXY(25, 15);
		if (opt.darkMode == 1)
			changeFontColor(black, white);
		else
			changeFontColor(white, black);
		if (set_time - milliseconds_as_int / 1000 <= 10)
		{
			if (opt.darkMode == 1)
				changeFontColor(black, red);
			else
				changeFontColor(white, red);
			PlaySound(TEXT("SOUND GAME CARO\\keyboard\\time.wav"), NULL, SND_ASYNC | opt.vfxFlag);
		}
		cout << set_time - milliseconds_as_int / 1000;

		GotoXY(140, 15);
		if (opt.darkMode == 1)
			changeFontColor(black, white);
		else
			changeFontColor(white, black);
		cout << set_time;
	}
	else
	{
		GotoXY(140, 15);
		if (opt.darkMode == 1)
			changeFontColor(black, white);
		else
			changeFontColor(white, black);
		cout << string(5, ' ');

		GotoXY(140, 15);
		if (opt.darkMode == 1)
			changeFontColor(black, white);
		else
			changeFontColor(white, black);
		if (set_time - milliseconds_as_int / 1000 <= 10)
		{
			if (opt.darkMode == 1)
				changeFontColor(black, red);
			else
				changeFontColor(white, red);
			PlaySound(TEXT("SOUND GAME CARO\\keyboard\\time.wav"), NULL, SND_ASYNC | opt.vfxFlag);
		}
		cout << set_time - milliseconds_as_int / 1000;

		GotoXY(25, 15);
		if (opt.darkMode == 1)
			changeFontColor(black, white);
		else
			changeFontColor(white, black);
		cout << set_time;
	}
}
void Player::play()
{
	create_saved_games_folder();
	
	//TimeMode = 1;
	if (TimeMode == 1)
	{
		if(set_time == 0)
			init_time();
		start_time = system_clock::now();
		end_time = system_clock::now();
		elapsed_time = duration_cast<milliseconds>(end_time - start_time);
	}
	
	/*
	y tuong:
	 dung ham move de vua di chuyen va danh
	 player.current_player == 1 thi x danh
	 player.current_player == 2 thi o dah
	 sau khi danh xong thi kiem tra da
	 */
	while (1)
	{
		move(); // di chuyen va ve o x len bang
		type = check_win(); // check : type==0 choi tiep | type==1 player x hoac o da win | type == 2 hoa
		if (TimeMode == 1 && type == 0)
		{
			end_time = system_clock::now();
			elapsed_time = duration_cast<milliseconds>(end_time - start_time);
			milliseconds_as_int = static_cast<int>(elapsed_time.count());
			if (milliseconds_as_int % 1000 == 0)
			{
				print_time();
			}
			if (milliseconds_as_int/1000 >= set_time)
			{
				if (check_saveload == 1)
					update_namegame();
				
				if (current_player == 1)
				{
					winner = 2;// player O = 2
					GotoXY(17, 15);
					if (opt.darkMode == 1)
						changeFontColor(black, white);
					else
						changeFontColor(white, black);
					cout << "RUN OUT OF TIME!";
					PlayMusic("Victory");
					visualizer.printWinStreak('O', winningCoord, initCoor);
					SceneHandle("WinScene_O");
					
				}
				else
				{
					winner = 1;// player X = 1
					GotoXY(132, 15);
					if (opt.darkMode == 1)
						changeFontColor(black, white);
					else
						changeFontColor(white, black);
					cout << "RUN OUT OF TIME!";
					PlayMusic("Victory");
					visualizer.printWinStreak('X', winningCoord, initCoor);
					SceneHandle("WinScene_X");
				}
			}
		}
		if (type) // neu 1 nguoi choi da thang hoac hoa thi thoat
			break;
		
		if (check_save == 1)
		{
			break;
		}
		if (check_play_ai == 1)
		{
			i = save_I;
			j = save_J;
			check_play_ai = 0;
		}

	}
	if (check_save == 1)
	{
		check_save = 0;
		save_game();
		SceneHandle("MAIN MENU");
	}
	if (type == 2)
	{
		if (check_saveload == 1)
			update_namegame();
		// tran dau hoa
		//draw_draw();
		SceneHandle("WinScene_D");
	}
	else if (type == 1)
	{
		if(check_saveload==1)
			update_namegame();
		selectWinStreak();

		/*GotoXY(0, 0); [Kiet - Vector victory _ animate]*/
		
		 
		// tran dau da co nguoi win => di kiem tra _POINT[i][j]
		// neu _POINT[i][j] == 1 thi x win
		// _POINT[i][j] == 2 thi o win 
		
		if (_POINT[i][j] == 1)
		{
			/*draw_x_win();*/
			winner = 1;// player X = 1
			PlayMusic("Victory");
			visualizer.printWinStreak('X', winningCoord, initCoor);
			SceneHandle("WinScene_X");
		}
		else
		{
			/*draw_o_win();*/
			winner = 2;// player O = 2
			PlayMusic("Victory");
			visualizer.printWinStreak('O', winningCoord, initCoor);
			SceneHandle("WinScene_O");
		}
	}
}
