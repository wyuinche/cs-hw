import random
magic = random.randint(1,99)
print('0과 100사이의 마법수를 맞춰보세요.')
while True:
    a = input('마법수는 무엇일까요? : ')
    a = int(a)
    if a == magic:
        print( '정답, 마법수는', magic, '입니다.')
        break
    elif a < magic:
        print('너무 작습니다.')
    elif a > magic:
        print('너무 큽니다.')
