#include<string>

class CommandServer {
public:
    void startTCPListener(int port);
    const char* procedCommand(const char* command);
private:
    const int hashString(std::string s);
};