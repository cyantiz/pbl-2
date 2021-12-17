#pragma once
#include <iostream>
#include <string>
#include "format.cpp"
#include "Book.h"

// singleton
class BookStore {
    private:
        Book *p;
        int _length;
        int _nextID;

        // constructors
        BookStore();

        // singleton instance
        static BookStore* _uniqueInstance;

    public:
        // Get singleton instance
        static BookStore *GetInstance();
        
        // destructor
        ~BookStore();


        // Geters, Setters
        int GetLength();
        void SetLength(int);
        long long GetTotalSold();
        long long GetTotalStock();
        Book* GetBook(int);
        Book* GetBookByIntID(int);
        Book* GetBookByWstringID(wstring);
        int GetNextID();
        // void SetBook(int);
        
        // search
        int GetBookIndexByID(wstring);

        // Add
        void addTail(Book &);
        void addHead(Book &);
        void addAt(int, Book &);

        // Delete
        void deleteAt(int);
        void deleteAll();

        // Update
        void UpdateAt(int, Book &);

        // Show
        void ShowAll();
        void ShowByName(wstring);
        void ShowByAuthor(wstring);
        void ShowByCategory(wstring);

        // sort
        int SortPartitionID(int, int);
        int SortPartitionName(int, int);
        int SortPartitionAuthor(int, int);
        int SortPartitionCategory(int, int);
        int SortPartitionPrice(int, int);
        int SortPartitionSold(int, int);
        int SortPartitionStock(int, int);
        void QuickSort(int, int, int);
        void Sort(int);
};

// constructors, destructors
BookStore::BookStore() : p(nullptr), _length(0), _nextID(1) {
}
BookStore::~BookStore() {
    delete[] this->p;
}

// Singleton Instance
BookStore *BookStore::_uniqueInstance = nullptr;
BookStore* BookStore::GetInstance() {
    if(_uniqueInstance == nullptr) {
        _uniqueInstance = new BookStore();
    }
    return _uniqueInstance;
}


// Getters, Setters
int BookStore::GetLength() {
    return this->_length;
}
void BookStore::SetLength(int length) {
    this->_length = length;
}
long long BookStore::GetTotalSold() {
    long long totalSold = 0;
    for (int i = 0; i < this->_length; i++) {
        totalSold += (this->p + i)->GetSold();
    }
    return totalSold;
}
long long BookStore::GetTotalStock() {
    long long totalStock = 0;
    for (int i = 0; i < this->_length; i++) {
        totalStock += (this->p + i)->GetStock();
    }
    return totalStock;
}
Book* BookStore::GetBook(int index) {
    return this->p + index;
}
Book* BookStore::GetBookByIntID(int intID) {
    wstring id = IntIDtoWstring(intID);
    int index = this->GetBookIndexByID(id);
    if(index == -1) {
        return NULL;
    }
    return this->GetBook(index);
}
Book* BookStore::GetBookByWstringID(wstring id) {
    int index = this->GetBookIndexByID(id);
    if(index == -1) {
        return NULL;
    }
    return this->GetBook(index);
}

int BookStore::GetNextID() {
    while(this->GetBookByIntID(this->_nextID)) {
        this->_nextID++;
    }
    return this->_nextID;
}

// search
int BookStore::GetBookIndexByID(wstring id) {
    for (int i = 0; i < this->_length; i++) {
        if( (this->p + i)->GetID() == id)
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
    this->_nextID = 1;
}


// update
void BookStore::UpdateAt(int index, Book &b) {
    *(this->p + index) = b;
}

// Show
void BookStore::ShowAll() {
    wcout << L"=====================LIST=======================" << endl;
    for (int i = 0; i < this->_length; i++) {
        (this->p + i)->Show();
    }
    wcout << L"===================END LIST=====================" << endl;
    wcout << L"Danh sách này có " << SetColor(0, 14) << this->_length << SetColor(0, 15) << L" đầu sách" << endl;
    wcout << L"Tổng số cuốn sách còn trong kho: "
          <<  SetColor(0, 14) << this->GetTotalStock() << SetColor(0, 15) << endl;
    wcout << L"Tổng số cuốn sách đã bán: "
          << SetColor(0, 14) << this->GetTotalSold() <<  SetColor(0, 15) << endl;
}
void BookStore::ShowByName(wstring name) {
    int count = 0;
    for (int i = 0; i < this->_length; i++) {
        if( LowerCase((this-> p + i)->GetName()) == LowerCase(name) ) {
            (this->p + i)->Show();
            count++;
        }
    }
    if(count == 0) {
        wcout << SetColor(0, 12) << L"Không tìm thấy đầu sách nào có tên "
              << SetColor(0, 14) << name << SetColor(0, 15) << endl;
    }
    else {
        wcout << SetColor(0, 10) << endl << L"Tìm thấy " << count << L" đầu sách có tên "
              << SetColor(0, 14) << name << SetColor(0, 15) << endl;
    }
}
void BookStore::ShowByAuthor(wstring author) {
    int count = 0;
    for (int i = 0; i < this->_length; i++) {
        if( LowerCase((this-> p + i)->GetAuthor()) == LowerCase(author)) {
            (this->p + i)->Show();
            count++;
        }
    }
    if(count == 0) {
        wcout << SetColor(0, 12) << L"Không tìm thấy đầu sách nào của tác giả "
              << SetColor(0, 14) << author << SetColor(0, 15) << endl;
    }
    else {
        wcout << SetColor(0, 10) << endl <<  L"Tìm thấy " << count << L" đầu sách của tác giả "
              << SetColor(0, 14) << author << SetColor(0, 15) << endl;
    }
}
void BookStore::ShowByCategory(wstring category) {
    int count = 0;
    for (int i = 0; i < this->_length; i++) {
        if( LowerCase((this-> p + i)->GetCategory()) == LowerCase(category)) {
            (this->p + i)->Show();
            count++;
        }
    }
    if(count == 0) {
        wcout << SetColor(0, 12) << L"Không tìm thấy đầu sách nào có thể loại "
              << SetColor(0, 14) << category << SetColor(0, 15) << endl;
    }
    else {
        wcout << SetColor(0, 10) << endl << L"Tìm thấy " << count << L" đầu sách có thể loại "
              << SetColor(0, 14) << category << SetColor(0, 15) << endl;
    }
}

//sort
int BookStore::SortPartitionID (int low, int high)
{
    wstring pivot = (this->p + high)->GetID();
    int i = (low - 1); 
    for (int j = low; j <= high - 1; j++)
    {
        if ( (this->p + j)->GetID() <= pivot)
        {
            i++;
            Book temp = *(this->p + i);
            *(this->p + i) = *(this->p + j);
            *(this->p + j) = temp;
        }
    }
    Book temp = *(this->p + i + 1);
    *(this->p + i + 1) = *(this->p + high);
    *(this->p + high) = temp;
    return (i + 1);
}
int BookStore::SortPartitionName (int low, int high)
{
    wstring pivot = (this->p + high)->GetName();
    int i = (low - 1); 
    for (int j = low; j <= high - 1; j++)
    {
        if ( (this->p + j)->GetName() <= pivot)
        {
            i++;
            Book temp = *(this->p + i);
            *(this->p + i) = *(this->p + j);
            *(this->p + j) = temp;
        }
    }
    Book temp = *(this->p + i + 1);
    *(this->p + i + 1) = *(this->p + high);
    *(this->p + high) = temp;
    return (i + 1);
}
int BookStore::SortPartitionAuthor (int low, int high)
{
    wstring pivot = (this->p + high)->GetAuthor();
    int i = (low - 1); 
    for (int j = low; j <= high - 1; j++)
    {
        if ( (this->p + j)->GetAuthor() <= pivot)
        {
            i++;
            Book temp = *(this->p + i);
            *(this->p + i) = *(this->p + j);
            *(this->p + j) = temp;
        }
    }
    Book temp = *(this->p + i + 1);
    *(this->p + i + 1) = *(this->p + high);
    *(this->p + high) = temp;
    return (i + 1);
}
int BookStore::SortPartitionCategory (int low, int high)
{
    wstring pivot = (this->p + high)->GetCategory();
    int i = (low - 1); 
    for (int j = low; j <= high - 1; j++)
    {
        if ( (this->p + j)->GetCategory() <= pivot)
        {
            i++;
            Book temp = *(this->p + i);
            *(this->p + i) = *(this->p + j);
            *(this->p + j) = temp;
        }
    }
    Book temp = *(this->p + i + 1);
    *(this->p + i + 1) = *(this->p + high);
    *(this->p + high) = temp;
    return (i + 1);
}
int BookStore::SortPartitionPrice (int low, int high)
{
    double pivot = (this->p + high)->GetPrice();
    int i = (low - 1); 
    for (int j = low; j <= high - 1; j++)
    {
        if ( (this->p + j)->GetPrice() <= pivot)
        {
            i++;
            Book temp = *(this->p + i);
            *(this->p + i) = *(this->p + j);
            *(this->p + j) = temp;
        }
    }
    Book temp = *(this->p + i + 1);
    *(this->p + i + 1) = *(this->p + high);
    *(this->p + high) = temp;
    return (i + 1);
}
int BookStore::SortPartitionStock (int low, int high)
{
    int pivot = (this->p + high)->GetStock();
    int i = (low - 1); 
    for (int j = low; j <= high - 1; j++)
    {
        if ( (this->p + j)->GetStock() <= pivot)
        {
            i++;
            Book temp = *(this->p + i);
            *(this->p + i) = *(this->p + j);
            *(this->p + j) = temp;
        }
    }
    Book temp = *(this->p + i + 1);
    *(this->p + i + 1) = *(this->p + high);
    *(this->p + high) = temp;
    return (i + 1);
}
int BookStore::SortPartitionSold (int low, int high)
{
    int pivot = (this->p + high)->GetSold();
    int i = (low - 1); 
    for (int j = low; j <= high - 1; j++)
    {
        if ( (this->p + j)->GetSold() <= pivot)
        {
            i++;
            Book temp = *(this->p + i);
            *(this->p + i) = *(this->p + j);
            *(this->p + j) = temp;
        }
    }
    Book temp = *(this->p + i + 1);
    *(this->p + i + 1) = *(this->p + high);
    *(this->p + high) = temp;
    return (i + 1);
}

void BookStore::QuickSort(int low, int high, int type) {
    if (low < high)
    {
        int pi;
        if(type == 1) { 
            pi = this->SortPartitionID(low, high);
        }
        if(type == 2) {
            pi = this->SortPartitionName(low, high);
        }
        if(type == 3) {
            pi = this->SortPartitionAuthor(low, high);
        }
        if(type == 4) {
            pi = this->SortPartitionCategory(low, high);
        }
        if(type == 5) {
            pi = this->SortPartitionPrice(low, high);
        }
        if(type == 6) {
            pi = this->SortPartitionSold(low, high);
        }
        if(type == 7) {
            pi = this->SortPartitionStock(low, high);
        }
        this->QuickSort(low, pi - 1, type);
        this->QuickSort(pi + 1, high, type); 
    }
}

void BookStore::Sort(int type) {
    /* type:
        1: Sort by ID, 2: Sort by Name, 3: Sort by Author, 4: Sort by Category,
        5: Sort by Price, 6: Sort by Sold, 7: Sort by Stock
    */
    this->QuickSort(0, this->_length - 1, type);
}