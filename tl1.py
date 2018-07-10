import sys

varDic = {}

def loadText():
    args = sys.argv
    if len(args) < 2:
        print("useage{} program-file\n".format(argv[0]))
        sys.exit()
    with open(argv[1]) as f:
        if f == 0:
            printf("fopen error : {}\n".format(argv[1]))
            sys.exit()

def getNumber(strNum):
    if strNum.isnumeric():
        return int(strNum)
    return 
    
    
def main() {
    loadText()
    args = sys.argv
    blankWord = ['\n', ' ', '\t', ';']

    with open(argv[1]) as f:
        for line in f:
            if line.find(blankWord):
                continue
            if line[1] == '=':
                if line[3] == ';':
                    varDic[line[0]] = line[2]
                elif line[3] == '+' and line[5] == ';':


}
    