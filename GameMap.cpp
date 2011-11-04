//
//  GameMap.cpp
//  comp345-assignment-02
//
//  Created by Charles Chao Yang on 11-11-03.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <fstream>

#include "GameMap.h"

namespace comp345 {
    GameObject::GameObject(int y, int x, GameObjectType type) : y(y), x(x), objt(type) {
        switch (type) {
            case EMPTY:
                c = 32;
                break;
            case WALL:
                c = '#';
                break;
            case MONSTER:
                c = 'x';
                break;
            case PLAYER:
                c = 'A';
                break;
            case CHEST:
                c = 'o';
                break;
            default:
                c = 32;
                break;
        }
    }
    
    // careful when using this constructor, because the y/x position
    // are set to 0, this could cause problem in some cases
    GameObject::GameObject() : y(0), x(0), objt(EMPTY), c(32) { }    
    
    GameMap::GameMap() : mapname("untitled_map") {
        for (int i = 0; i < STD_Y; i++)
            for (int j = 0; j < STD_X; j++)
                gobj_db[i][j] = GameObject(i, j, EMPTY);
        
        // attach(observers)
    }
    
    GameMap::GameMap(std::string name) : mapname(name) {
        //  check if the map already exists
        std::ifstream in;
        std::string input;
        
        if (!in.fail()) {
            ldmap();
//            while (true) {
//                std::cout << "A map with the name " << name << " is already present in the directory, would you like to edit it instead? (y/n): ";
//                getline(std::cin, input);
//                if (input.length() == 1) {
//                    c = input[0];
//                    if (c == 'y' || c == 'n' || c == 'Y' || c == 'N')
//                        break;
//                }
//                std::cout << "Invalid answer, please try again." << std::endl;
//            }
        } else {
            // create empty map
            for (int i = 0; i < STD_Y; i++)
                for (int j = 0; j < STD_X; j++)
                    gobj_db[i][j] = GameObject(i, j, EMPTY);
        }
        in.close();
        
        // attach observers
    }
    
    GameMap::~GameMap() {
        // detach observers
    }
    
    void GameMap::ldmap() {
        std::ifstream in;
        in.open(mapname.c_str());
        
        for (int i = 0; i < STD_Y; i++) {
            for (int j = 0; j < STD_X; j++) {
                gobj_db[i][j] = GameObject(i, j, static_cast<GameObjectType>(in.get()));
            }
        }
    }
    
    void GameMap::save() {
        std::ofstream out;
        out.open(mapname.c_str());
        
        for (int i = 0; i < STD_Y; i++) {
            for (int j = 0; j < STD_X; j++) {
                out << gobj_db[i][j].objt;
            }
        }
    }
    
    void GameMap::setAtLocation(int y, int x, GameObject gobj) {
        gobj_db[y][x] = gobj;
        
        //notify();
    }
    
    GameObject* GameMap::getAtLocation(int y, int x) {
        return &gobj_db[y][x];
    }
    
    
    
}