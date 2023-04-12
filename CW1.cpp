#include <iostream>
#include <string>
#include <regex>
#include <limits>
using namespace std;

// creating customer class / template to store collected data
class Customer
{
    // public attributes:
public:
    string name;
    string address;
    string postcode;
    string cardNumber;
    string expiryDate;
    string secretCode;
    // constructor - "creation template"
    Customer(string n, string a, string p, string c, string ex, string sec)
    {
        name = n;
        address = a;
        postcode = p;
        cardNumber = c;
        expiryDate = ex;
        secretCode = sec;
    };
};

// function validating integer expected and according message:
int productQty(string msg)
{
    // declaring the variables:
    string datum;
    string errorMsg = "Please input valid number. Our stocks are limited to 15 units";
    string regCondition = "[0-9]+";
    // instantiate regex:
    regex reg(regCondition);
    // print instruction for user what's expected from function
    cout << msg << endl;
    // as long as input doesn't meet expectations:
    do
    {
        // error message in "if" for first iteration:
        if (!regex_match(datum, reg) && datum != "")
        {
            cout << errorMsg << endl;
        }

        // clean the buffer
        cin.clear();
        // request the input to "datum" again
        getline(cin >> ws, datum);
    } while (!regex_match(datum, reg));

    // transform string input to integer
    return stoi(datum);
}

// function grouping product data related inputs
void productsForm()
{
    int beans = productQty("Enter Baked Beans units to buy.");
    int popcorn = productQty("Enter Popcorn units to buy.");
    int milk = productQty("Enter Evaporated Milk units to buy.");
    int bread = productQty("Enter Bread units to buy.");
    cout << endl
         << "beans " << beans << endl
         << "popcorn " << popcorn << endl
         << "milk " << milk << endl
         << "bread " << bread << endl;
}
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
        regCondition = "[A-Za-z]+";
        errorMsg = "Please input the name - at least 1 letter - no numbers or special characters.";
    }
    // regex simplified: 2 digits 0-9 per slash -> validates only format, not if date is out of range
    else if (typo == "date")
    {
        regCondition = "[0-9]{2}/[0-9]{2}/[0-9]{2}";
        errorMsg = "Please input the date in correct format.";
    }
    else if (typo == "postcode")
    // just format XXX(X)-XXX
    {
        regCondition = "([a-zA-Z0-9]{3,4} [a-zA-Z0-9]{3})|([a-zA-Z0-9]{3,4}[a-zA-Z0-9]{3})";
        errorMsg = "Please input the postcode in correct format. XXX(X)-XXX";
    }
    else if (typo == "card")
    // 16 digits
    {
        regCondition = "([0-9]{16})|([0-9]{4} [0-9]{4} [0-9]{4} [0-9]{4})";
        errorMsg = "Card number must contain 16 digits.";
    };

    if (typo != "none")
    {
        // instantiate regex
        regex reg(regCondition);
        // print instruction for user what's expected from function
        cout << msg << endl;
        // as long as input doesn't meet expectations:
        do
        {
            // error message in "if" for first iteration:
            if (!regex_match(datum, reg) && datum != "")
            {
                cout << errorMsg << endl;
            }
            // clean the buffer
            cin.clear();
            // request the input to "datum" again
            getline(cin >> ws, datum);
        } while (!regex_match(datum, reg));
        return datum;
    }

    cout << msg << endl;
    // request the input allowing whitespaces
    getline(cin >> ws, datum);
    return datum;
};

// function grouping customer data related inputs
void customerInputForm()
{
    string name = validation("name", "Enter a name (No special characters or numbers): ");
    string address = validation("none", "Enter 1st line of the address");
    string postcode = validation("postcode", "Enter postcode in format (XXX(x) XXX)");
    string cardNumber = validation("card", "Enter 16-digit card number");
    string expiryDate = validation("date", "Enter the expiry date (DD/MM/YY format) ");
    string secretCode = validation("none", "Enter your secret code");

    Customer Customer1(name, address, postcode, cardNumber, expiryDate, secretCode);

    cout << endl
         << "name " << Customer1.name << endl
         << "address " << Customer1.address << endl
         << "postcode " << Customer1.postcode << endl
         << "cardNumber " << Customer1.cardNumber << endl
         << "expiryDate " << Customer1.expiryDate << endl
         << "secretCode " << Customer1.secretCode << endl;
};

int main()
{
    customerInputForm();
    // productsForm();
}