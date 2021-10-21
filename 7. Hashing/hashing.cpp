#include <iostream>
#include <iomanip>
#include <string>
#include "linked_list.h"
using namespace std;

class PairSlI {
public:
    LinkedList<string> key;
    LinkedList<int> value;
};

class TripletIII {
public:
    int index, value, skipped;
    TripletIII(int index, int value, int skipped) {
        this->index = index;
        this->value = value;
        this->skipped = skipped;
    }
};

class HashTableChain {
     PairSlI *table;
     int prime;
     int size;
public:
    HashTableChain(int size = 1000, int prime = 2374717) {
        table = new PairSlI[size];
        this->prime = prime;
        this->size = size;
    }
private:
    long long int basicHash(string str) {
        long long int value = 0;
        long long int adder;
        long long int multiplier = 1;
        for(int i = 0; i < str.length(); i++) {
            if(str[i] >= 'a') {
                adder = str[i]- 'a' + 26;
            }
            else {
                adder = str[i] - 'A';
            }
            if(i) {
                multiplier *= 52;
                multiplier %= prime;
            }
            value += (int)adder * multiplier;
            value %= prime;
        }
        return value;
    }
public:
     int insert(string key, int value) {
        int index = basicHash(key) % size;
        table[index].key.pushBack(key);
        table[index].value.pushBack(value);
        return table[index].key.getSize()-1;
    }
    TripletIII search(string key) {
        int index = basicHash(key) % size;
        int hit = 1;
        Linker<string> *it;
        Linker<int> *it2;
        for(it = table[index].key.getHead()->getNext(), it2 = table[index].value.getHead()->getNext();
            it != table[index].key.getTail() && it->getValue() != key; it = it->getNext(), it2 = it2->getNext(), hit++) {}
        if(hit > table[index].key.getSize()) {
            return TripletIII(-1,-1,table[index].key.getSize());
        }
        else {
            return TripletIII(index, it2->getValue(), hit);
        }
    }
    TripletIII deletes(string key) {
        int index = basicHash(key) % size;
        int hit = 1;
        Linker<string> *it;
        Linker<int> *it2;
        for(it = table[index].key.getHead()->getNext(), it2 = table[index].value.getHead()->getNext();
            it != table[index].key.getTail() && it->getValue() != key; it = it->getNext(), it2 = it2->getNext(), hit++) {}
        if(hit > table[index].key.getSize()) {
            return TripletIII(-1,-1,table[index].key.getSize());
        }
        else {
            int value = it2->getValue();
            table[index].key.deletes(it);
            table[index].value.deletes(it2);
            return TripletIII(index, value, hit);
        }
    }
};

class PairSI
{
public:
    string key;
    int value;
};

const int auxHashPrimes[7] = {7184011, 4341299, 9232753, 6469817, 9192493, 3333373, 8294707};

class HashTableBasic {
protected:
    PairSI *table;
    bool *flag;
    int prime, auxPrime;
    int size;
protected:
    HashTableBasic(int size = 1000, int prime = 2374717, int prime2 = 3479249) {
        table = new PairSI[size];
        flag = new bool[size];
        for(int i = 0; i < size; i++) {
            flag[i] = false;
        }
        this->size = size;
        this->prime = prime;
        auxPrime = prime2;
    }
    long long int basicHash(string str) {
        long long int value = 0;
        long long int adder;
        long long int multiplier = 1;
        for(int i = 0; i < str.length(); i++) {
            if(str[i] >= 'a') {
                adder = str[i]- 'a' + 26;
            }
            else {
                adder = str[i] - 'A';
            }
            if(i) {
                multiplier *= 52;
                multiplier %= prime;
            }
            value += (int)adder * multiplier;
            value %= prime;
        }
        return value;
    }
    long long int auxHash(string str) {
        long long int value = 0;
        long long int adder;
        for(int i = 0; i < str.length(); i++) {
            if(str[i] >= 'a') {
                adder = str[i]- 'a' + 26;
            }
            else {
                adder = str[i] - 'A';
            }
            value += (int)adder * auxHashPrimes[i];
            value %= auxPrime;
        }
        return value;
    }
    virtual TripletIII locate(string key, long long int hash1, long long int hash2) {
        ///Must be overloaded
        cout << "locate not overloaded." << endl;
        return TripletIII(-1,-1,0);
    }
    int insertBasic(string key, int value, long long int hash1, long long int hash2) {
        TripletIII seek = locate(key, hash1, hash2);
        if(seek.index == -1 || seek.value != -1) {}
        else {
            flag[seek.index] = true;
            table[seek.index].key = key;
            table[seek.index].value = value;
        }
        /*if(seek.skipped == size) {  ///EXTRA
            cout << "Cannot insert" << endl;
        }*/
        return seek.skipped;
    }
    TripletIII searchBasic(string key, int hash1, int hash2) {
        TripletIII seek = locate(key, hash1, hash2);
        if(seek.skipped < size) {
            seek.skipped++;
        }
        /*else {  ///EXTRA
            cout << "Not found" << endl;
        }*/
        if(seek.value == -1) {
            return TripletIII(-1,-1,seek.skipped);
        }
        else {
            return seek;
        }
    }
    TripletIII deletesBasic(string key, int hash1, int hash2) {
        TripletIII seek = searchBasic(key, hash1, hash2);
        if(seek.value != -1) {
            flag[seek.index] = false;
        }
        return seek;
    }
public:
    int insert(string key, int value) {
        return insertBasic(key,value,basicHash(key),auxHash(key));
    }
    TripletIII search(string key) {
        return searchBasic(key,basicHash(key),auxHash(key));
    }
    TripletIII deletes(string key) {
        return deletesBasic(key,basicHash(key),auxHash(key));
    }
};

class HashTableDouble : public HashTableBasic {
public:
    HashTableDouble(int size = 1000, int prime = 2374717, int prime2 = 3479249) : HashTableBasic(size, prime, prime2) {}
private:
    TripletIII locate(string key, long long int hash1, long long int hash2) {
        hash1 %= size;
        hash2 %= size;
        int index = hash1, skipped = 0;
        for(int i = 0; i < size; i++) {
            index %= size;
            if(!flag[index]) {
                return TripletIII(index,-1,skipped);
            }
            else if(table[index].key == key) {
                return TripletIII(index, table[index].value, skipped);
            }
            index += hash2;
            skipped++;
        }
        /*if(skipped != size) {  ///EXTRA
            cout << "Fatal Error in HashTableDouble::locate" << endl;
        }*/
        return TripletIII(-1,-1,skipped);
    }
};

class HashTableCustom : public HashTableBasic {
    int c1,c2;
public:
    HashTableCustom(int size = 1000, int prime = 2374717, int prime2 = 3479249, int const1 = 5618287, int const2 = 2312137) : HashTableBasic(size, prime, prime2) {
        c1 = const1 % size;
        c2 = const2 % size;
    }
private:
    TripletIII locate(string key, long long int hash1, long long int hash2) {
        hash1 %= size;
        hash2 %= size;
        long long int added = hash1, index, skipped = 0;
        for(int i = 0; i < size; i++) {
            index = (added + c2*i*i) % size;
            if(!flag[index]) {
                return TripletIII(index,-1,skipped);
            }
            else if(table[index].key == key) {
                return TripletIII(index, table[index].value, skipped);
            }
            added += c1*hash2;
            added %= size;
            skipped++;
        }
        /*if(skipped != size) {  ///EXTRA
            cout << "Fatal Error in HashTableCustom::locate" << endl;
        }*/
        return TripletIII(-1,-1,skipped);
    }
};

#include <cstdlib>
#include <ctime>
string allLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

string randomString() {
    string str = "";
    for(int i = 0; i < 7; i++) {
        str += allLetters[rand()%51];
    }
    return str;
}

int main() {
    int size, inputs;
    cout << "Enter table size: ";
    cin >> size;
    cout << "Enter number of inputs: ";
    cin >> inputs;
    /*if(inputs * 10 > 7 * size) {
        cout << "Too many inputs." << endl;
        exit(0);
    }*/

    HashTableChain h1(size);
    HashTableDouble h2(size);
    HashTableCustom h3(size);
    int p1 = 7999241, p2 = 4917631, c1 = 4321997, c2 = 5555567;
    HashTableChain h4(size, p1);
    HashTableDouble h5(size, p1, p2);
    HashTableCustom h6(size, p1, p2, c1, c2);
    string given[inputs];
    srand (time(NULL));
    int col1 = 0, col2 = 0, col3 = 0, col4 = 0, col5 = 0, col6 = 0, hit1 = 0, hit2 = 0, hit3 = 0, hit4 = 0, hit5 = 0, hit6 = 0;
    for(int i = 1; i <= inputs; i++) {
        string now = randomString();
        given[i-1] = now;
        if(h1.search(now).index != -1) {
            i--;
            continue;
        }
        col1 += h1.insert(now,i);
        col2 += h2.insert(now,i);
        col3 += h3.insert(now,i);
        col4 += h4.insert(now,i);
        col5 += h5.insert(now,i);
        col6 += h6.insert(now,i);
    }
    int lookup = inputs/10;
    for(int i = 1; i <= lookup; i++) {
        string now = given[rand()%inputs];
        hit1 += h1.search(now).skipped;
        hit2 += h2.search(now).skipped;
        hit3 += h3.search(now).skipped;
        hit4 += h4.search(now).skipped;
        hit5 += h5.search(now).skipped;
        hit6 += h6.search(now).skipped;
    }

    ///Report
    cout << "\t\t\tHash 1\t\t\tHash 2" << endl;
    cout << fixed << setprecision(3);
    cout << "Chaining method:\t" << (double)col1 << "  " << (double)hit1/lookup << "\t\t" << (double)col4 << "  "<< (double)hit4/lookup << " " << endl;
    cout << "Double hashing:\t\t" << (double)col2 << "  " << (double)hit2/lookup << "\t\t" << (double)col5 << "  "<< (double)hit5/lookup << " " << endl;
    cout << "Custom probing:\t\t" << (double)col3 << "  " << (double)hit3/lookup << "\t\t" << (double)col6 << "  "<< (double)hit6/lookup << " " << endl;

}
