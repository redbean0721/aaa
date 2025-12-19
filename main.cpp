#include <iostream>
#include <string>
#include "cli.h"

#include "httplib.h"
#include "json.hpp"

// windows
#ifdef _WIN32
    #include <conio.h>
// __linux__, __APPLE__
#elif __linux__ || __APPLE__
    #include <termios.h>
    #include <unistd.h>
#endif

using nlohmann::json;

const char* APP_NAME = "TaiwanFRP Launcher";
inline constexpr const char* KEYRING_NAME = "taiwanfrp-launcher";
const char* VERSION = "2.0.0";
const char* COPYRIGHT = "Copyright (c) 2025 TaiwanFRP";

inline std::string FRP_VERSION;

inline constexpr const char* API_URL = "https://api.redbean0721.com/api";
inline constexpr const char* FRP_GITHUB_API_URL = "https://api.github.com/repos/fatedier/frp/tags/v%s";

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string get_password() {
#ifdef _WIN32
    std::string password;
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b' && !password.empty()) {
            password.pop_back();
        } else if (ch != '\b') {
            password += ch;
        }
    }
    std::cout << std::endl;
    return password;
#elif __linux__ || __APPLE__
    termios oldt{}, newt{};
    std::string password;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    std::cin >> password;

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    std::cout << std::endl;
    return password;
#endif
}

int main(int argc, char* argv[]) {
    // 解析命令列參數, -1 表示繼續執行, 其他值為退出碼
    if (int exitCode = CLI::parseArguments(argc, argv); exitCode != -1) {
        return exitCode;
    }

    // 主程式邏輯
    std::cout << "Starting TaiwanFRP Launcher...\n";

    httplib::Client cli("api.redbean0721.com");
    if (auto res = cli.Get("/api/frp/monitor/query")) {
        if (res->status == 200) {
            try {
                json j = json::parse(res->body);

                // 取得 stats -> version 的第一個 key
                if (j.contains("stats") && j["stats"].contains("version")) {
                    if (auto version_obj = j["stats"]["version"]; !version_obj.empty()) {
                        // 取第一個 key
                        FRP_VERSION = version_obj.begin().key();
                        std::cout << "FRP Version: " << FRP_VERSION << "\n";
                    }
                }
            } catch (std::exception& e) {
                std::cerr << "JSON parse error: " << e.what() << "\n";
                return 1;
            }
        }
    }

    std::cout << "請輸入使用者名稱: ";
    std::string username, password;
    std::cin >> username;
    std::cout << "請輸入密碼: ";
    // std::cin >> password;
    password = get_password();

    std::cout << "Username: " << username << ", " << "Password: " << password << "\n";

    return 0;
}