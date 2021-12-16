#pragma once
#include <iostream>
#include <Windows.h>
#include <fcntl.h> //_O_WTEXT -> SetUniCode();
#include <io.h>    //_setmode() -> SetUniCode();
#include <locale>  
#include <codecvt> 

using namespace std;

void SetUnicode();
wstring SetColor(int, int);
void clrscr();
void pause();
wstring intIDtoWstring(int);
wstring utf8_to_utf16(const string &);
string utf16_to_utf8(const wstring &);

/******************************************************/

void SetUnicode() {
    _setmode(_fileno(stdout), _O_WTEXT); //needed for output
    _setmode(_fileno(stdin), _O_WTEXT); //needed for input
}

wstring SetColor(int background_color, int text_color)
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
    wcout << endl << SetColor(0,10) << L"Nhấn phím bất kỳ để tiếp tục..." << endl << SetColor(0,15);
    system("pause > nul");
}

wstring intIDtoWstring(int id) {
    /*
        TODO: convert int id => wstring
              add "0" until id length = 8
    */
    wstring strID = to_wstring(id);
    while(strID.length() < 8) {
        strID = L"0" + strID;
    }
    return strID;
}

// string (utf8) -> u16string -> wstring
wstring utf8_to_utf16(const string& utf8)
{
    wstring_convert<codecvt_utf8_utf16<char16_t>,char16_t> convert; 
    u16string utf16 = convert.from_bytes(utf8);
    wstring wstr(utf16.begin(), utf16.end());
    return wstr;
}

// wstring -> u16string -> string (utf8)
string utf16_to_utf8(const wstring& utf16) {
    u16string u16str(utf16.begin(), utf16.end());
    wstring_convert<codecvt_utf8_utf16<char16_t>,char16_t> convert; 
    string utf8 = convert.to_bytes(u16str);
    return utf8;
}