#include <string>
#include "format.cpp"

using namespace std;
class Book {
    private:
        wstring _id;
        wstring _name;
        wstring _author;
        wstring _category;
        double _price; //dollars
        int _stock;
        int _sold;
    public:
        // Constructors, Destroctors,
        Book(wstring = L"XXXXXXXX", wstring = L"null_name", wstring = L"null_author", wstring = L"null_category", double = 0.0, int = 0, int = 0);
        ~Book();

        // Getters, Setters
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

        // Show
        void Show();

        // Input
        void Input(wstring);
};