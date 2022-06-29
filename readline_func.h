#ifdef __READLINE_DEBUG
#include "cmd_def.h"
#include <malloc.h>
#include <readline/history.h>
#include <readline/readline.h>

static const char* const pszCmdPrompt = ">>>";

//退出交互式调测器的命令(不区分大小写)
static const char* pszQuitCmd[] = { "Quit", "Exit", "End", "Bye", "Q", "E", "B" };
static const unsigned char ucQuitCmdNum = sizeof(pszQuitCmd) / sizeof(pszQuitCmd[0]);
static int IsUserQuitCmd(char* pszCmd)
{
    unsigned char ucQuitCmdIdx = 0;
    for (; ucQuitCmdIdx < ucQuitCmdNum; ucQuitCmdIdx++) {
        if (!strcasecmp(pszCmd, pszQuitCmd[ucQuitCmdIdx]))
            return 1;
    }

    return 0;
}

//剔除字符串首尾的空白字符(含空格)
static char* StripWhite(char* pszOrig)
{
    if (NULL == pszOrig)
        return "NUL";

    char* pszStripHead = pszOrig;
    while (isspace(*pszStripHead))
        pszStripHead++;

    if ('\0' == *pszStripHead)
        return pszStripHead;

    char* pszStripTail = pszStripHead + strlen(pszStripHead) - 1;
    while (pszStripTail > pszStripHead && isspace(*pszStripTail))
        pszStripTail--;
    *(++pszStripTail) = '\0';

    return pszStripHead;
}

static char* pszLineRead = NULL; //终端输入字符串
static char* pszStripLine = NULL; //剔除前端空格的输入字符串
char* ReadCmdLine()
{
    //若已分配命令行缓冲区，则将其释放
    if (pszLineRead) {
        free(pszLineRead);
        pszLineRead = NULL;
    }
    //读取用户输入的命令行
    pszLineRead = readline(pszCmdPrompt);

    //剔除命令行首尾的空白字符。若剔除后的命令不为空，则存入历史列表
    pszStripLine = StripWhite(pszLineRead);
    if (pszStripLine && *pszStripLine)
        add_history(pszStripLine);

    return pszStripLine;
}

static char* CmdGenerator(const char* pszText, int dwState)
{
    static int dwListIdx = 0, dwTextLen = 0;
    if (!dwState) {
        dwListIdx = 0;
        dwTextLen = strlen(pszText);
    }

    //当输入字符串与命令列表中某命令部分匹配时，返回该命令字符串
    const char* pszName = NULL;
    while ((pszName = GetCmdByIndex(dwListIdx))) {
        dwListIdx++;

        if (!strncmp(pszName, pszText, dwTextLen))
            return strdup(pszName);
    }

    return NULL;
}

static char** CmdCompletion(const char* pszText, int dwStart, int dwEnd)
{
    // rl_attempted_completion_over = 1;
    char** pMatches = NULL;
    if (0 == dwStart)
        //  rl_completion_matches()函数用于自动补全： 该函数返回一个字符串数组，即参数text的补全列表；若没有补全项，则函数返回NULL。
        //该数组以空指针结尾，首个条目将替换text，其余条目为可能的补全项。函数指针entry_func指向一个具有两个参数的函数。其中参数state在首次调用时为零，后续调用时为非零。未匹配到text时，entry_func返回空指针。
        pMatches = rl_completion_matches(pszText, CmdGenerator);
    return pMatches;
}

//初始化Tab键能补齐的Command函数
static void InitReadLine(void)
{
    rl_attempted_completion_function = CmdCompletion;
}

#endif