import sys
import os

varDic = {}
    
#main文
def main():
    loadText()
    args = sys.argv
    openFile = args[1]
    blankWord = ['\n', ' ', '\t', ';']

    with open(openFile) as f:
        for line in f:
            line = line.strip('\n')
            for word in blankWord:
                if line.find(word):
                    continue
            if line[1] == '=':
                if line[3] == ';':
                    varDic[line[0]] = line[2]
                elif line[3] == '+' and line[5] == ';':
                    varDic[line[0]] = getNumber(line[2]) + getNumber(line[4])
                elif line[3] == '-' and line[5] == ';':
                    varDic[line[0]] = getNumber(line[2]) + getNumber(line[4])
                else:
                    err(line)
            elif line[0] == 'p' and line[1] == 'r' and\
                    line[5] == ' ' and line[7] == ';':
                print("{}".format(varDic[line[6]]))
            else:
                err(line)


#プログラムファイルを読み込む
def loadText():
    args = sys.argv
    if len(args) < 2:
        print("useage {} program-file".format(args[0]))
        sys.exit()
    if not os.path.exists(args[1]):
        noFileErr(args[1])
    with open(args[1]) as f:
        if f == 0:
            print("fopen error : {}".format(args[1]))
            sys.exit()

#数字ならばint型で、変数ならば変数の値を返す
def getNumber(txt):
    if txt.isnumeric():
        return int(txt)
    return int(varDic[txt])


#プログラムの構文エラー
def err(strLine):
    print("syntax error : {}".format(strLine))
    sys.exit()


#ファイルが存在しないエラー
def noFileErr(fileStr):
    print("no file error : {}".format(fileStr))
    sys.exit()

if __name__ == "__main__":
    main()