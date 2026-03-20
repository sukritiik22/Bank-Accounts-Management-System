#include "Chaining.h"

void Chaining::createAccount(std::string id, int count) {
    Account A;
    A.id = id;
    A.balance = count;
    int h = Chaining::hash(id);
    bankStorage2d = table(bankStorage2d);
    bankStorage2d[h].push_back(A);
    size++;
}

std::vector<int> Chaining::getTopK(int k) {
    std::vector<int> kBiggest;
    for (auto &i: bankStorage2d) {
        for (const auto &A: i) {
            if (kBiggest.size() < k) {
                kBiggest.push_back(A.balance);
            } else {
                int minIdx = 0;
                for (int j = 1; j < k; ++j) {
                    if (kBiggest[j] < kBiggest[minIdx]) {
                        minIdx = j;
                    }
                }
                if (A.balance > kBiggest[minIdx]) {
                    kBiggest[minIdx] = A.balance;
                }
            }
        }
    }
    for(int i=0;i<kBiggest.size();i++){
        for(int j=i+1;j<kBiggest.size();j++){
            if(kBiggest[i]<kBiggest[j]){
                int temp = kBiggest[i];
                kBiggest[i] = kBiggest[j];
                kBiggest[j] = temp;
            }
        }
    }
    return kBiggest;
}

int Chaining::getBalance(std::string id) {
    int h = Chaining::hash(id);
    for (const Account &A: bankStorage2d[h]) {
        if (A.id == id) {
            return A.balance;
        }
    }
    return -1;
}

void Chaining::addTransaction(std::string id, int count) {

    if (doesExist(id)) {
        int h = Chaining::hash(id);
        for (Account &A: bankStorage2d[h]) {
            if (A.id == id) {
                A.balance += count;
                return;
            }
        }
    } else {
        createAccount(id, count);
    }
}

bool Chaining::doesExist(std::string id) {
    int h = Chaining::hash(id);
    for (const Account &A: bankStorage2d[h]) {
        if (A.id == id) {
            return true;
        }
    }
    return false;
}

bool Chaining::deleteAccount(std::string id) {
    int h = Chaining::hash(id);
    int index = -1;
    for (int i = 0; i < bankStorage2d[h].size(); i++) {
        if (bankStorage2d[h][i].id == id) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        return false;
    }
    bankStorage2d[h].erase(bankStorage2d[h].begin() + index);
    size--;
    return true;
}

int Chaining::databaseSize() {
    return size;
}

int Chaining::hash(std::string id) {
    int hashval = 0;
    std::vector<int> N = {49117,150162,69121,18921,190153,91853,35351,176563,17553,62283,71651,146273,198183,45133,56151,10963,171963,123137,15619,101983,};
    int n = 7*id[(5*id.size())%N.size()]+11*id[(7*id.size())%N.size()]+13*id[(11*id.size())%N.size()]+17*id[(13*id.size())%N.size()];
    n=n%11;
    for (int i = 0; i < 11; i++) {
        hashval += (N[i]+11)*id[(N[(n+i)%N.size()]*13)%id.size()];
    }
    hashval = hashval%capacity;
    return hashval;
}

