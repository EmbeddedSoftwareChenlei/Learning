# !/usr/bin/python
# -*- coding: UTF-8 -*-

import random
import string

allNum = [] #所有不重复的数字组合
numCount = {} #记录与正确答案相同的数字

# 检查是否有重复的字符
def checkDuplicate(inputNum):
    strNum = list(inputNum)
    solveNum = set(strNum)
    if len(strNum) == len(solveNum):
        return 0
    return 1


# 判断输出1A1B
def check(guessNum, ansNum):
    countA = 0
    countB = 0
    sameNumLoc = []
    sameNum = []
    global numCount
    for i in range(len(guessNum)):
        if guessNum[i] in ansNum:
            if guessNum[i] == ansNum[i]:
                countA += 1
                sameNumLoc += [{i: guessNum[i]}]
            else:
                countB += 1
                sameNum += [guessNum[i]]
    numCount = {"sameNum" : sameNum, "sameNumLoc" : sameNumLoc}
    result = str(countA) + "A" + str(countB) + "B"
    return result

#所有可能数据集
def calculate(guessNum, result):
    ans = []
    sameNum = numCount["sameNum"]
    sameNumLoc = numCount["sameNumLoc"]
    for value in allNum:
        flag = 0
        for i in sameNum:
            if i not in value:
                flag = 1 
        for dic in sameNumLoc:
            for _index, _value in dic.items():
                if value[_index] != _value:
                    flag = 1
        if flag != 1:
            ans += [value]
    return ans

#判断是否符合输入类型
def judgeNum(guessNum):
    if len(guessNum) != 4:
        print 'The wrong length!'
        return 0

    if checkDuplicate(guessNum) == 1:
        print 'The duplicate number!'
        return 0

    if guessNum.isdigit() == False:
        print 'The wrong type!'
        return 0


if __name__ == "__main__":
    for i in range(1000, 9999):
        inputNum = str(i)
        if checkDuplicate(inputNum) == 0:
            allNum += [inputNum]
    ansNum = random.choice(allNum)
    print "the correct answer: ", ansNum

    while (1):
        guessNum = raw_input("Please input your aAnswer: ")

        if judgeNum(guessNum) == 0:
            continue

        result = check(guessNum, ansNum)

        if result == "4A0B":
            print "Congratulations! You got the correct answer!!!\n"
            print "*****************\n"
            print "****GAME OVER****\n"
            print "*****************\n"
            break
        else:
            ans = calculate(guessNum, result)
            print "Your answer: ", guessNum, result,"\n"
            print "Computer try to guess!"
            while (1):
                compNum = random.choice(allNum)
                if compNum != guessNum:
                    break
            compResult = check(compNum, ansNum)
            print "Computer's answer: ", compNum, compResult

            if compResult == "4A0B":
                print "Computer got the correct ansert!\n"
                print "*****************\n"
                print "****GAME OVER****\n"
                print "*****************\n"
                break
            else:
                print "The result maybe is: \n", ans
                print "Please guess again!\n"
