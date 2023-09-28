#pragma once
#include <iostream>
#include <vector>
#include <cstdlib> // [for exit()]
#include <Windows.h>
#include <conio.h>
#include "View.h"
using namespace std;
// [Direct the pointer]

struct Pointer {
public:
	COORD coord;
	int id = 0;
	vector<Button> ptrBtnList; // [Main menu buttons list]
	void startMenu(string cmd);
	void initPtrBtnList();
	void checkEnter();
}; 



void GotoXY(int x, int y);

void InitializeData();

void StartGame();

void StartPlay();

void StartExit();

void StartMenu();
