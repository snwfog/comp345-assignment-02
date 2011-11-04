#ifndef GAMEMAP_H
#define GAMEMAP_H

namespace comp345 {
    // maximum width of stdscr
    const int STD_X = 80-16;
    // maximum height of stdscr
    const int STD_Y = 25-1;
 
    // character representation of the game objects
    enum GameObjectType { EMPTY = 32, WALL = '#', MONSTER = 'x', PLAYER = 'A', CHEST = 'o' };

    // structure to represent game objects
    struct GameObject {
        int y, x, c;
        GameObjectType objt;
        GameObject();
        GameObject(int, int, GameObjectType);

    };
    
    class GameMap {
    private:
        std::string mapname;
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
//        void attach(const Observer&);
//        void detach(const Observer&);
//        void notify(const Observer&);
        
    };
}
#endif