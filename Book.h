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
        int stock;
        int sold;
    public:
        // constructor
        Book(wstring = L"XXXXXXXX", wstring = L"null_name", wstring = L"null_author", wstring = L"null_category", double = 0.0, int = 0, int = 0);
        ~Book();

        // Getter, Setter
        wstring GetID();
        void SetID(wstring);
        wstring GetName();
        void SetName(wstring);
        wstring GetAuthor();
        void SetAuthor(wstring);
        wstring GetCategory();
        void SetCategory(wstring);
        double GetPrice();
        void SetPrice(double);
        int GetStock();
        void SetStock(int);
        int GetSold();
        void SetSold(int);

        // show
        void Show();
};