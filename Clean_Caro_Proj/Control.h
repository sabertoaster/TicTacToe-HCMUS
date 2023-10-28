#pragma once
#include <iostream>
#include <vector>
#include <cstdlib> // [for exit()]
#include <Windows.h>
#include <conio.h>
#include "View.h"
#include "Model.h"
#include <string>

//Unicode UTF8 char lib 
#include <wchar.h>
#include <fcntl.h>
#include <io.h>

using namespace std;
// [Direct the pointer]

struct Pointer {
public:
	COORD coord;
	int id = 0;
	vector<Button> ptrChoosePlayer = {}; // [Choose CPU/ Player buttons list]
	vector<Button> ptrBtnList = {}; // [Main menu buttons list]
	vector<Button> ptrAfterPlay = {};
	void startIndexing(string cmd, vector<Button> ptrTemp);
	void checkEnter(string str);
}; 

void GotoXY(int x, int y);

void InitializeData();

void StartGame();

void StartPlay();

void StartMatchScene(string typeMatch);

void StartWinScene(char);

void StartExit();

void StartMenu();

void StartHelp();

void StartAbout();
