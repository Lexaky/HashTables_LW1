#include <iostream>
#include <string>

using namespace std;


struct info
    {
        string TextName = "";
        unsigned long long int barcode = 0;
    };

class Hash
{
//Описание одной записи
private:
    info data; //Информация о товаре
    int status = 0; //Номер статуса
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
    void setValues(Hash anotherHash)
    {
        data = anotherHash.getData();
        status = 1;
    }
};

class HashTable
{
    //Описание таблицы из записей
private:
    unsigned long long int currentSizeTable; //Текущий размер таблицы
    unsigned long long int filledTable; //Заполненные ячейки таблицы
    float filledPercentTable = filledTable/currentSizeTable; //Заполненные ячейки таблицы в процентах
    unsigned long long int hashFunctionMain(unsigned long long int key);
    unsigned long long int hashFunctionCollision(int lastAdress, int tryNumber);
    void resizeTable(int N);
    Hash *table;
public:
    HashTable (unsigned long long int N) {
        Hash *table = new Hash[N];
        currentSizeTable = N;
    }
     int addHash(Hash newHash);
     int deleteHash(Hash delHash);
     int searchHash(Hash findHash);
    void printHashTable();
    ~HashTable();
};

unsigned long long int HashTable::hashFunctionMain(unsigned long long int key)
{
    unsigned long long int sum = 0;
    for (key; key > 0; key /= 10)
    {
        sum += key % 10;
    }
    return (sum % currentSizeTable);
}

int HashTable::addHash(Hash newHash)
{
    table[0].setValues(newHash);
    cout << "HEER!" << endl;
    return 0;
}

void HashTable::printHashTable()
{
    for (unsigned long long int i = 0; i < currentSizeTable - 1; i++)
    {
        cout << table->getData().TextName << ": " << table->getData().barcode << endl;
    }
}
HashTable::~HashTable()
{
    free(table);
}
int main()
{
    setlocale(LC_ALL, "rus");
    Hash new_Hash("Ноутбук", 11111111111);
    HashTable HT(4);
    HT.addHash(new_Hash);
    HT.printHashTable();
    return 0;
}
