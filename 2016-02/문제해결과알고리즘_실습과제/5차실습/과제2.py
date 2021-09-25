year = input('연도를 입력하세요:')
year = int(year)
if year%4 == 0:
    if year%100 == 0:
        if year%400 == 0:
            print(year,'은 윤년입니다.')
        else :
            print(year,'은 윤년이 아닙니다.')
    print(year,'은 윤년입니다.')
else :
    print(year,'은 윤년이 아닙니다.')
