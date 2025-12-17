#ifndef TAIWANFRP_LAUNCHER_CLI_H
#define TAIWANFRP_LAUNCHER_CLI_H

/*
解析命令列參數
返回 -1: 繼續執行主程式
返回  0: 正常退出 (如顯示幫助或版本)
返回  1: 錯誤退出 (未知選項)
*/
namespace CLI {
    // class cli {
    // };
    int parseArguments(int argc, char* argv[]);
} // CLI

#endif //TAIWANFRP_LAUNCHER_CLI_H