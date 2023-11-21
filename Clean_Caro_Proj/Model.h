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
using namespace std;



struct Player
{
    COORD initCoor;
    int i, j, a[100][100], current_player = 1, AI = 0, offSetX = 4, offSetY = 2, numcell, type=0;
    int check_saveload = 0;
    string ten_ban_dau = "";
    // initX y la vi tri con tro tren console
    // i j la vi tri tren bang a
    // player la luot cua nguoi choi x hoac o
    void khoitao()
    {
        memset(a, 0, sizeof(a));
    }
    void move(); // vua di chuyen vua phat am thanh
    int check_win(); //
    void play(); // play    neu su dung AI thi player.AI=1; sau do player.play();
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
    vector<pair<int, int>>erea(int);
    pair<int, int>find_best_move();
    int AttackPoint_Horizontal(int nline, int ncolumn, int player);
    int AttackPoint_Vertical(int nline, int ncolumn, int player);
    int AttackPoint_Diagonal1(int nline, int ncolumn, int player);
    int AttackPoint_Diagonal2(int nline, int ncolumn, int player);
    int DefendPoint_Horizontal(int nline, int ncolumn, int player);
    int DefendPoint_Vertical(int nline, int ncolumn, int player);
    int DefendPoint_Diagonal1(int nline, int ncolumn, int player);
    int DefendPoint_Diagonal2(int nline, int ncolumn, int player);
    int minimax(int, int, int , int);
    int cal_mark(int nline, int ncolumn,int player);
    int cal_mark2();
    int kt_win();
    void load_board();
    void save_game();
    void load_game();
    void update_namegame();
    int winner = 0;
    void selectWinStreak();

    //graphics
    // phan nay de tam trong day cho de debug
    // nho xoa phan nay
    void draw_rectangle(int x, int y, int u, int v, int color)
    {
        draw_background(x, y, u, y, color);
        //draw_background(x+1, y, u+1, y, color);
        draw_background(x, v, u, v, color);
        //draw_background(x + 1, v, u + 1, v, color);
        draw_background(x, y, x, v, color);
        draw_background(x + 1, y, x + 1, v, color);
        draw_background(u, y, u, v, color);
        draw_background(u - 1, y, u - 1, v, color);
    }
    void SetColor_2(int backgound_color, int text_color);
    void draw_background(int x, int y, int u, int v, int color)
    {
        SetColor_2(color, color);
        for (int i = x; i <= u; i++)
        {
            for (int j = y; j <= v; j++)
            {
                GotoXY(i, j);
                cout << " ";
                //Sleep(0.01);
            }
        }
    }
    void GotoXY(int x, int y)
    {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    void draw_board()
    {
        int x = 43, y = 0;
        for (int i = 1; i <= 16; i++)
        {
            for (int j = 1; j <= 16; j++)
            {
                GotoXY(x, y);
                x += 4;
                //Sleep(0.01);
            }
            y += 2;
            x = 43;
        }
    }
    void draw_x();
    void draw_o();

    void draw_x_win()
    {
        GotoXY(135, 20);
        cout << " X WIN";
        draw_rectangle(130, 15, 150, 25, 1);
        GotoXY(0, 41);
    }
    void draw_o_win()
    {
        GotoXY(135, 20);
        cout << "O WIN";
        draw_rectangle(130, 15, 150, 25, 1);
        GotoXY(0, 41);
    }
    void draw_draw()
    {

    }


};

