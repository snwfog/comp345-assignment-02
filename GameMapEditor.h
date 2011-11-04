//
//  GameMapEditor.h
//  comp345-assignment-02
//
//  Created by Charles Chao Yang on 11-11-03.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GAMEMAPEDITOR_H
#define GAMEMAPEDITOR_H

#include <ncurses.h>
#include "GameMap.h"

namespace comp345 {
    // struct for cursor object
    struct Cursor {
        int y, x;
        Cursor(int, int);
        Cursor();
    };
    
    class GameMapEditor {
    public:
        GameMapEditor();
        GameMapEditor(std::string);
        ~GameMapEditor();
        void edit();
        
        // assignment 2 functions
        void wrtdlg(std::string);
        
    private:
        GameMap* pmap;
        Cursor* csr; // the cursor
        WINDOW* wlgd; // legend window
        WINDOW* wdlg; // dialogue window
        
        WINDOW* createLegendWindow();
        WINDOW* createDialogueWindow();
        void printwdlg(std::string);
        void mvcsr(int);
        void mvcsrpos(int, int);
        void refreshmap();
        void addatcsr(int);
        void autowall();
        
    };
}


#endif
