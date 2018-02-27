# C语言配置文件解析库——iniparser

**前言**: 在对项目的优化时，发现Linux下没有专门的供给C语言使用的配置文件函数，于是搜索到了iniparser库，可以像那些面向对象语言一样，使用ini文件进行参数配置。

## 介绍
iniparser是针对INI文件的解析器。ini文件则是一些系统或者软件的配置文件。

iniparser库有三种下载方式：
1. [官方网站](http://ndevilla.free.fr/iniparser)
2. [我的github](https://github.com/AnSwErYWJ/Iniparser/blob/master/iniparser-3.1.tar.gz)
3. [我的网盘](http://pan.baidu.com/s/1jGEn86U)
4. [source code tree](https://github.com/ndevilla/iniparser)

## 基本语法
Iniparser库的API可以对ini文件（配置文件）进行解析、设置、删除等操作。

ini文件的最基本组成单元就是key或者叫property，每个key都有一个名称(name)和对应的值(value)：
```
name=value 
```

而许多个Key可以被归类为一组，即section。组名定义要独立一行，并用中括号括起来：
```
[section]
name=value
```

在section声明下的keys都会和该section关联起来。一个section的作用域会在下一个section声明的地方结束，如果没有下一个section的声明，那么该section的结束地方就是该文件末尾。section是不可以嵌套的。

定位一个key是用section:key来表示的，所以不同section下的key的名称是可以相同的。

iniparser库处理名称的时候，会统一换成小写，所以section和property的名称命名是大小写无关的。

注释要以分号开头：
```C
 ;comment
```

## API
iniparser.h：
```
int iniparser_getnsec(dictionary * d);	//获取dictionary对象的section个数

char * iniparser_getsecname(dictionary * d, int n);	//获取dictionary对象的第n个section的名字

void iniparser_dump_ini(dictionary * d, FILE * f);	//保存dictionary对象到file

void iniparser_dumpsection_ini(dictionary * d, char * s, FILE * f);	//保存dictionary对象一个section到file

void iniparser_dump(dictionary * d, FILE * f);	//保存dictionary对象到file

int iniparser_getsecnkeys(dictionary * d, char * s);	//获取dictionary对象某个section下的key个数

char ** iniparser_getseckeys(dictionary * d, char * s);	//获取dictionary对象某个section下所有的key

char * iniparser_getstring(dictionary * d, const char * key, char * def);	//返回dictionary对象的section:key对应的字串值

int iniparser_getint(dictionary * d, const char * key, int notfound);	//返回idictionary对象的section:key对应的整形值

double iniparser_getdouble(dictionary * d, const char * key, double notfound);	//返回dictionary对象的section:key对应的双浮点值

int iniparser_getboolean(dictionary * d, const char * key, int notfound);	//返回dictionary对象的section:key对应的布尔值

int iniparser_set(dictionary * ini, const char * entry, const char * val);	//设置dictionary对象的某个section:key的值

void iniparser_unset(dictionary * ini, const char * entry);	//删除dictionary对象中某个section:key

int iniparser_find_entry(dictionary * ini, const char * entry) ;	//判断dictionary对象中是否存在某个section:key

dictionary * iniparser_load(const char * ininame);	//解析dictionary对象并返回(分配内存)dictionary对象

void iniparser_freedict(dictionary * d);	//释放dictionary对象(内存)

unsigned dictionary_hash(const char * key);	//计算关键词的hash值

dictionary * dictionary_new(int size);	//创建dictionary对象

void dictionary_del(dictionary * vd);	//删除dictionary对象

char * dictionary_get(dictionary * d, const char * key, char * def);	//获取dictionary对象的key值

int dictionary_set(dictionary * vd, const char * key, const char * val);	//设置dictionary对象的key值

void dictionary_unset(dictionary * d, const char * key);	//删除dictionary对象的key值

void dictionary_dump(dictionary * d, FILE * out);	//保存dictionary对象
```

## 示例

首先解压你下载的库文件：
```
tar -zxvf iniparser-3.1.tar.gz
```

编译：
```
cd iniparser-3.1/
make
```

可以看到src目录下生成了六个文件，其中dictionary.h里面声明了一些直接解析ini file的API，iniparser.h里面声明了一些提供用户操作的API。iniparser.h里面的API是对dictionary.h里面API的再次封装，以提供用户友好性。

然后拷贝src下的头文件dictionary.h和iniparser.h以及压缩包目录下的静态库libiniparser.a和动态库libiniparser.so.0到目标文件系统的对应目录下。

编写ini文件：
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

测试文件：
```
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

运行：
```
gcc example.c -o example -L. -liniparser
./example
```

结果：
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

## 总结
这个库对配置文件的管理还是很方便的，希望对您有帮助。


## 反馈与建议
- 微博：[@AnSwEr不是答案](http://weibo.com/1783591593)
- github：[AnSwErYWJ](https://github.com/AnSwErYWJ)
- 博客：[AnSwEr不是答案的专栏](http://blog.csdn.net/u011192270)




