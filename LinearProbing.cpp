#include "LinearProbing.h"

void LinearProbing::createAccount(std::string id, int count) {
    bankStorage1d = table(bankStorage1d);
    int r = LinearProbing::hash(id);
    int t = r;
    do {
        if (bankStorage1d[r].balance == -1) {
            bankStorage1d[r].id = id;
            bankStorage1d[r].balance = count;
            size ++;
            return;
        } else {
            r += 1;
            r = r % capacity;
        }
    } while (r != t);
    return;
}


std::vector<int> LinearProbing::getTopK(int k) {
    std::vector<int> kBiggest;
    for (const auto &A: bankStorage1d) {
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

int LinearProbing::getBalance(std::string id) {
    int r = LinearProbing::hash(id);
    int t = r;
    do {
        if (bankStorage1d[r].id == id) {
            return bankStorage1d[r].balance;
        } else {
            r += 1;
            r = r % capacity;
        }
    } while (r!=t && bankStorage1d[r].id != "NULL");
    return -1;
}


void LinearProbing::addTransaction(std::string id, int count) {
    int r = LinearProbing::hash(id);
    int t = r;
    do {
        if (bankStorage1d[r].id == id) {
            bankStorage1d[r].balance += count;
            return;
        } else {
            r += 1;
            r = r % capacity;
        }
    } while (r!=t && bankStorage1d[r].id != "NULL");
    if(bankStorage1d[r].id == "NULL"){
        bankStorage1d[r].id = id;
        bankStorage1d[r].balance = count;
        size++;
        return;
    }
    createAccount(id,count);
    return;
}

bool LinearProbing::doesExist(std::string id) {
    int r = LinearProbing::hash(id);
    int t = r;
    do {
        if (bankStorage1d[r].id == id) {
            return true;
        } else {
            r += 1;
            r = r % capacity;
        }
    } while (r!=t && bankStorage1d[r].id != "NULL");
    return false;
}

bool LinearProbing::deleteAccount(std::string id) {
    int r = LinearProbing::hash(id);
    int t = r;
    do {
        if (bankStorage1d[r].id == id) {
            bankStorage1d[r].id = "DELETED";
            bankStorage1d[r].balance = -1;
            size--;
            return true;
        } else {
            r += 1;
            r = r % capacity;
        }
    } while (r!=t && bankStorage1d[r].id != "NULL");
    return false;
}
int LinearProbing::databaseSize() {
    return(size);
}

int LinearProbing::hash(std::string id) {
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

