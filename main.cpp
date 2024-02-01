#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void printMenu() {
    cout << "Ciphers Menu" << endl;
    cout << "------------" << endl;
    // Caesar Ciphers
    cout << "C - Encrypt with Caesar Cipher" << endl;
    cout << "D - Decrypt Caesar Cipher" << endl;
    // Vigenere
    cout << "V - Encrypt with Vigenère" << endl;
    // Utility
    cout << "X - Exit Program" << endl;
}

int findIndexInAlphabet(char c) { //DONE
    int index = ALPHABET.find(c);

    if(index != string::npos)
        return index;
    else
        return -1;
}

char rot(char c, int amount) { //DONE
    int charIndex = findIndexInAlphabet(c);

    if(charIndex != -1)
        c = ALPHABET.at((findIndexInAlphabet(c) + amount) % 26);

    return c;
}

string rot(string line, int amount) { //DONE
    string temp = "";

    for(char i: line)
        temp += rot(toupper(i), amount);

    return temp;
}

string removeNonAlpha(string line){
    string onlyAlpha = "";

    for(char i: line){
        if(isalpha(i))
            onlyAlpha += toupper(i);
    }

    return onlyAlpha;
}

string allUpper(string line){
    string uppercase = "";

    for(char i: line)
        uppercase += toupper(i);

    return uppercase;
}

void vigenereEncrypt(string line, string key){
    string encrypted = "";
    int num = 0;

    for(int i = 0; i < line.length(); i++){ //plaintext position in key
        if(isalpha(line.at(i))){
            char keyChar = key.at((i - num) % key.length());
            encrypted += rot(line.at(i), findIndexInAlphabet(keyChar));
        }
        else{
            encrypted += line.at(i);
            num++;
        }
    }

    cout << encrypted << endl;
} 

int main() {
    string command, text, shift, key;

    cout << "Welcome to Ciphers!" << endl;
    cout << "-------------------" << endl;
    cout << endl;
    
    do {
        printMenu();
        cout << endl << "Enter a command (case does not matter): ";
        getline(cin, command);
        cout << endl;

        if(command[0] == 'C' || command[0] == 'c'){ //DONE
            cout << "Enter text to encrypt:" << endl;
            getline(cin, text);
            cout << "Enter the number of characters to rotate by:" << endl;
            getline(cin, shift);

            cout << rot(text, stoi(shift));
        }
        else if(command[0] == 'D' || command[0] == 'd'){

        }
        else if(command[0] == 'V' || command[0] == 'v'){ //DONE
            cout << "Enter text to encrypt:" << endl;
            getline(cin, text);
            cout << "Enter the Vigenère key:" << endl;
            getline(cin, key);  

            vigenereEncrypt(allUpper(text), removeNonAlpha(key));
        }
        cout << endl;
    } while (!(command == "x" || command == "X")); 

    return 0;
}

