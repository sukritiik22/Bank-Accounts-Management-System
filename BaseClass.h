#ifndef BASECLASS_H
#define BASECLASS_H
#include <string>
#include <vector>
#include<Algorithm>

struct Account {
    std::string id;
    int balance;
};

class BaseClass {
public:
    virtual void createAccount(std::string id, int count){
        Account A;
        A.id = id;
        A.balance = count;
        bankStorage1d.push_back(A);
    };
    virtual std::vector<int> getTopK(int k){
        std::vector<int> v;
        for (Account& x:bankStorage1d){
            v.push_back(x.balance);
        }
        sort(v.begin(),v.end());
        reverse(v.begin(),v.end());
        std::vector<int> r;
        if (bankStorage1d.size()<k){
            return(v);
        }
        else{
            for(int i=0;i<k;i++){
                r.push_back(v[i]);
            }
            return(r);
        }
    };

    virtual int getBalance(std::string id){
        for(Account& x:bankStorage1d){
            if (x.id == id){
                return x.balance;
            }
            return -1;
        }
    };

    virtual void addTransaction(std::string id, int count){
        for(Account& x:bankStorage1d){
            if (x.id == id){
                x.balance += count;
                return;
            }
            else{
                createAccount(id,count);
                return;
            }
        }
    };
    virtual bool doesExist(std::string id){
        for(Account& x:bankStorage1d) {
            if (x.id == id) {
                return true;
            }
        }
        return false;
    };

    virtual bool deleteAccount(std::string id){
        if (doesExist(id)==true){
            for(int i=0;i<databaseSize();i++){
                if (bankStorage1d[i].id == id){
                    bankStorage1d.erase(bankStorage1d.begin()+i);
                    return(true);
                }
            }
        }
        else
            return(false);
    };
    virtual int databaseSize(){
        return(bankStorage1d.size());
    };

    virtual int hash(std::string id) = 0;

    std::vector<Account> bankStorage1d;
    std::vector<std::vector<Account>> bankStorage2d;
    
};

#endif // BASECLASS_H
