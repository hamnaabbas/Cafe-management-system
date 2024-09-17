#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

// Definitions for Ingredient, Item, Inventory, Menu, Order, and CafeManagement

struct Ingredient {
    char name[15];

    void changeName(const char* n) {
        strcpy(name, n);
    }
};

struct Item {
    char name[15];
    float price;
    int number_of_ingredient;
    Ingredient* ingr;
    string status;

    Item() : price(0.0), number_of_ingredient(0), ingr(nullptr) {}

    Item(const char* name5, float pr, int number, const string& s, Ingredient* ingredi) 
        : price(pr), number_of_ingredient(number), status(s) {
        strcpy(name, name5);
        ingr = new Ingredient[number_of_ingredient];
        for (int i = 0; i < number_of_ingredient; ++i) {
            ingr[i] = ingredi[i];
        }
    }

    ~Item() {
        delete[] ingr;
    }

    void changeName(const char* n) {
        strcpy(name, n);
    }

    void changePrice(float p) {
        price = p;
    }

    bool changeStatus(const string& s) {
        status = s;
        return true;
    }

    void addIngredient(const Ingredient& name1) {
        Ingredient* newIngredients = new Ingredient[number_of_ingredient + 1];
        for (int i = 0; i < number_of_ingredient; ++i) {
            newIngredients[i] = ingr[i];
        }
        newIngredients[number_of_ingredient] = name1;
        delete[] ingr;
        ingr = newIngredients;
        ++number_of_ingredient;
    }

    bool removeIngredient(const char* name_of) {
        for (int i = 0; i < number_of_ingredient; ++i) {
            if (strcmp(ingr[i].name, name_of) == 0) {
                for (int j = i; j < number_of_ingredient - 1; ++j) {
                    ingr[j] = ingr[j + 1];
                }
                --number_of_ingredient;
                Ingredient* newIngredients = new Ingredient[number_of_ingredient];
                for (int k = 0; k < number_of_ingredient; ++k) {
                    newIngredients[k] = ingr[k];
                }
                delete[] ingr;
                ingr = newIngredients;
                return true;
            }
        }
        return false;
    }

    void print() const {
        cout << "Item Name: " << name << endl;
        cout << "Price: " << price << endl;
        cout << "Ingredients: ";
        for (int i = 0; i < number_of_ingredient; ++i) {
            cout << ingr[i].name << " ";
        }
        cout << endl;
    }
};

struct Inventory {
    int quantity;
    int number_of_ing;
    Ingredient* ingred;

    Inventory() : quantity(0), number_of_ing(0), ingred(nullptr) {}

    Inventory(int quan, int number, Ingredient* ingre)
        : quantity(quan), number_of_ing(number) {
        ingred = new Ingredient[number_of_ing];
        for (int i = 0; i < number_of_ing; ++i) {
            ingred[i] = ingre[i];
        }
    }

    ~Inventory() {
        delete[] ingred;
    }

    void print() const {
        for (int i = 0; i < number_of_ing; ++i) {
            cout << "Ingredient " << i + 1 << ": " << ingred[i].name << ", Quantity: " << quantity << endl;
        }
    }

    void addIngredient(const Ingredient& name2) {
        Ingredient* newIngredients = new Ingredient[number_of_ing + 1];
        for (int i = 0; i < number_of_ing; ++i) {
            newIngredients[i] = ingred[i];
        }
        newIngredients[number_of_ing] = name2;
        delete[] ingred;
        ingred = newIngredients;
        ++number_of_ing;
    }

    void updateQuantity(const char* nam, int q) {
        for (int i = 0; i < number_of_ing; ++i) {
            if (strcmp(ingred[i].name, nam) == 0) {
                quantity = q;
                return;
            }
        }
    }
};

struct Menu {
    int number_of_item;
    Item* it;

    Menu() : number_of_item(0), it(nullptr) {}

    Menu(int number) : number_of_item(number) {
        it = new Item[number_of_item];
    }

    ~Menu() {
        delete[] it;
    }

    void print() const {
        for (int i = 0; i < number_of_item; ++i) {
            it[i].print();
        }
    }

    bool addItem(const Ingredient& name3, float p) {
        for (int i = 0; i < number_of_item; ++i) {
            if (strcmp(it[i].name, name3.name) == 0) {
                cout << "Item already exists!" << endl;
                return false;
            }
        }
        Item* newItems = new Item[number_of_item + 1];
        for (int i = 0; i < number_of_item; ++i) {
            newItems[i] = it[i];
        }
        newItems[number_of_item] = Item(name3.name, p, 1, "New", new Ingredient[1]{name3});
        delete[] it;
        it = newItems;
        ++number_of_item;
        return true;
    }

    void removeItem(const char* name) {
        int index = -1;
        for (int i = 0; i < number_of_item; ++i) {
            if (strcmp(it[i].name, name) == 0) {
                index = i;
                break;
            }
        }
        if (index != -1) {
            Item* newItems = new Item[number_of_item - 1];
            for (int i = 0, j = 0; i < number_of_item; ++i) {
                if (i != index) {
                    newItems[j++] = it[i];
                }
            }
            delete[] it;
            it = newItems;
            --number_of_item;
        }
    }
};

struct Order {
    int quantity;
    Menu* M;
    float cost;
    string status;

    Order() : quantity(0), M(nullptr), cost(0.0) {}

    Order(int quan, float cos, const string& update)
        : quantity(quan), cost(cos), status(update) {
        M = new Menu[quantity];
    }

    ~Order() {
        delete[] M;
    }

    void print() const {
        for (int i = 0; i < quantity; ++i) {
            cout << "Order Number: " << i + 1 << endl;
            M[i].print();
            cout << "Total Cost: " << cost << endl;
        }
    }

    void printBill() const {
        cout << "Total Amount: " << cost << endl;
    }

    void updateQuantity(int q) {
        quantity = q;
    }

    void updateStatus(const string& up) {
        status = up;
    }

    void addItem(const char* name1, int order_number, float p, const Ingredient& I) {
        if (order_number < quantity) {
            M[order_number].addItem(I, p);
        }
    }

    void calculateTotalPrice() {
        cost = 0.0;
        for (int i = 0; i < quantity; ++i) {
            for (int j = 0; j < M[i].number_of_item; ++j) {
                cost += M[i].it[j].price;
            }
        }
    }
};

struct CafeManagement {
    int number_of_inventory;
    int number_of_orders;
    Inventory* Inv;
    Order* order;
    int capital;

    CafeManagement() : number_of_inventory(0), number_of_orders(0), Inv(nullptr), order(nullptr), capital(0) {}

    ~CafeManagement() {
        delete[] Inv;
        delete[] order;
    }

    void setNumber_of_inventory(int n) {
        number_of_inventory = n;
    }

    void setNumber_of_orders(int o) {
        number_of_orders = o;
    }

    void setInventory(Inventory* I) {
        Inv = new Inventory[number_of_inventory];
        for (int i = 0; i < number_of_inventory; ++i) {
            Inv[i] = I[i];
        }
    }

    void setCapital(int c) {
        capital = c;
    }

    void printOrders() const {
        for (int i = 0; i < number_of_orders; ++i) {
            cout << "Order: " << i + 1 << endl;
            order[i].print();
            cout << "Ingredients: " << endl;
            for (int j = 0; j < Inv[i].number_of_ing; ++j) {
                cout << Inv[i].ingred[j].name << " Quantity: " << Inv[i].quantity << endl;
            }
        }
    }

    void addOrder(const Order& o) {
        Order* newOrders = new Order[number_of_orders + 1];
        for (int i = 0; i < number_of_orders; ++i) {
            newOrders[i] = order[i];
        }
        newOrders[number_of_orders] = o;
        delete[] order;
        order = newOrders;
        ++number_of_orders;
    }

    void printOrderByStatus(const string& up) const {
        for (int i = 0; i < number_of_orders; ++i) {
            if (order[i].status == up) {
                order[i].print();
            }
        }
    }
};

int main() {
    CafeManagement Cafe;
    int choice;

    while (true) {
        cout << "\nCafe Management System Menu" << endl;
        cout << "1. Add Order" << endl;
        cout << "2. Print All Orders" << endl;
        cout << "3. Print Orders By Status" << endl;
        cout << "4. Add Inventory" << endl;
        cout << "5. Print Inventory" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int numOrders;
                cout << "Enter the number of orders to add: ";
                cin >> numOrders;
                Cafe.setNumber_of_orders(numOrders);
                Cafe.order = new Order[numOrders];

                for (int i = 0; i < numOrders; ++i) {
                    cout << "Order " << i + 1 << endl;
                    
                    int numItems;
                    cout << "Enter the number of items: ";
                    cin >> numItems;
                    Menu menu(numItems);

                    for (int j = 0; j < numItems; ++j) {
                        cout << "Item " << j + 1 << endl;
                        char itemName[15];
                        float itemPrice;
                        int numIngredients;

                        cout << "Enter name of the item: ";
                        cin.ignore();
                        cin.getline(itemName, 15);
                        strcpy(menu.it[j].name, itemName);

                        cout << "Enter Price: ";
                        cin >> itemPrice;
                        menu.it[j].price = itemPrice;

                        cout << "Enter number of ingredients: ";
                        cin >> numIngredients;
                        Ingredient* ingredients = new Ingredient[numIngredients];
                        for (int k = 0; k < numIngredients; ++k) {
                            cout << "Enter name of ingredient " << k + 1 << ": ";
                            cin.ignore();
                            cin.getline(itemName, 15);
                            ingredients[k].changeName(itemName);
                        }
                        menu.it[j].number_of_ingredient = numIngredients;
                        menu.it[j].ingr = ingredients;
                    }
                    Cafe.order[i].M = new Menu[1];
                    Cafe.order[i].M[0] = menu;
                    Cafe.order[i].quantity = 1;
                    Cafe.order[i].status = "Pending";
                    Cafe.order[i].calculateTotalPrice();  // Calculate total price for each order
                }
                break;
            }

            case 2: {
                Cafe.printOrders();
                break;
            }

            case 3: {
                string status;
                cout << "Enter the status to filter orders by: ";
                cin.ignore();
                getline(cin, status);
                Cafe.printOrderByStatus(status);
                break;
            }

            case 4: {
                int numIngredients;
                cout << "Enter the number of ingredients to add: ";
                cin >> numIngredients;
                Ingredient* ingredients = new Ingredient[numIngredients];

                for (int i = 0; i < numIngredients; ++i) {
                    cout << "Enter name of ingredient " << i + 1 << ": ";
                    char ingredientName[15];
                    cin.ignore();
                    cin.getline(ingredientName, 15);
                    ingredients[i].changeName(ingredientName);
                }

                Inventory inventory(numIngredients, numIngredients, ingredients);
                Cafe.setInventory(&inventory);
                break;
            }

            case 5: {
                cout << "Current Inventory:" << endl;
                if (Cafe.Inv) {
                    for (int i = 0; i < Cafe.number_of_inventory; ++i) {
                        Cafe.Inv[i].print();
                    }
                } else {
                    cout << "No inventory available." << endl;
                }
                break;
            }

            case 6: {
                cout << "Exiting program." << endl;
                return 0;
            }

            default: {
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }

        char continueChoice;
        cout << "Do you want to continue? (y/n): ";
        cin >> continueChoice;
        if (continueChoice != 'y' && continueChoice != 'Y') {
            cout << "Exiting program." << endl;
            break;
        }
    }

    return 0;
}
