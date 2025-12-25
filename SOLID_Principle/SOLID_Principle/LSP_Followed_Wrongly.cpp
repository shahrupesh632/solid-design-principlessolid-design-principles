//This code follow the Liskov Subsititution Principle but wrongly. It voilated the OSP

#include<iostream>
#include<vector>

class Account {
public:
	virtual void deposit(double amt) = 0;
	virtual void withdraw(double amt) = 0;
};

class SavingAccount : public Account {
private:
	double balance;
public:
	SavingAccount(double balance) {
		this->balance = balance;
	}

	void deposit(double amt) override {
		balance += amt;
		std::cout << "Deposited: " << amt << " in saving account. New Balance: " << balance << std::endl;
	}

	void withdraw(double amt) override {
		if (balance >= amt) {
			balance -= amt;
			std::cout << "Withdrawn: " << amt << " from saving account. New Balance: " << balance << std::endl;
		}
		else {
			std::cout << "Insufficient funds in saving account!" << std::endl;
		}
	}
};

class CurrentAccount : public Account {
private:
	double balance;

public:
	CurrentAccount(double balance) {
		this->balance = balance;
	}

	void deposit(double amt) override {
		balance += amt;
		std::cout << "Deposited: " << amt << " in Current Account. New Balance: " << balance << std::endl;
	}

	void withdraw(double amt) override {
		if (balance >= amt) {
			balance -= amt;
			std::cout << "Withdrawn: " << amt << " from Current Account. New Balance: " << balance << std::endl;
		}
		else {
			std::cout << "Insufficient funds in Current Account!" << std::endl;
		}
	}
};

class FixedTermAccount : public Account {
private:
	double balance;

public:
	FixedTermAccount(double balance) {
		this->balance = balance;
	}

	void deposit(double amt) override {
		balance += amt;
		std::cout << "Deposited: " << amt << " in Fixed Term Account. New Balance: " << balance << std::endl;
	}

	void withdraw(double amt) override {
		throw std::logic_error("Withdrawals are not allowed from Fixed Term Account!");
	}
};

class BankClient {
private:
	std::vector<Account*> accounts;

public:
	BankClient(std::vector<Account*> accounts) {
		this->accounts = accounts;
	}
	void processTransactions() {
		for (auto acc : accounts) {
			if (typeid(*acc) == typeid(FixedTermAccount)) {
				acc->deposit(1000);
				std::cout << "Skiping withdraw for Fixed Term Account" << std::endl;
			}
			else
			{
				acc->deposit(1000);
				try
				{
					acc->withdraw(500);
				}
				catch (std::logic_error ex) {
					std::cout << "Exception: " << ex.what() << std::endl;
				}
			}
			
		}
	}
};

//int main() {
//	std::vector<Account*> accounts;
//
//	accounts.push_back(new SavingAccount(0));
//	accounts.push_back(new CurrentAccount(0));
//	accounts.push_back(new FixedTermAccount(0));
//
//	BankClient* client = new BankClient(accounts);
//
//	client->processTransactions();
//
//	std::cin.get();
//	return 0;
//}