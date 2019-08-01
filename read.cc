/*  Designed By ZhangTong
*   2019/07/13
*   A demo read  file 
*
*/
#include <stdio.h>
#include <string.h>


#define BUFFSIZE 1024

int main(int argc, char **argv){

    char buff[BUFFSIZE];
    FILE *fd = fopen (argv[1], "rb");
    int count, errno=0;

    bzero (buff, BUFFSIZE);
    while (!feof (fd)){
        count = fread (buff, sizeof (char), BUFFSIZE, fd);
        int n = feof (fd);
        printf ("%d,%d\n", count, n);
        printf ("%s\n",strerror (errno));
    }
    return 0;
}