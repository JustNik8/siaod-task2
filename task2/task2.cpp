#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <map> 
#include <string>
#include <algorithm>

using namespace std;

ifstream inFile;
ofstream outFile;
ifstream inBinaryFile;
ofstream sortedNumsFile;

string inFilePath = "data.txt";
string outFilePath = "output.txt";
string inBinaryFilePath = "binaryData.txt";
string sortedNumsFilePath = "sortedNums.txt";

vector<int> nums;

void readRecordingsFromFile();
void filterEvenNumbersToFile();
void readDataFromBinaryFile();
int getIndexOfKey(int key);
string getDataByKey(int key);
map<int, string>* getMapFromBinaryFile();
void sortNumsFromFile();

int main()
{
    setlocale(LC_ALL, "rus");

    readRecordingsFromFile();
    
    for (auto num : nums) {
        cout << num << endl;
    }

    filterEvenNumbersToFile();

    cout << "\n--------------------------\n";
    readDataFromBinaryFile();

    cout << endl;
    cout << getIndexOfKey(1) << endl;

    cout << getDataByKey(2) << endl;

    map<int, string>* myMap = getMapFromBinaryFile();

    cout << "\n------------------\n";
    for (map<int, string>::iterator it = myMap->begin(); it != myMap->end(); it++) {
        cout << it->first << ": " << it->second << endl;
    }

    sortNumsFromFile();
}

void readRecordingsFromFile() {
    inFile.open(inFilePath);
    if (!inFile.is_open()) {
        cout << "Ошибка, файл не удалось открыть :(";
        return;
    }

    while (!inFile.eof())
    {
        int num;
        inFile >> num;
        nums.push_back(num);
    }
    inFile.close();
}

void filterEvenNumbersToFile() {
    outFile.open(outFilePath);

    if (!outFile.is_open()) {
        cout << "Ошибка, файл не удалось открыть :(";
        return;
    }
    for (int num : nums) {
        if (num % 2 == 0) {
            outFile << num << " ";
        }
    }
    outFile.close();
}

void readDataFromBinaryFile() {
    inBinaryFile.open(inBinaryFilePath, ios::binary);
    if (!inBinaryFile.is_open()) {
        cout << "Файл не удалось открыть";
        return;
    }

    vector<unsigned char> buffer(istreambuf_iterator<char>(inBinaryFile), {});
    map<int, string> res;

    string recordingBuf = "";

    int key;
    string value;

    for (auto ch : buffer) {

        if (ch != 32 && ch != 13 && ch != 10) {
            recordingBuf += ch;
        }
        else if (ch == 32) {
            key = stoi(recordingBuf);
            recordingBuf = "";

        }
        else if (ch == 10) {
            value = recordingBuf;
            recordingBuf = "";
            res.insert({ key, value });
        }

    }


    for (map<int, string>::iterator it = res.begin(); it != res.end(); it++) {
        cout << it->first << ": " << it->second << endl;
    }

    inBinaryFile.close();
}

int getIndexOfKey(int key) {

    inBinaryFile.open(inBinaryFilePath, ios::binary);
    if (!inBinaryFile.is_open()) {
        cout << "Файл не удалось открыть";
        return -1;
    }

    vector<unsigned char> buffer(istreambuf_iterator<char>(inBinaryFile), {});

    string recordingBuf = "";

    int foundKey;
    int keysCnt = 0;

    for (auto ch : buffer) {

        if (ch != 32 && ch != 13 && ch != 10) {
            recordingBuf += ch;
        }
        else if (ch == 32) {
            foundKey = stoi(recordingBuf);
            if (key == foundKey) {
                inBinaryFile.close();
                return keysCnt;
            }
            else {
                keysCnt++;
            }
            recordingBuf = "";

        }
        else if (ch == 10) {
            recordingBuf = "";
        }
    }

    inBinaryFile.close();
    return -1;

}

string getDataByKey(int key) {
    inBinaryFile.open(inBinaryFilePath, ios::binary);
    if (!inBinaryFile.is_open()) {
        cout << "Файл не удалось открыть";
        return "";
    }

    vector<unsigned char> buffer(istreambuf_iterator<char>(inBinaryFile), {});

    string recordingBuf = "";
    int foundKey;
    bool keyWasFound = false;
    int i = 0;
    for (; i < buffer.size(); i++) {
        if (buffer[i] != 32 && buffer[i] != 13 && buffer[i] != 10) {
            recordingBuf += buffer[i];
        }
        else if (buffer[i] == 32) {
            foundKey = stoi(recordingBuf);
            if (key == foundKey) {
                i++;
                keyWasFound = true;
                break;
            }
            recordingBuf = "";
        }
        else if (buffer[i] == 10) {
            recordingBuf = "";
        }
    }

    recordingBuf = "";
    if (keyWasFound) {
        while (buffer[i] != 13) {
            recordingBuf += buffer[i];
            i++;
        }
    }

    inBinaryFile.close();
    return recordingBuf;
}

map<int, string>* getMapFromBinaryFile() {

    map<int, string>* res = new map<int, string>();

    inBinaryFile.open(inBinaryFilePath, ios::binary);
    if (!inBinaryFile.is_open()) {
        cout << "Не удалось открыть файл!";
        return res;
    }

    vector<unsigned char> buffer(istreambuf_iterator<char>(inBinaryFile), {});

    string recordingBuf = "";
    int key;
    string value;

    for (auto ch : buffer) {

        if (ch != 32 && ch != 13 && ch != 10) {
            recordingBuf += ch;
        }
        else if (ch == 32) {
            key = stoi(recordingBuf);
            recordingBuf = "";

        }
        else if (ch == 10) {
            value = recordingBuf;
            recordingBuf = "";
            res->insert({ key, value });
        }

    }

    inBinaryFile.close();
    return res;
}

void sortNumsFromFile() {

    sort(nums.begin(), nums.end());

    sortedNumsFile.open(sortedNumsFilePath);
    if (!sortedNumsFile.is_open()) {
        cout << "Не удалось открыть файл!";
        return;
    }

    for (int num : nums) {
        sortedNumsFile << num << " ";
    }

    outFile.close();

}
