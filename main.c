/*
 * @Descripttion:
 * @version:
 * @Author: liyu
 * @Date: 2022-06-29 05:34:09
 */
/* gcc -Wall -o main cmd_def.h readline_func.h main.c -D__READLINE_DEBUG -lreadline -lncurses */

#include "readline_func.h"

int main(int argc, char* argv[])
{
#ifndef __READLINE_DEBUG
    printf("Note: Macro __READLINE_DEBUG is Undefined, thus InteractiveCmd is Unavailable!!!\n\n");
#else
    printf("Note: Welcome to Interactive Command!\n");
    printf("      Press 'Quit'/'Exit'/'End'/'Bye'/'Q'/'E'/'B' to quit!\n\n");
    InitReadLine();
    while (1) { //也可加入超时机制以免忘记退出
        char* pszCmdLine = ReadCmdLine();
        if (IsUserQuitCmd(pszCmdLine)) {
            free(pszLineRead);
            break;
        }

        ExecCmd(pszCmdLine);
    }
#endif
    return 0;
}
