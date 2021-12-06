#pragma once
#include <Windows.h>
#include <fcntl.h> //_O_WTEXT
#include <io.h>    //_setmode()

using namespace std;

void setUnicode();
wstring setColor();
void clrscr();
void pause();

/******************************************************/

void setUnicode() {
    _setmode(_fileno(stdout), _O_WTEXT); //needed for output
    _setmode(_fileno(stdin), _O_WTEXT); //needed for input
}

wstring setColor(int background_color, int text_color)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    int color_code = background_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
    /*-----------------------------------------------------------
    0 = Black       1 = Blue        2 = Green       3 = Aqua
    4 = Red         5 = Purple      6 = Yellow      7 = White
    8 = Gray        9 = Li Blue     10 = Li Green    11 = Li Aqua
    12 = Li Red     13 = Li Purple  14 = Li Yellow  15 = Bri White
    -------------------------------------------------------------*/
    return L"";
}

void clrscr() {
    system("cls");
}

void pause() {
    wcout << setColor(0,10) << L"Nhấn phím bất kỳ để tiếp tục..." << endl << setColor(0,15);
    system("pause > nul");
}