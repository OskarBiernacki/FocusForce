class CommandServer {
public:
    void startTCPListener(int port);
    const char* procedCommand(const char* command);
};