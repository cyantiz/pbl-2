#pragma once
#include <iostream>
#include <string>
#include "format.cpp"
#include "Book.h"

class Store {
    private:
        Book *p;
        int _length;
        long long _totalSold;
        long long _totalStock;
    public:
        // constructors, destructors
        Store();
        Store(Store &);
        ~Store();

        // geters, setters
        int getLength();
        void setLength(int);
        long long getTotalSold();
        void setTotalSold(long long);
        long long getTotalStock();
        void setTotalStock(long long);
        Book getBook(int);
        // void setBook(int);
        
        // search
        int getBookIndexByID(wstring);

        // Add
        void addTail(Book &);
        void addHead(Book &);
        void addAt(int, Book &);

        // show
        void show();
};

// constructors, destructors
Store::Store() : p(nullptr), _length(0), _totalSold(0), _totalStock(0) {
}
Store::Store(Store& s): _length(s.getLength()), _totalSold(s.getTotalSold()), _totalStock(s.getTotalStock()){
    this->p = new Book[this->_length];
    for (int i = 0; i < this->_length; i++) {
        *(this->p + i) = s.getBook(i);
    }
}
Store::~Store() {
    delete[] this->p;
}

// getters, setters
int Store::getLength() {
    return this->_length;
}
void Store::setLength(int length) {
    this->_length = length;
}
long long Store::getTotalSold() {
    return this->_totalSold;
}
void Store::setTotalSold(long long totalSold){
    this->_totalSold = totalSold;
}
long long Store::getTotalStock() {
    return this->_totalStock;
}
void Store::setTotalStock(long long totalStock){
    this->_totalStock = totalStock;
}
Book Store::getBook(int index) {
    return *(this->p + index);
}

// search
int Store::getBookIndexByID(wstring id) {
    for (int i = 0; i < this->_length; i++) {
        if(this->getBook(i).getID() == id)
            return i;
    }
    return -1;
}

// add
void Store::addTail(Book &newBook) {
    if(this->_length == 0) {
      this->p = new Book[this->_length + 1];
      *(this->p + this->_length) = newBook;
    }
    else {
        Book *temp = new Book[this->_length];
        for (int i = 0; i < this->_length; i++)
            *(temp + i) = *(this->p + i);
        delete[] this->p;
        this->p = new Book[this->_length + 1];
        for (int i = 0; i < this->_length; i++) {
            *(this->p + i) = *(temp + i);
        };
        *(this->p + this->_length) = newBook;
   }
   this->_length++;
}
void Store::addHead(Book &newBook) {
    if(this->_length == 0) {
      this->p = new Book[this->_length + 1];
      *(this->p + this->_length) = newBook;
    }
    else {
        Book *temp = new Book[this->_length];
        for (int i = 0; i < this->_length; i++)
            *(temp + i) = *(this->p + i);
        delete[] this->p;
        this->p = new Book[this->_length + 1];
        *(this->p + 0) = newBook;
        for (int i = 0; i < this->_length; i++) {
            *(this->p + i + 1) = *(temp + i);
        };
   }
   this->_length++;
}
void Store::addAt(int index, Book &newBook) {
    if(index > _length || index < 0)
        return;
    
    Book *temp = new Book[this->_length];
    for (int i = 0; i < this->_length; i++)
        *(temp + i) = *(this->p + i);
    delete[] this->p;
    this->p = new Book[this->_length + 1];
    *(this->p + 0) = newBook;
    for (int i = 0; i < this->_length + 1; i++) {
        if(i < index) {
            *(this->p + i) = *(temp + i);
        }
        else if(i > index) {
            *(this->p + i) = *(temp + i - 1);
        }
    };
    *(this->p + index) = newBook;
    this->_length++;
}

// show
void Store::show() {
    wcout << L"=====================LIST=======================" << endl;
    for (int i = 0; i < this->_length; i++) {
        (this->p + i)->show();
    }
    wcout << L"===================END LIST=====================" << endl;
}
