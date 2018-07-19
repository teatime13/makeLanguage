#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef unsigned char *String; //Stringはunsigned char * の代用

void loadText(int argc, const char **argv, unsigned char *t, int siz)
{
    FILE *fp;
    int i;
    if(argc < 2) { //引数が少ないのでエラー表示して終了
        printf("usage>%s program-file\n", argv[0]);
        exit(1);
    }
    fp = fopen(argv[1], "rt"); //テキストモードでファイルを開く
    if(fp == 0) { //ファイルがひらけなかった
        printf("fopen error : %s\n", argv[1]);
        exit(1);
    }
    i = fread(t, 1, siz - 1, fp);
    fclose(fp);
    t[i] = 0; //終端マークを書いておく
}

int isNumber(unsigned char c) // 数字かどうか
{
    if('0' <= c && c <= '9') return 1;
    return 0;
}

int isAlphabet(unsigned char c) //変数名の一文字目に使える文字か
{
    if('a' <= c && c <= 'z') return 1;
    if('A' <= c && c <= 'Z') return 1;
    if(c == '_') return 1;
    return 0
}

int isSymbol(unsigned char c) //普通の記号文字
{
    if(strchar("=+-*/!%&~|<>?:.", c) != 0) return 1;
    return 0;
}

int lexer(String s, String b, String t[]) //プログラムを単語に切り分ける
{
    int i = 0, j = 0, k = 0;
    for(;;) {
        if(s[i] == ' ' || s[i] == '\t' || s[i] == '\n') { //空白類
            i++;
            continue;
        }
        t[k++] = &b[j]; //単語の先頭を登録
        if(s[i] == 0) //ファイル終端
            return k;
        if(strchr("(){}[];,", s[i]) != 0) { //１文字記号
        b[j++] = s[i++];
        } else if (isNumber(s[i]) != 0) { //１文字目が数字
            while(isNumber(s[i]) != 0)
                b[j++] = s[i++];
        } else if(isAlphabet(s[i]) != 0) { //１文字目が英字
            while(isAlphabet(s[i]) != 0 || isNumber(s[i]) != 0)
                b[j++] = s[i++];
        } else if(isSymbol(s[i]) != 0){ //１文字目が普通の記号
            while(isSymbol(s[i]) != 0)
                b[j++] = s[i++];
        } else {
            printf("syntax error : %.10s\n", &s[i]);
            exit(1);
        }
        b[j++] = 0; //単語の終端マーク
    }
}

int var[256]; //変数
String varName[256]; //変数名
unsigned char txt[10000]; //ソースコード
int pc = 0; //プログラムカウンタ

int varNumber(String t) //変数名から変数番号を得る
{
    int i;
    for(i = 0; varName[i] != 0; i++) {
        if(strcmp(t, varName[i]) == 0)
            return i;
    }
    varName[i] = t;
    return i;
}

int getNumber(String t)
{
    if(isNumber(t[0]) == 0) //１文字目が数字以外
        return var[varNumber(t)];
    return strtol(t, 0, 0); //tを数値に変換
}

int main(int argc, const char **argv)
{
    int i, pc0;
    unsigned char buf[10000];
    String t[10000]; //トークン
    loadText(argc, argv, txt, 10000);
    i = lexer(txt, buf, t);
}