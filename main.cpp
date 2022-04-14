#include <iostream>
#include <cstdarg>
#include <cmath>

/* ��������...��ʾ0��n������ */

/* �� putchar ���Լ�дmy_printf() */

/*
 *
 *
    %a,%A ����һ������ֵ(��C99��Ч)
    %c ����һ���ַ�
    %d ����ʮ��������
    %i ����ʮ���ƣ��˽��ƣ�ʮ����������
    %o ����˽�������
    %x,%X ����ʮ����������
    %s ����һ���ַ��������ո��Ʊ�����з�������
    %f,%F,%e,%E,%g,%G ��������ʵ����������С����ʽ��ָ����ʽ���롣
    %p ����һ��ָ��
    %u ����һ���޷���ʮ��������
    %n �����Ѷ���ֵ�ĵȼ��ַ���
    %[] ɨ���ַ�����
    %% ��%����
 *
 *
 * */

/*printf��ȡ�Ĳ����� char,\,%
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
                        lf = lf * pow(10.0,count); /*���� 12 λ*/
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
         * ��ת��������������Ҫ������λ, �ɼ�����float����������Խ��,С�����ֵľ��Ⱦ�Խ��
            ��float����˵��Ч����ԼΪ7λ(2^23Լ����10^7),������������ռ��λ��Խ��,С������
            �ľ��Ⱦ�Խ��,���������ֳ���9999999��С�������Ѿ���ȫ�޾�����

            �����Ҳ�ȡf*10000000���㴦��,ʡ��С�����7λ�Ժ��С��
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
                /*double��2^52 = 4503599627370496��һ��16λ��ͬ��double�ľ���Ϊ15~16λ�� */
                if(flag!=1){
                    space(counts);
                }

                double lf = va_arg(*v,double);
                lf = lf * 100000000000000; /*���� 14 λ*/
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
         * 0B��ͷΪ2����
         * 0��ͷΪ8����
         * 0X��ͷΪ16����
         *
            %i ����ʮ���ƣ��˽��ƣ�ʮ����������
            %o ����˽�������
            %x,%X ����ʮ����������
         */
        case 'i':{
            if(flag!=1){
                space(counts);
            }
            /*%d %i�� printf ��ʽ����ʹ��ʱ��û������*/
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

/* ���л��� Clion ������ minGW  �����ʽGBK */

int main() {
    unsigned int i = 12;
    int x = 2;
    char str[100] = "���Ƕ�ү\0";
    char s = 'x';
    float f = 1.231923423;
    double  dou = 2.129334789290;
    int oxi = 0x1A;
    int oi = 071;
    void* pointer = &x;
    My_printf("���Ե�ֵΪ%12903132q �ų��˷�ռλ��ʱ%��Ӱ��,"
              "\ni��ֵΪ=%-2u �޷�������,"
              "\nd��ֵΪ=%d �з�������,"
              "\nstr��ֵΪ=%-2s �ַ���,"
              "\ns��ֵΪ=%c �ַ�,"
              "\nf��ֵΪ=%f ����,"
              "\ndouble��ֵΪ=%lf ˫���ȸ���,"
              "\noxi��ֵΪ%i ʮ����������,"
              "\noi��ֵΪ%i �˽�������,"
              "\npointer��ֵΪ%p ָ��"
              "",i,x,str,s,f,dou,oxi,oi,pointer);
    return 0;
}
