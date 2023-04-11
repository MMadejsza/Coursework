#include <iostream>
#include <string>
#include <regex>
#include <limits>
using namespace std;

// function validating name:
string nameValid()
{
    // declare the name
    string name;
    // specify validation rules in regex
    regex reg("^[A-Z]([a-z])*");
    // print instruction for user what's expected
    cout << "Enter a name: " << endl;
    // as long as input doesn't meet expectations:
    while (!regex_match(name, reg))
    {
        // clean the buffer
        cin.clear();
        // request the input to "name" again
        cin >> name;
        // error message in "if" for first iteration:
        if (!regex_match(name, reg))
        {
            cout << "Please input the name starting from capital letters, no numbers or special characters please " << endl;
        }
    };
    return name;
};

void inputForm()
{
    string name = nameValid();
    string address;
    string postcode;
    string cardNumber;
    string expiryDate;
    string secretCode;

    // cout << name;
};

int main()
{
    inputForm();
}