#include <iostream>
#include <string>
#include <regex>     //regex for validation
#include <vector>    //vectors
#include <cmath>     //rounding calculations
#include <iomanip>   //printing invoice
#include <algorithm> //transform to uppercase
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
    // VAT calculations:
    void calcVat()
    {
        VAT = round(netCost * vatValue * 100) / 100;
    };
    // gross cost calculations:
    void calcGross()
    {
        grossCost = round((netCost + VAT) * 100) / 100;
    };

    // PRINTING------------------------------------------------------------
    //  Prints 3-column line
    void tripleLine(string type, string itemText, string qty, string price, string cost, int width, string padding, string header)
    {
        // assign upper readability to specific meaning variable
        int toEndOfHeaderDist = width;
        // Calculations - everything is aligned to right
        // Entire invoice width is previous double distance to the end of text - this text because it's symmetric. We add 1 padding because we don't set its field at the end of line
        int entireWidth = padding.size() + toEndOfHeaderDist + (toEndOfHeaderDist - header.size()) + padding.size();
        // 1/3 Width:
        int oneThirdOfInvoice = (entireWidth - 2 * padding.size()) / 3;
        // center of 1/3 Width: (it's width of field ending at the center remembering about alignment to right)
        int centerOfOneThird = oneThirdOfInvoice / 2;
        // moving by text half to center it
        int centeredThirdText = centerOfOneThird + (0.5 * itemText.size());
        int centeredThirdQty = centerOfOneThird + (0.5 * qty.size());
        int centeredThirdPrice = centerOfOneThird + (0.5 * (0.5 * price.size()));
        int centeredThirdQP = centerOfOneThird + (0.5 * ((qty + " x ").size()));
        int centeredThirdCost = centerOfOneThird + (0.5 * cost.size());
        // rest to fill up as 1/3 - width to the end of text -1 for ending with space " "
        int toEndOfThird = oneThirdOfInvoice - centeredThirdText + 1;
        int toEndOfThirdQty = oneThirdOfInvoice - centeredThirdQty;
        int toEndOfThirdPrice = oneThirdOfInvoice - centeredThirdPrice;
        // 4 is number of following 0s to cut when price is a string
        int toEndOfThirdQP = oneThirdOfInvoice - (centeredThirdQP + price.size() - 5);
        int toEndOfThirdCost = oneThirdOfInvoice - centeredThirdCost + padding.size() - 1;
        // PADDING START EVERYWHERE
        cout
            << setw(padding.size())
            << padding;
        // IF PRINTING HEADINGS
        if (type == "headings")
        {
            // 1/3 of Invoice
            cout
                << setw(centeredThirdText)
                << setfill(' ')
                << itemText;
            cout
                << setw(toEndOfThird)
                << setfill(' ')
                << " ";
            // 2/3 of Invoice
            cout
                << setw(centeredThirdQty)
                << setfill(' ')
                << qty;
            cout
                << setw(toEndOfThirdQty)
                << setfill(' ')
                << " ";
            // 3/3 of Invoice
            cout.precision(2);
            cout
                << setw(centeredThirdCost)
                << setfill(' ')
                << cost;
            cout
                << setw(toEndOfThirdCost)
                << setfill(' ')
                << padding << endl;
        }
        // IF PRINTING PRODUCTS OR FOOTER  (the same 1st 1/3)
        if ((type == "products") || (type == "footer"))
        {
            // 1/3 of Invoice
            cout
                << setw(oneThirdOfInvoice)
                << setfill(' ')
                << itemText;
            cout
                << setw(1)
                << setfill(' ')
                << " ";
        }
        // IF PRINTING PRODUCTS ONLY (unique 2/3 and 3/3)
        if (type == "products")
        {
            // 2/3 of Invoice
            // manual aligning (numbers):
            cout.precision(2);
            cout
                << setw(centerOfOneThird)
                << setfill(' ') << fixed
                << qty + " x " << stof(price);
            cout
                << setw(centerOfOneThird - price.size() + 5)
                << setfill(' ')
                << " ";
            // 3/3 of Invoice
            cout.precision(2);
            cout
                // align center by dot
                << setw(centerOfOneThird + 3)
                << setfill(' ') << fixed
                << stof(cost);
            cout
                << setw(centerOfOneThird)
                << setfill(' ')
                << padding << endl;
        }
        // IF PRINTING FOOTER ONLY (unique 2/3+3/3)
        else if (type == "footer")
        {
            // 2/3 of Invoice
            cout
                << setw(oneThirdOfInvoice)
                << setfill(' ')
                << " ";
            // 3/3 of Invoice
            cout.precision(2);
            cout
                << setw(centerOfOneThird + 3)
                << setfill(' ')
                << stof(cost);
            cout
                << setw(centerOfOneThird)
                << setfill(' ')
                << padding << endl;
        }
    }
    // Prints 2-column line / centered text
    void centeredLine(string text, int width, string padding, string header)
    {
        // assign upper readability to specific meaning variable
        int toEndOfHeaderDist = width;
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

        cout // field for padding only because we want to keep default right align but stil start from specific padding
            << setw(padding.size())
            << padding;
        // If we center actual header of Invoice we change filling characters (couldn'y be done with function swapping char):
        if (text == header)
        {
            // First column to the end of the text:
            cout
                << setw(distToCenterOfHeader + (0.5 * text.size()))
                << setfill('*')
                << text;
            // Second column from the end of the text:
            cout
                << setw(endOfTextToEnd)
                << setfill('*')
                << padding
                << endl;
        }
        else
        {
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
    // Prints bottom  section - summary with vVAT:
    void printFooter(string header, string paddings, int width, float VAT, float grossCost, float netCost)
    {
        // Print invoice elements using specific functions:
        centeredLine(" ", width, paddings, header);
        centeredLine("TOTAL:", width, paddings, header);
        // (empty strings swap "product quantity" and "product price"):
        tripleLine("footer", "TOTAL NET:", "", "", to_string(netCost), width, paddings, header);
        tripleLine("footer", "VAT:", "", "", to_string(VAT), width, paddings, header);
        tripleLine("footer", "TOTAL INC. VAT:", "", "", to_string(grossCost), width, paddings, header);
        centeredLine(" ", width, paddings, header);
        centeredLine(header, width, paddings, header);
    }
    // Prints center section - center header + list of items:
    void printItems(string header, string paddings, int width, vector<Product> products)
    {
        // Define heading for each column:
        vector<string> headings{"ITEMS:", "QTY x PRICE:", "COST:"};
        // Print header using support function (empty string swaps "product price"):
        tripleLine("headings", headings[0], headings[1], "", headings[2], width, paddings, header);
        centeredLine(" ", width, paddings, header);
        // Print out products from cart using support function
        for (int i = 0; i < products.size(); i++)
        {
            // string conversion only to let it be universal for headings and products printing - utilized within function
            tripleLine("products", products[i].name, to_string(products[i].quantity), to_string(products[i].price), to_string(products[i].totalNet), width, paddings, header);
        }
    }
    // Prints Header section - "Invoice + customer details"
    void printHeader(string header, string padding, int width, Customer c)
    {
        // Print invoice elements using specific functions:
        centeredLine(header, width, padding, header);
        centeredLine(" ", width, padding, header);
        centeredLine("CUSTOMER:", width, padding, header);
        centeredLine(c.name, width, padding, header);
        centeredLine(c.address, width, padding, header);
        centeredLine(c.postcode, width, padding, header);
        centeredLine(c.cardNumber, width, padding, header);
        centeredLine(c.expiryDate, width, padding, header);
        centeredLine(c.secretCode, width, padding, header);
        centeredLine(" ", width, padding, header);
    }
    // Invoice printer:
    void printInvoice()
    {
        // Describe invoice
        string header = " I N V O I C E ";
        string paddings = " * ";
        int width = 33;
        Customer c = ownerDetails[0];

        cout << endl;
        // Print the invoice header
        printHeader(header, paddings, width, c);
        // Print all bought items
        printItems(header, paddings, width, products);
        // Print summary in footer
        printFooter(header, paddings, width, VAT, grossCost, netCost);
        cout << endl;
    }
    // PRINTING END------------------------------------------------------------
    //  constructor - "creation template"
    Cart(vector<Product> productsVector, vector<Customer> ownerVector)
    {
        // assign received vector with products
        ownerDetails = ownerVector;
        // assign customer object wrapped in vector
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

    // as long as input doesn't meet expectations:
    do
    {
        // print instruction for user what's expected from function
        cout << msg << endl;
        // error message in "if" for first iteration:
        if (!regex_match(datum, reg) && datum != "")
        {
            cout << errorMsg << endl;
        }
        // clean the buffer
        cin.clear();
        // request the input to "datum" again
        cin >> datum;
    } while (!regex_match(datum, reg));

    // transform string input to integer
    return stoi(datum);
}

// function grouping product data related inputs
Cart productsForm(Customer Cust)
{
    // Collect data about quantity using validation function:
    int beans = productQty("Enter Baked Beans units to buy.");
    int popcorn = productQty("Enter Popcorn units to buy.");
    int milk = productQty("Enter Evaporated Milk units to buy.");
    int bread = productQty("Enter Bread units to buy.");

    // Dummy data to test invoice printing:
    // int beans = 1;
    // int popcorn = 1;
    // int milk = 1;
    // int bread = 1;

    // instantiate objects for each product:
    Product Beans("Baked Beans", 1.20, beans);
    Product Popcorn("Popcorn", 0.80, popcorn);
    Product Milk("Evaporated Milk", 1.15, milk);
    Product Bread("Bread", 2.34, bread);

    // declare container of products:
    vector<Product> productsVector;
    // insert many products into it:
    productsVector.insert(productsVector.end(), {Beans, Popcorn, Milk, Bread});
    // declare container customer object (way around for declaring object in foreign class):
    vector<Customer> ownerDetailsVector;
    ownerDetailsVector.push_back(Cust);

    // instantiate Cart with products and assign it to customer:
    Cart Cart1(productsVector, ownerDetailsVector);
    return Cart1;
}

// function validating expected input type "typo" and according message:
// (type of  expected datum, instruction for users)
string validation(string typo, string msg)
{
    // declaring the variables:
    string datum;
    string regCondition;
    string errorMsg;

    // specify validation rules in regex based on given argument "typo"
    if (typo == "name")
    {
        regCondition = "[A-Za-z ]+";
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

    // if we require validation:
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
        // transform to upper case:
        transform(datum.begin(), datum.end(), datum.begin(), ::toupper);
        return datum;
    }
    // if we do NOT require validation:
    cout << msg << endl;
    // request the input allowing whitespaces
    getline(cin >> ws, datum);
    // transform to upper case:
    transform(datum.begin(), datum.end(), datum.begin(), ::toupper);
    return datum;
};

// function grouping customer data related inputs
Customer customerInputForm()
{
    // Collect data using validation function:
    string name = validation("name", "Enter a name (No special characters or numbers): ");
    string address = validation("none", "Enter 1st line of the address");
    string postcode = validation("postcode", "Enter postcode in format (XXX(x) XXX)");
    string cardNumber = validation("card", "Enter 16-digit card number");
    string expiryDate = validation("date", "Enter the expiry date (DD/MM/YY format) ");
    string secretCode = validation("none", "Enter your secret code");

    // Dummy data for testing without validation:
    // string name = "Maciej Madejsza";
    // string address = "6 Magpie way";
    // string postcode = "RG31 4SJ";
    // string cardNumber = "1111 2222 3333 4444";
    // string expiryDate = "12/12/12";
    // string secretCode = "SecretCode";

    // create object customer based on collected data
    Customer Customer1(name, address, postcode, cardNumber, expiryDate, secretCode);
    return Customer1;
};

int main()
{
    // customerInputForm returning Customer object;
    auto Customer1 = customerInputForm();
    // productsForm returning Cart object signed by Customer into argument;
    auto Cart1 = productsForm(Customer1);
    // print output:
    Cart1.printInvoice();
}

// ? Resources:
// ? https://developer.mozilla.org/en-US/
// ? https://www.w3schools.com/
// ? https://stackoverflow.com/