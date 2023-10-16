#include "Control.h"

void Pointer::startIndexing(string cmd, vector<Button> ptrTemp) {
	GotoXY(ptrTemp[id].coord.X - 2, ptrTemp[id].coord.Y + 1);
	cout << "  "; // delete the old pointer
	if (cmd == "") {
		id = 0;
	}
	else if (cmd == "next") {
		id = ptrTemp[id].nextBtn->id;
	}
	else if (cmd == "prev") {
		id = ptrTemp[id].prevBtn->id;
	}
	GotoXY(ptrTemp[id].coord.X - 2, ptrTemp[id].coord.Y + 1);
	changeFontColor(white, black);
	cout << ">>";
}


void Pointer::checkEnter(string str) {
	if (str == "Menu") {
		ptrBtnList[id].playScene();
		_getch();
		return;
	}
	if (str == "PlayScene") {
		ptrChoosePlayer[id].playScene();
		_getch();
		return;
	}
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
	playBtn.coord.X = 80;
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
	pointer.ptrBtnList = visualizer.buttons; // initialize buttons for main menu


	Button chooseCPUBtn(L"PLAYER VERSUS COMPUTER"); // define buttons for choose CPU/ player scene
	Button choosePlayerBtn(L"PLAYER VERSUS PLAYER");
	chooseCPUBtn.coord.X = 80;
	chooseCPUBtn.coord.Y = 10;
	chooseCPUBtn.nextBtn = &(choosePlayerBtn);
	chooseCPUBtn.prevBtn = &(choosePlayerBtn);
	chooseCPUBtn.id = 0;
	choosePlayerBtn.nextBtn = &(chooseCPUBtn);
	choosePlayerBtn.prevBtn = &(chooseCPUBtn);
	choosePlayerBtn.coord.X = chooseCPUBtn.coord.X;
	choosePlayerBtn.coord.Y = chooseCPUBtn.coord.Y + 12;
	choosePlayerBtn.id = 1;
	pointer.ptrChoosePlayer = { chooseCPUBtn, choosePlayerBtn };
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
	DrawObject("Background");
	DrawObject("Border");

	for (auto i : pointer.ptrChoosePlayer) { //Visualize Btn;
		i.printButton();
	}
	pointer.ptrChoosePlayer[0].nextBtn = pointer.ptrChoosePlayer[0].prevBtn = &(pointer.ptrChoosePlayer[1]);
	pointer.ptrChoosePlayer[1].nextBtn = pointer.ptrChoosePlayer[1].prevBtn = &(pointer.ptrChoosePlayer[0]);
	pointer.startIndexing("", pointer.ptrChoosePlayer);
	bool _checkNotEnter = true;
	while (_checkNotEnter)
	{
		if (_kbhit())
		{
			COORD currentCoord = GetConsoleCursorPosition(); // get current (x,y)
			switch (_getch())
			{
			case 'a':
				pointer.startIndexing("prev", pointer.ptrChoosePlayer);
				break;
			case 'w':
				pointer.startIndexing("prev", pointer.ptrChoosePlayer);
				break;
			case 's':
				pointer.startIndexing("next", pointer.ptrChoosePlayer);
				break;
			case 'd':
				pointer.startIndexing("next", pointer.ptrChoosePlayer);
				break;
			case 13: //Enter ASCII value of enter
				_checkNotEnter = false;
				break;
			default:
				break;
			};
		}
	}
	pointer.checkEnter("PlayScene"); // redirect to pve or pvp
}

void StartExit() {
	exit(0);
}


void StartMatchScene(string matchType) {
	DrawObject("Background");
	DrawObject("Border");
	GotoXY(4, 4);
	DrawObject("PlayerFrame");
	GotoXY(52, 1);
	DrawObject("BoardCanvas");

}

void StartMenu() {
	DrawObject("Background");
	visualizer.printMenuBorder(); // [temporary]
	GotoXY(68, 1);
	DrawObject("Main_Logo");
	DrawObject("Button");
	pointer.startIndexing("", pointer.ptrBtnList);
	bool _checkNotEnter = true;
	while (_checkNotEnter)
	{
		// visualize animations
		static int index[10] = { 0, 8, 6, 3, 0, 0, 3, 6, 8, 0 }, coorX[10] = { 4, 17, 30, 43, 56, 103, 116, 129, 142, 155 }, coorY = 1;
		const int animationCol = 10;
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
				pointer.startIndexing("prev", pointer.ptrBtnList);
				break;
			case 'w':
				pointer.startIndexing("prev", pointer.ptrBtnList);
				break;
			case 's':
				pointer.startIndexing("next", pointer.ptrBtnList);
				break;
			case 'd':
				pointer.startIndexing("next", pointer.ptrBtnList);
				break;
			case 13: //Enter ASCII value of enter
				_checkNotEnter = false;
				break;
			default:
				break;
			};
		}
	}
	pointer.checkEnter("Menu");
}

void StartHelp() {
	DrawObject("Background");
	DrawObject("Border");
	COORD helpTextCoor;
	helpTextCoor.X = 30;
	helpTextCoor.Y = 10;
	const char* helpText[6] = { "1. Caro is played using the Xand O symbol.", "2. Two players play against each other on 15 x 15 or 19 x 19 grid.", "3. The player representing the \"X\" symbol gets to take the first turn followed by the player representing the \"O\" symbol.", "4. Players take turns placing their symbol on an open intersection on the board.", "5. The player that manages to create five in a row first wins the round.The row can be horizontal, vertical, or diagonal as long as it is unbroken.", "6. Once a player places a symbol on the board, the symbol cannot be moved or changed." };
	/*1. Caro is played using the Xand O symbol.
	2. Two players play against each other on 15 x 15 or 19 x 19 grid.
	3. The player representing the “X” symbol gets to take the first turn followed by the player representing the “O” symbol.
	4. Players take turns placing their symbol on an open intersetion on the board.
	5. The player that manages to create five in a row first wins the round.The row can be horizontal, vertical, or diagonal as long as it is unbroken.
	6. Once a player places a symbol on the board, the symbol cannot be moved or changed.*/
	for (int i = 0; i < sizeof(helpText) / sizeof(helpText[0]); i++) {
		GotoXY(helpTextCoor.X, helpTextCoor.Y + i);
		cout << helpText[i];
	}

	bool _checkNotEnter = true;
	while (_checkNotEnter)
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			case 13: //Enter ASCII value of enter
				_checkNotEnter = false;
				break;
			case 27:
				_checkNotEnter = false;
			default:
				break;
			};
		}
	}

	SceneHandle("MAIN MENU");
}

void StartAbout() {
	DrawObject("Background");
	DrawObject("Border");
	GotoXY(62, 1);
	DrawObject("About_Logo");

	COORD tableCoord;
	tableCoord.X = 62;
	tableCoord.Y = 10;
	GotoXY(tableCoord.X, tableCoord.Y);
	cout << "Bring to you by the 2nd group 23TNT1 - Advisor: Truong Toan Thinh" << endl;
	GotoXY(tableCoord.X, tableCoord.Y+1);
	cout << "23122008 - Mai Duc Minh Huy" << endl;
	GotoXY(tableCoord.X, tableCoord.Y+2);
	cout << "23122033 - Mai Duc Minh Huy" << endl;
	GotoXY(tableCoord.X, tableCoord.Y+3);
	cout << "23122036 - Mai Duc Minh Huy" << endl;
	GotoXY(tableCoord.X, tableCoord.Y+4);
	cout << "23122039 - Mai Duc Minh Huy" << endl;

	bool _checkNotEnter = true;
	while (_checkNotEnter)
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			case 13: //Enter ASCII value of enter
				_checkNotEnter = false;
				break;
			case 27:
				_checkNotEnter = false;
			default:
				break;
			};
		}
	}

	SceneHandle("MAIN MENU");
}
