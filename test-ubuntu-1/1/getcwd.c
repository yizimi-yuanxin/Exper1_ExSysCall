/*
 * 测试通过时输出：
 * "getcwd OK."
 * 测试失败时输出：
 * "getcwd ERROR."
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void test_getcwd(void){
    char *cwd = NULL;
    char buf[128] = {0};
    cwd = getcwd(buf, 128);
    if(cwd != NULL) {
        printf("current dir: %s\n", buf);
        printf("getcwd OK.\n");
    } 
    else printf("getcwd ERROR.\n");
}

int main(void){
    test_getcwd();
    return 0;
}
