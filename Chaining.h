#ifndef CHAINING_H
#define CHAINING_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

class Chaining : public BaseClass {
public:
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;

private:
    int size = 0;
    int capacity = 178013;
    std::vector<std::vector<Account>> table(std::vector<std::vector<Account>> v){
        if(v.size() != 0)
            return v;
        int t = capacity;
        std::vector<Account> n;
        while(t>0){
            v.push_back(n);
            t--;
        }
        return v;
    }

    // Other data members and functions specific to Chaining
};

#endif // CHAINING_H