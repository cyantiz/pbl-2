#include "Book.h"

// Constructors, Destructors
Book::Book(wstring id, wstring name, wstring author, wstring category, double price, int stock, int sold)
    :_id(id), _name(name), _author(author), _category(category), _price(price), _stock(stock), _sold(sold) {
}
Book::~Book() { }

// Getter, Setters
wstring Book::GetID() {
    return this->_id;
}
void Book::SetID(wstring id) {
    this->_id = id;
}
wstring Book::GetName() {
    return this->_name;
}
void Book::SetName(wstring name) {
    this->_name = name;
}
wstring Book::GetAuthor() {
    return this->_author;
}
void Book::SetAuthor(wstring author) {
    this->_author = author;
}
wstring Book::GetCategory() {
    return this->_category;
}
void Book::SetCategory(wstring category) {
    this->_category = category;
}
double Book::GetPrice() {
    return this->_price;
}
void Book::SetPrice(double price) {
    this->_price = price;
}
int Book::GetStock() {
    return this->_stock;
}
void Book::SetStock(int stock) {
    this->_stock = stock;
}
int Book::GetSold() {
    return this->_sold;
}
void Book::SetSold(int sold) {
    this->_sold = sold;
}

// Show
void Book::Show() {  
    wcout << SetColor(0, 14) <<  L"#" << this->_id << L"  " << SetColor(0, 15);
    wcout << L"Tên:        " << this->_name << endl
            << L"           Tác giả:    "  << this->_author << endl
            << L"           Thể loại:   "  << this->_category << endl
            << L"           Giá:        $";
    wprintf(L"%.2lf\n", this->GetPrice());
    wcout   << L"           Trong kho:  "  << this->_stock << endl
            << L"           Đã bán:     "  << this->_sold << endl;
}

// Input
void Book::Input(wstring id) {
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

    this->_id = id;
    this->_name = name;
    this->_author = author;
    this->_category = category;
    this->_price = price;
    this->_sold = sold;
    this->_stock = stock;
}