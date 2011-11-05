//
//  GameMapEditor.h
//  comp345-assignment-02
//
//  Created by Charles Chao Yang on 11-11-03.

#ifndef GAMEMAPEDITOR_H
#define GAMEMAPEDITOR_H

#include <ncurses.h>
#include "GameMap.h"

// struct for cursor object
struct Cursor {
    int y, x;
    Cursor(int, int);
    Cursor();
};

class GameMapEditor : Observer {
public:
    GameMapEditor();
    GameMapEditor(std::string);
    ~GameMapEditor();
    void wrtdlg(std::string);
    void update(GameMap*);
    
private:
    GameMap* pmap;
    Cursor* csr; // the cursor
    WINDOW* wlgd; // legend window
    WINDOW* wdlg; // dialogue window
    
    WINDOW* createLegendWindow();
    WINDOW* createDialogueWindow();
    
    void edit();
    void printwdlg(std::string);
    void mvcsr(int);
    void mvcsrpos(int, int);
    void refreshmap();
    void addatcsr(int);
    void autowall();
    
    
};
#endif
