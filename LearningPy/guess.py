# -*- coding: utf-8 -*- 
import random
import time

# allNum用来记录所有无重复的4位数
allNum = []
# resultNum使用来统计各种情况下XAXB的情况
resultNum = {}

# 检查4位数字是否有重复，重复返回1，无重复返回0
def checkDuplicate(inputNum):
    strNum = list(inputNum)
    solveNum = set(strNum)
    if len(strNum) == len(solveNum):
        return 0
    return 1

def check(guessNum, ansNum):
    countA = 0
    countB = 0
    for i in range(len(guessNum)):
        if guessNum[i] in ansNum:
            if guessNum[i]==ansNum[i]:
                countA += 1
            else:
                countB += 1
    result = str(countA)+"A"+str(countB)+"B"
    return result

def calculate(guessNum, result):
    ans = resultNum[result]
    return ans
    

if __name__ == "__main__":
    for i in range(1000, 9999):
        inputNum = str(i)
        if 0 == checkDuplicate(inputNum):
            allNum += [inputNum]
        #print allNum
    ansNum = random.choice(allNum)
    print "the correct answer: ", ansNum   

    for i in allNum:
        result = check(i, ansNum)
        if result in resultNum:
            resultNum[result] += [i]
        else:
            resultNum[result] = [i]
    #print resultNum
    while (1):
        guessNum = raw_input("please input your answer: \n")
        result = check(str(guessNum), ansNum)
        print("check your answer now, waiting for moment pls...")
        time.sleep(2)
        if result == "4A0B":
            print "Congratulations! You Got The Correct Answer!!!\n"
            print "*****************\n"
            print "****GAME OVER****\n"
            print "*****************\n"
            break
        else:
            ans = calculate(guessNum, result)
            print "your answer: ", guessNum, result
            print "What a pity! You Got The Wrong Answer!!!\n"
            print "Computer try to guess!"
            while (1):
                compNum = random.choice(allNum)
                if compNum != guessNum:
                    break
            compResult = check(compNum, ansNum)
            print "computer's answer: ", compNum, compResult 
            print("check computer answer now, waiting for moment pls...")
            time.sleep(2)
            if compResult == "4A0B":
                print "Computer Got The Correct Ansert!!!\n"
                print "*****************\n"
                print "****GAME OVER****\n"
                print "*****************\n"
                break
            else:
                print "Luckily!!! Computer Got The Wrong Answer!!!\n"
                print "The result maybe is: \n", ans
                print "pls try again~\n"
