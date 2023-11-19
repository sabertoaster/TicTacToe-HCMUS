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
	const wchar_t* aboutLogo[6] = { L" █████╗ ██████╗  ██████╗ ██╗   ██╗████████╗", L"██╔══██╗██╔══██╗██╔═══██╗██║   ██║╚══██╔══╝", L"███████║██████╔╝██║   ██║██║   ██║   ██║   ", L"██╔══██║██╔══██╗██║   ██║██║   ██║   ██║   ", L"██║  ██║██████╔╝╚██████╔╝╚██████╔╝   ██║   ", L"╚═╝  ╚═╝╚═════╝  ╚═════╝  ╚═════╝    ╚═╝   " };
	const wchar_t* big_x[5] = { L"O))   O))", L"  O) O)) ", L"   O)    ", L" O)  O)) ", L"O))   O))" };
	const wchar_t* big_o[5] = { L"   O))    ", L" O))  O)) ", L"O))    O))", L" O))  O)) ", L"   O))    " };
	const wchar_t* avt_x[8] = { L" ___    ___ ", L"|\\  \\  /  /|", L"\\ \\  \\/  / /", L" \\ \\    / / ", L"  /     \\/  ", L" /  /\\   \\  ", L"/__/ \\\\ __\\ ", L"|__|/ \\|__| "};
	COORD avtXCoor = { 0, 0 };
	const wchar_t* avt_o[7] = { L" ________     ", L"|\\   __  \\    ", L"\\ \\  \\ \\  \\   ", L" \\ \\  \\ \\  \\  ", L"  \\ \\  \\_\\  \\ ", L"   \\ \\_______\\", L"    \\|_______|"};	
	COORD avtOCoor = { 0, 0 };
	const wchar_t* winnerXBanner[8] = { L" █████ █████    █████  █████████     ███████████ █████   █████ ██████████    █████   ███   █████ █████ ██████   █████ ██████   █████ ██████████ ███████████  ", L"░░███ ░░███    ░░███  ███░░░░░███   ░█░░░███░░░█░░███   ░░███ ░░███░░░░░█   ░░███   ░███  ░░███ ░░███ ░░██████ ░░███ ░░██████ ░░███ ░░███░░░░░█░░███░░░░░███ ", L" ░░███ ███      ░███ ░███    ░░░    ░   ░███  ░  ░███    ░███  ░███  █ ░     ░███   ░███   ░███  ░███  ░███░███ ░███  ░███░███ ░███  ░███  █ ░  ░███    ░███ ", L"  ░░█████       ░███ ░░█████████        ░███     ░███████████  ░██████       ░███   ░███   ░███  ░███  ░███░░███░███  ░███░░███░███  ░██████    ░██████████  ", L"   ███░███      ░███  ░░░░░░░░███       ░███     ░███░░░░░███  ░███░░█       ░░███  █████  ███   ░███  ░███ ░░██████  ░███ ░░██████  ░███░░█    ░███░░░░░███ ", L"  ███ ░░███     ░███  ███    ░███       ░███     ░███    ░███  ░███ ░   █     ░░░█████░█████░    ░███  ░███  ░░█████  ░███  ░░█████  ░███ ░   █ ░███    ░███ ", L" █████ █████    █████░░█████████        █████    █████   █████ ██████████       ░░███ ░░███      █████ █████  ░░█████ █████  ░░█████ ██████████ █████   █████", L"░░░░░ ░░░░░    ░░░░░  ░░░░░░░░░        ░░░░░    ░░░░░   ░░░░░ ░░░░░░░░░░         ░░░   ░░░      ░░░░░ ░░░░░    ░░░░░ ░░░░░    ░░░░░ ░░░░░░░░░░ ░░░░░   ░░░░░ " };
	const wchar_t* winnerOBanner[8] = { L" ▄██████▄        ▄█     ▄████████          ███        ▄█    █▄       ▄████████       ▄█     █▄   ▄█  ███▄▄▄▄   ███▄▄▄▄      ▄████████    ▄████████", L"███    ███      ███    ███    ███      ▀█████████▄   ███    ███     ███    ███      ███     ███ ███  ███▀▀▀██▄ ███▀▀▀██▄   ███    ███   ███    ███", L"███    ███      ███▌   ███    █▀          ▀███▀▀██   ███    ███     ███    █▀       ███     ███ ███▌ ███   ███ ███   ███   ███    █▀    ███    ███", L"███    ███      ███▌   ███                 ███   ▀  ▄███▄▄▄▄███▄▄  ▄███▄▄▄          ███     ███ ███▌ ███   ███ ███   ███  ▄███▄▄▄      ▄███▄▄▄▄██▀", L"███    ███      ███▌ ▀███████████          ███     ▀▀███▀▀▀▀███▀  ▀▀███▀▀▀          ███     ███ ███▌ ███   ███ ███   ███ ▀▀███▀▀▀     ▀▀███▀▀▀▀▀  ", L"███    ███      ███           ███          ███       ███    ███     ███    █▄       ███     ███ ███  ███   ███ ███   ███   ███    █▄  ▀███████████", L"███    ███      ███     ▄█    ███          ███       ███    ███     ███    ███      ███ ▄█▄ ███ ███  ███   ███ ███   ███   ███    ███   ███    ███", L" ▀██████▀       █▀    ▄████████▀          ▄████▀     ███    █▀      ██████████       ▀███▀███▀  █▀    ▀█   █▀   ▀█   █▀    ██████████   ███    ███" };
	const wchar_t* winnerOBanner1[9] = { L" ▒█████      ██▓  ██████    ▄▄▄█████▓ ██░ ██ ▓█████     █     █░ ██▓ ███▄    █  ███▄    █ ▓█████  ██▀███  ", L"▒██▒  ██▒   ▓██▒▒██    ▒    ▓  ██▒ ▓▒▓██░ ██▒▓█   ▀    ▓█░ █ ░█░▓██▒ ██ ▀█   █  ██ ▀█   █ ▓█   ▀ ▓██ ▒ ██▒", L"▒██░  ██▒   ▒██▒░ ▓██▄      ▒ ▓██░ ▒░▒██▀▀██░▒███      ▒█░ █ ░█ ▒██▒▓██  ▀█ ██▒▓██  ▀█ ██▒▒███   ▓██ ░▄█ ▒", L"▒██   ██░   ░██░  ▒   ██▒   ░ ▓██▓ ░ ░▓█ ░██ ▒▓█  ▄    ░█░ █ ░█ ░██░▓██▒  ▐▌██▒▓██▒  ▐▌██▒▒▓█  ▄ ▒██▀▀█▄  ", L"░ ████▓▒░   ░██░▒██████▒▒     ▒██▒ ░ ░▓█▒░██▓░▒████▒   ░░██▒██▓ ░██░▒██░   ▓██░▒██░   ▓██░░▒████▒░██▓ ▒██▒", L"░ ▒░▒░▒░    ░▓  ▒ ▒▓▒ ▒ ░     ▒ ░░    ▒ ░░▒░▒░░ ▒░ ░   ░ ▓░▒ ▒  ░▓  ░ ▒░   ▒ ▒ ░ ▒░   ▒ ▒ ░░ ▒░ ░░ ▒▓ ░▒▓░", L"  ░ ▒ ▒░     ▒ ░░ ░▒  ░ ░       ░     ▒ ░▒░ ░ ░ ░  ░     ▒ ░ ░   ▒ ░░ ░░   ░ ▒░░ ░░   ░ ▒░ ░ ░  ░  ░▒ ░ ▒░", L"░ ░ ░ ▒      ▒ ░░  ░  ░       ░       ░  ░░ ░   ░        ░   ░   ▒ ░   ░   ░ ░    ░   ░ ░    ░     ░░   ░ ", L"    ░ ░      ░        ░               ░  ░  ░   ░  ░       ░     ░           ░          ░    ░  ░   ░     " };

	int colorArr[8] = {244, 246, 254, 242, 251, 241, 253, 246};

	const wchar_t* fullBlock = L"█";
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	vector<Button> buttons = {};
	Visualizer() {
		GetConsoleScreenBufferInfo(hConsoleOutput, &csbi); // initialize value to csbi when create class instance
	}

	void printLogo(string str);
	void printBackground(int width, int height);
	void printMenuBorder();
	void printBorder();
	void printPlayerFrame(char input); // X or O
	void printAvatar(char input, int color);

	void printBackgroundAnimation(int index, int coorX, int coorY);
	void printWinAnimation(char, int, int, COORD);
	void printButton();

	void printBoardCanvas(int numCell);
};

extern Visualizer visualizer;


// [Draw custom object] 
void DrawObject(string objName);

void SceneHandle(string sceneName);

void ShowConsoleCursor(bool showFlag);