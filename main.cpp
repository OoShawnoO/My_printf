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

void zero(int count){
    while(count>0){
        putchar('0');
        count--;
    }
}



void process_x(long long d,int x){
    if(d>=x){
        process_x(d/x,x);
        if(x==16){
            if(d%x>=10){
                putchar(d%x-10+'a');
            }
            else{
                putchar(48+d%x);
            }
        }else{
            putchar(48+d%x);
        }

    }
    else{
        putchar(48+d);
    }
}

void process_x(unsigned long d,int x){
    process_x((long long)(d),x);
}

void process_x(int d,int x){
    process_x((long long)d,x);
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


void Switch(char **c,va_list* v,int counts,char* first,int right,int zro,int spa,int sign){

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
                    if(right!=1){
                        space(counts);
                    }
                    double f = va_arg(*v, double);
                    f = f * pow(10.0,count);
                    int d = floor(double(f));
                    if(d<0){
                        putchar('-');
                        d = -(d);
                    }
                    else{
                        if(sign==2){
                            putchar('+');
                        }
                        if(spa==4){
                            putchar(' ');
                        }
                    }
                    process_int(d,count);
                    if(right==1){
                        space(counts);
                    }

                }
                case 'l':{
                    if(*(*c+1)=='f'){
                        if(right!=1){
                            space(counts);
                        }
                        double lf = va_arg(*v,double);
                        lf = lf * pow(10.0,count); /*���� 12 λ*/
                        long long int d = floor(lf);

                        if(d<0){
                            putchar('-');
                            d = -(d);
                        }
                        else{
                            if(sign==2){
                                putchar('+');
                            }
                            if(spa==4){
                                putchar(' ');
                            }
                        }
                        process_int(d,count);
                        if(right==1){
                            space(counts);
                        }
                    }
                    else{
                        break;
                    }
                }
                case 'd':{
                    if(right!=1 and zro!=3){
                        space(counts);
                    }
                    int d = va_arg(*v,int);
                    int j = d;
                    int cs = 0;
                    while(j>1){
                        j/=10;
                        cs++;
                    }
                    if(zro==3){
                        zero(counts-cs+1);
                    }
                    if(d<0){
                        putchar('-');
                        d = -(d);
                    }
                    else{
                        if(sign==2){
                            putchar('+');
                        }
                        if(spa==4){
                            putchar(' ');
                        }
                    }
                    process_int(d,100);
                    if(right==1){
                        space(counts);
                    }
                    break;
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
            if(right!=1){
                space(counts);
            }

            float f = va_arg(*v, double);
            f = f * 10000000;
            int d = floor(double(f));
            if(d<0){
                putchar('-');
                d = -(d);
            }
            else{
                if(sign==2){
                    putchar('+');
                }
            }
            process_int(d,7);
            if(right==1){
                space(counts);
            }
        }
        case 'l':{
            if(*(*c+1)=='f'){
                /*double��2^52 = 4503599627370496��һ��16λ��ͬ��double�ľ���Ϊ15~16λ�� */
                if(right!=1){
                    space(counts);
                }

                double lf = va_arg(*v,double);
                lf = lf * 100000000000000; /*���� 14 λ*/
                long long int d = floor(lf);
                if(d<0){
                    putchar('-');
                    d = -(d);
                }
                else{
                    if(sign==2){
                        putchar('+');
                    }
                    if(spa==4){
                        putchar(' ');
                    }
                }
                process_int(d,14);
                if(right==1){
                    space(counts);
                }

            }
            break;
        }
        case 'd': {
            if(right!=1){
                space(counts);
            }
            int d = va_arg(*v,int);
            if(d<0){
                putchar('-');
                d = -(d);
            }
            else{
                if(sign==2){
                    putchar('+');
                }
                if(spa==4){
                    putchar(' ');
                }
            }
            process_int(d,100);
            if(right==1){
                space(counts);
            }
            break;
        }
        case 's':{
            if(right!=1){
                space(counts);
            }
            char* str = va_arg(*v,char*);
            while(*(str)!='\0'){
                putchar(*str);
                str++;
            }
            if(right==1){
                space(counts);
            }
            break;
        }
        case 'c':{
            if(right!=1){
                space(counts);
            }
            char ca = **v;
            va_arg(*v,char*);
            putchar(ca);
            if(right==1){
                space(counts);
            }
            break;

        }
        case 'u':{
            if(right!=1){
                space(counts);
            }
            unsigned int d = va_arg(*v,unsigned int);
            process_int(d,100);
            if(right==1){
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
            if(right!=1){
                space(counts);
            }
            /*%d %i�� printf ��ʽ����ʹ��ʱ��û������*/
            int d = va_arg(*v,int);
            if(d<0){
                putchar('-');
                d = -(d);
            }
            else{
                if(sign==2){
                    putchar('+');
                }
                if(spa==4){
                    putchar(' ');
                }
            }
            process_int(d,100);
            if(right==1){
                space(counts);
            }
            break;

        }
        case 'o':{
            if(right!=1){
                space(counts);
            }
            int d = va_arg(*v,int);
            if(d<0){
                putchar('-');
                d = -(d);
            }
            else{
                if(sign==2){
                    putchar('+');
                }
                if(spa==4){
                    putchar(' ');
                }
            }
            process_x(d,8);
            if(right==1){
                space(counts);
            }
            break;
        }
        case 'x':{
            if(right!=1){
                space(counts);
            }
            int d = va_arg(*v,int);
            if(d<0){
                putchar('-');
                d = -(d);
            }
            else{
                if(sign==2){
                    putchar('+');
                }
                if(spa==4){
                    putchar(' ');
                }
            }
            process_x(d,16);
            if(right==1){
                space(counts);
            }
            break;
        }
        case 'p':{
            if(right!=1){
                space(counts);
            }
            zero(6);
            long long int ptr = va_arg(*v,long long int);
//            if(ptr<0){
//                ptr = -(ptr);
//            }
            process_x(ptr,16);
            if(right==1){
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
            
            int right = 0;
            int sign = 0;
            int spa = 0;
            int zro = 0;
            
            c++;
            if(*c=='-'){
                right = 1;
                c++;
            }
            if(*c=='+'){
                sign = 2;
                c++;
            }
            if(*c=='0'){
                zro = 3;
                c++;
            }
            if(*c==' '){
                spa = 4;
                c++;
            }


            char *first = c;
            int count = 0;
            if(*c=='*'){
                int y = va_arg(v,int);
                c++;
                count = y;
                Switch(&c,&v,count,first,right,zro,spa,sign);
                c++;
            }
            else if(*c>='0'&&*c<='9'){
                count = 0;int x = 1;
                while(*c>='0'&&*c<='9') {
                    int j = strtol(c, nullptr, 10);
                    count = j * x + count;
                    x *= 10;
                    c++;
                }

                Switch(&c,&v,count,first,right,zro,spa,sign);
                c++;
                }
            else{
                Switch(&c,&v,0,first,right,zro,spa,sign);
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
    int oi = 71;
    void* pointer = &x;
    /*
     * ����� - �����
     * ����� 0 ��0
     * ����� ��������λ��
     * ����� * ��С����ڲ����б�
     * */

    printf("���Ե�ֵΪ%12903132q �ų��˷�ռλ��ʱ%��Ӱ��,"
              "\ni��ֵΪ=%-u �޷�������,"
              "\nd��ֵΪ=%-06d �з�������,"
              "\nstr��ֵΪ=%-2s �ַ���,"
              "\ns��ֵΪ=%c �ַ�,"
              "\nf��ֵΪ=%-0*f ����,"
              "\ndouble��ֵΪ=% lf ˫���ȸ���,"
              "\noxi��ֵΪ%i ʮ����������,"
              "\noi��ֵΪ%o �˽�������,"
              "\npointer��ֵΪ%p ָ��"
              "\n",i,x,str,s,4,f,dou,oxi,oi,pointer);

    My_printf("\n���Ե�ֵΪ%12903132q �ų��˷�ռλ��ʱ%��Ӱ��,"
              "\ni��ֵΪ=%-u �޷�������,"
              "\nd��ֵΪ=%-06d �з�������,"
              "\nstr��ֵΪ=%-2s �ַ���,"
              "\ns��ֵΪ=%c �ַ�,"
              "\nf��ֵΪ=%-0*f ����,"
              "\ndouble��ֵΪ=% lf ˫���ȸ���,"
              "\noxi��ֵΪ%i ʮ����������,"
              "\noi��ֵΪ%o �˽�������,"
              "\npointer��ֵΪ%p ָ��"
              "",i,x,str,s,4,f,dou,oxi,oi,pointer);
    return 0;
}
