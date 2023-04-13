#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <cmath>
#include <iomanip>
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

    int printInvoice()
    {
        /*
         * Print Invoice to the console
         * Parameters:
         * custName: the name to appear on the invoice
         * orderDescription[]: an array of strings describing the items for the invoice
         * quantities[]: an array of ints denoting the quantities of each item being
         * ordered
         * unitCost[]: the unit cost (in pence) of each item being ordered
         *
         * Returns the total cost (including VAT) in pence
         */

        // Print the invoice header
        printHeader();

        // // Print the items line by line + return total cost
        // int totalPrice = printItems(orderDescription, quantities, unitCost);

        // // Print the invoice footer
        // totalPrice = printFooter(totalPrice);
        // return totalPrice;
    }

    int printFooter(int totalPrice)
    {
        // Print the invoice footer, with total
        // Returns totalPrice with VAT

        cout << "\nTotal \t\t = " << totalPrice;
        totalPrice = addVAT(totalPrice);
        cout << "Total+VAT \t = " << totalPrice;
        return totalPrice;
    }

    int addVAT(int cost)
    {
        // Add VAT 	tost
        return cost + (int)(cost * VAT);
    }

    int printItems(string orderDescription[], int quantities[], int unitCost[])
    {
        // Parameters as for PrintInvoice()
        // Returns total price (ex VAT)
        int totalPrice = 0; // Total cost of items bought
        for (int z = 0; z < sizeof(orderDescription); z++)
        {                                            // Loop through each item
            int price = unitCost[z] * quantities[z]; // Calculate price for each
            // item
            totalPrice = totalPrice + price;
            // Print line on invoice
            cout << orderDescription[z] << "\tx " << quantities[z] << "\t = " << price << endl;
        }
        return totalPrice;
    }

    void centeredLine(string text, int toEndOfHeaderDist, string padding, string header)
    {

        int distToCenterOfHeader = toEndOfHeaderDist - (header.size() / 2);
        int entireWidth = toEndOfHeaderDist + (toEndOfHeaderDist - header.size() + padding.size()); // if we have padding on the left with field size and we don't add field size at the end
        int toEndOfCenteredTextDist = distToCenterOfHeader + (0.5 * text.size());
        int endOfTextToEnd;
        if (header.size() == text.size())
        {
            endOfTextToEnd = (toEndOfHeaderDist - text.size() + padding.size());
        }
        else
        {
            endOfTextToEnd = entireWidth - toEndOfCenteredTextDist;
        };

        if (text == header)
        {
            cout // field for padding only because we want to keep default right align but start from padding
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

            cout // field for padding only because we want to keep default right align but start from padding
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

    void printHeader()
    {
        // Describe invoice
        string header = " I N V O I C E ";
        string padding = " * ";
        Customer c = ownerDetails[0];
        int toEndOfHeaderDist = 30;

        // Print invoice header
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

        cout << "Item\tQty\tCost(p)\n";
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

    int beans = 2;
    int popcorn = 2;
    int milk = 2;
    int bread = 2;

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
    Cart1.printHeader();

    // for (int i = 0; i < 1; i++)
    // {
    //     cout << endl
    //          << Cart1.ownerDetails[i].name << " " << Cart1.ownerDetails[i].address << endl;
    // }
    // cout << endl
    //      << Cart1.ownerDetails[0].name << " " << Cart1.ownerDetails[0].address << endl;

    // cout << endl
    //      << "cart netCost " << Cart1.netCost << endl;
    // cout << endl
    //      << "cart Vat " << Cart1.VAT << endl;
    // cout << endl
    //      << "cart gross " << Cart1.grossCost << endl;
}
// ? Resources:
// ? https://developer.mozilla.org/en-US/
// ? https://www.w3schools.com/
// ? https://stackoverflow.com/