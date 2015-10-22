#C���������ļ������⡪��iniparser
**ǰ�ԣ�**�ڶ���Ŀ���Ż�ʱ������Linux��û��ר�ŵĹ���C����ʹ�õ������ļ�������������������iniparser�⣬��������Щ�����������һ����ʹ��ini�ļ����в������á�

##����
iniparser�����INI�ļ��Ľ�������ini�ļ�����һЩϵͳ��������������ļ���

iniparser�����������ط�ʽ��
1. [�ٷ���վ](http://ndevilla.free.fr/iniparser)
2. [�ҵ�github](https://github.com/AnSwErYWJ/Iniparser/blob/master/iniparser-3.1.tar.gz)
3. [�ҵ�����](http://pan.baidu.com/s/1jGEn86U)
4. [source code tree](https://github.com/ndevilla/iniparser)

##�����﷨
Iniparser���API���Զ�ini�ļ��������ļ������н��������á�ɾ���Ȳ�����

ini�ļ����������ɵ�Ԫ����key���߽�property��ÿ��key����һ������(name)�Ͷ�Ӧ��ֵ(value)��
```
name=value 
```

������Key���Ա�����Ϊһ�飬��section����������Ҫ����һ�У�������������������
```
[section]
name=value
```

��section�����µ�keys����͸�section����������һ��section�������������һ��section�����ĵط����������û����һ��section����������ô��section�Ľ����ط����Ǹ��ļ�ĩβ��section�ǲ�����Ƕ�׵ġ�

��λһ��key����section:key����ʾ�ģ����Բ�ͬsection�µ�key�������ǿ�����ͬ�ġ�

iniparser�⴦�����Ƶ�ʱ�򣬻�ͳһ����Сд������section��property�����������Ǵ�Сд�޹صġ�

ע��Ҫ�Էֺſ�ͷ��
```C
 ;comment
```

##API
iniparser.h��
```
int iniparser_getnsec(dictionary * d);	//��ȡdictionary�����section����

char * iniparser_getsecname(dictionary * d, int n);	//��ȡdictionary����ĵ�n��section������

void iniparser_dump_ini(dictionary * d, FILE * f);	//����dictionary����file

void iniparser_dumpsection_ini(dictionary * d, char * s, FILE * f);	//����dictionary����һ��section��file

void iniparser_dump(dictionary * d, FILE * f);	//����dictionary����file

int iniparser_getsecnkeys(dictionary * d, char * s);	//��ȡdictionary����ĳ��section�µ�key����

char ** iniparser_getseckeys(dictionary * d, char * s);	//��ȡdictionary����ĳ��section�����е�key

char * iniparser_getstring(dictionary * d, const char * key, char * def);	//����dictionary�����section:key��Ӧ���ִ�ֵ

int iniparser_getint(dictionary * d, const char * key, int notfound);	//����idictionary�����section:key��Ӧ������ֵ

double iniparser_getdouble(dictionary * d, const char * key, double notfound);	//����dictionary�����section:key��Ӧ��˫����ֵ

int iniparser_getboolean(dictionary * d, const char * key, int notfound);	//����dictionary�����section:key��Ӧ�Ĳ���ֵ

int iniparser_set(dictionary * ini, const char * entry, const char * val);	//����dictionary�����ĳ��section:key��ֵ

void iniparser_unset(dictionary * ini, const char * entry);	//ɾ��dictionary������ĳ��section:key

int iniparser_find_entry(dictionary * ini, const char * entry) ;	//�ж�dictionary�������Ƿ����ĳ��section:key

dictionary * iniparser_load(const char * ininame);	//����dictionary���󲢷���(�����ڴ�)dictionary����

void iniparser_freedict(dictionary * d);	//�ͷ�dictionary����(�ڴ�)

unsigned dictionary_hash(const char * key);	//����ؼ��ʵ�hashֵ

dictionary * dictionary_new(int size);	//����dictionary����

void dictionary_del(dictionary * vd);	//ɾ��dictionary����

char * dictionary_get(dictionary * d, const char * key, char * def);	//��ȡdictionary�����keyֵ

int dictionary_set(dictionary * vd, const char * key, const char * val);	//����dictionary�����keyֵ

void dictionary_unset(dictionary * d, const char * key);	//ɾ��dictionary�����keyֵ

void dictionary_dump(dictionary * d, FILE * out);	//����dictionary����
```

##ʾ��

���Ƚ�ѹ�����صĿ��ļ���
```
tar -zxvf iniparser-3.1.tar.gz
```

���룺
```
cd iniparser-3.1/
make
```

���Կ���srcĿ¼�������������ļ�������dictionary.h����������һЩֱ�ӽ���ini file��API��iniparser.h����������һЩ�ṩ�û�������API��iniparser.h�����API�Ƕ�dictionary.h����API���ٴη�װ�����ṩ�û��Ѻ��ԡ�

Ȼ�󿽱�src�µ�ͷ�ļ�dictionary.h��iniparser.h�Լ�ѹ����Ŀ¼�µľ�̬��libiniparser.a�Ͷ�̬��libiniparser.so.0��Ŀ���ļ�ϵͳ�Ķ�ӦĿ¼�¡�

��дini�ļ���
```
#ini file for example

[tcp]
;for tcp communication

port = 8000;
ip = 127.0.0.1;
family = AF_INET;

[serial port]
;for serial port communication

speed = 9600;
```

�����ļ���
```
/*************************************************************************
	> File Name: example.c
	> Author: AnSwEr
	> Mail: 1045837697@qq.com
	> Created Time: 2015��10��22�� ������ 20ʱ37��10��
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
```

���У�
```
gcc example.c -o example -L. -liniparser
./example
```

�����
```
dictionary obj:
[tcp]=UNDEF
[tcp:port]=[8000]
[tcp:ip]=[127.0.0.1]
[tcp:family]=[AF_INET]
[serial port]=UNDEF
[serial port:speed]=[9600]

tcp:
port : 8000
ip : 127.0.0.1
family : AF_INET

serial port:
speed : 9600

```

##�ܽ�
�����������ļ��Ĺ����Ǻܷ���ģ�ϣ�������а�����


## �����뽨��
- ΢����[@AnSwEr���Ǵ�](http://weibo.com/1783591593)
- github��[AnSwErYWJ](https://github.com/AnSwErYWJ)
- ���ͣ�[AnSwEr���Ǵ𰸵�ר��](http://blog.csdn.net/u011192270)




