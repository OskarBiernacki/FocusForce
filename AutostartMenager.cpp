#include "AutostartMenager.h"
#include <string>
#include <windows.h>
#include <iostream>
#include <shlobj.h>

using namespace std;

bool AutostartMenager::isInTempFolder(string currentPath) {
    char tempPath[MAX_PATH];
    if (GetTempPathA(MAX_PATH, tempPath) == 0) {
        std::cerr << "Nie udało się uzyskać ścieżki do folderu Temp." << std::endl;
        return false;
    }

    char charCurrentPath[MAX_PATH];
    for(int i=0;i<MAX_PATH;i++)
        if(i < currentPath.size())
            charCurrentPath[i]=currentPath[i];
        else
            charCurrentPath[i]='t';

    for(int i=MAX_PATH-1;i>=0;i--)
        if (tempPath[i]=='\\'){
            for(int x=i;x<MAX_PATH;x++)
                tempPath[x]='t';
            break;
        }
    
    for(int i=MAX_PATH-1;i>=0;i--)
        if (charCurrentPath[i]=='\\'){
            for(int x=i;x<MAX_PATH;x++)
                charCurrentPath[x]='t';
            break;
        }
    //cout << tempPath << "\n" << charCurrentPath << "\n";
    if (strstr(charCurrentPath, tempPath) != nullptr) {
        return true;
    }
    return false;
}
string AutostartMenager::moveToTempFolder() {
    char tempPath[MAX_PATH];
    if (GetTempPathA(MAX_PATH, tempPath) == 0) {
        std::cerr << "Nie udało się uzyskać ścieżki do folderu Temp." << std::endl;
        return NULL;
    }

    char fileName[MAX_PATH];
    if (GetModuleFileNameA(NULL, fileName, MAX_PATH) == 0) {
        std::cerr << "Nie udało się uzyskać ścieżki do pliku wykonywalnego." << std::endl;
        return NULL;
    }

    std::string newFilePath = std::string(tempPath) + "windowNet.exe";
    

    cout << "Przenoszę do: " << std::string(newFilePath) << "\n";
    DeleteFileA(newFilePath.c_str());
    if (MoveFileA(fileName, newFilePath.c_str())) {
        std::cout << "Program został przeniesiony do folderu Temp." <<std::endl;
    } else {
        std::cerr << "Błąd podczas przenoszenia pliku: " << GetLastError() << std::endl;
    }
    return newFilePath;
}
bool AutostartMenager::isInStartup(const std::string& appName) {
    HKEY hKey;
    const char* registryPath = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    char value[1024];
    DWORD valueLength = sizeof(value);
    if (RegOpenKeyExA(HKEY_CURRENT_USER, registryPath, 0, KEY_READ, &hKey) != ERROR_SUCCESS) {
        std::cerr << "Nie można otworzyć klucza rejestru!" << std::endl;
        return false;
    }
    if (RegQueryValueExA(hKey, appName.c_str(), nullptr, nullptr, (LPBYTE)value, &valueLength) == ERROR_SUCCESS) {
        RegCloseKey(hKey);
        return true;
    }
    RegCloseKey(hKey);
    return false;
}
bool AutostartMenager::addToStartup(const std::string& appName, const std::string& filePath) {
    HKEY hKey;
    const char* registryPath = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    if (RegOpenKeyExA(HKEY_CURRENT_USER, registryPath, 0, KEY_WRITE, &hKey) != ERROR_SUCCESS) {
        std::cerr << "Nie można otworzyć klucza rejestru!" << std::endl;
        return false;
    }
    // Dodaj wpis do rejestru
    if (RegSetValueExA(
            hKey,
            appName.c_str(),
            0,
            REG_SZ,
            reinterpret_cast<const BYTE*>(filePath.c_str()),
            static_cast<DWORD>(filePath.size() + 1)
        ) != ERROR_SUCCESS) {
        std::cerr << "Nie można dodać wpisu do rejestru!" << std::endl;
        RegCloseKey(hKey);
        return false;
    }
    RegCloseKey(hKey);
    return true;
}