#include <iostream>
#include "AutostartMenager.h"

using namespace std;

int main(int argc, char** argv) {
    AutostartMenager autostartMenager;
    autostartMenager.baka("FocusForce init...\n");

    if(autostartMenager.isInTempFolder()==false)
        autostartMenager.moveToTempFolder();
    
    return 0;
}
