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

	// [Huy_Darkmode]
	if (opt.darkMode == 1)
		changeFontColor(black, white);
	else
		changeFontColor(white, black);
	// [Huy_Darkmode]

	cout << ">>";
}

void Pointer::startIndexingOptions(string cmd, vector<OptionButton> ptrTemp) {
	GotoXY(ptrTemp[id].coord.X - 9, ptrTemp[id].coord.Y + 1);
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
	GotoXY(ptrTemp[id].coord.X - 9, ptrTemp[id].coord.Y + 1);

	// [Huy_Darkmode]
	if (opt.darkMode == 1)
		changeFontColor(black, white);
	else
		changeFontColor(white, black);
	// [Huy_Darkmode]

	cout << ">>";
}


void Pointer::checkEnter(string str) {
	if (str == "Menu") {
		ptrBtnList[id].playScene();
		return;
	}
	if (str == "PlayScene") {
		ptrChoosePlayer[id].playScene();
		return;
	}
	if (str == "AfterPlay") {
		ptrAfterPlay[id].playScene();
		return;
	}
	if (str == "Options") {
		ptrOptions[id].playScene();
		return;
	}
}
Pointer pointer;

Options opt;


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

	OptionButton darkModeBtn(L"Dark Mode Toggle");
	OptionButton musicBtn(L"Background Music Toggle");
	OptionButton vfxBtn(L"Effect Music Toggle");

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

	darkModeBtn.coord.X = 65;
	darkModeBtn.coord.Y = 12;
	offset = 8;
	pointer.ptrOptions = { darkModeBtn, musicBtn, vfxBtn };
	for (int i = 0; i < pointer.ptrOptions.size(); i++) { // [FIXED REMOVE BUTTONS FROM VISUALIZER
		pointer.ptrOptions[i].id = i;

		int nextIndex = (i + 1) % pointer.ptrOptions.size();

		pointer.ptrOptions[i].coord.X = pointer.ptrOptions[0].coord.X;
		pointer.ptrOptions[i].coord.Y = pointer.ptrOptions[0].coord.Y + offset * i;

		pointer.ptrOptions[i].nextBtn = &(pointer.ptrOptions[nextIndex]);
		pointer.ptrOptions[nextIndex].prevBtn = &(pointer.ptrOptions[i]);
	}
}

void PlayMusic(string cmd) {
	if (cmd == "Background") {
		PlaySound(TEXT("SOUND GAME CARO\\music\\nhacnen.wav"), NULL, SND_LOOP | SND_ASYNC | opt.soundFlag);
		return;
	}
	if (cmd == "Victory") {
		PlaySound(TEXT("SOUND GAME CARO\\music\\victory.wav"), NULL, SND_ASYNC | opt.vfxFlag);
		return;
	}
	if (cmd == "Beep") {
		PlaySound(TEXT("SOUND GAME CARO\\click\\enter1.wav"), NULL, SND_SYNC | opt.vfxFlag);
		if (opt.soundFlag == 0) {
			PlayMusic("Background");
		}
		else {
			PlaySound(nullptr, nullptr, 0);
		}
		return;
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
	bool _checkNotEnter = true, _checkEsc = false;
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
			case 27:
				_checkEsc = true;
				_checkNotEnter = false;
				break;
			default:
				break;
			};
		}
	}
	if (!_checkEsc)
		pointer.checkEnter("PlayScene"); // redirect to pve or pvp
	else SceneHandle("MAIN MENU");
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
		playerManager.Minimax = 1;
	}
	playerManager.khoitao();
	playerManager.play();

}

void StartWinScene(char player) {
	PlayMusic("Background");
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
	/*PlayMusic("Victory");*/
	pointer.checkEnter("AfterPlay");

	//SceneHandle("MAIN MENU");
}

void StartExit() {
	exit(0);
}





void StartMenu() {
	ShowConsoleCursor(false);
	PlayMusic("Background");
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

void StartOption() {
	DrawObject("Background");
	DrawObject("Border");
	DrawObject("CornerEsc");
	/*visualizer.printTextBorder(57, 113);*/
	DrawObject("Text_Border",57,113);
	GotoXY(57, 1);
	DrawObject("Options_Logo");
	for (auto i : pointer.ptrOptions) { //Visualize Btn;
		i.printButton();
		bool state = false;
		switch (i.id) {
		case 0:
			state = opt.darkMode;
			break;
		case 1: 
			state = (opt.soundFlag != opt.muteFlag);
			break;
		case 2:
			state = (opt.vfxFlag != opt.muteFlag);
		default:
			break;
		}
		COORD temp = i.coord;
		temp.X -= 6;
		visualizer.printRadioBtn(temp, state);
	}

	pointer.startIndexingOptions("", pointer.ptrOptions);



	bool _checkNotEnter = true, _checkEsc = false;
	while (_checkNotEnter)
	{
		if (_kbhit())
		{
			switch (_getch())
			{
			case 'a':
			case 'w':
				pointer.startIndexingOptions("prev", pointer.ptrOptions);
				break;
			case 's':
			case 'd':
				pointer.startIndexingOptions("next", pointer.ptrOptions);
				break;
			case 13: //Enter ASCII value of enter
				_checkNotEnter = false;
				pointer.checkEnter("Options");
				break;
			case 27: //ASCII value of escape
				_checkNotEnter = false;
				_checkEsc = true;
			default:
				break;
			};
		}
	}
	if (!_checkEsc)
		SceneHandle("OPTIONS");
	else SceneHandle("MAIN MENU");
}

void StartHelp() {
	DrawObject("Background");
	DrawObject("Border");
	DrawObject("Text_Border",65,95);
	
	DrawObject("CornerEsc");
	GotoXY(65, 1);
	DrawObject("Help_Logo");

	COORD helpTextCoor;
	helpTextCoor.X = 30;
	helpTextCoor.Y = 10;
	const char* helpText[18] = { "Player Movement: ","'W': Go up","'S': Go down","'A': Go left","'D': Go right","'Enter': Mark","", "Command Key:","'P': Save game","'Z': Undo the last move", "'Esc': Halt the game/ Return to the previous scene of the game","" ,"Caro is the game using the X and O symbols to represent players and followed by a set of rules: ", "1. Two players play against each other on 16 x 16 grid.", "2. \"X\" player gets to take the first turn followed by \"O\" player.", "3. Players take turns placing their symbol on an open intersection on the board.", "4. The player that manages to create five in a row first wins the round.", "   The row can be horizontal, vertical, or diagonal as long as it is continuous." };

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
	5. The player that manages to create five in _POINT row first wins the round.The row can be horizontal, vertical, or diagonal as long as it is unbroken.
	6. Once _POINT player places _POINT symbol on the board, the symbol cannot be moved or changed.*/
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
	//set to UTF16 text cout

	DrawObject("Background");//
	DrawObject("Border");//
	DrawObject("Text_Border",62,104);
	DrawObject("CornerEsc");
	GotoXY(62, 1);
	DrawObject("About_Logo");
	_setmode(_fileno(stdout), _O_U16TEXT);
	const wchar_t* avtStorage[5] = { L"      ▄▀ ", L" █▀▀▀█▀█ ", L"  ▀▄░▄▀  ", L"    █    ", L"  ▄▄█▄▄  " };
	const wchar_t* mainAvtStorage[5] = { L"▄   ▄   ▄", L"█  █▀█  █", L"█▀▀▀█▀▀▀█", L"█ ▀▄ ▄▀ █", L"▀▀▄▄▄▄▄▀▀"};
	COORD tableCoord;
	tableCoord.X = 60;
	tableCoord.Y = 10;

	int i = 0, offset = 6;
	GotoXY(tableCoord.X - 9, tableCoord.Y);
	wcout << L"Bring to you by the 2nd group 23TNT1 - Advisor: Truong Toan Thinh" << endl;
	i = i + 2;

	GotoXY(tableCoord.X, tableCoord.Y + i);
	for (int j = 0; j < 5; j++) {
		GotoXY(tableCoord.X - 10, tableCoord.Y + i + j);
		wcout << mainAvtStorage[j];
	}
	GotoXY(tableCoord.X, tableCoord.Y + i + 2);
	wcout << L"23122008 - Mai Duc Minh Huy \t Leader - Graphic Designer - God" << endl;
	i += offset;


	GotoXY(tableCoord.X, tableCoord.Y + i);
	for (int j = 0; j < 5; j++) {
		GotoXY(tableCoord.X - 10, tableCoord.Y + i + j);
		wcout << avtStorage[j];
	}
	GotoXY(tableCoord.X, tableCoord.Y + i + 2);
	wcout << L"23122033 - Le Hoang Minh Huy \t Mechanic and Feature Sub Dev" << endl;
	i += offset;


	GotoXY(tableCoord.X, tableCoord.Y + i);
	for (int j = 0; j < 5; j++) {
		GotoXY(tableCoord.X - 10, tableCoord.Y + i + j);
		wcout << avtStorage[j];
	}
	GotoXY(tableCoord.X, tableCoord.Y + i + 2);
	wcout << L"23122036 - Nguyen Ngoc Khoa \t Mechanic and Feature Sub Dev" << endl;
	i += offset;

	GotoXY(tableCoord.X, tableCoord.Y + i);
	for (int j = 0; j < 5; j++) {
		GotoXY(tableCoord.X - 10, tableCoord.Y + i + j);
		wcout << avtStorage[j];
	}
	GotoXY(tableCoord.X, tableCoord.Y + i + 2);
	wcout << L"23122039 - Huynh Trung Kiet \t Mechanic and Feature Core Dev - Audio collector" << endl;

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
	_setmode(_fileno(stdout), _O_TEXT);//set to UTF16 text cout
	SceneHandle("MAIN MENU");
}
void StartLoad()
{
	Player playerManager(52 + 2, 3 + 1, 16, 1, 1);
	playerManager.khoitao();
	playerManager.load_game();
	DrawObject("Background");
	DrawObject("Border");
	DrawObject("PlayerFrame"); // built-in coor for player frame
	GotoXY(52, 3);
	DrawObject("BoardCanvas");
	playerManager.load_board();
	ShowConsoleCursor(true);
	playerManager.check_saveload = 1;
	if (playerManager.type == 0)
	{
		playerManager.play();
	}
	playerManager.check_saveload = 0;
}