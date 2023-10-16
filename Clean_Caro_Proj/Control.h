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
	vector<Button> ptrChoosePlayer; // [Choose CPU/ Player buttons list]
	void startIndexing(string cmd, vector<Button> ptrTemp);
	void checkEnter(string str);
}; 



void GotoXY(int x, int y);

void InitializeData();

void StartGame();

void StartPlay();

void StartExit();

void StartMatchScene(string typeMatch);

void StartMenu();

void StartHelp();

void StartAbout();
