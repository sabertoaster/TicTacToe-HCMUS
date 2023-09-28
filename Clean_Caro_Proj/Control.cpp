#include "Control.h"

void Pointer::startMenu(string cmd) {
	GotoXY(ptrBtnList[id].coord.X - 2, ptrBtnList[id].coord.Y + 1);
	cout << "  "; // delete the old pointer
	if (cmd == "") {
		id = 0;
	}
	else if (cmd == "next") {
		id = ptrBtnList[id].nextBtn->id;
	}
	else if (cmd == "prev") {
		id = ptrBtnList[id].prevBtn->id;
	}
	GotoXY(ptrBtnList[id].coord.X - 2, ptrBtnList[id].coord.Y + 1);
	changeFontColor(white, black);
	cout << ">>";
}

void Pointer::initPtrBtnList() {
	ptrBtnList = visualizer.buttons;
}

void Pointer::checkEnter() {
	ptrBtnList[id].playScene();
}
Pointer pointer;

void GotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void InitializeData() {
	// initialize data for things like buttons, save games, about text, help documention, options

	// [initialize buttons]
	Button playBtn(L"PLAY");
	Button loadBtn(L"LOAD");
	Button optionBtn(L"OPTIONS");
	Button helpBtn(L"HELP");
	Button aboutBtn(L"ABOUT");
	Button exitBtn(L"EXIT");
	playBtn.coord.X = 56;
	playBtn.coord.Y = 10;
	visualizer.buttons = { playBtn, loadBtn, optionBtn, helpBtn, aboutBtn, exitBtn };
	for (int i = 0; i < visualizer.buttons.size(); i++) {
		visualizer.buttons[i].id = i;
		if (i == visualizer.buttons.size() - 1) {
			visualizer.buttons[i].coord.X = visualizer.buttons[i - 1].coord.X;
			visualizer.buttons[i].coord.Y = visualizer.buttons[i - 1].coord.Y + 5;
			visualizer.buttons[i].nextBtn = &(visualizer.buttons[0]);
			visualizer.buttons[i].prevBtn = &(visualizer.buttons[i - 1]);
			continue;
		}
		if (i == 0) {
			visualizer.buttons[i].nextBtn = &(visualizer.buttons[i + 1]);
			visualizer.buttons[i].prevBtn = &(visualizer.buttons[visualizer.buttons.size() - 1]);
			continue;
		}
		visualizer.buttons[i].coord.X = visualizer.buttons[i - 1].coord.X;
		visualizer.buttons[i].coord.Y = visualizer.buttons[i - 1].coord.Y + 5; // offset for visualizer.buttons
		visualizer.buttons[i].prevBtn = &(visualizer.buttons[i - 1]);
		visualizer.buttons[i].nextBtn = &(visualizer.buttons[i + 1]);
	}
	pointer.initPtrBtnList();
}

void StartGame() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	FixConsoleWindow();
	ShowConsoleCursor(false);
	InitializeData();
	StartMenu();
}

void StartPlay() {

}

void StartExit() {
	exit(0);
}

void StartMenu() {
	DrawObject("Background");
	GotoXY(43, 1);
	DrawObject("Main_Logo");
	DrawObject("Button");
	pointer.startMenu("");
	bool _checkNotEnter = true;
	while (_checkNotEnter)
	{
		// visualize animations
		static int index[6] = { 6, 3, 0, 0, 3, 6 }, coorX[6] = { 4, 17, 30, 80, 93, 105 }, coorY = 1;
		const int animationCol = 6;
		for (int i = 0; i < animationCol; i++) {
			visualizer.printBackgroundAnimation(index[i], coorX[i], coorY);
			index[i]++;
			if (index[i] == 10) {
				index[i] = 0;
			}
		}
		coorY++;
		if (coorY == 39) {
			Sleep(100);
			coorY = 1;
		}


		if (_kbhit())
		{
			COORD currentCoord = GetConsoleCursorPosition(); // get current (x,y)
			switch (_getch())
			{
			case 'a':
				cout << 'a';
				GotoXY(currentCoord.X - 1, currentCoord.Y);
				break;
			case 'w':
				pointer.startMenu("prev");
				break;
			case 's':
				pointer.startMenu("next");
				break;
			case 'd':
				cout << 'd';
				GotoXY(currentCoord.X + 1, currentCoord.Y);
				break;
			case 13: //Enter ASCII value of enter
				_checkNotEnter = false;
				break;
			default:
				break;
			};
		}
	}
	pointer.checkEnter();
}

