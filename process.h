#pragma once
#include <Windows.h>
#include<string>
#include<iostream>
using namespace std;



struct player
{ 
    COORD initCoor;
    int i ,j, a[100][100], current_player = 1, AI = 0, offSetX=4, offSetY=2, numcell;
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
    int solve(int,int,int);  // ham nay dung de tinh diem
    int pow10(int, int ); // ham ho tro cho solve
    int cal(int ); // ham ho tro cho solve
    player(int initx, int inity, int numcell, int relaX, int relaY  );


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
    void SetColor_2(int backgound_color, int text_color)
    {
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

        int color_code = backgound_color * 16 + text_color;
        SetConsoleTextAttribute(hStdout, color_code);
    }
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
                draw_rectangle_1(x, y, x + 4, y + 2, 7, 1);
                x += 4;
                //Sleep(0.01);
            }
            y += 2;
            x = 43;
        }
    }
    void draw_x()
    {
        SetColor_2(7, 4);
        cout << "X";
    }
    void draw_o()
    {
        SetColor_2(7, 0);
        cout << "O";
    }
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
player::player(int x, int y, int inputnumcell , int j, int i) {
    // x,y la toa do console // i tuong ung voi y // j tuong ung voi x
    initCoor.X = x;
    initCoor.Y = y;
    numcell = inputnumcell;
    this->i = i;
    this->j = j;
}
int player::pow10(int a, int b)
{
    int res = 1;
    while (b)
    {
        if (b % 2 == 1)
            res *= a;
        a *= a;
        b /= 2;
    }
    return res;
}
int player::cal(int n)
{
    if (n == 0)
        return 0;
    return pow10(10, n);
}
int player::solve(int x, int y, int k)
{
    int tmp1 = x, tmp2 = y, cnt = 0, ans = 0;
    for (int i = 1; i <= 6; i++)
    {
        x++;
        y--;
        if (a[x][y] ==k )
            cnt++;
        else
            break;
    }
    /*ans += cal(cnt+(k==2));
    cnt = 0;*/
    x = tmp1, y = tmp2;
    for (int i = 1; i <= 6; i++)
    {
        x--;
        y++;
        if (a[x][y] == k)
            cnt++;
        else
            break;
    }
    ans += cal(cnt + (k == 2));
    cnt = 0;
    // check 2
    x = tmp1, y = tmp2;
    for (int i = 1; i <= 6; i++)
    {
        x--;
        y--;
        if (a[x][y] == k)
            cnt++;
        else
            break;
    }
    /*ans += cal(cnt + (k == 2));
    cnt = 0;*/
    x = tmp1, y = tmp2;
    for (int i = 1; i <= 6; i++)
    {
        x++;
        y++;
        if (a[x][y] == k)
            cnt++;
        else
            break;
    }
    ans += cal(cnt + (k == 2));
    cnt = 0;
    //check 3
    x = tmp1, y = tmp2;
    for (int i = 1; i <= 6; i++)
    {
        x--;
        //y--;
        if (a[x][y] == k)
            cnt++;
        else
            break;
    }
    /*ans += cal(cnt + (k == 2));
    cnt = 0;*/
    x = tmp1, y = tmp2;
    for (int i = 1; i <= 6; i++)
    {
        x++;
        //y++;
        if (a[x][y] == k)
            cnt++;
        else
            break;
    }
    ans += cal(cnt + (k == 2));
    cnt = 0;
    // check 4;
    x = tmp1, y = tmp2;
    for (int i = 1; i <= 6; i++)
    {
        //x--;
        y--;
        if (a[x][y] == k)
            cnt++;
        else
            break;
    }
    /*ans += cal(cnt + (k == 2));
    cnt = 0;*/
    x = tmp1, y = tmp2;
    for (int i = 1; i <= 6; i++)
    {
        //x++;
        y++;
        if (a[x][y] == k)
            cnt++;
        else
            break;
    }
    ans += cal(cnt + (k == 2));
    return ans;
}
void player::move()
{
    int check_up = 0, check_down = 0, check_right = 0, check_left = 0, check_enter = 0, cnt = 1, win = 1;
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
    }
    if (check_up || check_down || check_right || check_left)
    {
        PlaySound(TEXT("SOUND GAME CARO\\click\\click1.wav"), NULL, SND_ASYNC);
    }
    if (check_enter)
    {
        PlaySound(TEXT("SOUND GAME CARO\\click\\enter.wav"), NULL, SND_ASYNC);
    }
    if (check_enter == 1 && a[i][j] != 0)
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
    if (AI == 0)
    {
        if (a[i][j] == 0 && check_enter && !check_up && !check_down && !check_right && !check_left)
        {
            if (current_player == 1)
            {
                draw_x();
                a[i][j] = 1;
            }
            else
            {
                draw_o();
                a[i][j] = 2;
            }
            current_player = 1 - current_player;
            check_enter = 0;
        }
    }
    if(AI == 1)
    {
        if (current_player == 1)
        {
            if (a[i][j] == 0 && check_enter && !check_up && !check_down && !check_right && !check_left)
            {
                draw_x();
                a[i][j] = 1;
                current_player = 1 - current_player;
                check_enter = 0;
            }
        }
        else
        {
            // duyet het cac o trong bang 16x16 luu lai o co nuoc di toi uu
            int  tmpi = 0, tmpj = 0; // tmpi , tmpj = i,j
            int ans = -1;   //tmpx, tmp initCoor.Y =initCoor.X,initCoor.Y;
            for (int _i = 1; _i <= numcell; _i++)
            {
                for (int _j = 1; _j <= numcell; _j++)
                {
                    if (a[_i][_j] != 0)
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


            a[tmpi][tmpj] = 2;
             //debug AI
            //i = tmpi; j = tmpj;
            /*SetColor_2(7, 0);
            GotoXY(135, 25);
            cout << ans << "\n";
            GotoXY(0, 5);
            for (int _i = 1; _i <= 16; _i++)
            {
                for (int _j = 1; _j <= 16; _j++)
                    cout << a[_i][_j] << " ";
                cout << '\n';
            }*/
            GotoXY(initCoor.X + (tmpj - 1) * offSetX, initCoor.Y + (tmpi - 1) * offSetY);
            draw_o();
            current_player = 1 - current_player;
            check_enter = 0;
            GotoXY(initCoor.X + (j - 1) * offSetX, initCoor.Y + (i - 1) * offSetY);
        }
    }
    
}
int player::check_win()
{
    int x = i, y = j;
    int k = a[i][j];
    if (k == 0)
        return 0;
    //check 1
    int tmp1 = x, tmp2 = y, cnt = 1;
    for (int i = 1; i <= 6; i++)
    {
        x++;
        y--;
        if (a[x][y] == k)
            cnt++;
        else
            break;
    }
    x = tmp1, y = tmp2;
    for (int i = 1; i <= 6; i++)
    {
        x--;
        y++;
        if (a[x][y] == k)
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
        if (a[x][y] == k)
            cnt++;
        else
            break;
    }
    x = tmp1, y = tmp2;
    for (int i = 1; i <= 6; i++)
    {
        x++;
        y++;
        if (a[x][y] == k)
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
        if (a[x][y] == k)
            cnt++;
        else
            break;
    }
    x = tmp1, y = tmp2;
    for (int i = 1; i <= 6; i++)
    {
        x++;
        //y++;
        if (a[x][y] == k)
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
        if (a[x][y] == k)
            cnt++;
        else
            break;
    }
    x = tmp1, y = tmp2;
    for (int i = 1; i <= 6; i++)
    {
        //x++;
        y++;
        if (a[x][y] == k)
            cnt++;
        else
            break;
    }
    if (cnt >= 5)
        return 1;
    cnt = 0;
    for (int i = 1; i <= numcell; i++)
        for (int j = 1; j <= numcell; j++)
            if (a[i][j] == 0)
                cnt++;
    if (cnt == 0)
        return 2;
    return 0;
}
void player::play()
{
    khoitao();// cho tat ca a = 0
    draw_board();
    int type;

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
        if (type) // neu 1 nguoi choi da thang hoac hoa thi thoat
            break;
        
    }
    if (type == 2)
    {
        // tran dau hoa
        draw_draw();
    }
    else if (type == 1)
    {
        // tran dau da co nguoi win => di kiem tra a[i][j]
        // neu a[i][j] == 1 thi x win
        // a[i][j] == 2 thi o win 
        if (a[i][j]==1)
        {
            draw_x_win();
        }
        else
        {
            draw_o_win();
        }
    }
}
