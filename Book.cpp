#include "Book.h"

// constructor
Book::Book(wstring id, wstring name, wstring author, wstring category, double price, int stock, int sold)
    :id(id), name(name), author(author), category(category), price(price), stock(stock), sold(sold) {
}
Book::~Book() { }

// Getter, Setter
wstring Book::GetID() {
    return this->id;
}
void Book::SetID(wstring id) {
    this->id = id;
}
wstring Book::GetName() {
    return this->name;
}
void Book::SetName(wstring name) {
    this->name = name;
}
wstring Book::GetAuthor() {
    return this->author;
}
void Book::SetAuthor(wstring author) {
    this->author = author;
}
wstring Book::GetCategory() {
    return this->category;
}
void Book::SetCategory(wstring category) {
    this->category = category;
}
double Book::GetPrice() {
    return this->price;
}
void Book::SetPrice(double price) {
    this->price = price;
}
int Book::GetStock() {
    return this->stock;
}
void Book::SetStock(int stock) {
    this->stock = stock;
}
int Book::GetSold() {
    return this->sold;
}
void Book::SetSold(int sold) {
    this->sold = sold;
}

// show
void Book::Show() {  
    wcout << SetColor(0, 14) <<  L"#" << this->id << L"  " << SetColor(0, 15);
    wcout << L"Tên:        " << this->name << endl
            << L"           Tác giả:    " << this->author << endl
            << L"           Thể loại:   " << this->category << endl
            << L"           Giá:        $" << this->price << endl
            << L"           Trong kho:  " << this->stock << endl
            << L"           Đã bán:     " << this->sold << endl;
}