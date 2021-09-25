k = input('값을 입력하세요: ')
def str(text):
    l = list(text)
    a = ''
    m = len(text)
    n = int(m)-1
    while n>-1:
        a += l[n]
        n-=1
    else:
        print(a)
        return a
str(k)

