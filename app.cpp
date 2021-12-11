#include <fstream>
#include <math.h>
#include <string>
#include "format.h"
#include "BookStore.h"

using namespace std;

BookStore db;

void printMenu();
wstring intIDtoWstring(int); // int->wstring id with 8 characters: 1 -> L"00000001", 69 -> L"00000069"
int wstringIDtoInt(wstring);
Book &inputNewBook(wstring);
void importDataFromFile(wstring &);
void exportDataToFile(wstring &);

int main() {
    // initial console setup
    setColor(0, 15);
    setUnicode();
    int nextID = 1;

    // initial assignment
    
    int menuSelection = -1;

    /*
    TODO:
        WHILE LOOP: (until menuSelection = 0 which mean exit)
            Print menu -> Select (VALIDATED) -> Do selection 
    */
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
        clrscr();
        // 1. print list
        if(menuSelection == 1) {
            if(db.getLength() == 0)
                wcout << setColor(0,12) << L"Danh sách rỗng!" << setColor(0,15) << endl; 
            else 
                db.show();
        }

        // 2. show specific book info by ID
        if(menuSelection == 2) {
            wstring id;
            wcout << setColor(0, 10) << L"Xem thông tin sách" << setColor(0, 15) << endl
                  << L">> Nhập ID sách: ";
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

        // 3. add book (new book id = nextID)
        if(menuSelection == 3) {
            wstring id = intIDtoWstring(nextID);
            wcout << setColor(0, 15) << L"THÊM ĐẦU SÁCH MỚI VÀO DANH SÁCH" << endl
                  << setColor(0, 10) << L"Đầu sách này sẽ có ID "
                  << setColor(0, 14) << id << endl
                  << setColor(0, 10) << L"Nhập thông tin sách mới: " << setColor(0,15) << endl;
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

            /* set nextID
            TODO:
                Find the highest ID (max)
                Plus it to 1 and assign it to nextID
            */
            int max = -1;
            for (int i = 0; i < db.getLength(); i++) {
                int id = stoi(db.getBook(i).getID());
                if(id > max) {
                    max = id;
                }
            }
            nextID = max + 1;
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


/**********************************************************************************/

void printMenu() {
    wcout << L"+--------------------------------------------------+" << endl
          << L"|                                                  |" << endl
          << L"|            "
          << setColor(0, 14) << L"QUẢN LÍ SÁCH TRONG CỬA HÀNG"
          << setColor(0, 15) << L"           |"                      << endl
          << L"|                                                  |" << endl
          << L"|            0. Thoát                              |" << endl
          << L"|            1. In danh sách các đầu sách          |" << endl
          << L"|            2. Xem thông tin sách                 |" << endl
          << L"|            3. Thêm đầu sách                      |" << endl
          << L"|            4. Xóa đầu sách                       |" << endl
          << L"|            5. Cập nhật sách                      |" << endl
          << L"|            6. Nhập danh sách từ file             |" << endl
          << L"|            7. Xuất danh sách ra file             |" << endl
          << L"|                                                  |" << endl
          << L"+--------------------------------------------------+" << endl;
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

void importDataFromFile(wstring& fileName) {
    /*
     * It impossible to import data from a utf-16 encoding .txt file, but this program store text data as utf-16 wstring,
     * So data is saved in utf-8 encoding .txt file    
     TODO:
        ==> Open utf-8 file
        ==> import data to a utf-8 string
        ==> convert string to wstring using utf8_to_utf16 function (in format.h)
    */
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
    /* 
     TODO:
        ==> Open file (utf8)
        ==> Convert utf16 wstring to utf8 string (using utf16_to_utf8 in format.h) 
        ==> export data as utf8 string
    */
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
    /*
    TODO:
        input all information of a book
        Create a book object with input information --> return that object;
    */

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
