//Single Resposibility Principle
#include<iostream>
#include<vector>
#include<string>

class Product{
public:

    double price;
    std::string name;

    Product(std::string name, double price){
        this->price = price;
        this->name = name;
    }
};

class ShoppingCart{
    private:
    std::vector<Product*> products;

    public:
    void addProduct(Product* p){
        products.push_back(p);
    }

    const std::vector<Product*> getProducts(){
        return products;
    }

    double calculateTotal(){
        double total = 0;
        for(auto p : products){
            total += p->price;
        }
        return total;
    }

    void printInvoice(){
        std::cout<<"Shopping cart invoice:\n";
        for(auto p: products){
            std::cout << p->name<<" - RS "<<p->price<<std::endl;
        }
        std::cout<<"Total: RS "<<calculateTotal() << std::endl;
    }

    void saveToDatabase(){
        std::cout<<"Saving shopping cart to database..."<< std::endl;
    }
};

//int main(){
//    ShoppingCart* cart = new ShoppingCart();
//    cart->addProduct(new Product("Laptop", 50000));
//    cart->addProduct(new Product("Mobile", 20000));
//
//    cart->printInvoice();
//    cart->saveToDatabase();
//    std::cin.get();
//    return 0;
//}