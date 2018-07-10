import sys

varDic = {}
    
    
def main():
    loadText()
    args = sys.argv
    sys.args = sys.args
    blankWord = ['\n', ' ', '\t', ';']

    with open(openFile[1]) as f:
        for line in f:
            if line.find(blankWord):
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
                print("{}\n".format(varDic[6]))
            else:
                err(line)
    print(varDic)


def loadText():
    args = sys.argv
    if len(args) < 2:
        print("useage{} program-file\n".format(argv[0]))
        sys.exit()
    with open(args[1]) as f:
        if f == 0:
            printf("fopen error : {}\n".format(argv[1]))
            sys.exit()


def getNumber(txt):
    if txt.isnumeric():
        return int(txt)
    return varDic[txt]


def err(strLine):
    print("syntax error : {}\n".format(strLine))
    sys.exit()

if __name__ == "__main__":
    main()