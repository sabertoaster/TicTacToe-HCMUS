#include "View.h"


//Unicode UTF8 char lib 
#include <fcntl.h>
#include <io.h>

using namespace std;

void FixConsoleWindow()
{
	// [Disable resize property of console]
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);

	ModifyConsoleSize(120, 40);
	// [REMOVE THE SCROLL BAR]
	// get handle to the console window
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	// retrieve screen buffer info
	CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
	GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);
	// current window size
	short winWidth = scrBufferInfo.srWindow.Right - scrBufferInfo.srWindow.Left + 1;
	short winHeight = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;
	// current screen buffer size
	short scrBufferWidth = scrBufferInfo.dwSize.X;
	short scrBufferHeight = scrBufferInfo.dwSize.Y;
	// to remove the scrollbar, make sure the window height matches the screen buffer height
	COORD newSize;
	newSize.X = scrBufferWidth;
	newSize.Y = winHeight;
	// set the new screen buffer dimensions
	int Status = SetConsoleScreenBufferSize(hOut, newSize);
	if (Status == 0)
	{
		cout << "SetConsoleScreenBufferSize() failed! Reason : " << GetLastError() << endl;
		exit(Status);
	}

}

void ModifyConsoleSize(int width, int height) {
	// Create a SMALL_RECT structure to define the new console size
	SMALL_RECT rect;
	rect.Left = 0;
	rect.Top = 0;
	rect.Right = width - 1;
	rect.Bottom = height - 1;

	// Set the console screen buffer size to match the new size
	COORD size;
	size.X = width;
	size.Y = height;

	// Set the console window size and screen buffer size
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), size);
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &rect);

}

COORD GetConsoleCursorPosition()
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE); // get console_output_handle
	if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
	{
		return cbsi.dwCursorPosition;
	}
	else
	{
		// The function failed. Call GetLastError() for details.
		COORD invalid = { 0, 0 };
		return invalid;
	}
}

int getColor(color bgColor, color fontColor) {
	return 16 * bgColor + fontColor;
};
void changeFontColor(color backgroundColor, color fontColor) {
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleOutput, getColor(backgroundColor, fontColor));
}

enum objID {
	mainLogo,
	button,
	background,
	boardCanvas,
	xMark,
	oMark
};
objID string_hash(string const& inString) {
	if (inString == "Main_Logo") return mainLogo;
	if (inString == "Button") return button;
	if (inString == "Background") return background;
}

void Button::printButton() {
	/*top layer*/
	GotoXY(coord.X, coord.Y);
	wcout << L"╔═";
	for (int i = 0; i < nameLength; i++) {
		wcout << L"═";
	}
	wcout << L"═╗";

	/*mid layer*/
	GotoXY(coord.X, coord.Y + 1);
	wcout << L"║ ";
	wcout << buttonName;
	wcout << L" ║";

	/*bot layer*/
	GotoXY(coord.X, coord.Y + 2);
	wcout << L"╚═";
	for (int i = 0; i < nameLength; i++) {
		wcout << L"═";
	}
	wcout << L"═╝";
}
void Button::playScene() {
	wstring ws(buttonName);
	string temp(ws.begin(), ws.end());
	SceneHandle(temp);
}


// [define visualizer func]
void Visualizer::printMainLogo() {
	COORD currentCoord = GetConsoleCursorPosition();
	for (int i = 0; i < sizeof(mainLogo) / sizeof(mainLogo[0]); i++) {
		wcout << mainLogo[i];
		GotoXY(currentCoord.X, currentCoord.Y + 1);
		currentCoord.Y++; //update the new pointer coordinate
	}
}
void Visualizer::printBackground(int width, int height) {
	SetConsoleTextAttribute(hConsoleOutput, 15);
	//wcout << L"Width" << csbi.dwSize.X << L"Height" << csbi.dwSize.Y << endl; //test width and height of console
	GotoXY(0, 0);
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			wcout << fullBlock;
		}
	}
	SetConsoleTextAttribute(hConsoleOutput, 240); // 240 for black font white background
	printBorder();
}
void Visualizer::printBorder() {//hard-code [saber]
	GotoXY(0, 0);
	wcout << L"╔";
	for (int i = 1; i <= 41; i++) {
		GotoXY(i, 0);
		wcout << L"═";
	}
	wcout << L"╗";
	GotoXY(76, 0);
	wcout << L"╔";
	for (int i = 77; i <= 118; i++) {
		GotoXY(i, 0);
		wcout << L"═";
	}
	wcout << L"╗";

	GotoXY(0, 1);
	wcout << L"║";
	GotoXY(41, 1);
	wcout << L"╔";
	GotoXY(42, 1);
	wcout << L"╝";
	GotoXY(76, 1);
	wcout << L"╚";
	GotoXY(77, 1);
	wcout << L"╗";
	GotoXY(119, 1);
	wcout << L"║";

	for (int i = 2; i <= 5; i++) {
		GotoXY(0, i);
		wcout << L"║";
		GotoXY(41, i);
		wcout << L"║";
		GotoXY(77, i);
		wcout << L"║";
		GotoXY(119, i);
		wcout << L"║";
	}

	GotoXY(0, 6);
	wcout << L"║";
	GotoXY(41, 6);
	wcout << L"╚";
	GotoXY(42, 6);
	wcout << L"╗";
	GotoXY(76, 6);
	wcout << L"╔";
	GotoXY(77, 6);
	wcout << L"╝";
	GotoXY(119, 6);
	wcout << L"║";

	GotoXY(0, 7);
	wcout << L"║";
	GotoXY(42, 7);
	wcout << L"╚";
	for (int i = 43; i <= 75; i++) {
		GotoXY(i, 7);
		wcout << L"═";
	}
	GotoXY(76, 7);
	wcout << L"╝";
	GotoXY(119, 7);
	wcout << L"║";

	for (int i = 8; i <= 38; i++) {
		GotoXY(0, i);
		wcout << L"║";
		GotoXY(119, i);
		wcout << L"║";
	}

	GotoXY(0, 39);
	wcout << L"╚";
	for (int i = 1; i <= 118; i++) {
		GotoXY(i, 39);
		wcout << L"═";
	}
	wcout << L"╝";
}
void Visualizer::printBackgroundAnimation(int index, int coorX, int coorY) {
	GotoXY(coorX, coorY);
	if (index / 5 == 0) {
		SetConsoleTextAttribute(hConsoleOutput, 244); //244
		wcout << big_x[index % 5] << L"\n";
	}
	else {
		SetConsoleTextAttribute(hConsoleOutput, 241); //241
		wcout << big_o[index % 5] << L"\n";
	}
}
void Visualizer::printButton() { //[saber]
	for (auto i : buttons) {
		i.printButton();
	}
}

Visualizer visualizer;

void DrawObject(string objName) {
	_setmode(_fileno(stdout), _O_U16TEXT);//set to UTF16 text cout
	switch (string_hash(objName))
	{
	case mainLogo:
		visualizer.printMainLogo();
		break;
	case button:
		visualizer.printButton();
		break;
	case background:
		visualizer.printBackground(120, 40);
		break;
	default:
		break;
	}
	_setmode(_fileno(stdout), _O_TEXT);//return to normal cout

  /*wcout << L"  █████╗ █████╗ ██████╗  ██████╗\n";
	wcout << L"██╔════╝██╔══██╗██╔══██╗██╔═══██╗\n";
	wcout << L"██║     ███████║██████╔╝██║   ██║\n";
	wcout << L"██║     ██╔══██║██╔══██╗██║   ██║\n";
	wcout << L"╚██████╗██║  ██║██║  ██║╚██████╔╝\n";
	wcout << L" ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝\n";*/
}

void SceneHandle(string sceneName) {
	if (sceneName == "MAIN MENU") {
		StartMenu();
	}
	if (sceneName == "PLAY") {
		StartMenu();
	}
	if (sceneName == "LOAD") {
		StartMenu();
	}
	if (sceneName == "OPTIONS") {
		StartMenu();
	}
	if (sceneName == "HELP") {
		StartMenu();
	}
	if (sceneName == "ABOUT") {
		StartMenu();
	}
	if (sceneName == "EXIT") {
		StartExit();
	}
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

