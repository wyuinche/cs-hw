s = 0
while True :
    a = input('정수를 입력하세요 (0을 입력하면 종료):')
    a = int(a)
    if a == 0 :
        print('합계는', s, '입니다.')
        break
    s = s + a
