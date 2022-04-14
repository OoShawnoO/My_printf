#include <iostream>
#include <cstdarg>
#include <cmath>

/* 函数参数...表示0到n个参数 */

/* 用 putchar ，自己写my_printf() */

/*
 *
 *
    %a,%A 读入一个浮点值(仅C99有效)
    %c 读入一个字符
    %d 读入十进制整数
    %i 读入十进制，八进制，十六进制整数
    %o 读入八进制整数
    %x,%X 读入十六进制整数
    %s 读入一个字符串，遇空格、制表符或换行符结束。
    %f,%F,%e,%E,%g,%G 用来输入实数，可以用小数形式或指数形式输入。
    %p 读入一个指针
    %u 读入一个无符号十进制整数
    %n 至此已读入值的等价字符数
    %[] 扫描字符集合
    %% 读%符号
 *
 *
 * */

/*printf读取的参数有 char,\,%
 * */

void space(int count){
    while(count>0){
        putchar(' ');
        count--;
    }
}

void process_int(long long int d,int count){
    int x = 10;
    char ints[256] = {0};
    char *is = ints;

    while(d>10){
        *is = 48+(d)%x;
        is++;
        d = d/x;
    }
    *is = d+48;
    while((is+1)!=ints){
        if(is-count+1==ints){
            putchar('.');
        }
        putchar(*is);
        is--;
    }
}

void process_int(int d,int count){
    process_int((long long int) d,count);
}

void process_int(unsigned int d,int count){
    process_int(int(d),count);
}


void Switch(char **c,va_list* v,int counts,char* first,int flag){

    switch(**c){
        case '.':{
            (*c)++;
            int count = 0,x = 1;
            while(**c>='0'&&**c<='9'){
                int j = strtol(*c, nullptr, 10);
                count = j*x + count;
                x*=10;
                (*c)++;
            }
            switch(**c){
                case 'f':{
                    if(flag!=1){
                        space(counts);
                    }
                    double f = va_arg(*v, double);
                    f = f * pow(10.0,count);
                    int d = floor(double(f));
                    if(d<0){
                        putchar('-');
                        d = -(d);
                    }
                    process_int(d,count);
                    if(flag==1){
                        space(counts);
                    }

                }
                case 'l':{
                    if(*(*c+1)=='f'){
                        if(flag!=1){
                            space(counts);
                        }
                        double lf = va_arg(*v,double);
                        lf = lf * pow(10.0,count); /*保留 12 位*/
                        long long int d = floor(lf);

                        if(d<0){
                            putchar('-');
                            d = -(d);
                        }
                        process_int(d,count);
                        if(flag==1){
                            space(counts);
                        }
                    }
                    else{
                        break;
                    }
                }
            }
            break;
        }
        /*
         * 在转换过程中由于需要往右移位, 可见对于float数整数部分越大,小数部分的精度就越低
            对float数来说有效数字约为7位(2^23约等于10^7),所以整数部分占的位数越多,小数部分
            的精度就越低,当整数部分超过9999999后小数部分已经完全无精度了

            所以我采取f*10000000方便处理,省略小数点后7位以后的小数
         * */
        case 'f':{
            if(flag!=1){
                space(counts);
            }

            float f = va_arg(*v, double);
            f = f * 10000000;
            int d = floor(double(f));
            if(d<0){
                putchar('-');
                d = -(d);
            }
            process_int(d,7);
            if(flag==1){
                space(counts);
            }
        }
        case 'l':{
            if(*(*c+1)=='f'){
                /*double：2^52 = 4503599627370496，一共16位，同理，double的精度为15~16位。 */
                if(flag!=1){
                    space(counts);
                }

                double lf = va_arg(*v,double);
                lf = lf * 100000000000000; /*保留 14 位*/
                long long int d = floor(lf);
                if(d<0){
                    putchar('-');
                    d = -(d);
                }
                process_int(d,14);
                if(flag==1){
                    space(counts);
                }

            }
            break;
        }
        case 'd': {
            if(flag!=1){
                space(counts);
            }
            int d = va_arg(*v,int);
            if(d<0){
                putchar('-');
                d = -(d);
            }
            process_int(d,100);
            if(flag==1){
                space(counts);
            }
            break;
        }
        case 's':{
            if(flag!=1){
                space(counts);
            }
            char* str = va_arg(*v,char*);
            while(*(str)!='\0'){
                putchar(*str);
                str++;
            }
            if(flag==1){
                space(counts);
            }
            break;
        }
        case 'c':{
            if(flag!=1){
                space(counts);
            }
            char ca = **v;
            va_arg(*v,char*);
            putchar(ca);
            if(flag==1){
                space(counts);
            }
            break;

        }
        case 'u':{
            if(flag!=1){
                space(counts);
            }
            unsigned int d = va_arg(*v,unsigned int);
            process_int(d,100);
            if(flag==1){
                space(counts);
            }
            break;

        }
        /*
         * 0B开头为2进制
         * 0开头为8进制
         * 0X开头为16进制
         *
            %i 读入十进制，八进制，十六进制整数
            %o 读入八进制整数
            %x,%X 读入十六进制整数
         */
        case 'i':{
            if(flag!=1){
                space(counts);
            }
            /*%d %i在 printf 格式串中使用时，没有区别*/
            int d = va_arg(*v,int);
            if(d<0){
                putchar('-');
                d = -(d);
            }
            process_int(d,100);
            if(flag==1){
                space(counts);
            }
            break;

        }
        case 'o':{
            if(flag!=1){
                space(counts);
            }
            int d = va_arg(*v,int);
            if(d<0){
                putchar('-');
                d = -(d);
            }
            process_int(d,100);
            if(flag==1){
                space(counts);
            }
            break;
        }
        case 'x':{
            if(flag!=1){
                space(counts);
            }
            int d = va_arg(*v,int);
            if(d<0){
                putchar('-');
                d = -(d);
            }
            process_int(d,100);
            if(flag==1){
                space(counts);
            }
            break;
        }
        case 'p':{
            if(flag!=1){
                space(counts);
            }
            int ptr = va_arg(*v, int);
            if(ptr<0){
                ptr = -(ptr);
            }
            process_int(ptr,100);
            if(flag==1){
                space(counts);
            }
            break;
        }
        default:{
            while(first!=*c){
                putchar(*first);
                first++;
            }
            putchar(**c);
        }
    }
}

void My_printf(const char *str,...){
    va_list v;
    va_start(v,str);
    char *c = (char*)str;
    while(*c!='\0'){
        while(*c!='\0'&&*c!='%'){
            putchar(*(c++));
        }
        if(*c=='%'){
            int flag = 0;
            c++;
            if(*c=='-'){
                flag = 1;
                c++;
            }
            if(*c=='+'){
                flag = 2;
                c++;
            }


            char *first = c;
            if(*c>='0'&&*c<='9'){
                int count = 0,x = 1;
                while(*c>='0'&&*c<='9'){
                    int j = strtol(c, nullptr, 10);
                    count = j*x + count;
                    x*=10;
                    c++;
                }
                Switch(&c,&v,count,first,flag);
                c++;
            }
            else{
                Switch(&c,&v,0,first,flag);
                c++;
            }

        }
    }
}

/* 运行环境 Clion 编译器 minGW  编码格式GBK */

int main() {
    unsigned int i = 12;
    int x = 2;
    char str[100] = "我是二爷\0";
    char s = 'x';
    float f = 1.231923423;
    double  dou = 2.129334789290;
    int oxi = 0x1A;
    int oi = 071;
    void* pointer = &x;
    My_printf("测试的值为%12903132q 排除了非占位符时%的影响,"
              "\ni的值为=%-2u 无符号整形,"
              "\nd的值为=%d 有符号整形,"
              "\nstr的值为=%-2s 字符串,"
              "\ns的值为=%c 字符,"
              "\nf的值为=%f 浮点,"
              "\ndouble的值为=%lf 双精度浮点,"
              "\noxi的值为%i 十六进制整数,"
              "\noi的值为%i 八进制整数,"
              "\npointer的值为%p 指针"
              "",i,x,str,s,f,dou,oxi,oi,pointer);
    return 0;
}
