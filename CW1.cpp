#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

// creating Product class / template to store collected data of each product
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

// creating Cart class / template to store collected data
class Cart
{
    // public attributes:
public:
    vector<Customer> ownerDetails;
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
            float productValue = round(products[i].price * float(products[i].quantity) * 100) / 100;
            // store/assign it in Product object:
            products[i].totalNet = productValue;
            // Add item total price to cart net value:
            cartNetValue += productValue;
        };
        // assign result to Cart:
        netCost = cartNetValue;
    };

    float calcVat()
    {
        VAT = round(netCost * vatValue * 100) / 100;
    };

    float calcGross()
    {
        grossCost = round((netCost + VAT) * 100) / 100;
    };

    void printFooter(string header, string paddings, int width, float VAT, float grossCost, float netCost)
    {
        centeredLine(" ", width, paddings, header);
        centeredLine("TOTAL:", width, paddings, header);
        tripleLine("footer", "Total net:", " ", "", to_string(netCost), width, paddings, header);
        tripleLine("footer", "VAT:", " ", "", to_string(VAT), width, paddings, header);
        tripleLine("footer", "Total inc. VAT:", " ", "", to_string(grossCost), width, paddings, header);
        centeredLine(" ", width, paddings, header);
        centeredLine(header, width, paddings, header);
    }

    // Prints center section - center header + list of items:
    void printItems(string header, string paddings, int width, vector<Product> products)
    {
        vector<string> headings{"ITEM:", "QTY x PRICE:", "COST:"};
        int toEndOfHeaderDist = width;

        tripleLine("headings", headings[0], headings[1], "", headings[2], toEndOfHeaderDist, paddings, header);
        centeredLine(" ", width, paddings, header);

        for (int i = 0; i < products.size(); i++)
        {
            tripleLine("products", products[i].name, to_string(products[i].quantity), to_string(products[i].price), to_string(products[i].totalNet), toEndOfHeaderDist, paddings, header);
        }
    }

    void tripleLine(string type, string text, string text2, string text3, string text4, int toEndOfHeaderDist, string padding, string header)
    {
        // Calculations - everything is aligned to right
        // Entire invoice width is previous double distance to the end of text - this text because it's symmetric. We add 1 padding because we don't set its field at the end of line
        int entireWidth = toEndOfHeaderDist + (toEndOfHeaderDist - header.size() + 2 * padding.size());
        // 1/3 Width:
        int oneThirdOfInvoice = (entireWidth - padding.size()) / 3;
        // center of 1/3 Width: (it's width of field ending at the center remembering about alignment to right)
        int centerOfOneThird = oneThirdOfInvoice / 2;
        // moving by text half to center it
        int centeredThirdText = centerOfOneThird + (0.5 * text.size());
        int centeredThirdText2 = centerOfOneThird + (0.5 * text2.size());
        int centeredThirdText3 = centerOfOneThird + (0.5 * text3.size());
        // rest to fill up as 1/3 - width to the end of text -1 for ending with space " "
        int toEndOfThird = oneThirdOfInvoice - centeredThirdText - 1;
        int toEndOfThird2 = oneThirdOfInvoice - centeredThirdText2 - 1;
        int toEndOfThird3 = oneThirdOfInvoice - centeredThirdText3 - 1;

        if (type == "headings")
        {
            // 1/3 of Invoice
            // Padding
            cout
                << setw(padding.size())
                << padding;
            cout
                << setw(centerOfOneThird + (0.5 * text.size()))
                << setfill(' ')
                << text;
            cout
                << setw(toEndOfThird - (padding.size() / 2))
                << setfill(' ')
                << " ";
            // 1/3 of Invoice
            cout
                << setw(centerOfOneThird + (0.5 * text2.size()))
                << setfill(' ')
                << text2;
            cout
                << setw(toEndOfThird2 - (padding.size() / 2))
                << setfill(' ')
                << " ";
            // 1/3 of Invoice
            cout
                << setw(centerOfOneThird + (0.5 * text3.size()))
                << setfill(' ')
                << text4;
            cout
                << setw(toEndOfThird3 + padding.size() + 2)
                << setfill(' ')
                << padding << endl;
        }
        else if (type == "products")
        {
            // 1/3 of Invoice
            // Padding
            cout
                << setw(padding.size())
                << padding;
            cout
                << setw(oneThirdOfInvoice - padding.size())
                << setfill(' ')
                << text;
            cout
                << setw(1)
                << setfill(' ')
                << " ";
            // 1/3 of Invoice
            // manual aligning (numbers):
            cout.precision(2);
            cout
                << setw(centerOfOneThird - (0.5 * (text2 + " x " + "  ").size()))
                << setfill(' ') << fixed
                << text2 << " x " << stof(text3);
            cout
                << setw(toEndOfThird2 - 5)
                << setfill(' ')
                << " ";
            // 1/3 of Invoice
            cout.precision(2);
            cout
                << setw(centerOfOneThird)
                << setfill(' ') << fixed
                << stof(text4);
            cout
                << setw(toEndOfThird3 + padding.size() + 6)
                << setfill(' ')
                << padding << endl;
        }
        else
        {

            // 1/3 of Invoice
            // Padding
            cout
                << setw(padding.size())
                << padding;
            cout
                << setw(oneThirdOfInvoice - padding.size())
                << setfill(' ')
                << text;
            cout
                << setw(1)
                << setfill(' ')
                << " ";
            // 1/3 of Invoice
            cout
                << setw(centerOfOneThird + (0.5 * text2.size()))
                << setfill(' ')
                << text2;
            cout
                << setw(toEndOfThird2 - (padding.size() / 2))
                << setfill(' ')
                << " ";
            // 1/3 of Invoice
            cout.precision(2);
            cout
                << setw(centerOfOneThird + (0.5 * text3.size()))
                << setfill(' ') << fixed
                << stof(text4);
            cout
                << setw(toEndOfThird3 + padding.size() + 2)
                << setfill(' ')
                << padding << endl;
        }
    }

    void centeredLine(string text, int toEndOfHeaderDist, string padding, string header)
    {
        // Calculations - everything is aligned to right
        // Width of field ending in the center of Header Text, "toEndOfHeaderDist" is initial value which we treat as width of invoice.
        int distToCenterOfHeader = toEndOfHeaderDist - (header.size() / 2);
        // Width of field ending with the end of centered text (moved right/wider)
        int toEndOfCenteredTextDist = distToCenterOfHeader + (0.5 * text.size());
        // Entire invoice width is previous double distance to the end of text - this text because it's symmetric. We add 1 padding because we don't set its field at the end of line
        int entireWidth = toEndOfHeaderDist + (toEndOfHeaderDist - header.size() + padding.size());
        // Field width to the end of the invoice is conditional like below
        int endOfTextToEnd;

        if (header.size() == text.size())
        {
            endOfTextToEnd = (toEndOfHeaderDist - text.size() + padding.size());
        }
        else
        {
            endOfTextToEnd = entireWidth - toEndOfCenteredTextDist;
        };

        // If we center actual header of Invoice we change filling characters:
        if (text == header)
        {
            cout // field for padding only because we want to keep default right align but stil start from specific padding
                << setw(padding.size())
                << padding;
            cout
                << setw(distToCenterOfHeader + (0.5 * text.size()))
                << setfill('*')
                << text;
            cout
                << setw(endOfTextToEnd)
                << setfill('*')
                << padding
                << endl;
        }
        else
        {

            cout
                << setw(padding.size())
                << padding;
            cout
                << setw(distToCenterOfHeader + (0.5 * text.size()))
                << setfill(' ')
                << text;
            cout
                << setw(endOfTextToEnd)
                << setfill(' ')
                << padding
                << endl;
        }
    }

    // Prints Header section - "Invoice + customer details"
    void printHeader(string header, string padding, int length, Customer c)
    {
        int toEndOfHeaderDist = length;
        // Print invoice elements using specific functions:
        centeredLine(header, toEndOfHeaderDist, padding, header);
        centeredLine(" ", toEndOfHeaderDist, padding, header);
        centeredLine("Customer:", toEndOfHeaderDist, padding, header);
        centeredLine(c.name, toEndOfHeaderDist, padding, header);
        centeredLine(c.address, toEndOfHeaderDist, padding, header);
        centeredLine(c.postcode, toEndOfHeaderDist, padding, header);
        centeredLine(c.cardNumber, toEndOfHeaderDist, padding, header);
        centeredLine(c.expiryDate, toEndOfHeaderDist, padding, header);
        centeredLine(c.secretCode, toEndOfHeaderDist, padding, header);
        centeredLine(" ", toEndOfHeaderDist, padding, header);
    }

    void printInvoice()
    {
        // Describe invoice
        string header = " I N V O I C E ";
        string paddings = " * ";
        int width = 33;
        Customer c = ownerDetails[0];

        // Print the invoice header
        printHeader(header, paddings, width, c);
        // Print all bought items
        printItems(header, paddings, width, products);
        // Print summary in footer
        printFooter(header, paddings, width, VAT, grossCost, netCost);
    }

    // constructor - "creation template"
    Cart(vector<Product> productsVector, vector<Customer> ownerVector)
    {
        ownerDetails = ownerVector;
        products = productsVector;
        // call straight away when instantiating:
        calcNet();
        calcVat();
        calcGross();
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
Cart productsForm(Customer Cust)
{
    // int beans = productQty("Enter Baked Beans units to buy.");
    // int popcorn = productQty("Enter Popcorn units to buy.");
    // int milk = productQty("Enter Evaporated Milk units to buy.");
    // int bread = productQty("Enter Bread units to buy.");

    int beans = 3;
    int popcorn = 3;
    int milk = 3;
    int bread = 3;

    // instantiate objects for each product:
    Product Beans("Baked Beans", 1.20, beans);
    Product Popcorn("Popcorn", 0.80, popcorn);
    Product Milk("Evaporated Milk", 1.15, milk);
    Product Bread("Bread", 2.34, bread);

    // declare container of products:
    vector<Product> productsVector;
    // push products into it:
    productsVector.insert(productsVector.end(), {Beans, Popcorn, Milk, Bread});
    // productsVector.push_back(Popcorn);
    // productsVector.push_back(Milk);
    // productsVector.push_back(Bread);
    vector<Customer> ownerDetailsVector;
    ownerDetailsVector.push_back(Cust);

    // instantiate Cart with product and assign it to customer:
    Cart Cart1(productsVector, ownerDetailsVector);
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

    string name = "Maciej Madejsza";
    string address = "6 Magpie way";
    string postcode = "RG31 4SJ";
    string cardNumber = "1111 2222 3333 4444";
    string expiryDate = "12/12/12";
    string secretCode = "SecretCode";

    Customer Customer1(name, address, postcode, cardNumber, expiryDate, secretCode);
    // vector<Customer> customer1vector;
    // customer1vector.push_back(Customer1);

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
    // print output:
    Cart1.printInvoice();
}

// ? Resources:
// ? https://developer.mozilla.org/en-US/
// ? https://www.w3schools.com/
// ? https://stackoverflow.com/