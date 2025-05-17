#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <algorithm>
#include <string>

using namespace std;

class BankDeposit {
private:
    string name;
    double amount;
    string currency;
    double rate;

public:
    BankDeposit() : name(""), amount(0.0), currency(""), rate(0.0) {}
    BankDeposit(const string& n, double a, const string& c, double r)
        : name(n), amount(a), currency(c), rate(r) {}

    BankDeposit(const BankDeposit& other) = default;

    BankDeposit& operator=(const BankDeposit& other) = default;

    BankDeposit(BankDeposit&& other) noexcept = default;

    BankDeposit& operator=(BankDeposit&& other) noexcept = default;

    const string& getName() const { return name; }
    double getAmount() const { return amount; }
    const string& getCurrency() const { return currency; }
    double getRate() const { return rate; }

    friend ostream& operator<<(ostream& os, const BankDeposit& deposit) {
        os << "Deposit: " << deposit.name 
           << ", Amount: " << deposit.amount 
           << " " << deposit.currency 
           << ", Rate: " << deposit.rate << "%";
        return os;
    }
};

vector<BankDeposit> readFile(const string& filename) {
    ifstream file(filename);
    vector<BankDeposit> deposits;
    string name, currency;
    double amount, rate;

    while (file >> name >> amount >> currency >> rate) {
        deposits.emplace_back(name, amount, currency, rate);
    }

    file.close();
    return deposits;
}

template<typename Container>
void writeToFile(ofstream& file, const Container& container, const string& title) {
    file << title << endl;
    for (const auto& deposit : container) {
        file << deposit << endl;
    }
    file << endl;
}

int main() {
    vector<BankDeposit> deposits = readFile("input.txt");

    ofstream outFile("output.txt");
    writeToFile(outFile, deposits, "Original Container (vector)");

    sort(deposits.begin(), deposits.end(), 
        [](const BankDeposit& a, const BankDeposit& b) {
            return a.getName() < b.getName();
        });

    writeToFile(outFile, deposits, "Sorted Container (vector)");

    deque<BankDeposit> depositDeque;
    copy(deposits.begin(), deposits.end(), back_inserter(depositDeque));

    writeToFile(outFile, depositDeque, "Copied Container (deque)");

    outFile.close();
    cout << "Results written to output.txt" << endl;

    return 0;
}
