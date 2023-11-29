#pragma once
#include <Windows.h>
#include <string>
#include <iostream>
#include <mmsystem.h>
#include <conio.h>
#include <playsoundapi.h>
#include <vector>
#include "View.h"
#include "Control.h"
#include<stdio.h>
#include<algorithm>
using namespace std;



struct Player
{
    COORD initCoor;
    int i, j, _POINT[100][100], current_player = 1, BruteForce = 0, offSetX = 4, offSetY = 2, numcell, type = 0, Minimax = 0;
    int check_saveload = 0;
    string name_repeat_load = "";
    // initX y la vi tri con tro tren console
    // i j la vi tri tren bang _POINT
    // player la luot cua nguoi choi x hoac o
    void khoitao()
    {
        memset(_POINT, 0, sizeof(_POINT));
    }
    void move(); // vua di chuyen vua phat am thanh
    int check_win(); //
    void play(); // play    neu su dung BruteForce thi player.BruteForce=1; sau do player.play();
    int solve(int, int, int);  // ham nay dung de tinh diem
    int pow10(int, int); // ham ho tro cho solve
    int cal(int); // ham ho tro cho solve
    Player(int initx, int inity, int numcell, int relaX, int relaY);
    int check_huong();
    int check_4_huong(int ,int );
    vector<pair<int, int>> huong1();
    vector<pair<int, int>> huong2();
    vector<pair<int, int>> huong3();
    vector<pair<int, int>> huong4();
    vector<COORD> winningCoord ;    
    vector<pair<int, int>>history;
    vector<pair<int, int> >re_history;
    vector<pair<int, int>>area(int);
    pair<int, int>find_best_move();
    pair<int, int>find_best_bruteforce();
    int AttackPoint_Horizontal(int nline, int ncolumn, int player);
    int AttackPoint_Vertical(int nline, int ncolumn, int player);
    int AttackPoint_Diagonal1(int nline, int ncolumn, int player);
    int AttackPoint_Diagonal2(int nline, int ncolumn, int player);
    int DefendPoint_Horizontal(int nline, int ncolumn, int player);
    int DefendPoint_Vertical(int nline, int ncolumn, int player);
    int DefendPoint_Diagonal1(int nline, int ncolumn, int player);
    int DefendPoint_Diagonal2(int nline, int ncolumn, int player);
    int minimax(int, int, int , int);
    int cal_mark();
    int kt_win();
    void load_board();
    void save_game();
    int load_game();
    void update_namegame();
    int winner = 0;
    void selectWinStreak();
    void load_board_mini();
    vector<string> list_namesave();
    //graphics
    // phan nay de tam trong day cho de debug
    // nho xoa phan nay
    void draw_x();
    void draw_o();

};

