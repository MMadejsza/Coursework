#include <iostream>
#include <string>
#include <regex>
#include <limits>
using namespace std;

// function validating name:
string validation(string typo)
{
    if (typo == "name")
    {
        // declare the name
        string name;
        // specify validation rules in regex
        regex reg("[A-Z]*[a-z]*");
        // print instruction for user what's expected
        cout << "Enter a name (No special characters or numbers): " << endl;
        // request the input to "name" again
        cin >> name;
        // as long as input doesn't meet expectations:
        while (!regex_match(name, reg))
        {
            // error message in "if" for first iteration:
            if (!regex_match(name, reg))
            {
                cout << "Please input the name starting from capital letters, no numbers or special characters." << endl;
            }
            // clean the buffer
            cin.clear();
            // request the input to "name" again
            cin >> name;
        };
        return name;
    }
    if (typo == "date")
    {
        // declare the date
        string date;
        // specify validation rules in regex
        regex reg("[0-9]{2}/[0-9]{2}/[0-9]{2}");
        // print instruction for user what's expected
        cout << "Enter the expiry date (DD/MM/YY format) " << endl;
        // as long as input doesn't meet expectations:
        while (!regex_match(date, reg))
        {
            // clean the buffer
            cin.clear();
            // request the input to "name" again
            cin >> date;
            // error message in "if" for first iteration:
            if (!regex_match(date, reg))
            {
                cout << "Please input the date in correct format" << endl;
            }
        };
        return date;
    }
};

string simpleInput(string text)
{
    string data;
    // print instruction for user what's expected from function
    cout << "Enter " << text << endl;
    // request the input allowing whitespaces
    getline(cin >> ws, data);
    return data;
};

void inputForm()
{
    string name = validation("name");
    string address = simpleInput("Enter 1st line of the address");
    string postcode = simpleInput("Enter postcode");
    string cardNumber = simpleInput("Enter 16-digit card number");
    string expiryDate = validation("date");
    string secretCode = simpleInput("Enter your secret code");

    cout << name << endl
         << address << endl
         << postcode << endl
         << cardNumber << endl
         << expiryDate << endl
         << secretCode << endl;
};

int main()
{
    inputForm();
}