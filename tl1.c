#include<stdio.h>
#include<stdlib.h>

void loadText(int argc, const char **argv, unsigned char *t, int siz) {
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

int var[256]; //変数
unsigned char txt[10000]; //ソースコード
int pc = 0; //プログラムカウンタ

int getNumber(unsigned char c) {
    if('0' <= c && c <= '9')
        return c - '0'; //1桁の定数
    return var[c]; //1文字の変数名
}

int main(int argc, const char **argv) {
    int i, pc0;
    loadText(argc, argv, txt, 10000);
    for(;;) {
        pc0 = pc;
        if(txt[pc] == 0) //ファイル終端
            exit(0);
        if(txt[pc] == '\n' || txt[pc] == ' ' || txt[pc] == '\t' ||
            txt[pc] == ';') {
            pc++;
            continue;        
        }
        if(txt[pc + 1] == '=') { //2文字目が"="
            i = txt[pc];
            if(txt[pc + 3] == ';') { //単純代入
                var[i] = getNumber(txt[pc + 2]);
            } else if(txt[pc + 3] == '+' && txt[pc + 5] == ';') { //加算
                var[i] = getNumber(txt[pc + 2]) + getNumber(txt[pc + 4]);
            } else if(txt[pc + 3] == '-' && txt[pc + 5] == ';') { //減纂
                var[i] = getNumber(txt[pc + 2]) - getNumber(txt[pc + 4]);
            } else
                goto err;
        } else if(txt[pc] == 'p' && txt[pc + 1] == 'r' &&
                txt[pc + 5] == ' ' && txt[pc + 7] == ';') { //print
            printf("%d\n", var[txt[pc + 6]]);
        } else
            goto err;
        while(txt[pc] != ';')
            pc++;
    }
err:
    printf("syntax error : %.10s\n", &txt[pc0]);
    exit(1);
}