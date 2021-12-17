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