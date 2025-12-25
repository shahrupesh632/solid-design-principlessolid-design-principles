//This code follow the Liskov Subsititution Principle without voilating any principle

#include<iostream>
#include<vector>

class DepositOnlyAccount {
public:
	virtual void deposit(double amt) = 0;
};

class WithdrawableAccount : public DepositOnlyAccount {
public:
	virtual void withdraw(double amt) = 0;
};


class SavingAccount : public WithdrawableAccount {
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

class CurrentAccount : public WithdrawableAccount {
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

class FixedTermAccount : public DepositOnlyAccount {
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
};

class BankClient {
private:
	std::vector<DepositOnlyAccount*> depositOnlyAccounts;
	std::vector<WithdrawableAccount*> withdrawableAccounts;

public:
	BankClient(std::vector<DepositOnlyAccount*> depositOnlyAccounts,
	std::vector<WithdrawableAccount*> withdrawableAccounts) {
		this->depositOnlyAccounts = depositOnlyAccounts;
		this->withdrawableAccounts = withdrawableAccounts;
	}
	void processTransactions() {
		for (auto acc : withdrawableAccounts) {
				acc->deposit(1000);
				acc->withdraw(500);
		}
		for (auto acc : depositOnlyAccounts) {
			acc->deposit(1000);
		}
	}
};

int main() {
	std::vector<WithdrawableAccount*> withdrawableAccounts;
	std::vector<DepositOnlyAccount*> depositOnlyAccounts;

	withdrawableAccounts.push_back(new SavingAccount(0));
	withdrawableAccounts.push_back(new CurrentAccount(0));
	depositOnlyAccounts.push_back(new FixedTermAccount(0));

	BankClient* client = new BankClient(depositOnlyAccounts, withdrawableAccounts);

	client->processTransactions();

	std::cin.get();
	return 0;
}