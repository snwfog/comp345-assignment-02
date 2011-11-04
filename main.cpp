//
//  main.cpp
//  comp345-assignment-02
//
//  Created by Charles Chao Yang on 11-11-03.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "GameMapEditor.h"


int main (int argc, const char * argv[])
{
    comp345::GameMapEditor* editor = new comp345::GameMapEditor("test");
    editor->edit();
    return 0;
}

