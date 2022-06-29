<!--
 * @Descripttion: 利用C readline库模拟shell用户输入,支持Tab键补全,上下键回溯历史输入
 * @version: 
 * @Author: liyu
 * @Date: 2022-06-29 05:43:36
-->
## 依赖
    sudo apt install libreadline-dev
## 编译
    gcc -Wall -o main cmd_def.h readline_func.h main.c -D__READLINE_DEBUG -lreadline -lncurses

## 参考
    https://www.cnblogs.com/clover-toeic/p/3892688.html