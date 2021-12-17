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

