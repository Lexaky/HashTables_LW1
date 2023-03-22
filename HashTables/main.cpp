#include <iostream>
#include <string>

#define accuracy 0.5

using namespace std;


struct info
    {
        string TextName = "";
        unsigned long long int barcode = 0;
    };

class Hash
{
//description one record of item
private:
    info data; // Item info
    int status = 0; //Current status
public:
    Hash(string itemName, unsigned long long int barCode)
    {
        data.TextName = itemName;
        data.barcode = barCode;
    }
    Hash()
    {
        data.TextName = "";
        data.barcode = 0;
    }
    info getData()
    {
        return data;
    }
    int getStatus()
    {
        return status;
    }
    void setValues(Hash *anotherHash)
    {
        data = anotherHash->getData();
        status = 1;
    }
    void setStatus(int newStatus)
    {
        status = newStatus;
    }
};

class HashTable
{
    //Description table of hashes
private:
    unsigned long long int currentSizeTable;
    unsigned long long int filledTable;
    float filledPercentTable;
    unsigned long long int hashFunctionMain(unsigned long long int key);
    unsigned long long int hashFunctionCollision(int lastAdress, int tryNumber);
    void resizeTable(int N);
public:
    Hash *table;
    HashTable(unsigned long long int N)
    :currentSizeTable(N), filledTable(0), filledPercentTable(0.0)
    {
        table = new Hash[N];
    }
    HashTable ()
    {
        table = new Hash[10];
        currentSizeTable = 10;
        filledTable = 0;
        filledPercentTable = 0.0;
    }
    void addHash(Hash *newHash);
    void expandTable();
    int deleteHash(Hash delHash);
    int searchHash(Hash findHash);
    void printHashTable();
    unsigned long long int getTableSize();
    void clearTable(Hash *table, unsigned long long int tableSize);

    ~HashTable()
    {
        delete[] table;
    }
};

unsigned long long int HashTable::getTableSize()
{
    return currentSizeTable;
}

void HashTable::clearTable(Hash *table, unsigned long long int tableSize)
{
    for(unsigned long long int i = 0; i < tableSize; i++)
    {
        table[i].setStatus(0);
    }
}

void HashTable::expandTable()
{ //Неправильно работает в случае коллизий
    Hash *table_save = new Hash[currentSizeTable];
    for(unsigned long long int i = 0; i < currentSizeTable; i++)
    {
        table_save[i] = table[i];
    }
    table = new Hash[currentSizeTable*2];
    clearTable(table, currentSizeTable);
    int attempt;
    unsigned long long int key_;
    currentSizeTable *= 2;
    for (unsigned long long int i = 0; i < currentSizeTable/2; i++)
    { //Проблемка тут
        if (table_save[i].getStatus() != 0)
        {
            key_ = hashFunctionMain(table_save[i].getData().barcode);
            if (table[key_].getStatus() == 0)
            {
                table[key_].setValues(&table_save[i]);
            } else {
                //Коллизия
                attempt = 0;
                while (table[key_].getStatus() != 0)
                {
                    key_ = hashFunctionCollision(key_, attempt);
                    attempt++;
                }
                table[key_].setValues(&table_save[i]);
            }
        }
    }
    delete[] table_save;
}

unsigned long long int HashTable::hashFunctionMain(unsigned long long int key)
{ // Верная функция
    unsigned long long int sum = 0;
    for (key; key > 0; key /= 10)
    {
        sum += key % 10;
    }
    return (sum % currentSizeTable);
}

unsigned long long int HashTable::hashFunctionCollision(int lastAdress, int tryNumber)
{ //Скатал у Вовы, хз правильно ли работает, пока непонятно
    return (lastAdress + tryNumber * tryNumber) % currentSizeTable;
}


void HashTable::addHash(Hash *newHash)
{ //Не работает
    unsigned long long int key_ = hashFunctionMain(newHash->getData().barcode);
    if (filledPercentTable > accuracy)
        {
            expandTable();
        }
    if (table[key_].getStatus() == 0)
    {
        table[key_].setValues(newHash); //status -->> 1, data -->> filling
    } else {
    //Full cell. Percentage test for fullfill of hashTable
        int attempt = 0;
        int startKey = key_;
        bool startIn = false;
        while (table[key_].getStatus() != 0)
        {
            key_ = hashFunctionCollision(key_, attempt);
            attempt++;
            if (startIn == false) startIn = true;
        }
        table[key_].setValues(newHash);
    }
    filledTable++;
    filledPercentTable = (float)filledTable/(float)currentSizeTable;
}

void HashTable::printHashTable()
{
    for (unsigned long long int i = 0; i < currentSizeTable; i++)
    {
        cout.width(5);
        cout << i << "|";
        cout.width(20);
        cout << table[i].getData().TextName << "|";
        cout.width(11);
        cout << table[i].getData().barcode << endl;
        cout.width(5);
    }
}

int main()
{
    cout.fill(' ');
    setlocale(LC_ALL, "rus");
    Hash *anotherHash = new Hash("Laptop", 11111111111); // Создался нормально
    HashTable HT(4);

    Hash *anotherHash2 = new Hash("PC", 12222222222);
    HT.addHash(anotherHash);
    HT.addHash(anotherHash2);
    Hash *an = new Hash("buububu", 0);
    Hash *a = new Hash("ufufufuf", 5);
    HT.addHash(a);
    HT.addHash(an);
    Hash *aa = new Hash("qwueqwe", 6);
    HT.addHash(aa);
    Hash *aaa = new Hash ("Abidabasdfadsfaida", 0);
    HT.addHash(aaa);
    Hash *b = new Hash("aba", 0);
    Hash *bb = new Hash("abba", 0);
    Hash *bbb = new Hash("abbba", 0);
    HT.addHash(b);
    HT.addHash(bb);
    HT.addHash(bbb);
    HT.printHashTable();
    return 0;
}
