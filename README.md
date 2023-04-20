# Cpp_Coursework_Shopping_Cart
File created using syntax and .md format  properly displaying on [my GitHub](https://github.com/MMadejsza/Cpp_Coursework_Shopping_Cart)
## Difficulties:


### :x: *Willing to practice the OOP approach but not to overbuild the code length referring to the specification*
- :white_check_mark: I resigned from encapsulation with getters(), setters() methods and left only public scope
```

// creating Product class / template to store collected data of each product
class Product
{
    // public attributes:
public:
    string name;
    float price;
    int quantity;
    float totalNet;
```


### :x: *Defining foreign object as an attribute of already existing one*
- :white_check_mark: Like in JavaScript, I could assign foreign Objects and all their properties, in C++ I didn't find a short straightforward solution. That's why I wrapped the object in vectors
- JS [Project](https://github.com/MMadejsza/JS_OOP_Project-Slot_Machine/blob/master/Game.js):
```
class Game {
	constructor(startWallet) {
		//- initiating previous classes
		this.stats = new Statistics();
		this.wallet = new Wallet(startWallet);
[...]
```
- C++:
```
// creating Cart class / template to store collected data
class Cart
{
    // public attributes:
public:
    vector<Customer> ownerDetails;
    vector<Product> products;
[...]
```
### :x: *Regex validation not fully bulletproof, inputs cutting of spaces*
- :white_check_mark: Despite practicing more complex features than the specification required, I wanted to keep the code quite simple and apply only solutions I fully understand. That's why we may find regex postcode validation allowing some unreal postcodes but on the other hand, the regex doesn't allow errors to occur and I didn't have to use try/catch phrases.
- :white_check_mark: cutting white spaces sorted out using getline and ws (white space):
```
  getline(cin >> ws, datum);
 ```
### :x: *Proper calculations on currency format*
- :white_check_mark: If I'd like to just display output with the precision of 2 digits, I would use the string "%.2f" restriction. The problem was to further compute prices having two decimal points. Here I used the round method but moved the decimal point by 2 for rounding and then get I back:
```
[...]
float productValue = round(products[i].price * float(products[i].quantity) * 100) / 100;
[...]
```
#### :x: *Despite while loop, no repetitive error message after wrong input*
- :x: Problem remained.

## Printing Invoice Difficulties:
### :x: *Flow complexity and repetition*
 To print out a satisfying invoice, the procedure required long lines of code. Repetitive, differing only in small details and calculations for different sections.
 - :white_check_mark: In the main printing function, the "config" section with variables containing values a bit managing invoice style or shorting notation to pass down to partial functions:
 ```
 // Invoice printer:
    void printInvoice()
    {
        // Describe invoice
        string header = " I N V O I C E ";
        string paddings = " * ";
        int width = 33;
        Customer c = ownerDetails[0];
	[...]
 ```
 - :white_check_mark: Encapsulation into support/partial functions and wrapping content which may change in vectors:
  ```
  [...]
// Define heading for each column:
        vector<string> headings{"ITEMS:", "QTY x PRICE:", "COST:"};
        // Print header using support function (empty string swaps "product price"):
        tripleLine("headings", headings[0], headings[1], "", headings[2], width, paddings, header);
        centeredLine(" ", width, paddings, header);
  [...]
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
  ```
### :x: *Different justify rules*
 - :white_check_mark: Using 2 separate functions:
```
//  Prints 3-column line
    void tripleLine(string type, string itemText, string qty, string price, string cost, int width, string padding, string header)
// Prints 2-column line / centered text
    void centeredLine(string text, int width, string padding, string header)
```
### :x: *Getting columns with centered content*
- :white_check_mark: The default behavior of setw() is justify-right. Thus to achieve -center feature the best for me was to divide the visible column into 2 invisible ones and set the middle as justifying start + moving half of the content
```
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
```
- :white_check_mark: 3 visible columns = 6 real ones in default setup

### :x: *Invoice flexibility*
- :white_check_mark: having different input values causing sometimes 3-6 characters output I had to set the widths of fields as flexible based on calculations:
```
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
	[...]
```
