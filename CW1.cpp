#include <iostream>
#include <string>
#include <regex>
#include <limits>
using namespace std;

// function validating expected input type "typo" and according message:
string validation(string typo, string msg)
{
    // declaring the variables:
    string datum;
    string regCondition;
    string errorMsg;

    // specify validation rules in regex based on given argument "typo"
    if (typo == "name")
    {
        regCondition = "[A-Z]*[a-z]*";
        errorMsg = "Please input the name starting from capital letters, no numbers or special characters.";
    }
    // 2 digits 0-9 per slash -> validates only format, not if date is out of range
    else if (typo == "date")
    {
        regCondition = "[0-9]{2}/[0-9]{2}/[0-9]{2}";
        errorMsg = "Please input the date in correct format";
    }
    else if (typo == "postcode")
    {
        regCondition = "[A-Z]*[a-z]*";
    }
    else if (typo == "card")
    {
        regCondition = "[A-Z]*[a-z]*";
    };

    if (typo != "none")
    {
        // instantiate regex
        regex reg(regCondition);
        // print instruction for user what's expected from function
        cout << msg << endl;
        // request the input to "datum"
        cin >> datum;
        // as long as input doesn't meet expectations:
        while (!regex_match(datum, reg))
        {
            // error message in "if" for first iteration:
            if (!regex_match(datum, reg))
            {
                cout << errorMsg << endl;
            }
            // clean the buffer
            cin.clear();
            // request the input to "datum" again
            cin >> datum;
        };
        return datum;
    }

    cout << msg << endl;
    // request the input allowing whitespaces
    getline(cin >> ws, datum);
    return datum;
};

void inputForm()
{
    string name = validation("name", "Enter a name (No special characters or numbers): ");
    string address = validation("none", "Enter 1st line of the address");
    string postcode = validation("none", "Enter postcode");
    string cardNumber = validation("none", "Enter 16-digit card number");
    string expiryDate = validation("date", "Enter the expiry date (DD/MM/YY format) ");
    string secretCode = validation("none", "Enter your secret code");

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