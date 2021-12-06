#include <iostream>
#include <math.h>
#include <string>
#include "format.cpp"
#include "Store.h"

using namespace std;

/**************************************************************/

void printMenu() {
    wcout << L"+--------------------------------------------------+" << endl
          << L"|                                                  |" << endl
          << L"|       CHƯƠNG TRÌNH QUẢN LÝ CỬA HÀNG SÁCH         |" << endl
          << L"|                                                  |" << endl
          << L"|            0. Thoát                              |" << endl
          << L"|            1. In danh sách sách                  |" << endl
          << L"|            2. Xem thông tin sách                 |" << endl
          << L"|            3. Thêm sách                          |" << endl
          << L"|            4. Xóa sách                           |" << endl
          << L"|            5. Cập nhật sách                      |" << endl
          << L"|                                                  |" << endl
          << L"+--------------------------------------------------+" << endl;
}

wstring intIDtoWstring(int id) {
    wstring strID = to_wstring(id);
    while(strID.length() < 8) {
        strID = L"0" + strID;
    }
    return strID;
}

Book& inputNewNhanVien(int intID) {
    wstring id = intIDtoWstring(intID);
    wstring name;
    wstring author;
    wstring category;
    double price; //dollars
    int sold;
    int stock;
    wcout << L"Nhập thông tin sách mới: " << endl;
    wcout << L">> Nhập tên sách: ";
    wcin.ignore();
    wcin.ignore();
    getline(wcin, name);
    wcout << L">> Nhập tên tác giả: ";
    wcin.ignore();
    getline(wcin, author);
    wcout << L">> Nhập thể loại: ";
    wcin.ignore();
    getline(wcin, category);
    wcout << L">> Nhập giá sách ($): ";
    wcin >> price;
    wcout << L">> Nhập số lượng trong kho: ";
    wcin >> stock;
    wcout << L">> Nhập số lượng đã bán: ";
    wcin >> sold;

    Book *newBook = new Book(id, name, author, category, price, stock, sold);
    return *newBook;
}


int main() {
    // initial console setup
    setColor(0, 15);
    setUnicode();

    // initial assignment
    int nextID = 0;
    int menuSelection = -1;
    Store db;

    // go 
    while(menuSelection != 0) {
        menuSelection = -1;
        do {
            clrscr();
            printMenu();
            wcout << L">> Lựa chọn của bạn: ";
            wcin >> menuSelection;
        } while (menuSelection < 0 || menuSelection > 5);

        // print list
        if(menuSelection == 1) {
            if(db.getLength() == 0)
                wcout << L"Danh sách rỗng!" << endl; 
            else 
                db.show();
        }

        // show specific book info by ID
        if(menuSelection == 2) {
            wstring tempID;
            wcout << L"Nhập ID sách: ";
            wcin >> tempID;

            int index = db.getBookIndexByID(tempID);
            if(index == -1) {
                wcout << L"Không tìm thấy sách với ID ";
                wcout << setColor(0, 14) << tempID << setColor(0, 15) << endl;
            }
            else {
                db.getBook(index).show();
            }
        }   

        // add book by ID
        if(menuSelection == 3) {
            nextID++;
            Book newBook = inputNewNhanVien(nextID);
            db.addTail(newBook);
        }

        // delete book by ID

        // update book info by ID

        if(menuSelection != 0)
            pause();
    }



    // Book b1("00000001", "The Old Man and the Sea", "Ernest Hemingway", "Novel", 20, 10, 1);
    // Book b2("00000002", "化物語", "西尾維新", "Novel", 10, 100, 70);
    


    setColor(0, 7);
}