#include <fstream>
#include <math.h>
#include <string>
#include "format.h"
#include "Store.h"

using namespace std;

Store db;

void printMenu();
wstring intIDtoWstring(int); // int->wstring id with 8 characters: 1 -> L"00000001", 69 -> L"00000069"
Book &inputNewBook(wstring);
void importDataFromFile(wstring &);
void exportDataToFile(wstring &);

int main() {
    // initial console setup
    setColor(0, 15);
    setUnicode();

    // initial assignment
    int nextID = 1;
    int menuSelection = -1;

    // ==> go  
    while(menuSelection != 0) {
        menuSelection = -1;
        
        // menu
        do {
            clrscr();
            printMenu();
            wcout << L">> Lựa chọn của bạn: ";
            wcin >> menuSelection;
        } while (menuSelection < 0 || menuSelection > 7);

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

        // 6. import data from file
        if(menuSelection == 6) {
            wstring fileName;
            wcout << L">> Nhập tên file: ";
            cin.ignore();
            wcin >> fileName;
            importDataFromFile(fileName);
        }
        
        // 7. export data to file
        if(menuSelection == 7) {
            wstring fileName;
            wcout << L">> Nhập tên file: ";
            cin.ignore();
            wcin >> fileName;
            exportDataToFile(fileName);
        }

        if(menuSelection != 0)
            pause();
    }

    setColor(0, 7); //default console color
    return 0;
}


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
          << L"|            6. Nhập danh sách từ file             |" << endl
          << L"|            7. Xuất danh sách ra file             |" << endl
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

void importDataFromFile(wstring& fileName) {
    ifstream fin(fileName.c_str());
    try {
        if( fin.is_open() ) {
            // delete all data in order to import new one :)
            db.deleteAll();
            
            // input length
            int length;
            fin >> length;
            
            //input data: 
            string ignore, id, name, author, category;
            double price;
            int stock, sold;
            
            for(int i = 0; i < length; i++) {
                fin.ignore();
                getline(fin, id);
                getline(fin, name);
                getline(fin, author);
                getline(fin, category);
                wstring wid = utf8_to_utf16(id);
                wstring wname = utf8_to_utf16(name);
                wstring wauthor = utf8_to_utf16(author);
                wstring wcategory = utf8_to_utf16(category);
                fin >> price >> sold >> stock;
                Book newBook(wid, wname, wauthor, wcategory, price, sold, stock);
                db.addTail(newBook);
            }
            fin.close();
            wcout << L"Nhập dữ liệu thành công!" << endl;
        }
        else {
            wcout << setColor(0,12) << L"Mở file thất bại!" << setColor(0,15) << endl;
        }
    }
    catch(...) {
        wcout << setColor(0,12) << L"Nhập dữ liệu thất bại!" << setColor(0,15) << endl;
    }
}

void exportDataToFile(wstring& fileName) {
    ofstream fout(fileName.c_str());
    try {
        if( fout.is_open() ) {
            fout << db.getLength() << endl;
            for (int i = 0; i < db.getLength(); i++) {
                string id = utf16_to_utf8(db.getBook(i).getID());
                string name = utf16_to_utf8(db.getBook(i).getName());
                string author = utf16_to_utf8(db.getBook(i).getAuthor());
                string category = utf16_to_utf8(db.getBook(i).getCategory());
                fout << id << endl
                     << name << endl
                     << author << endl
                     << category << endl
                     << db.getBook(i).getPrice() << endl
                     << db.getBook(i).getStock() << endl
                     << db.getBook(i).getSold() << endl;
            }
            fout.close();
            wcout << setColor(0,10) << L"Xuất dữ liệu thành công!" << setColor(0,15) << endl;
        }
        else {
            wcout << setColor(0,12) << L"Xuất dữ liệu thất bại!" << setColor(0,15) << endl;
        }
    }
    catch(...) {
        wcout << setColor(0,12) << L"Xuất dữ liệu thất bại!" << setColor(0,15) << endl;
    }
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
