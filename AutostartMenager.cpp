#include "AutostartMenager.h"
#include <string>
#include <windows.h>
#include <iostream>

using namespace std;

void AutostartMenager::baka(const std::string& appName){
    cout << appName;
}

bool AutostartMenager::IsInStartup(const std::string& appName) {
    HKEY hKey;
    const char* registryPath = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    char value[1024];
    DWORD valueLength = sizeof(value);
    // Otwórz klucz rejestru z uprawnieniami do odczytu
    if (RegOpenKeyExA(HKEY_CURRENT_USER, registryPath, 0, KEY_READ, &hKey) != ERROR_SUCCESS) {
        std::cerr << "Nie można otworzyć klucza rejestru!" << std::endl;
        return false;
    }
    // Sprawdź, czy wpis istnieje
    if (RegQueryValueExA(hKey, appName.c_str(), nullptr, nullptr, (LPBYTE)value, &valueLength) == ERROR_SUCCESS) {
        // Zamknij klucz rejestru
        RegCloseKey(hKey);
        return true; // Wpis istnieje
    }
    // Zamknij klucz rejestru
    RegCloseKey(hKey);
    return false; // Wpis nie istnieje
}
bool AutostartMenager::AddToStartup(const std::string& appName, const std::string& filePath) {
    HKEY hKey;
    const char* registryPath = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    // Otwórz klucz rejestru z uprawnieniami do zapisu
    if (RegOpenKeyExA(HKEY_CURRENT_USER, registryPath, 0, KEY_WRITE, &hKey) != ERROR_SUCCESS) {
        std::cerr << "Nie można otworzyć klucza rejestru!" << std::endl;
        return false;
    }
    // Dodaj wpis do rejestru
    if (RegSetValueExA(
            hKey,                            // Klucz rejestru
            appName.c_str(),                 // Nazwa wartości (np. nazwa aplikacji)
            0,                               // Zawsze 0
            REG_SZ,                          // Typ danych (ciąg znaków)
            reinterpret_cast<const BYTE*>(filePath.c_str()), // Ścieżka do pliku
            static_cast<DWORD>(filePath.size() + 1)          // Rozmiar danych (z null-terminatorem)
        ) != ERROR_SUCCESS) {
        std::cerr << "Nie można dodać wpisu do rejestru!" << std::endl;
        RegCloseKey(hKey);
        return false;
    }
    // Zamknij klucz rejestru
    RegCloseKey(hKey);
    return true;
}