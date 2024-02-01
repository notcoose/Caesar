#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


/*Outputs menu with letters for each functionality*/
void printMenu() {
    cout << "Ciphers Menu" << endl;
    cout << "------------" << endl;
    cout << "C - Encrypt with Caesar Cipher" << endl;
    cout << "D - Decrypt Caesar Cipher" << endl;
    cout << "V - Encrypt with Vigenère" << endl;
    cout << "X - Exit Program" << endl;
}

/*Returns the index of a letter in the alphabet*/
int findIndexInAlphabet(char c) { 
    int index = ALPHABET.find(c);

    if(index != string::npos)
        return index;
    
    return -1; //Defaults to -1 if there is no valid index
}

/*Returns the letter result of a letter being rotated by a given amount*/
char rot(char c, int amount) {
    int charIndex = findIndexInAlphabet(c);

    if(charIndex != -1)
        c = ALPHABET.at((findIndexInAlphabet(c) + amount) % 26);

    return c; //Returns the given char if it is not in alphabet
}

/*Returns the result of capitalizing and rotating every char by the given amount*/
string rot(string line, int amount) { 
    string temp = "";

    for(char i: line)
        temp += rot(toupper(i), amount);

    return temp;
}

/*Returns the given string with only alphabetic characters*/
string removeNonAlpha(string line){
    string onlyAlpha = "";

    for(char i: line){
        if(isalpha(i))
            onlyAlpha += toupper(i);
    }

    return onlyAlpha;
}

/*Returns the given string with all letters capitalied*/
string allUpper(string line){
    string uppercase = "";

    for(char i: line)
        uppercase += toupper(i);

    return uppercase;
}

/*Returns the boolean value of whether a string is in the dictionary*/
bool inDict(vector<string>& dict, string word){
    for(string i: dict){
        if(word == i){
            return true;
        }
    }

    return false;
}

/*Preforms the Vingenere encryption and outputs the result*/
void vigenereEncrypt(string line, string key){
    string encrypted = "";
    int num = 0;

    for(int i = 0; i < line.length(); i++){ 
        /*If char in line is alphabetical, finds position of char in line on key, 
        and uses char result of rotating original char by the index of key char in alphabet*/
        if(isalpha(line.at(i))){
            char keyChar = key.at((i - num) % key.length());
            encrypted += rot(line.at(i), findIndexInAlphabet(keyChar));
        }
        else{
            encrypted += line.at(i); //Doesn't change non-alphabetical chars
            num++;
        }
    }

    cout << encrypted << endl;
} 

int main() {
    string command, text, shift, key, word;
    vector<string> dict;

    /*Opens file, puts every word into dictionary vector, then closes file*/
    ifstream file;
    file.open("dictionary.txt");

    if(!file.is_open()) //Returns 1 if file didn't open
        return 1;

    while(!file.eof()){
        getline(file, text);
        dict.push_back(text);
    }

    file.close();

    
    cout << "Welcome to Ciphers!" << endl;
    cout << "-------------------" << endl;
    cout << endl;
    
    do {
        printMenu();
        cout << endl << "Enter a command (case does not matter): ";
        getline(cin, command);
        cout << endl;

        /*If Caesar encrypt is desired, outputs the text rotated by desired amount*/
        if(command[0] == 'C' || command[0] == 'c'){ 
            cout << "Enter the text to encrypt:" << endl;
            getline(cin, text);
            cout << "Enter the number of characters to rotate by:" << endl;
            getline(cin, shift);

            cout << rot(text, stoi(shift));
        }
        /*If Caesar decyrpt is desired, outputs "best match" decryptions, checking for valid word matches in dictionary to determine match*/
        else if(command[0] == 'D' || command[0] == 'd'){
            vector<string> words;
            int start, end = 0;

            cout << "Enter the text to Caesar-cipher decrypt:";
            getline(cin, text);

            /*Seperates input text into vector of strings delimited by spaces*/
            start = text.find_first_not_of(' ', end); //Start of substring, given by finding index of first char that is not a space starting from end
            while(start != string::npos){
                end = text.find(' ', start); //End of substring, given by finding index of next space after start
                words.push_back(text.substr(start, (end - start))); //Adds substring to vector of words from user input
                start = text.find_first_not_of(' ', end);
            }

            /*Removes any non-alphabetic characters and capitalizes*/
            for(string i: words){ 
                i = removeNonAlpha(i);
            }

            /*Performs the following actions for every possible shift*/
            for(int j = 0; j <= 25; j++){ 
                int count = 0;


                /*Shifts every word in text by one more*/
                for(string &i: words){ 
                    i = rot(i, 1);
                }

                /*Counts how many shifted words are in the dictionary*/
                for(string i: words){ 
                    if(inDict(dict, i))
                        count++;
                }

                /*If more than half of the words are in the dictionary, outputs entire vector decrypted*/
                if(count > (words.size()/2)){ 
                    for(int i = 0; i < (words.size() - 1); i++){
                        cout << words.at(i) << " ";
                    }
                    cout << words.at(words.size() - 1) << endl;
                }

            }
        }
        /*If Vingenere encryption is desired, outputs the text encrypted with user given key*/
        else if(command[0] == 'V' || command[0] == 'v'){ 
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

