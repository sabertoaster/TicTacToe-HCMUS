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

#define DARKMODE_ "Dark Mode Toggle"
#define MUSIC_ "Background Music Toggle"
#define VFX_ "Effect Music Toggle"
using namespace std;
// [Direct the pointer]

struct Pointer {
public:
	COORD coord;
	int id = 0;
	vector<Button> ptrChoosePlayer = {}; // [Choose CPU/ Player buttons list]
	vector<Button> ptrBtnList = {}; // [Main menu buttons list]
	vector<Button> ptrAfterPlay = {};
	vector<OptionButton> ptrOptions = {};
	void startIndexing(string cmd, vector<Button> ptrTemp);
	void startIndexingOptions(string, vector<OptionButton>);
	void checkEnter(string str);
};

struct Options {
public:
	const char muteFlag = 0x00040004L;
	char soundFlag = 0; // default on 
	char vfxFlag = 0; // default on 
	int darkMode = 0;
};

extern Options opt;

void GotoXY(int x, int y);

void InitializeData();

void PlayMusic(string);

void StartGame();

void StartPlay();

void StartMatchScene(string typeMatch);

void StartWinScene(char);

void StartExit();

void StartMenu();

void StartOption();

void StartHelp();

void StartAbout();

void StartLoad();