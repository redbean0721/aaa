#include "cli.h"
#include <iostream>
#include <cstring>

extern const char* APP_NAME;
extern const char* VERSION;
extern const char* COPYRIGHT;

namespace CLI {
    static void showHelp(const char *programName) {
        std::cout << "Usage: " << programName << " [options]\n"
                  << "Options:\n"
                  << "  -h, --help        Show this help message\n"
                  << "  -v, --version     Show version information\n"
                  << "  -c, --config      Specify config file\n"
                  << "  -d, --daemon      Run as daemon\n";
    }

    static void showVersion() {
        std::cout << APP_NAME << " " << VERSION << "\n"
                  << COPYRIGHT << "\n";
    }

    int parseArguments(int argc, char* argv[]) {
        // 沒有參數, 繼續執行主程式
        if (argc == 1) {
            return -1;
        }

        const char* arg = argv[1];

        // 檢查是否為選項 (以 '-' 或 '--' 開頭)
        if (arg[0] == '-') {
            if (strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0) {
                showHelp(argv[0]);
                return 0;
            }

            if (strcmp(arg, "-v") == 0 || strcmp(arg, "--version") == 0) {
                showVersion();
                return 0;
            }

            // 未知選項
            std::cerr << "Unknown option: " << arg << "\n";
            std::cerr << "Use -h for help\n";
            return 1;
        }

        // 非選項參數, 繼續執行主程式
        return -1;
    }
} // CLI