//
//  GameMapEditor.cpp
//  comp345-assignment-02
//
//  Created by Charles Chao Yang on 11-11-03.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//


#include <iostream>
#include "GameMapEditor.h"

namespace comp345 {
    // struct for cursor object
    Cursor::Cursor(int y, int x) : y(y), x(x) { }
    Cursor::Cursor() : y((STD_Y)/2), x((STD_X)/2) { }
    
    GameMapEditor::GameMapEditor() {
        // ncurses initialization funcs
        initscr();
        noecho();
        curs_set(0);
        raw();
        keypad(stdscr, TRUE);
        wclear(stdscr);
        refresh();
        // end of ncurses initialization funcs
        
        // initialize member variables
        csr = new Cursor();
        pmap = new GameMap();
        wlgd = createLegendWindow();
        wdlg = createDialogueWindow();
        
        // flush the map
        refreshmap();
        
        // set the initial cursor to blinking
        attron(A_BLINK);
        mvwprintw(stdscr, csr->y, csr->x, "_");
        attroff(A_BLINK);
        refresh();
    }
    
    GameMapEditor::GameMapEditor(std::string name) {
        // ncurses initialization funcs
        initscr();
        noecho();
        curs_set(0);
        raw();
        keypad(stdscr, TRUE);
        wclear(stdscr);
        refresh();
        // end of ncurses initialization funcs
        
        // initialize member variables
        csr = new Cursor();
        pmap = new GameMap(name);
        wlgd = createLegendWindow();
        wdlg = createDialogueWindow();
        
        // flush the map
        refreshmap();
        
        // set the initial cursor to blinking
        GameObject* tmp = pmap->getAtLocation(csr->y, csr->x);
        attron(A_BLINK | A_UNDERLINE);
        mvwprintw(stdscr, csr->y, csr->x, "%c", tmp->c);
        attroff(A_BLINK | A_UNDERLINE);
        refresh();
        
    }
    
    GameMapEditor::~GameMapEditor() {
        // save();
        delete pmap;
        pmap = NULL;
        
        delete csr;
        csr = NULL;
        endwin();
    }
    
    WINDOW* GameMapEditor::createLegendWindow() {
        // create the legend window
        WINDOW* pwTemp = newwin(STD_Y+1, 16, 0, STD_X);
        // change the border style of the legend window
        wborder(pwTemp, '|', '|', '-', '-', '+', '+', '+', '+');
        
        // print the legend text
        mvwprintw(pwTemp, 1, 1, " LEGEND   ");
        
        mvwprintw(pwTemp, 3, 1, " # (w)all");
        mvwprintw(pwTemp, 4, 1, " A (p)layer");
        mvwprintw(pwTemp, 5, 1, " o (c)hest");
        mvwprintw(pwTemp, 6, 1, " x (m)onster");  
        
        mvwprintw(pwTemp, 8, 1, " (a)uto walls");
        // disabled, specific of door have not been determined
        //mvwprintw(pwTemp, 9, 1, " (d)oor");
        
        mvwprintw(pwTemp, 11, 1, " (r)emove");
        
        //mvwprintw(pwTemp, 13, 1, " (s)ave map");
        mvwprintw(pwTemp, 14, 1, " (q)uit");
        
        // display the legend window
        wrefresh(pwTemp);
        return pwTemp;
    }
    
    WINDOW* GameMapEditor::createDialogueWindow() {
        WINDOW* pwTemp = newwin(1, STD_X, STD_Y, 0);
        
        // display the dialog window (empty for now)
        wrefresh(pwTemp);
        return pwTemp;
    }
    
    void GameMapEditor::edit() {
        int c;
        while ((c = getch()) != 'q') {
            switch (c) {
                case KEY_LEFT:
                case KEY_RIGHT:
                case KEY_UP:
                case KEY_DOWN:
                    mvcsr(c);
                    break;
                case 'w':
                case 'p':
                case 'c':
                case 'm':
                case 'r':
                    addatcsr(c);
                    break;
                case 'a':
                    autowall();
                    break;
                default:
                    // mvwprintw(pwDialog, 0, 0, "Error: Unrecognized option. ");
                    // wrefresh(pwDialog);
                    break;
            }
        }
        
        // when quitting, save the current map
        // saveMap();
    }
    
    void GameMapEditor::mvcsr(int c) {
        switch (c) {
            case KEY_LEFT:
                mvcsrpos(csr->y, csr->x-1);
                break;
            case KEY_RIGHT:
                mvcsrpos(csr->y, csr->x+1);
                break;
            case KEY_UP:
                mvcsrpos(csr->y-1, csr->x);
                break;
            case KEY_DOWN:
                mvcsrpos(csr->y+1, csr->x);
                break;
            default:
                mvcsrpos(csr->y, csr->x);
                break;
        }
    }
    
    void GameMapEditor::mvcsrpos(int y, int x) {
        // check if y and x are out of the stdscr boundaries
        if (!(y >= STD_Y || y < 0 || x >= STD_X || x < 0)) {
            
            // restore old cursor pos object
            // this should happen without notifying the user, i.e. its not an intentional change
            // from the user, but just to display on the GUI
            GameObject* tmp = pmap->getAtLocation(csr->y, csr->x);
            if (tmp->objt == EMPTY) {
                // print empty space at current cursor pos
                mvwprintw(stdscr, csr->y, csr->x, " ");
            } else {
                // print the object in the game obj db's
                mvwprintw(stdscr, csr->y, csr->x, "%c", tmp->c);
            }
            
            // update cursor coordinate
            csr->x = x;
            csr->y = y;
            
            // retrieve game object at new csr pos
            tmp = pmap->getAtLocation(csr->y, csr->x);
            if (tmp->objt == EMPTY) {
                // turn on the blinking attribute of stdscr
                attron(A_BLINK);
                mvwprintw(stdscr, y, x, "_");
                attroff(A_BLINK);
                refresh();
            } else {
                attron(A_BLINK | A_UNDERLINE);
                mvwprintw(stdscr, y, x, "%c", tmp->c);
                attroff(A_BLINK | A_UNDERLINE);
                refresh();
            }
            
            
            wclear(wdlg);
            mvwprintw(wdlg, 0, 0, "cursor: %dy, %dx", csr->y, csr->x);
            wrefresh(wdlg);
        }
    }
    
    void GameMapEditor::refreshmap() {
        for (int i = 0; i < STD_Y; i++) {
            for (int j = 0; j < STD_X; j++) {
                mvwprintw(stdscr, i, j, "%c", (pmap->getAtLocation(i, j))->c);
            }
        }
        
        mvcsr(NULL);
        refresh();
    }
    
    void GameMapEditor::addatcsr(int c) {
        int tmp;
        switch (c) {
            case 'w':
                tmp = '#'; 
                break;
            case 'p':
                tmp = 'A';
                // remove the old player
                for (int i = 0; i < STD_Y; i++) {
                    for (int j = 0; j < STD_X; j++) {
                        if ((pmap->getAtLocation(i, j))->objt == PLAYER)
                            pmap->setAtLocation(i, j, GameObject(i, j, EMPTY));
                    }
                }
                break;
            case 'c':
                tmp = 'o';
                break;
            case 'm':
                tmp = 'x';
                break;
            case 'r':
                tmp = 32;
                break;
            default:
                tmp = '%';
                break;
        }
        pmap->setAtLocation(csr->y, csr->x, GameObject(csr->y, csr->x, static_cast<GameObjectType>(tmp)));
        refreshmap();
    }
    
    void GameMapEditor::autowall() {
        int y1 = csr->y;
        int x1 = csr->x;
        int y2, x2, c;
        
        printwdlg("auto wall mode on, press 'a' again to confirm wall location");
        
        while ((c = getch()) != 'a') {
            // allow cursor movement
            switch (c) {
                case KEY_LEFT:
                case KEY_RIGHT:
                case KEY_UP:
                case KEY_DOWN:
                    refreshmap();
                    mvcsr(c);
                    y2 = csr->y;
                    x2 = csr->x;
                    // create walls preview
                    for (int i = y1; i <= y2; i++) {
                        mvwprintw(stdscr, i, x1, "#");
                        mvwprintw(stdscr, i, x2, "#");
                    }
                    for (int i = x1; i <= x2; i++) {
                        mvwprintw(stdscr, y1, i, "#");
                        mvwprintw(stdscr, y2, i, "#");
                    }
                    refresh();
                    break;
                default:
                    printwdlg("error: only arrow keys are accepted");
                    break;
            }
        }
        // confirm placement of the walls
        // destroying all previous data's
        for (int i = y1; i <= y2; i++) {
            pmap->setAtLocation(i, x1, GameObject(i, x1, WALL));
            pmap->setAtLocation(i, x2, GameObject(i, x1, WALL));
        }            
        for (int i = x1; i <= x2; i++) {
            pmap->setAtLocation(y1, i, GameObject(y1, i, WALL));
            pmap->setAtLocation(y2, i, GameObject(y2, i, WALL));
        }
        refreshmap();
        printwdlg("auto wall mode completed");
    }
    
    void GameMapEditor::printwdlg(std::string str) {
        wclear(wdlg);
        mvwprintw(wdlg, 0, 0, str.c_str());
        wrefresh(wdlg);
    }
}
