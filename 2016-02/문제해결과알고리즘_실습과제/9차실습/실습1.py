s = input('몇개의 숫자를 입력하겠습니까?')
s = int(s)

def makeList(n):
    myList = []
    for k in range(1,n+1,1):
        a = input('{0}번째 숫자를 입력하세요.'.format(k))
        a = int(a)
        myList.append(a)
    return myList

print(makeList(s))
