//
//  GameMap.h
//  comp345-assignment-02
//
//  Created by Charles Chao Yang on 11-11-03.


#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <vector>

// maximum width of stdscr
const int STD_X = 80-16;
// maximum height of stdscr
const int STD_Y = 25-1;

// character representation of the game objects
enum GameObjectType { EMPTY = 32, WALL = '#', MONSTER = 'x', PLAYER = 'A', CHEST = 'o' };

// structure to represent game objects
struct GameObject {
    int y, x, c;
    // type should contains the name of the type in later version
    GameObjectType objt;
    GameObject();
    GameObject(int, int, GameObjectType);

};

// forward declare
class GameMap;

// observer abstract class
class Observer {
public:
    Observer() { };
    ~Observer() { };
    
    virtual void update(GameMap*) = 0;
};

class GameMap {
private:
    std::string mapname;
    // observers vectors
    std::vector<Observer*> observers;
    
    GameObject gobj_db[STD_Y][STD_X]; // game object database
    
    // helping functions
    void ldmap();
    
    
public:
    GameMap();
    GameMap(std::string);
    ~GameMap();
    
    std::string getmapname() { return mapname; };
    void save();
    void setAtLocation(int, int, GameObject);
    GameObject* getAtLocation(int, int);

    // function added for assignment 2
    // obeservers pattern
    void attach(Observer*);
    //void detach(const Observer&);
    void notify();
};

#endif