#include <iostream>
#include <math.h>
#include <string>
#include "format.cpp"
#include "Store.h"

using namespace std;

void printMenu();
wstring intIDtoWstring(int); // int->wstring id with 8 characters: 1 -> L"00000001", 69 -> L"00000069"
Book &inputNewBook(int);

/********************************************************************************************************/

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

Book& inputNewBook(wstring id) {
    // initial
    wstring name;
    wstring author;
    wstring category;
    double price = -1; //dollars
    int sold = -1;
    int stock = -1;

    // input information
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
    do {
        wcout << L">> Nhập giá sách ($): ";
        wcin >> price;
    } while (price <= 0);
    do {
        wcout << L">> Nhập số lượng trong kho: ";
        wcin >> stock;
    } while (stock < 0);
    do {
        wcout << L">> Nhập số lượng đã bán: ";
        wcin >> sold;
    } while (sold < 0);

    Book *newBook = new Book(id, name, author, category, price, stock, sold);
    return *newBook;
}


int main() {
    // initial console setup
    setColor(0, 15);
    setUnicode();

    // initial assignment
    int nextID;
    int menuSelection = -1;
    Store db;

    // test tí =))) 
    Book b1(L"00000001", L"The Old Man and the Sea", L"Ernest Hemingway", L"Tiểu thuyết", 20, 10, 1);
    Book b2(L"00000002", L"化物語", L"西尾維新", L"Tiểu thuyết", 10, 100, 70);
    Book b3(L"00000003", L"A Brief History Of Time", L"Stephen Hawking", L"Khoa học", 10, 100, 70);
    nextID = 4;
    db.addTail(b1);
    db.addTail(b2);
    db.addTail(b3);

    // ==> go  
    while(menuSelection != 0) {
        menuSelection = -1;
        do {
            clrscr();
            printMenu();
            wcout << L">> Lựa chọn của bạn: ";
            wcin >> menuSelection;
        } while (menuSelection < 0 || menuSelection > 5);

        // 1. print list
        if(menuSelection == 1) {
            if(db.getLength() == 0)
                wcout << L"Danh sách rỗng!" << endl; 
            else 
                db.show();
        }

        // 2. show specific book info by ID
        if(menuSelection == 2) {
            wstring id;
            wcout << L"Nhập ID sách: ";
            wcin >> id;

            int index = db.getBookIndexByID(id);
            if(index == -1) {
                wcout << setColor(0, 12) << L"Không tìm thấy sách có ID "
                      << setColor(0, 14) << id << setColor(0, 15) << endl;
            }
            else {
                db.getBook(index).show();
            }
        }   

        // 3. add book by ID
        if(menuSelection == 3) {
            wstring id = intIDtoWstring(nextID);
            wcout << L"Nhập thông tin sách mới: " << endl;
            Book newBook = inputNewBook(id);
            db.addTail(newBook);
            wcout << setColor(0, 10) << L"Thêm thành công sách với ID "
                  << setColor(0, 14) << id << setColor(0, 15) << endl;
            nextID++;   
        }

        // 4. delete book by ID
        if(menuSelection == 4) {
            wstring id;
            wcout << L"Nhập ID sách: ";
            wcin >> id;

            int index = db.getBookIndexByID(id);
            if(index == -1) {
                wcout << setColor(0, 12) << L"Không tìm thấy sách có ID "
                      << setColor(0, 14) << id << setColor(0, 15) << endl;
            }
            else {
                db.deleteAt(index);
                wcout << setColor(0, 10) << L"Xóa thành công sách có ID "
                      << setColor(0, 14) << id << setColor(0, 15) << endl;
            }
        }

        // 5. update book info by ID
        if(menuSelection == 5) {
            wstring id;
            wcout << L"Nhập ID sách: ";
            wcin >> id;

            int index = db.getBookIndexByID(id);
            if(index == -1) {
                wcout << setColor(0, 12) << L"Không tìm thấy sách có ID "
                      << setColor(0, 14) << id << setColor(0, 15) << endl;
            }
            else {
                wcout << L"Cập nhật thông tin sách: " << endl;
                Book newBook = inputNewBook(id);
                db.UpdateAt(index, newBook);
                wcout << setColor(0, 10) << L"Cập nhật thành công sách có ID "
                      << setColor(0, 14) << id << setColor(0, 15) << endl;
            }
        }

        if(menuSelection != 0)
            pause();
    }

    setColor(0, 7); //default console color
    return 0;
}