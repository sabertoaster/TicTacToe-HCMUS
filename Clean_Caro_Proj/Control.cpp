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
	if (str == "AfterPlay") {
		ptrAfterPlay[id].playScene();
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
	Button menuBtn(L"MAIN MENU");
	Button playBtn(L"PLAY");
	Button loadBtn(L"LOAD");
	Button optionBtn(L"OPTIONS");
	Button helpBtn(L"HELP");
	Button aboutBtn(L"ABOUT");
	Button exitBtn(L"EXIT");
	playBtn.coord.X = 80;
	playBtn.coord.Y = 10;
	int offset = 5;
	pointer.ptrBtnList = { playBtn, loadBtn, optionBtn, helpBtn, aboutBtn, exitBtn };
	for (int i = 0; i < pointer.ptrBtnList.size(); i++) { // [FIXED REMOVE BUTTONS FROM VISUALIZER
		pointer.ptrBtnList[i].id = i;

		int nextIndex = (i + 1) % pointer.ptrBtnList.size();

		pointer.ptrBtnList[i].coord.X = pointer.ptrBtnList[0].coord.X;
		pointer.ptrBtnList[i].coord.Y = pointer.ptrBtnList[0].coord.Y + offset * i;

		pointer.ptrBtnList[i].nextBtn = &(pointer.ptrBtnList[nextIndex]);
		pointer.ptrBtnList[nextIndex].prevBtn = &(pointer.ptrBtnList[i]);
	}

	Button chooseCPUBtn(L"PLAYER VERSUS COMPUTER"); // define buttons for choose CPU/ player scene
	Button choosePlayerBtn(L"PLAYER VERSUS PLAYER");
	chooseCPUBtn.coord.X = 80;
	chooseCPUBtn.coord.Y = 10;
	offset = 15;
	pointer.ptrChoosePlayer = { chooseCPUBtn, choosePlayerBtn }; // initialize buttons for main menu
	for (int i = 0; i < pointer.ptrChoosePlayer.size(); i++) { // [FIXED REMOVE BUTTONS FROM VISUALIZER
		pointer.ptrChoosePlayer[i].id = i;

		int nextIndex = (i + 1) % pointer.ptrChoosePlayer.size();

		pointer.ptrChoosePlayer[i].coord.X = pointer.ptrChoosePlayer[0].coord.X;
		pointer.ptrChoosePlayer[i].coord.Y = pointer.ptrChoosePlayer[0].coord.Y + offset * i;

		pointer.ptrChoosePlayer[i].nextBtn = &(pointer.ptrChoosePlayer[nextIndex]);
		pointer.ptrChoosePlayer[nextIndex].prevBtn = &(pointer.ptrChoosePlayer[i]);
	}


	playBtn.coord.X = 80;
	playBtn.coord.Y = 20;
	offset = 3;
	pointer.ptrAfterPlay = { playBtn, menuBtn, exitBtn };
	for (int i = 0; i < pointer.ptrAfterPlay.size(); i++) { // [FIXED REMOVE BUTTONS FROM VISUALIZER
		pointer.ptrAfterPlay[i].id = i;

		int nextIndex = (i + 1) % pointer.ptrAfterPlay.size();

		pointer.ptrAfterPlay[i].coord.X = pointer.ptrAfterPlay[0].coord.X;
		pointer.ptrAfterPlay[i].coord.Y = pointer.ptrAfterPlay[0].coord.Y + offset * i;

		pointer.ptrAfterPlay[i].nextBtn = &(pointer.ptrAfterPlay[nextIndex]);
		pointer.ptrAfterPlay[nextIndex].prevBtn = &(pointer.ptrAfterPlay[i]);
	}
}

void StartGame() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	FixConsoleWindow();
	InitializeData();
	StartMenu();
}

void StartPlay() {
	DrawObject("Background");
	DrawObject("Border");

	for (auto i : pointer.ptrChoosePlayer) { //Visualize Btn;
		i.printButton();
	}

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
			case 'w':
				pointer.startIndexing("prev", pointer.ptrChoosePlayer);
				break;
			case 's':
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

void StartMatchScene(string matchType) {
	DrawObject("Background");
	DrawObject("Border");
	DrawObject("PlayerFrame"); // built-in coor for player frame
	GotoXY(52, 3);
	DrawObject("BoardCanvas");
	ShowConsoleCursor(true);
	Player playerManager(52 + 2, 3 + 1, 16, 1, 1);
	if (matchType == "PVE") {
		playerManager.AI = 1;
	}
	playerManager.khoitao();
	playerManager.play();

}

void StartWinScene(char player) {
	ShowConsoleCursor(false);
	DrawObject("Background");
	DrawObject("Border");
	for (auto i : pointer.ptrAfterPlay) { //Visualize Btn;
		i.printButton();
	}
	pointer.startIndexing("", pointer.ptrAfterPlay);
	COORD animPivot = { 8, 5 }; // animPivot [hard-code]
	int waveWidth = 25, initNumChar = 0;
	bool _checkNotEnter = true;
	while (_checkNotEnter) {
		initNumChar += 2;
		if (initNumChar % 20 == 0) {
			initNumChar = 0;
		}

		switch (player) {
		case 'X':
			visualizer.printWinAnimation('X', waveWidth, initNumChar, animPivot);
			/*DrawObject("WinAnimation_X");*/
			break;
		case 'O':
			visualizer.printWinAnimation('O', waveWidth, initNumChar, animPivot);
			/*DrawObject("WinAnimation_O");*/
			break;
		default:
			break;
		}

		if (_kbhit())
		{
			switch (_getch()) {
			case 'a':
			case 'w':
				pointer.startIndexing("prev", pointer.ptrAfterPlay);
				break;
			case 's':
			case 'd':
				pointer.startIndexing("next", pointer.ptrAfterPlay);
				break;
			case 13:
				_checkNotEnter = false;
				break;
			default:
				break;
			}
		}

	}
	pointer.checkEnter("AfterPlay");

	//SceneHandle("MAIN MENU");
}

void StartExit() {
	exit(0);
}



void PlayMusic() {
	PlaySound(TEXT("SOUND GAME CARO\\music\\nhacnen.wav"), NULL, SND_LOOP | SND_ASYNC);
}

void StartMenu() {
	ShowConsoleCursor(false);
	PlayMusic();
	DrawObject("Background");
	visualizer.printMenuBorder(); // [temporary]
	GotoXY(68, 1);
	DrawObject("Main_Logo");

	for (auto i : pointer.ptrBtnList) { //Visualize Btn;
		i.printButton();
	}
	//pointer.ptrChoosePlayer[0].nextBtn = pointer.ptrChoosePlayer[0].prevBtn = &(pointer.ptrChoosePlayer[1]);
	//pointer.ptrChoosePlayer[1].nextBtn = pointer.ptrChoosePlayer[1].prevBtn = &(pointer.ptrChoosePlayer[0]);
	pointer.startIndexing("", pointer.ptrBtnList);
	bool _checkNotEnter = true;
	while (_checkNotEnter)
	{
		// play music in loop background
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
			COORD currentCoord = GetConsoleCursorPosition(); // get current (x,y) [delete]
			switch (_getch())
			{
			case 'a':
			case 'w':
				pointer.startIndexing("prev", pointer.ptrBtnList);
				break;
			case 's':
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
	GotoXY(65, 1);
	DrawObject("Help_Logo");

	COORD helpTextCoor;
	helpTextCoor.X = 30;
	helpTextCoor.Y = 10;
	const char* helpText[18] = { "Player Movement: ","'W': Go up","'S': Go down","'A': Go left","'D': Go right","'Enter': Mark","", "Command Key:","'P': Save game","'Z': Undo the last move", "'Esc': Halt the game","" ,"Caro is the game using the X and O symbols to represent players and followed by a set of rules: ", "3. Two players play against each other on 15 x 15 or 19 x 19 grid.", "4. \"X\" player gets to take the first turn followed by \"O\" player.", "5. Players take turns placing their symbol on an open intersection on the board.", "6. The player that manages to create five in a row first wins the round.", "   The row can be horizontal, vertical, or diagonal as long as it is continuous." };

	/*
	Player Movement:
	'W': Go up
	'S': Go down
	'A': Go left
	'D': Go right
	'Enter': Mark

	Command Key:
	'P': Save game
	'Z': Undo the last move
	'Esc': Halt the game

	1. Caro is played using the Xand O symbol.
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
	GotoXY(tableCoord.X, tableCoord.Y + 1);
	cout << "23122008 - Mai Duc Minh Huy" << endl;
	GotoXY(tableCoord.X, tableCoord.Y + 2);
	cout << "23122033 - Le Hoang Minh Huy" << endl;
	GotoXY(tableCoord.X, tableCoord.Y + 3);
	cout << "23122036 - Nguyen Ngoc Khoa" << endl;
	GotoXY(tableCoord.X, tableCoord.Y + 4);
	cout << "23122039 - Huynh Trung Kiet" << endl;

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
void StartLoad()
{
	DrawObject("Background");
	DrawObject("Border");
	DrawObject("PlayerFrame"); // built-in coor for player frame
	GotoXY(52, 3);
	DrawObject("BoardCanvas");
	Player playerManager(52 + 2, 3 + 1, 16, 1, 1);
	playerManager.khoitao();
	playerManager.load_game();
	playerManager.load_board();
	ShowConsoleCursor(true);
	playerManager.check_saveload = 1;
	if (playerManager.type == 0)
	{
		playerManager.play();
	}
	playerManager.check_saveload = 0;
}