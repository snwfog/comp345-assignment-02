//
//  main.cpp
//  comp345-assignment-02
//
//  Created by Charles Chao Yang on 11-11-03.

#include <iostream>
#include <sstream>
#include "GameMapEditor.h"

using namespace std;

int main (int argc, const char* argv[]) {
    int opt;
    string input = "";
    cout << "Welcome to the Game Editor!" << endl;
    
    while (true) {
        cout << "1. Map Editor" << endl;
        cout << "2. Character Editor" << endl;
        cout << "3. Quit Editor" << endl;
        cout << "Choose your option: ";
        // for safety check of input http://www.cplusplus.com/forum/articles/6046/
        getline(cin, input);
        stringstream stm(input);
        if (stm >> opt && opt <= 3 && opt >= 1) {
            switch (opt) {
                case 1: {
                    cout << "Please enter a map name. If the map already exists, " << endl;
                    cout << "it will be loaded, else a new map will be created with the name." << endl;
                    cout << "Map name: ";
                    string file;
                    cin >> file;
                    GameMapEditor* editor = new GameMapEditor(file);
                    break; }
                case 2: {
                    cout << "Sorry, the Character Editor  is not available yet." << endl;
                    break; }
                case 3: {
                    cout << "Good bye!" << endl;
                    exit(1);
                    break;}
                default: {
                    cout << "Unrecognized option." << endl;
                    break;  }  
            }

        }
        
        cout << "Error: Unrecognized option, please try again." << endl;    
    }
    
    return 0;
}