//Open Close Principle Followed Example

#include<iostream>
#include<vector>
#include<string>

class Product {
public:

    double price;
    std::string name;

    Product(std::string name, double price) {
        this->price = price;
        this->name = name;
    }
};

class ShoppingCart {
private:
    std::vector<Product*> products;

public:
    void addProduct(Product* p) {
        products.push_back(p);
    }

    const std::vector<Product*> getProducts() {
        return products;
    }

    double calculateTotal() {
        double total = 0;
        for (auto p : products) {
            total += p->price;
        }
        return total;
    }

};

class ShoppingCartPrinter {
private:
    ShoppingCart* cart;

public:
    ShoppingCartPrinter(ShoppingCart* cart) {
        this->cart = cart;
    }

    void printInvoice() {
        std::cout << "Shopping cart invoice:\n";
        for (auto p : cart->getProducts()) {
            std::cout << p->name << " - RS " << p->price << std::endl;
        }
        std::cout << "Total: RS " << cart->calculateTotal() << std::endl;
    }

};

class Persistence {
protected:
    ShoppingCart* cart;
public:
    virtual void save() = 0; //Pure virtual function
};

class SQLPersistence : public Persistence {
public:
    SQLPersistence(ShoppingCart* cart) {
        this->cart = cart;
    }
    void save() override {
        std::cout << "Saving shopping cart to SQL database..." << std::endl;
    }
};

class MongoPersistence : public Persistence {
public:
    MongoPersistence(ShoppingCart* cart) {
        this->cart = cart;
    }
    void save() override {
        std::cout << "Saving shopping cart to Mongo DB..." << std::endl;
    }
};

class FilePersistence : public Persistence {
public:
    FilePersistence(ShoppingCart* cart) {
        this->cart = cart;
    }
    void save() override {
        std::cout << "Saving shopping cart to a file..." << std::endl;
    }
};

//class ShoppingCartStorage {
//private:
//    ShoppingCart* cart;
//
//public:
//    ShoppingCartStorage(ShoppingCart* cart) {
//        this->cart = cart;
//    }
//    void saveToSQLDB() {
//        std::cout << "Saving shopping cart to SQL database..." << std::endl;
//    }
//    void saveToMongoDB() {
//        std::cout << "Saving shopping cart to Mongo DB..." << std::endl;
//    }
//    void saveToFile() {
//        std::cout << "Saving shopping cart to a file..." << std::endl;
//    }
//};

//int main() {
//    ShoppingCart* cart = new ShoppingCart();
//    cart->addProduct(new Product("Laptop", 50000));
//    cart->addProduct(new Product("Mobile", 20000));
//
//    ShoppingCartPrinter* printer = new ShoppingCartPrinter(cart);
//    printer->printInvoice();
//
////    ShoppingCartStorage* db = new ShoppingCartStorage(cart);
////    db->saveToSQLDB();
//
//    Persistence* db = new SQLPersistence(cart);
//    Persistence* Mongo = new MongoPersistence(cart);
//    Persistence* File = new FilePersistence(cart);
//
//    db->save();
//    Mongo->save();
//    File->save();
//
//    std::cin.get();
//    return 0;
//}