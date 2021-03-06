#include <fstream>
#include "BookStore.h"

using namespace std;

void printMenu();
void importDataFromFile(wstring &);
void exportDataToFile(wstring &);

int main() {
    // initial console setup
    SetColor(0, 15);
    SetUnicode();

    // initial assignment
    int menuSelection = -1;
    BookStore *db = BookStore::GetInstance();

    /*  
        -> WHILE LOOP: (until menuSelection = 0 which mean exit)
            Print menu -> Select (VALIDATED) -> Do the selected function
    */
    // ==> go
    while(menuSelection != 0) {
        Menu:
        menuSelection = -1;
        
        // menu and select
        do {
            Clrscr();
            printMenu();
            wcout << L">> Lựa chọn chức năng: ";
            wcin >> menuSelection;
        } while (menuSelection < 0 || menuSelection > 8);
        
        Clrscr();
        
        // 1. print list
        if(menuSelection == 1) {
            /*
                + If there is no book -> print message
                + else Print all books in store
            */
            if(db->GetLength() == 0)
                wcout << SetColor(0,12) << L"Danh sách rỗng!" << SetColor(0,15) << endl; 
            else 
                db->ShowAll();
        }

        // 2. sort list
        if(menuSelection == 2) {
            /*
                -> Selection: choose what property to sort by 
                -> Sort
            */
            int sortSelection = -1;
            do {
                Clrscr();
                wcout << SetColor(0, 14) << L"SẮP XẾP DANH SÁCH CÁC ĐẦU SÁCH" << SetColor(0, 15) << endl << endl
                      << SetColor(0, 12)
                      << L"\t0. Trở lại menu" << SetColor(0, 15) << endl
                      << L"\t1. Sắp xếp theo ID" << endl
                      << L"\t2. Sắp xếp theo Tên" << endl
                      << L"\t3. Sắp xếp theo Tác giả" << endl
                      << L"\t4. Sắp xếp theo Thể loại" << endl
                      << L"\t5. Sắp xếp theo Giá" << endl
                      << L"\t6. Sắp xếp theo số lượng trong kho" << endl
                      << L"\t7. Sắp xếp theo số lượng đã bán" << endl << endl
                      << L">> Nhập lựa chọn: ";
                wcin >> sortSelection;
            } while (sortSelection < 0 || sortSelection > 7);
            if(sortSelection == 0)
                goto Menu;
            db->Sort(sortSelection);
            wcout << SetColor(0,10) << L"Sắp xếp danh sách thành công!" << SetColor(0,15) << endl; 
        }

        // 3. Show specific book info by ID
        if(menuSelection == 3) {
            /*
                + Choose what property of book to search by (id, name,...)
                + Search
            */
            int searchSelection = -1;
            do {
                wcout << SetColor(0, 14) << L"TÌM ĐẦU SÁCH" << SetColor(0, 15) << endl << endl
                      << SetColor(0, 12)
                      << L"\t0. Trở lại menu" << SetColor(0, 15) << endl
                      << L"\t1. Tìm bằng ID" << endl
                      << L"\t2. Tìm theo Tên" << endl
                      << L"\t3. Tìm theo Tác giả" << endl
                      << L"\t4. Tìm theo Thể loại" << endl << endl
                      << L">> Nhập lựa chọn: ";
                wcin >> searchSelection;
            } while (searchSelection < 0 || searchSelection > 4);
            Clrscr();

            if(searchSelection == 0) {
                goto Menu;
            }
            if(searchSelection == 1) {
                wcout << SetColor(0, 14) << L"TÌM ĐẦU SÁCH BẰNG ID" << SetColor(0, 15) << endl;
                wstring id;
                wcout << L">> Nhập ID: ";
                wcin >> id;
                int index = db->GetBookIndexByID(id);
                if(index == -1) {
                    wcout << SetColor(0, 12) << L"Không tìm thấy sách có ID "
                        << SetColor(0, 14) << id << SetColor(0, 15) << endl;
                }
                else {
                    db->GetBook(index)->Show();
                }
            }
            if(searchSelection == 2) {
                wcout << SetColor(0, 14) << L"TÌM ĐẦU SÁCH BẰNG TÊN" << SetColor(0, 15) << endl;
                wstring name;
                wcout << L">> Nhập tên đầu sách: ";
                wcin.ignore();
                wcin.ignore();
                getline(wcin, name);
                wcout << endl;
                db->ShowByName(name);
            }
            if(searchSelection == 3) {
                wcout << SetColor(0, 14) << L"TÌM ĐẦU SÁCH BẰNG TÁC GIẢ" << SetColor(0, 15) << endl;
                wstring author;
                wcout << L">> Nhập tên tác giả: ";
                wcin.ignore();
                wcin.ignore();
                getline(wcin, author);
                wcout << endl;
                db->ShowByAuthor(author);
            }
            if(searchSelection == 4) {
                wcout << SetColor(0, 14) << L"TÌM ĐẦU SÁCH BẰNG THỂ LOẠI" << SetColor(0, 15) << endl;
                wstring category;
                wcout << L">> Nhập tên thể loại: ";
                wcin.ignore();
                wcin.ignore();
                getline(wcin, category);
                wcout << endl;
                db->ShowByCategory(category);
            }
            
        }   

        // 4. add book (new book id = nextID)
        if(menuSelection == 4) {
            /* 
                -> Choose where to add book
                -> Input new book infor
                -> Add it
            */
            int addSelection = -1, addIndex = -1;
            do {
                Clrscr();
                wcout << SetColor(0, 14) << L"THÊM ĐẦU SÁCH" << endl << endl
                      << SetColor(0, 12)
                      << L"\t0. Trở lại menu" << SetColor(0, 15) << endl
                      << L"\t1. Thêm đầu sách vào cuối danh sách" << endl
                      << L"\t2. Thêm đầu sách vào đầu danh sách" << endl
                      << L"\t3. Thêm đầu sách vào vị trí chỉ định" << endl << endl
                      << L">> Lựa chọn: ";
                wcin >> addSelection;
            } while(addSelection < 0 || addSelection > 3);
            if(addSelection == 0) {
                goto Menu;
            }
            if(db->GetLength() == 0) {
                addIndex = 0;
            }
            else if(addSelection == 3) {
                wcout << SetColor(0, 14)
                      <<  L"Vị trí thêm phải là số nguyên từ 0 -> " << db->GetLength()
                      << endl << SetColor(0, 15);
                do {
                    wcout << L">> Nhập vị trí muốn thêm sách: ";
                    wcin >> addIndex;
                } while (addIndex < 0 || addIndex > db->GetLength());
            }
            Clrscr();
            wstring id = IntIDtoWstring(db->GetNextID());
            wcout << SetColor(0, 15) << L"THÊM ĐẦU SÁCH MỚI VÀO DANH SÁCH" << endl << endl
                  << SetColor(0, 10) << L"Đầu sách này sẽ có ID "
                  << SetColor(0, 14) << id << endl
                  << SetColor(0, 10) << L"Nhập thông tin sách mới: " << SetColor(0,15) << endl;
            Book newBook;
            newBook.Input(id);
            if(addSelection == 1) {
                db->addTail(newBook);
            }
            if(addSelection == 2) {
                db->addHead(newBook);
            }
            if(addSelection == 3) {
                db->addAt(addIndex, newBook);
            }

            wcout << SetColor(0, 10) << L"Thêm thành công sách với ID "
                  << SetColor(0, 14) << id << SetColor(0, 15) << endl;
        }

        // 5. delete book by ID
        if(menuSelection == 5) {
            /* 
                Selection
                    -> Delete specific book by id
                        + Input ID
                        + If book not Found -> Print message
                        + If book found -> delete
                    -> Delete All
            */
            int deleteSelection = -1;
            do {
                Clrscr();

                wcout << SetColor(0, 14) << L"XÓA ĐẦU SÁCH" << endl << endl
                      << SetColor(0, 12)
                      << L"\t0. Trở lại menu" << SetColor(0, 15) << endl
                      << L"\t1. Xóa đầu sách có ID nhập từ bàn phím" << endl
                      << L"\t2. Xóa tất cả đầu sách" << endl << endl
                      << L">> Lựa chọn: ";
                wcin >> deleteSelection;
            } while(deleteSelection < 0 || deleteSelection > 2);
            Clrscr();
            if(deleteSelection == 0) {
                goto Menu;
            }
            if(deleteSelection == 1) {
                wstring id;
                wcout << SetColor(0, 14) << L"XÓA ĐẦU SÁCH" << SetColor(0, 15) << endl << endl
                      << L">> Nhập ID đầu sách muốn xóa: ";
                wcin >> id;

                int index = db->GetBookIndexByID(id);
                if(index == -1) {
                    wcout << SetColor(0, 12) << L"Không tìm thấy sách có ID "
                        << SetColor(0, 14) << id << SetColor(0, 15) << endl;
                }
                else {
                    db->deleteAt(index);
                    wcout << SetColor(0, 10) << L"Xóa thành công sách có ID "
                        << SetColor(0, 14) << id << SetColor(0, 15) << endl;
                }
            }
            if(deleteSelection == 2) {
                db->deleteAll();
                wcout << SetColor(0, 10) << L"Xóa tất cả đầu sách thành công!" << SetColor(0, 15) << endl;
            }
            
        }

        // 6. update book info by ID
        if(menuSelection == 6) {
            /* 
                -> Input book id;
                -> + If book not found -> Print message
                   + If book found -> Input new info -> Update 
            */
            wstring id;
            wcout << SetColor(0, 14) << L"CẬP NHẬT THÔNG TIN ĐẦU SÁCH" << SetColor(0, 15) << endl << endl
                  << L">> Nhập ID đầu sách muốn cập nhật: ";
            wcin >> id;

            int index = db->GetBookIndexByID(id);
            if(index == -1) {
                wcout << SetColor(0, 12) << L"Không tìm thấy sách có ID "
                      << SetColor(0, 14) << id << SetColor(0, 15) << endl;
            }
            else {
                wcout << SetColor(0, 10) << L"Thông tin đầu sách hiện tại"
                      << SetColor(0, 15) << endl;
                
                db->GetBook(index)->Show();
                
                wcout << SetColor(0, 10) << L"Nhập thông tin mới: "
                      << SetColor(0, 15) << endl;
                Book newBook;
                newBook.Input(id);

                Clrscr();
                wcout << SetColor(0, 10) << L"Thông tin cũ"
                      << SetColor(0, 15) << endl;
                db->GetBook(index)->Show();
                
                wcout << SetColor(0, 10) << L"Thông tin mới"
                      << SetColor(0, 15) << endl;
                newBook.Show();

                wstring promt = L"O";
                wcout << SetColor(0,10) << L"Bạn có chắc muốn cập nhật thông tin không? (Y/N)"
                      << SetColor(0, 15) << endl;
                do {
                    wcout << L">> Nhập Y (đồng ý) hoặc N (không đồng ý): ";
                    wcin >> promt;
                } while (promt != L"Y" && promt != L"N" && promt != L"y" && promt != L"n");
                
                if(promt == L"Y" || promt == L"y") {
                    db->UpdateAt(index, newBook);
                    wcout << SetColor(0, 10) << L"Cập nhật thành công đầu sách có ID "
                          << SetColor(0, 14) << id << SetColor(0, 15) << endl;
                }
                else {
                    wcout << SetColor(0, 12) << endl
                          << L"Đã hủy tiến trình cập nhật" << endl;
                }
            }
        }

        // 7. import data from file
        if(menuSelection == 7) {
            /* 
                -> Input name of data file;
                (if file name = -1 -> back to menu)
                -> Import
            */
            wcout << SetColor(0, 14) << L"NHẬP DANH SÁCH MỚI TỪ FILE" << endl 
                  << SetColor(0, 12) << L"Lưu ý: \n\tDanh sách hiện tại sẽ bị xóa!" << endl
                  << L"\tBạn có thể nhập tên file là -1 để trở lại menu" << SetColor(0, 15) << endl << endl;
            wstring fileName;
            wcout << L">> Nhập tên file: ";
            cin.ignore();
            wcin >> fileName;
            if(fileName == L"-1") {
                goto Menu;
            }
            importDataFromFile(fileName);
        }
        
        // 8. export data to file
        if(menuSelection == 8) {
            /* 
                -> Input name of export file;
                -> Export
            */
            wstring fileName;
            wcout << SetColor(0, 14) << L"XUẤT DANH SÁCH RA FILE" << SetColor(0, 15) << endl << endl
                  << L">> Nhập tên file: ";
            cin.ignore();
            wcin >> fileName;
            exportDataToFile(fileName);
        }

        if(menuSelection != 0)
            Pause();
    }

    SetColor(0, 7); //default console color
    return 0;
}


/**********************************************************************************/

void printMenu() {
    wcout << L"+-------------------------------------------------+" << endl
          << L"|                                                 |" << endl
          << L"|            "
          << SetColor(0, 14) << L"QUẢN LÍ SÁCH TRONG CỬA HÀNG"
          << SetColor(0, 15) << L"          |"                      << endl
          << L"|                                                 |" << endl
          << L"|         0. Thoát                                |" << endl
          << L"|         1. In danh sách tất cả đầu sách         |" << endl
          << L"|         2. Sắp xếp lại danh sách                |" << endl
          << L"|         3. Tìm xem thông tin đầu sách           |" << endl
          << L"|         4. Thêm đầu sách                        |" << endl
          << L"|         5. Xóa đầu sách                         |" << endl
          << L"|         6. Cập nhật sách                        |" << endl
          << L"|         7. Nhập danh sách từ file               |" << endl
          << L"|         8. Xuất danh sách ra file               |" << endl
          << L"|                                                 |" << endl
          << L"+-------------------------------------------------+" << endl;
}

void importDataFromFile(wstring& fileName) {
    /*
     * It impossible to import data from a utf-16 encoding .txt file, but this program store text data as utf-16 wstring,
     * So data is saved in utf-8 encoding .txt file    
        ==> Open utf-8 file
        ==> import data to a utf-8 string
        ==> convert string to wstring using utf8_to_utf16 function (in format.h)
    */
    BookStore *db = BookStore::GetInstance();
    ifstream fin(fileName.c_str());
    try {
        if( fin.is_open() ) {
            // delete all data in order to import new one :)
            db->deleteAll();
            
            // input length
            int length;
            fin >> length;
            
            //input data: 
            string ignore, id, name, author, category;
            double price;
            int stock, sold;
            
            for(int i = 0; i < length; i++) {
                // get book info
                fin.ignore();
                getline(fin, id);
                getline(fin, name);
                getline(fin, author);
                getline(fin, category);
                fin >> price >> sold >> stock;

                // convert utf-8 string to utf-16 wstring 
                wstring wid = utf8_to_utf16(id);
                wstring wname = utf8_to_utf16(name);
                wstring wauthor = utf8_to_utf16(author);
                wstring wcategory = utf8_to_utf16(category);
                
                // create a temp book and add it to database
                Book newBook(wid, wname, wauthor, wcategory, price, sold, stock);
                db->addTail(newBook);
            }
            fin.close();
            wcout << SetColor(0, 10) <<  L"Nhập dữ liệu thành công!" << SetColor(0,15) << endl;
        }
        else {
            wcout << SetColor(0,12) << L"Mở file thất bại!" << SetColor(0,15) << endl;
        }
    }
    catch(...) {
        wcout << SetColor(0,12) << L"Nhập dữ liệu thất bại!" << SetColor(0,15) << endl;
    }
}

void exportDataToFile(wstring& fileName) {
    /* 
        ==> Open file (utf8)
        ==> Convert utf16 wstring to utf8 string (using utf16_to_utf8 in format.h) 
        ==> export data as utf8 string
    */
    BookStore *db = BookStore::GetInstance();
    ofstream fout(fileName.c_str());
    try {
        if( fout.is_open() ) {
            fout << db->GetLength() << endl;
            for (int i = 0; i < db->GetLength(); i++) {
                // convert utf-16 wstring to utf-8 string
                string id = utf16_to_utf8(db->GetBook(i)->GetID());
                string name = utf16_to_utf8(db->GetBook(i)->GetName());
                string author = utf16_to_utf8(db->GetBook(i)->GetAuthor());
                string category = utf16_to_utf8(db->GetBook(i)->GetCategory());
                
                // write data to file
                fout << id << endl
                     << name << endl
                     << author << endl
                     << category << endl
                     << db->GetBook(i)->GetPrice() << endl
                     << db->GetBook(i)->GetStock() << endl
                     << db->GetBook(i)->GetSold() << endl;
            }
            fout.close();
            wcout << SetColor(0,10) << L"Xuất dữ liệu thành công!" << SetColor(0,15) << endl;
        }
        else {
            wcout << SetColor(0,12) << L"Xuất dữ liệu thất bại!" << SetColor(0,15) << endl;
        }
    }
    catch(...) {
        wcout << SetColor(0,12) << L"Xuất dữ liệu thất bại!" << SetColor(0,15) << endl;
    }
}