/*
 * @Descripttion:
 * @version:
 * @Author: liyu
 * @Date: 2022-06-29 05:28:55
 */
#ifndef CMD_DEF_H
#define CMD_DEF_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//命令结构体
typedef int (*CmdProcFunc)(void);
typedef struct {
    char* pszCmd;
    CmdProcFunc fpCmd;
} CMD_PROC;

//命令处理函数定义
#define MOCK_FUNC(funcName)                 \
    int funcName(void)                      \
    {                                       \
        printf("  Enter " #funcName "!\n"); \
        return 0;                           \
    }

MOCK_FUNC(ShowMeInfo);
MOCK_FUNC(SetLogCtrl);
MOCK_FUNC(TestBatch);
MOCK_FUNC(TestEndianOper);

//命令表项宏，用于简化书写
#define CMD_ENTRY(cmdStr, func) \
    {                           \
        cmdStr, func            \
    }
#define CMD_ENTRY_END \
    {                 \
        NULL, NULL    \
    }

//命令表
static CMD_PROC gCmdMap[] = {
    CMD_ENTRY("ShowMeInfo", ShowMeInfo),
    CMD_ENTRY("SetLogCtrl", SetLogCtrl),
    CMD_ENTRY("TestBatch", TestBatch),
    CMD_ENTRY("TestEndian", TestEndianOper),

    CMD_ENTRY_END
};
#define CMD_MAP_NUM (sizeof(gCmdMap) / sizeof(CMD_PROC)) - 1 /*End*/

//返回gCmdMap中的CmdStr列(必须为只读字符串)，以供CmdGenerator使用
static char* GetCmdByIndex(unsigned int dwCmdIndex)
{
    if (dwCmdIndex >= CMD_MAP_NUM)
        return NULL;
    return gCmdMap[dwCmdIndex].pszCmd;
}

//执行命令
static int ExecCmd(char* pszCmdLine)
{
    if (NULL == pszCmdLine)
        return -1;

    unsigned int dwCmdIndex = 0;
    for (; dwCmdIndex < CMD_MAP_NUM; dwCmdIndex++) {
        if (!strcmp(pszCmdLine, gCmdMap[dwCmdIndex].pszCmd))
            break;
    }
    if (CMD_MAP_NUM == dwCmdIndex)
        return -1;
    gCmdMap[dwCmdIndex].fpCmd(); //调用相应的函数

    return 0;
}

#endif