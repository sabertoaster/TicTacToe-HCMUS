#pragma once

#include <iostream>
#include <windows.h>
#include <wchar.h>
#include <string>
#include <vector>

struct Button {
public:
	Button(const wchar_t* btnName) {
		nameLength = static_cast<int>(wcslen(btnName)); // cast to int type from size_t
		buttonName = btnName;
		///*top layer*/
		//wcscat_s(buttonImgInactive[0], 2, L"╔═");
		//for (int i = 0; i < nameLength; i++) {
		//	wcscat_s(buttonImgInactive[0], 1, L"═");
		//}
		//wcscat_s(buttonImgInactive[0], 2, L"═╗");
		///*mid layer*/
		//wcscat_s(buttonImgInactive[1], 2, L"║ ");
		//wcscat_s(buttonImgInactive[1], nameLength, btnName);
		//wcscat_s(buttonImgInactive[1], 2, L" ║");
		///*bot layer*/
		//wcscat_s(buttonImgInactive[2], 2, L"╚═");
		//for (int i = 0; i < nameLength; i++) {
		//	wcscat_s(buttonImgInactive[2], 1, L"═");
		//}
		//wcscat_s(buttonImgInactive[2], 2, L"═╝");
	}
	int id = -1;
	COORD coord;
	const wchar_t* buttonName;
	int nameLength;
	wchar_t* buttonImgInactive[3];
	wchar_t* buttonImgActive[5];
	Button* nextBtn;
	Button* prevBtn;

	void playScene();

	void printButton();

	//next scene operations [saber]
};

#include "Control.h"

using namespace std;

void FixConsoleWindow();
void ModifyConsoleSize(int width, int height);
// [Return the Coordinates of pointer console windows]
COORD GetConsoleCursorPosition();

// [Return the color pallete num of request background and font]
enum color { black, blue1, green1, blue2, red, purple1, darkbeige, grey1, grey2, blue3, green2, cyan, pink, purple2, beige, white };
int getColor(color bgColor, color fontColor);
void changeFontColor(color backgroundColor, color fontColor);

// [Pen simulator]
struct Visualizer {
public:
	const wchar_t* mainLogo[6] = { L"  █████╗ █████╗ ██████╗  ██████╗", L"██╔════╝██╔══██╗██╔══██╗██╔═══██╗", L"██║     ███████║██████╔╝██║   ██║", L"██║     ██╔══██║██╔══██╗██║   ██║",L"╚██████╗██║  ██║██║  ██║╚██████╔╝", L" ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝" };
	const wchar_t* playButtonSmall[3] = { L"╔══════╗", L"║ Play ║", L"╚══════╝" };
	const wchar_t* loadButtonSmall[3] = { L"╔══════╗", L"║ Load ║", L"╚══════╝" };
	const wchar_t* helpButtonSmall[3] = { L"╔══════╗", L"║ Help ║", L"╚══════╝" };
	const wchar_t* exitButtonSmall[3] = { L"╔══════╗", L"║ Exit ║", L"╚══════╝" };
	const wchar_t* big_x[5] = { L"O))   O))", L"  O) O)) ", L"   O)    ", L" O)  O)) ", L"O))   O))" };
	const wchar_t* big_o[5] = { L"   O))    ", L" O))  O)) ", L"O))    O))", L" O))  O)) ", L"   O))    " };
	const wchar_t* fullBlock = L"█";
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);


	vector<Button> buttons;
	Visualizer() {
		GetConsoleScreenBufferInfo(hConsoleOutput, &csbi); // initialize value to csbi when create class instance
	}

	void printMainLogo();
	void printBackground(int width, int height);
	void printBorder();
	void printBackgroundAnimation(int index, int coorX, int coorY);
	void printButton();
};

extern Visualizer visualizer;


// [Draw custom object] 
void DrawObject(string objName);

void SceneHandle(string sceneName);

void ShowConsoleCursor(bool showFlag);