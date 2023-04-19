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
