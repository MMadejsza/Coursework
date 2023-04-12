#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <limits>
using namespace std;

// creating Product class / template to store collected data
class Product
{
    // public attributes:
public:
    string name;
    float price;
    int quantity;
    float totalNet;

    // constructor - "creation template"
    Product(string n, float p, int q)
    {
        name = n;
        price = p;
        quantity = q;
    };
};

// creating Cart class / template to store collected data
class Cart
{
    // public attributes:
public:
    string owner;
    vector<Product> products;
    float netCost;
    float vatValue = 0.2;
    float VAT;
    float grossCost;

    // methods:
    // net calculations:
    void calcNet()
    {
        // initial value:
        float cartNetValue = 0;
        for (int i = 0; i < products.size(); i++)
        {
            // calculate each product price:
            float productValue = products[i].price * float(products[i].quantity);
            // store it in product object:
            products[i].totalNet = productValue;
            cartNetValue += productValue;
        };
        netCost = cartNetValue;
    };

    float calcVat()
    {
        VAT = netCost * vatValue;
    };

    float calcGross()
    {
        grossCost = netCost + VAT;
    };

    // constructor - "creation template"
    Cart(vector<Product> productsVector, string name)
    {
        owner = name;
        products = productsVector;
        calcNet();
        calcVat();
        calcGross();
    };
};

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
auto productsForm(auto Customer)
{
    int beans = productQty("Enter Baked Beans units to buy.");
    int popcorn = productQty("Enter Popcorn units to buy.");
    int milk = productQty("Enter Evaporated Milk units to buy.");
    int bread = productQty("Enter Bread units to buy.");

    // instantiate objects for each product:
    Product Beans("Baked Beans", 1.20, beans);
    Product Popcorn("Popcorn", 0.80, popcorn);
    Product Milk("Evaporated Milk", 1.15, milk);
    Product Bread("Bread", 2.34, bread);

    // declare container of products:
    vector<Product> productsVector;
    // push products into it:
    productsVector.push_back(Beans);
    productsVector.push_back(Popcorn);
    productsVector.push_back(Milk);
    productsVector.push_back(Bread);

    // instantiate Cart with product and assign it to customer:
    Cart Cart1(productsVector, Customer.name);
    return Cart1;
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
auto customerInputForm()
{
    // string name = validation("name", "Enter a name (No special characters or numbers): ");
    // string address = validation("none", "Enter 1st line of the address");
    // string postcode = validation("postcode", "Enter postcode in format (XXX(x) XXX)");
    // string cardNumber = validation("card", "Enter 16-digit card number");
    // string expiryDate = validation("date", "Enter the expiry date (DD/MM/YY format) ");
    // string secretCode = validation("none", "Enter your secret code");

    string name = "a";
    string address = "a";
    string postcode = "a";
    string cardNumber = "a";
    string expiryDate = "a";
    string secretCode = "a";

    Customer Customer1(name, address, postcode, cardNumber, expiryDate, secretCode);
    return Customer1;
    // cout << endl
    //      << "name " << Customer1.name << endl
    //      << "address " << Customer1.address << endl
    //      << "postcode " << Customer1.postcode << endl
    //      << "cardNumber " << Customer1.cardNumber << endl
    //      << "expiryDate " << Customer1.expiryDate << endl
    //      << "secretCode " << Customer1.secretCode << endl;
};

int main()
{
    // customerInputForm returning Customer object;
    auto Customer1 = customerInputForm();
    // productsForm returning Cart object signed by Customer;
    auto Cart1 = productsForm(Customer1);
    for (int i = 0; i < Cart1.products.size(); i++)
    {
        cout << endl
             << Cart1.products[i].name << " " << Cart1.products[i].totalNet << endl;
    }
    cout << endl
         << "cart netCost " << Cart1.netCost << endl;
    cout << endl
         << "cart Vat " << Cart1.VAT << endl;
    cout << endl
         << "cart gross " << Cart1.grossCost << endl;
}
// ? Resources:
// ? https://developer.mozilla.org/en-US/
// ? https://www.w3schools.com/
// ? https://stackoverflow.com/