#pragma once
#include <iostream>
#include <string>
#include "format.cpp"

using namespace std;
class Book {
    private:
        wstring id;
        wstring name;
        wstring author;
        wstring category;
        double price; //dollars
        int sold;
        int stock;
    public:
        // constructor
        Book(wstring = L"XXXXXXXX", wstring = L"null_name", wstring = L"null_author", wstring = L"null_category", double = 0.0, int = 0, int = 0);
        ~Book();

        // getter, setter
        wstring getID();
        void setID(wstring);
        wstring getName();
        void setName(wstring);
        wstring getAuthor();
        void setAuthor(wstring);
        wstring getCategory();
        void setCategory(wstring);
        double getPrice();
        void setPrice(double);
        int getSold();
        void setSold(int);
        int getStock();
        void setStock(int);

        // show
        void show();
};

// constructor
Book::Book(wstring id, wstring name, wstring author, wstring category, double price, int stock, int sold)
    :id(id), name(name), author(author), category(category), price(price), stock(stock), sold(sold) {
}
Book::~Book() { }

// getter, setter
wstring Book::getID() {
    return this->id;
}
void Book::setID(wstring id) {
    this->id = id;
}
wstring Book::getName() {
    return this->name;
}
void Book::setName(wstring name) {
    this->name = name;
}
wstring Book::getAuthor() {
    return this->author;
}
void Book::setAuthor(wstring author) {
    this->author = author;
}
wstring Book::getCategory() {
    return this->author;
}
void Book::setCategory(wstring category) {
    this->category = category;
}
double Book::getPrice() {
    return this->price;
}
void Book::setPrice(double price) {
    this->price = price;
}
int Book::getSold() {
    return this->sold;
}
void Book::setSold(int sold) {
    this->sold = sold;
}
int Book::getStock() {
    return this->stock;
}
void Book::setStock(int stock) {
    this->stock = stock;
}

// show
void Book::show() {  
    wcout << setColor(0, 14) <<  L"#" << this->id << L"  " << setColor(0, 15);
    wcout << L"Tên:        " << this->name << endl
            << L"           Tác giả:    " << this->author << endl
            << L"           Thể loại:   " << this->category << endl
            << L"           Giá:        $" << this->price << endl
            << L"           Trong kho:  " << this->stock << endl
            << L"           Đã bán:     " << this->sold << endl;
}