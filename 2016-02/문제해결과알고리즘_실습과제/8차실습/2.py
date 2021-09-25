def gcd():
    a = input('첫 번째 정수를 입력하세요 :')
    b = input('두 번째 정수를 입력하세요 :')
    a = int(a)
    b = int(b)
    x = a
    y = b
    if a < b:
        (a, b) = (b, a)
    while b != 0:
        (a, b) = (b, a % b)
    return print(x,'와',y,'의 공약수는', a,'입니다.')

gcd()
