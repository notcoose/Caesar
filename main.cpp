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

int main() {
    string command;

    cout << "Welcome to Ciphers!" << endl;
    cout << "-------------------" << endl;
    cout << endl;
    
    

    /*do {
        printMenu();
        cout << endl << "Enter a command (case does not matter): ";
        // Use getline for all user input to avoid needing to handle
        // input buffer issues relating to using both >> and getline
        getline(cin, command);
        cout << endl;
        if(command[0] == 'C' || command[0] == 'c'){
        }
        else if(command[0] == 'D' || command[0] == 'd'){
        }
        else if(command[0] == 'V' || command[0] == 'v'){
        }
        cout << endl;
    } while (!(command == "x" || command == "X")); */

    return 0;
}

