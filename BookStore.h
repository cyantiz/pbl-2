#pragma once
#include <iostream>
#include <string>
#include "format.h"
#include "Book.h"

class BookStore {
    private:
        Book *p;
        int _length;
    public:
        // constructors, destructors
        BookStore();
        BookStore(BookStore&);
        ~BookStore();

        // geters, setters
        int getLength();
        void setLength(int);
        long long getTotalSold();
        long long getTotalStock();
        Book getBook(int);
        // void setBook(int);
        
        // search
        int getBookIndexByID(wstring);

        // Add
        void addTail(Book &);
        void addHead(Book &);
        void addAt(int, Book &);

        // Delete
        void deleteHead();
        void deleteTail();
        void deleteAt(int);
        void deleteAll();

        // Update
        void UpdateAt(int, Book &);

        // show
        void show();

        
};

// constructors, destructors
BookStore::BookStore() : p(nullptr), _length(0) {
}
BookStore::BookStore(BookStore& s): _length(s.getLength()){
    this->p = new Book[this->_length];
    for (int i = 0; i < this->_length; i++) {
        *(this->p + i) = s.getBook(i);
    }
}
BookStore::~BookStore() {
    delete[] this->p;
}

// getters, setters
int BookStore::getLength() {
    return this->_length;
}
void BookStore::setLength(int length) {
    this->_length = length;
}
long long BookStore::getTotalSold() {
    long long totalSold = 0;
    for (int i = 0; i < this->_length; i++) {
        totalSold += (this->p + i)->getSold();
    }
    return totalSold;
}
long long BookStore::getTotalStock() {
    long long totalStock = 0;
    for (int i = 0; i < this->_length; i++) {
        totalStock += (this->p + i)->getStock();
    }
    return totalStock;
}
Book BookStore::getBook(int index) {
    return *(this->p + index);
}

// search
int BookStore::getBookIndexByID(wstring id) {
    for (int i = 0; i < this->_length; i++) {
        if( (this->p + i)->getID() == id)
            return i;
    }
    return -1;
}

// add
void BookStore::addTail(Book &newBook) {
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
void BookStore::addHead(Book &newBook) {
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
void BookStore::addAt(int index, Book &newBook) {
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

// delete
void BookStore::deleteTail() {
    if(this->_length == 0) {
        return;
    }
    else {
        Book *temp = new Book[this->_length];
        for (int i = 0; i < this->_length; i++)
            *(temp + i) = *(this->p + i);
        delete[] this->p;
        this->p = new Book[this->_length - 1];
        for (int i = 0; i < this->_length - 1; i++) {
            *(this->p + i) = *(temp + i);
        }
   }
   this->_length--;
}
void BookStore::deleteHead() {
    if(this->_length == 0) {
        return;
    }
    else {
        Book *temp = new Book[this->_length];
        for (int i = 0; i < this->_length; i++)
            *(temp + i) = *(this->p + i);
        delete[] this->p;
        this->p = new Book[this->_length - 1];
        for (int i = 0; i < this->_length - 1; i++) {
            *(this->p + i) = *(temp + i + 1);
        }
   }
   this->_length--;
}
void BookStore::deleteAt(int index) {
    if(this->_length == 0) {
        return;
    }
    else {
        Book *temp = new Book[this->_length];
        for (int i = 0; i < this->_length; i++)
            *(temp + i) = *(this->p + i);
        delete[] this->p;
        this->p = new Book[this->_length - 1];
        for (int i = 0; i < this->_length; i++) {
            if(i < index)
                *(this->p + i) = *(temp + i);
            else if(i > index)
                *(this->p + i - 1) = *(temp + i);
        }
   }
   this->_length--;
}
void BookStore::deleteAll() {
    delete[] this->p;
    this->_length = 0;
}


// update
void BookStore::UpdateAt(int index, Book &b) {
    *(this->p + index) = b;
}

// show
void BookStore::show() {
    wcout << L"=====================LIST=======================" << endl;
    for (int i = 0; i < this->_length; i++) {
        (this->p + i)->show();
    }
    wcout << L"===================END LIST=====================" << endl;
    wcout << L"Danh sách này có " << setColor(0, 14) << this->_length << setColor(0, 15) << L" đầu sách" << endl;
    wcout << L"Tổng số cuốn sách còn trong kho: "
          <<  setColor(0, 14) << this->getTotalStock() << setColor(0, 15) << endl;
    wcout << L"Tổng số cuốn sách đã bán: "
          << setColor(0, 14) << this->getTotalSold() <<  setColor(0, 15) << endl;
}
