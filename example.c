/*************************************************************************
	> File Name: example.c
	> Author: AnSwEr
	> Mail: 1045837697@qq.com
	> Created Time: 2015年10月22日 星期四 20时37分10秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "iniparser.h"

int main(void)
{
    dictionary *ini;
    int n = 0;
    char *str;

    ini = iniparser_load("example.ini");//parser the file
    if(ini == NULL)
    {
        fprintf(stderr,"can not open %s","example.ini");
        exit(EXIT_FAILURE);
    }

    printf("dictionary obj:\n");
    iniparser_dump(ini,stderr);//save ini to stderr

    printf("number of keys in %s is %d\n", "tcp", iniparser_getsecnkeys(ini, "tcp"));
    
    printf("\n%s:\n",iniparser_getsecname(ini,0));//get section name
    n = iniparser_getint(ini,"tcp:port",-1);
    printf("port : %d\n",n);

    str = iniparser_getstring(ini,"tcp:ip","null");
    printf("ip : %s\n",str);

    str = iniparser_getstring(ini,"tcp:family","null");
    printf("family : %s\n",str);

    printf("\n%s:\n",iniparser_getsecname(ini,1));
    n = iniparser_getint(ini,"serial port:speed",-1);
    printf("speed : %d\n",n);

    iniparser_freedict(ini);//free dirctionary obj

    return 0;
}
