cnt = 0
import turtle

def isNumber_TwoChoices(x):    
    try:
        int(x)
        if int(x) == 1:
            return True
        elif int(x) ==2:
            return True
        else :
            return False
    except:
        return False

def isNumber_ThreeChoices(x):    
    try:
        int(x)
        if int(x) == 1:
            return True
        elif int(x) ==2:
            return True
        elif int(x) ==3:
            return True
        else :
            return False
    except:
        return False

def isNumber_height_weight(x):
    try:
        int(x)
        if int(x) >= 1:
            return True
        else:
            return False
    except :
        return False

def isNumber_count(x):
    global cnt
    try:
        int(x)
        if int(x) > cnt :
            return False
        elif int(x) > 0 :
            return True
        else :
            return False
    except :
        return False
    

sex = input('당신의 성별은? 1.여자 2.남자') #sex변수 : 1은 여자, 2는 남자
while not isNumber_TwoChoices(sex):
    sex = input('당신의 성별은?(1또는 2만 입력해주세요.) 1.여자 2.남자')
sex = int(sex)
    
height = input('키는? (cm): ') #height = 키
while not isNumber_height_weight(height):
    height = input('키는? (cm) (자연수만 입력해주세요): ')
height = int(height)

weight = input('몸무게는? (kg): ') # weight = 몸무게
while not isNumber_height_weight(weight):
    weight = input('몸무게는? (kg) (자연수만 입력해주세요): ')
weight = int(weight)

weight_set = 0
height_set = 0
body = 0
w = 0
cloth = 0
place = 0
cnt = 0
match = 0
연인 = 0
장소 = 0
score = 0
answer1 = 0
sorted_count = []
unsorted_count = []
unsorted_score = []
sorted_score = []
unsorted_reminiscence = []
answer2 = 0
answer3 = 0
answer1_say =0
answer2_say = 0
man_list=('귀여운 남자','섹시한 남자','순수한 남자')
woman_list=('지적인 여자','귀여운 여자','섹시한 여자')
date_style = {}
#save_score
save_score=[]
ask_change=0
#save
save_scoresquence = {}
wonder = 0
wonder_scene = 0
result_score = {}
save_relist =[0,1,2]
place_list=[]
save = []
answer3_say = 0

name = input('당신의 이름을 입력하세요 :')

def pick_body(w):
    global answer3_say
    global save
    global place_list
    global save_score
    global ask_change
    global save_scoresquence
    global wonder
    global wonder_scene
    global man_list
    global woman_list
    global save_relist
    global answer1
    global final_pick
    global answer2
    global result_score
    global answer3
    global answer1_say
    global final_pick
    global answer2_say
    global score
    global sex
    global date_style
    global height
    global weight
    global weight_set
    global height_set
    global body
    global cloth
    global name
    global place
    global match
    global 장소
    global 연인
    weight_set = w
    body = input('당신은 어느부분에 살이 더 많다고 생각하는가? 1.상체 2.하체 3.상체와 하체가 비슷하다')
    while not isNumber_ThreeChoices(body):
        body = input('당신은 어느부분에 살이 더 많다고 생각하는가? (1, 2, 3 중에서만 선택해주세요) 1.상체 2.하체 3.상체와 하체가 비슷하다')
    body = int(body)
    return body

def pick_cloth(h,c):
    global answer3_say
    global place_list
    global save
    global save_score
    global ask_change
    global save_scoresquence
    global final_pick
    global wonder
    global wonder_scene
    global man_list
    global woman_list
    global answer1
    global answer2
    global answer3
    global answer1_say
    global answer2_say
    global score
    global sex
    global height
    global weight
    global weight_set
    global height_set
    global body
    global cloth
    global name
    global place
    global match
    global 장소
    global 연인
    if height_set == h :
        if weight_set == 1:
             if body == 1:
                cloth = c
             elif body == 2:
                cloth =c+1
             elif body == 3:
                cloth = c+2
        else :
            cloth = c+3
    return 1

if sex == 1: #여자
    if height >= 163:
        height_set = 1 # height_set이 1이면 키가 큰 여자
        if weight >= 55:
            pick_body(1)
        else :
            weight_set = 2 #키가 크면서 마른 여자
            body = 4 # body 1,2,3,4 = 상체비만, 하체비만, 전체적으로 비만, 마름
    else :
        height_set = 2 # height_set이 2이면 키가 작은 여자
        if weight >= 50:
            pick_body(1)
        else :
            weight_set = 2 #키가 작으면서 마른 여자
            body = 4 # body 1,2,3,4 = 상체비만, 하체비만, 전체적으로 비만, 마름
    pick_cloth(1,1)
    pick_cloth(2,5)

if sex == 2: #남
    if height >= 177:
        height_set = 1 # height_set이 1이면 키가 큰 남
        if weight >= 67:
            pick_body(1)
        else :
            weight_set = 2 #키가 크면서 마른 남
            body = 4 # body 1,2,3,4 = 상체비만, 하체비만, 전체적으로 비만, 마름
    else :
        height_set = 2 # height_set이 2이면 키가 작은 남
        if weight >= 63:
            pick_body(1)
        else :
            weight_set = 2 #키가 작으면서 마른 남
            body = 4 # body 1,2,3,4 = 상체비만, 하체비만, 전체적으로 비만, 마름
    pick_cloth(1,9)
    pick_cloth(2,13)

def top_score(p):
    global score
    global cnt
    global unsorted_score
    unsorted_score = []
    result_score['{0}번째 데이트의 점수'.format(p)] = score  
    return score

def score1():
    global score
    score = score + 1
    return 1
def score2():
    global score
    score = score + 2
    return 2
def score3():
    global score
    score = score + 3
    return 3

def scene_score(k,a,b,c):
    global final_pick
    global save_score
    global score
    global save_relist
    if final_pick[k] == a:
        score3()
        save_relist[k] = 3
    elif final_pick[k] == b: 
        score2()
        save_relist[k] = 2
    elif final_pick[k] == c:
        save_relist[k] = 1
        score1()
    return 1

def pick_match():
    global answer3_say
    global save
    global place_list
    global save_score
    global ask_change
    global save_scoresquence
    global wonder
    global wonder_scene
    global man_list
    global woman_list
    global answer1
    global answer2
    global result_score
    global answer3
    global answer1_say
    global answer2_say
    global score
    global final_pick
    global final_pick
    global sex
    global height
    global weight
    global weight_set
    global height_set
    global body
    global w
    global cloth
    global name
    global place
    global match
    global 장소
    global 연인
    global save_relist
    if sex == 1:
        print(man_list)
        match = input('당신은 어떤 남자가 맘에 드는가? 1.귀여운 남자 2.섹시한 남자 3.순수한 남자')
        while not isNumber_ThreeChoices(match):
            match = input('당신은 어떤 남자가 맘에 드는가?(1,2,3중에서만 선택해주세요) 1.귀여운 남자 2.섹시한 남자 3.순수한 남자')
        match = int(match)
        print(man_list[match-1],'을 고르셨습니다.')
        if match == 1:
            연인 = '귀여운 남자'
        if match == 2:
            연인 = '섹시한 남자'
        if match == 3:
            연인 = '순수한 남자'
        save.append(match)
    if sex == 2:
        print(woman_list)
        match = input('당신은 어떤 여자가 맘에 드는가? 1.지적인 여자 2.귀여운 여자 3.섹시한 여자') #1은 세련된 것, 2는 다정하고 부드러운 것, 3은 카리스마 있는 것을 좋아함
        while not isNumber_ThreeChoices(match):
            match = input('당신은 어떤 여자가 맘에 드는가?(1,2,3중에서만 선택해주세요) 1.지적인 여자 2.귀여운 여자 3.섹시한 여자')
        match = int(match)
        print(woman_list[match-1],'을 고르셨습니다.')
        if match == 1:
            연인 = '지적인 여자'
        if match == 2:
            연인 = '귀여운 여자'
        if match == 3:
            연인 = '섹시한 여자'
        save.append(match+3)
    return match

def pick_place():
    global answer3_say
    global save
    global place_list
    global save_relist
    global save_score
    global ask_change
    global save_scoresquence
    global wonder
    global wonder_scene
    global man_list
    global woman_list
    global answer1
    global answer2
    global answer3
    global answer1_say
    global answer2_say
    global score
    global sex
    global final_pick
    global height
    global final_pick
    global result_score
    global weight
    global weight_set
    global height_set
    global body
    global date_style
    global cloth
    global name
    global place
    global match
    global 장소
    global 연인
    print(place_list)
    place = input('당신이 원하는 데이트 장소는? 1.영화관 2.해변 3.놀이동산')
    while not isNumber_ThreeChoices(place):
        place = input('당신이 원하는 데이트 장소는?(1,2,3중에서만 선택해주세요) 1.영화관 2.해변 3.놀이동산')
    place = int(place)
    if place == 1:
        장소 = '영화관'
    if place == 2:
        장소 = '해변'
    if place == 3:
        장소 = '놀이동산'
    print(place_list[place-1],'을 고르셨습니다.')
    save.append(place)
    return place

def start():
    import turtle
    global cnt
    print('오늘은 당신이 연인과 {0}번째 데이트를 하는 날입니다.'.format(cnt))
    global answer3_say
    global unsorted_reminiscence
    global place_list
    global save_relist
    global result_score
    global save_score
    global ask_change
    global save_scoresquence
    global final_pick
    global wonder
    global wonder_scene
    global man_list
    global woman_list
    global answer1
    global answer2
    global answer3
    global answer1_say
    global answer2_say
    global score
    global sex
    global height
    global weight
    global weight_set
    global height_set
    global body
    global name
    global place
    global match
    global save
    global 장소
    global 연인
    global cloth
    global date_style

    place = 0
    match = 0
    연인 = 0
    장소 = 0
    score = 0
    answer1 = 0
    answer2 = 0
    answer3 = 0
    answer1_say =0
    answer2_say = 0
    man_list=('귀여운 남자','섹시한 남자','순수한 남자')
    woman_list=('지적인 여자','귀여운 여자','섹시한 여자')
    date_style = {}
    #save_score
    save_score=[]
    ask_change=0
    #save
    save_scoresquence = {}
    wonder = 0
    wonder_scene = 0
    save_relist =[0,1,2]
    place_list=[]
    save = []
    answer3_say = 0

    place_list = ('영화관','해변','놀이동산')

    pick_match()
    pick_place()

    date_style['place'] = place_list[place-1]
    if sex == 1:
        date_style['match'] = man_list[match-1]
    if sex == 2:
        date_style['match'] = woman_list[match-1]

    print('당신은 ', 연인,' 과 함께', 장소, '에 갑니다.')
    
    ask_change = input('그대로 진행하시겠습니까? 1.yes 2.no')
    while not isNumber_TwoChoices(ask_change):
        ask_change = input('그대로 진행하시겠습니까?(1 또는 2만 선택해주세요) 1.yes 2.no')
    ask_change = int(ask_change)
    while ask_change != 1:
        if ask_change ==2:
            save = []
            del date_style['match']
            pick_match()
            date_style['match'] = 연인
            del date_style['place']
            pick_place()
            date_style['place'] = 장소
            print('당신은 ', 연인,' 과 함께', 장소, '에 갑니다.')
            ask_change = input('그대로 진행하시겠습니까? 1.yes 2.no')
            while not isNumber_TwoChoices(ask_change):
                ask_change = input('그대로 진행하시겠습니까?(1 또는 2만 선택해주세요) 1.yes 2.no')
            ask_change = int(ask_change)
        
    print('당신은 ', 연인,' 과 함께', 장소, '에 가기로 결정하였습니다.')
        
    if sex == 2:
        if match == 1 : # 남자1이 선호하는 여성스타일과 옷에 대한 점수계산
            if cloth <= 4: # 키가 큰 여성은 좋아하지 않음
                score1()
            elif cloth <=6: # 중간정도 선호
                score2()
            else : # 선호
                score3()
        if match == 2 : # 남2이 선호하는 여성스타일과 옷에 대한 점수계산
            if cloth >= 5: # 키가 작은 여성은 선호하지 않음
                score1()
            elif cloth >= 3: # 선호
                score3()
            else :# 중간선호match
                score2()
        if match == 3 : # 남자3이 선호하는 여성스타일과 옷에 대한 점수계산
            if cloth == 4: # 선호
                score3()
            elif cloth == 1 :
                score3()
            elif cloth >=7:
                score3()
            elif cloth ==2: # 중간
                score2()
            elif cloth ==5:
                score2()
            else :
                score1()

    if sex == 1:
        if match == 1 : # 여1이 선호하는 남성스타일과 옷에 대한 점수계산
            if cloth ==12:
                score3()
            elif cloth == 16:
                score3()
            elif cloth == 11: # 중간정도 선호
                score2()
            elif cloth <= 15:
                score2()
            else :
                score1()
        if match == 2 : # 여2이 선호하는 남성스타일과 옷에 대한 점수계산
            if cloth ==10: 
                score3()
            elif cloth == 14:
                score3()
            elif cloth == 11:
                score2()
            elif cloth == 15:
                score2()
            else :
                score1()
        if match == 3 : # 여3이 선호하는 남성스타일과 옷에 대한 점수계산
            if cloth ==9: 
                score3()
            elif cloth == 13:
                score3()
            elif cloth == 11:
                score2()
            elif cloth == 15:
                score2()
            else :
                score1()

    print('당신의 스타일에 대해 연인이 느끼는 만족도는',score,'점입니다.')

    def theater_scene():
        global final_pick
        global answer3_say
        global save
        global place_list
        global date_style
        global save_score
        global ask_change
        global save_scoresquence
        global wonder
        global wonder_scene
        global date_style
        global man_list
        global woman_list
        global answer1
        global answer2
        global answer3
        global answer1_say
        global answer2_say
        global score
        global final_pick
        global sex
        global height
        global weight
        global weight_set
        global height_set
        global body
        global name
        global place
        global match
        global save_relist
        global 장소
        global 연인
        global cloth
        global result_score
        print(date_style['place'], ' #1')
        answer1 = input('연인 : 무슨 영화를 볼래? 1.로맨스 2.공포 3.액션')
        while not isNumber_ThreeChoices(answer1):
            answer1 = input('연인 : 무슨 영화를 볼래?(1,2,3중에서만 선택해주세요) 1.로맨스 2.공포 3.액션')
        answer1 = int(answer1)
        if answer1 == 1:
            answer1_say = '로맨스'
        elif answer1 == 2 :
            answer1_say = '공포'
        elif answer1 == 3:
            answer1_say = '액션'
        print('당신 : 난,' , answer1_say, '영화가 보고싶어.' )
        print(date_style['place'], ' #2')
        answer2 = input('연인 : 무슨 맛 팝콘이 좋아? 1.사워크림 2.치즈 3.카라멜')
        while not isNumber_ThreeChoices(answer2):
            answer2 = input('연인 : 무슨 맛 팝콘이 좋아?(1,2,3중에서만 선택해주세요) 1.사워크림 2.치즈 3.카라멜')
        answer2 = int(answer2)
        if answer2 == 1:
            answer2_say = '사워크림'
        if answer2 == 2:
            answer2_say = '치즈'
        if answer2 == 3:
            answer2_say = '카라멜'
        print('당신 : 난', answer2_say,'맛이 좋아')
        print(date_style['place'], ' #3')
        answer3 = input('연인 : 이제 영화시작 15분 남았는데 들어가서 앉아있을까? 1.그래 2.5분만 있다가 들어가자 3.들어가도 10분동안 광고하잖아. 시간 딱 맞춰 들어가자.')
        while not isNumber_ThreeChoices(answer3):
            answer3 = input('연인 : 이제 영화시작 15분 남았는데 들어가서 앉아있을까?(1,2,3중 하나만 선택해주세요) 1.그래 2.5분만 있다가 들어가자 3.들어가도 10분동안 광고하잖아. 시간 딱 맞춰 들어가자.')
        answer3 = int(answer3)
        if answer3 == 1:
            answer3_say = '영화 시작 15분 전'
            print('당신 : 그래그래')
        if answer3 == 2:
            print('당신 : 조금만 더 있다 들어가자')
            answer3_say = '영화시작 5분 전'
        if answer3 == 3:
            print('당신 : 싫어. 안은 너무 답답해')
            answer3_say = '영화 시작 직전'
        save_score = [answer1_say,answer2_say,answer3_say]
        final_pick = [answer1,answer2,answer3]
        return 1

    def beach_scene():
        global final_pick
        global answer3_say
        global save
        global place_list
        global save_score
        global ask_change
        global save_scoresquence
        global wonder
        global wonder_scene
        global man_list
        global woman_list
        global answer1
        global answer2
        global save_relist
        global final_pick
        global answer3
        global answer1_say
        global answer2_say
        global score
        global date_style
        global sex
        global height
        global weight
        global weight_set
        global height_set
        global body
        global cloth
        global name
        global place
        global match
        global 장소
        global 연인
        global result_score
        
        print(date_style['place'], ' #1')
        answer1 = input('연인 : 해변은 어디로 갈까? 1.하와이 2.호주 3.귀찮아 그냥 제주도로 가자')
        while not isNumber_ThreeChoices(answer1):
            answer1 = input('연인 : 해변은 어디로 갈까?(1,2,3중에서만 선택해주세요) 1.하와이 2.호주 3.귀찮아 그냥 제주도로 가자')
        answer1 = int(answer1)
        if answer1 == 1:
            answer1_say = '하와이'
        elif answer1 == 2 :
            answer1_say = '호주'
        elif answer1 == 3:
            answer1_say = '제주도'
        print('당신 : 난,' , answer1_say, '로 가고싶어')
        print(date_style['place'], ' #2')
        answer2 = input('연인 : 숙소는 어디로 잡을까? 1.난 무조건 7성급 2.수영장이 딸린 팬션 3.게스트하우스')
        while not isNumber_ThreeChoices(answer2):
            answer2 = input('연인 : 숙소는 어디로 잡을까?(1,2,3중에서만 선택해주세요) 1.난 무조건 7성급 2.수영장이 딸린 팬션 3.게스트하우스')
        answer2 = int(answer2)
        if answer2 == 1:
            print('당신 : 당연히 호텔이지')
            answer2_say = '7성급 호텔'
        elif answer2 == 2 :
            print('당신 : 전망이 예쁜 팬션이 좋겠어')
            answer2_say = '수영장이 딸린 팬션'
        elif answer2 == 3:
            print('당신 : 게스트하우스에서 다양한 사람들을 만나면 재밌을 것 같아')
            answer2_say = '게스트하우스'
        print(date_style['place'], ' #3')
        answer3 = input('연인 : 무엇을 할까? 1.물놀이! 2.해변가에 앉아서 노래듣기 3.먹는게 최고야')
        while not isNumber_ThreeChoices(answer3):
            answer3 = input('연인 : 무엇을 할까?(1,2,3중에서만 선택해주세요) 1.물놀이! 2.해변가에 앉아서 노래듣기 3.먹는게 최고야')
        answer3 = int(answer3)
        if answer3 == 1:
            answer3_say = '물놀이'
            print('당신 : 바다에 갔으면 물놀이를 해야지!')
        elif answer3 == 2 :
            answer3_say = '해변가에 앉아서 음악감상'
            print('당신 : 모래사장에 앉아서 힐링하고 싶어')
        elif answer3 == 3:
            answer3_say = '레스토랑에서 식사'
            print('당신 : 그 옆 호텔 레스토랑이 미슐랭 3스타라던데....')
        save_score = [answer1_say,answer2_say,answer3_say]
        final_pick = [answer1,answer2,answer3]
        return 1
    
    def park_scene():
        global final_pick
        global answer3_say
        global save
        global place_list
        global save_score
        global ask_change
        global save_relist
        global save_scoresquence
        global wonder
        global wonder_scene
        global man_list
        global result_score
        global woman_list
        global final_pick
        global answer1
        global answer2
        global answer3
        global answer1_say
        global answer2_say
        global score
        global sex
        global height
        global weight
        global weight_set
        global height_set
        global body
        global date_style
        global cloth
        global name
        global place
        global match
        global 장소
        global 연인
        print(date_style['place'], ' #1')
        answer1 = input('연인 : 어디로 갈까? 1.애버랜드 2.롯데월드 3.디즈니랜드')
        while not isNumber_ThreeChoices(answer1):
            answer1 = input('연인 : 어디로 갈까?(1,2,3중에서만 선택해주세요) 1.애버랜드 2.롯데월드 3.디즈니랜드')
        answer1 = int(answer1)
        if answer1 == 1:
            answer1_say = '애버랜드'
        elif answer1 == 2 :
            answer1_say = '롯데월드'
        elif answer1 == 3:
            answer1_say = '미쿸 디즈니랜드'
        print('당신 : 난,' , answer1_say, '로 가고싶어')
        print(date_style['place'], ' #2')
        answer2 = input('연인 : 자유이용권인 어떻게 끊을까? 1.종일 2.야간개장 3.하루가지고 되니? 2박3일')
        while not isNumber_ThreeChoices(answer2):
            answer2 = input('연인 : 자유이용권인 어떻게 끊을까?(1,2,3중에서만 선택해주세요) 1.종일 2.야간개장 3.하루가지고 되니? 2박3일')
        answer2 = int(answer2)
        if answer2 == 1:
            answer2_say = '하루종일'
            print('당신 : 다 타려면 아침부터 가야지')
        elif answer2 == 2 :
            answer2_say = '밤 내내'
            print('당신 : 야간개장으로 가서 불꽃놀이도 보고오자')
        elif answer2 == 3:
            answer2_say ='2박3일'
            print('당신 : 주변에 숙소 잡고 2박 3일동안 놀자')
        print(date_style['place'], ' #3')
        answer3 = input('연인 : 무엇을 탈까? 1.롤러코스터 2.우주관람차 3.바이킹')
        while not isNumber_ThreeChoices(answer3):
            answer3 = input('연인 : 무엇을 탈까?(1,2,3중에서만 선택해주세요) 1.롤러코스터 2.우주관람차 3.바이킹')
        answer3 = int(answer3)
        if answer3 == 1:
            answer3_say = '롤러코스터'
            print('당신 : 이 롤러코스터가 우리나라 최장길이래')
        elif answer3 == 2 :
            answer3_say = '우주관람차'
            print('당신 : 우주관람차 꼭대기에서 아래를 내려다보는건 정말 예쁠 것 같아')
        elif answer3 == 3:
            answer3_say = '바이킹'
            print('당신 : 놀이동산에 와서 바이킹을 안타는 건 말이 안 되지')
        save_score = [answer1_say,answer2_say,answer3_say]
        final_pick = [answer1,answer2,answer3]
        return 1
    
    if save[0] == 1:
        if save[1] == 1:
            theater_scene()
            #선호도순서 : 132-321-123
            scene_score(0,1,3,2) 
            scene_score(1,3,2,1)
            scene_score(2,1,2,3)
            print('당신은', 연인,'과',save_score[1],'맛 팝콘을 사서',save_score[2],'에 영화관에 들어가',save_score[0],'영화를 봤습니다.')
            unsorted_reminiscence.append('당신은 ' + 연인 + '과 '+ save_score[1]+'맛 팝콘을 사서 ' + save_score[2]+'에 영화관에 들어가 ' + save_score[0]+ '영화를 봤습니다.')
        if save[1] == 2:
            beach_scene()
            #선호도순서 : 132-231-312
            scene_score(0,1,3,2)
            scene_score(1,2,3,1)
            scene_score(2,3,1,2)
            print('당신은', 연인,'과',save_score[0],'에 있는 해변가에 가',save_score[2],'을 하고',save_score[1],'에서 밤을 보냈습니다')
            unsorted_reminiscence.append('당신은 '+ 연인 +'과 '+ save_score[0] +'에 있는 해변가에 가 '+ save_score[2]+'을 하고 '+ save_score[1] +'에서 밤을 보냈습니다')
        if save[1] == 3:
            park_scene()
            #선호도순서 : 213-213-231
            scene_score(0,2,1,3)
            scene_score(1,2,1,3)
            scene_score(2,2,3,1)
            print('당신은', 연인,'과',save_score[0],'에 가',save_score[2],'등을 타며',save_score[1],'놀았습니다.')
            unsorted_reminiscence.append('당신은 ' + 연인 + '과 '+ save_score[0]+ '에 가 '+ save_score[2]+'등을 타며 '+ save_score[1] +'놀았습니다.')


    if save[0] == 2:
        if save[1] == 1:
            theater_scene()
            #선호도순서 : 321-213-213
            scene_score(0,3,2,1)
            scene_score(1,2,1,3)
            scene_score(2,2,1,3)
            print('당신은', 연인,'과',save_score[1],'맛 팝콘을 사서',save_score[2],'에 영화관에 들어가',save_score[0],'영화를 봤습니다.')
            unsorted_reminiscence.append('당신은 ' + 연인 + '과 '+ save_score[1]+'맛 팝콘을 사서 ' + save_score[2]+'에 영화관에 들어가 ' + save_score[0]+ '영화를 봤습니다.')
        if save[1] == 2:
            beach_scene()
            #선호도순서 : 123-123-213
            scene_score(0,1,2,3)
            scene_score(1,1,2,3)
            scene_score(2,2,1,3)
            print('당신은', 연인,'과',save_score[0],'에 있는 해변가에 가', save_score[2],'을 하고',save_score[1],'에서 밤을 보냈습니다')
            unsorted_reminiscence.append('당신은 '+ 연인 +'과 '+save_score[0] +'에 있는 해변가에 가 '+ save_score[2]+'을 하고 '+save_score[1]+'에서 밤을 보냈습니다')
        if save[1] == 3:
            park_scene()
            #선호도순서 : 312-321-213
            scene_score(0,3,1,2)
            scene_score(1,3,2,1)
            scene_score(2,2,1,3)
            print('당신은', 연인,'과',save_score[0],'에 가',save_score[2],'등을 타며',save_score[1],'놀았습니다.')
            unsorted_reminiscence.append('당신은 ' + 연인 + '과 '+ save_score[0]+ '에 가 '+ save_score[2]+'등을 타며 '+ save_score[1] +'놀았습니다.')

    if save[0] == 3:
        if save[1] == 1:
            theater_scene()
            #선호도순서 : 132-321-123
            scene_score(0,1,3,2)
            scene_score(1,3,2,1)
            scene_score(2,1,2,3)
            print('당신은', 연인,'과',save_score[1],'맛 팝콘을 사서',save_score[2],'에 영화관에 들어가',save_score[0],'영화를 봤습니다.')
            unsorted_reminiscence.append('당신은 ' + 연인 + '과 '+ save_score[1]+'맛 팝콘을 사서 ' + save_score[2]+'에 영화관에 들어가 ' + save_score[0]+ '영화를 봤습니다.')
        if save[1] == 2:
            beach_scene()
            #선호도순서 : 132-231-312
            scene_score(0,1,3,2)
            scene_score(1,2,3,1)
            scene_score(2,3,1,2)
            print('당신은', 연인,'과',save_score[0],'에 있는 해변가에 가',save_score[2],'을 하고',save_score[1],'에서 밤을 보냈습니다')
            unsorted_reminiscence.append('당신은 '+ 연인 +'과 '+save_score[0] +'에 있는 해변가에 가 '+save_score[2]+'을 하고 '+save_score[1]+'에서 밤을 보냈습니다')
        if save[1] == 3:
            park_scene()
            #선호도순서 : 213-213-231
            scene_score(0,2,1,3)
            scene_score(1,2,1,3)
            scene_score(2,2,3,1)
            print('당신은', 연인,'과',save_score[0],'에 가',save_score[2],'등을 타며',save_score[1],'놀았습니다.')
            unsorted_reminiscence.append('당신은 ' + 연인 + '과 '+ save_score[0]+ '에 가 '+save_score[2]+'등을 타며 '+ save_score[1] +'놀았습니다.')

    if save[0] == 4:
        if save[1] == 1:
            theater_scene()
            #선호도순서 : 312-123-123
            scene_score(0,3,1,2)
            scene_score(1,1,2,3)
            scene_score(2,1,2,3)
            print('당신은', 연인,'과',save_score[1],'맛 팝콘을 사서',save_score[2],'에 영화관에 들어가',save_score[0],'영화를 봤습니다.')
            unsorted_reminiscence.append('당신은 ' + 연인 + '과 '+ save_score[1]+'맛 팝콘을 사서 ' + save_score[2]+'에 영화관에 들어가 ' + save_score[0]+ '영화를 봤습니다.')
        if save[1] == 2:
            beach_scene()
            #선호도순서 : 123-123-213
            scene_score(0,1,2,3)
            scene_score(1,1,2,3)
            scene_score(2,2,1,3)
            print('당신은', 연인,'과',save_score[0],'에 있는 해변가에 가',save_score[2],'을 하고',save_score[1],'에서 밤을 보냈습니다')
            unsorted_reminiscence.append('당신은 '+ 연인 +'과 '+save_score[0] +'에 있는 해변가에 가 '+save_score[2]+'을 하고 '+save_score[1]+'에서 밤을 보냈습니다')
        if save[1] == 3:
            park_scene()
            #선호도순서 : 312-213-231
            scene_score(0,3,1,2)
            scene_score(1,2,1,3)
            scene_score(2,2,3,1)
            print('당신은', 연인,'과',save_score[0],'에 가',save_score[2],'등을 타며',save_score[1],'놀았습니다.')
            unsorted_reminiscence.append('당신은 ' + 연인 + '과 '+ save_score[0]+ '에 가 '+save_score[2]+'등을 타며 '+ save_score[1] +'놀았습니다.')

    if save[0] == 5:
        if save[1] == 1:
            theater_scene()
            #선호도순서 : 213-312-123
            scene_score(0,2,1,3)
            scene_score(1,3,1,2)
            scene_score(2,1,2,3)
            print('당신은', 연인,'과',save_score[1],'맛 팝콘을 사서',save_score[2],'에 영화관에 들어가',save_score[0],'영화를 봤습니다.')
            unsorted_reminiscence.append('당신은 ' + 연인 + '과 '+ save_score[1]+'맛 팝콘을 사서 ' + save_score[2]+'에 영화관에 들어가 '+ save_score[0]+ '영화를 봤습니다.')
        if save[1] == 2:
            beach_scene()
            #선호도순서 : 231-321-132
            scene_score(0,2,3,1)
            scene_score(1,3,2,1)
            scene_score(2,1,3,2)
            print('당신은 ', 연인,'과',save_score[0],'에 있는 해변가에 가 ',save_score[2],'을 하고',save_score[1],'에서 밤을 보냈습니다')
            unsorted_reminiscence.append('당신은 '+ 연인 +'과 '+save_score[0] +'에 있는 해변가에 가 '+save_score[2]+'을 하고 '+save_score[1]+'에서 밤을 보냈습니다')
        if save[1] == 3:
            park_scene()
            #선호도순서 : 213-321-123
            scene_score(0,2,1,3)
            scene_score(1,3,2,1)
            scene_score(2,1,2,3)
            print('당신은 ', 연인,'과',save_score[0],'에 가 ',save_score[2],'등을 타며',save_score[1],'놀았습니다.')
            unsorted_reminiscence.append('당신은 ' + 연인 + '과 '+ save_score[0]+ '에 가 '+save_score[2]+'등을 타며 '+ save_score[1] +'놀았습니다.')

    if save[0] == 6:
        if save[1] == 1:
            theater_scene()
            #a의 선호도순서 : 321-123-321
            scene_score(0,3,2,1)
            scene_score(1,1,2,3)
            scene_score(2,3,2,1)
            print('당신은 ', 연인,'과',save_score[1],'맛 팝콘을 사서 ',save_score[2],'에 영화관에 들어가',save_score[0],'영화를 봤습니다.')
            unsorted_reminiscence.append('당신은 ' + 연인 + '과 '+ save_score[1]+'맛 팝콘을 사서 ' + save_score[2]+'에 영화관에 들어가 ' + save_score[0]+ '영화를 봤습니다.')
        if save[1] == 2:
            beach_scene()
            #선호도순서 : 213-213-231
            scene_score(0,2,1,3)
            scene_score(1,2,1,3)
            scene_score(2,2,3,1)
            print('당신은 ', 연인,'과',save_score[0],'에 있는 해변가에 가 ',save_score[2],'을 하고',save_score[1],'에서 밤을 보냈습니다')
            unsorted_reminiscence.append('당신은 '+ 연인 +'과 '+save_score[0] +'에 있는 해변가에 가 '+save_score[2]+'을 하고 '+save_score[1]+'에서 밤을 보냈습니다')
        if save[1] == 3:
            park_scene()
            #선호도순서 : 123-213-132
            scene_score(0,1,2,3)
            scene_score(1,2,1,3)
            scene_score(2,1,3,2)
            print('당신은 ', 연인,'과',save_score[0],'에 가 ',save_score[2],'등을 타며',save_score[1],'놀았습니다.')
            unsorted_reminiscence.append('당신은 ' + 연인 + '과 '+ save_score[0]+ '에 가 '+save_score[2]+'등을 타며 '+ save_score[1] +'놀았습니다.')
    
    print('당신과',연인,'은 데이트를 마치고 집에 돌아갔습니다. 당신은 두근거리는 마음으로',연인,'의 연락을 기다립니다. 과연 당신의 데이트는 성공적이었을까요?')  
    
    save_scoresquence['score_answer1'] = save_relist[0]
    save_scoresquence['score_answer2'] = save_relist[1]
    save_scoresquence['score_answer3'] = save_relist[2]

    def score_wonder():
        global save_scoresquence
        global wonder_scene
        global wonder
        wonder = input('당신이 연인에게 각 scene에서 몇점을 받았는지 궁금하나요? 1.yes 2.no')
        while not isNumber_TwoChoices(wonder):
            wonder = input('당신이 연인에게 각 scene에서 몇점을 받았는지 궁금하나요?(1,2중 하나만 선택해주세요) 1.yes 2.no')
        wonder = int(wonder)
        while wonder != 2:
            if wonder == 1:
                wonder_scene = input('몇번째 씬의 점수를 알고싶나요? 1.#1 2.#2 3.#3')
                while not isNumber_ThreeChoices(wonder_scene):
                    wonder_scene = input('몇번째 씬의 점수를 알고싶나요?(1,2,3중에서만 선택해주세요) 1.#1 2.#2 3.#3')
                wonder_scene = int(wonder_scene)
            if wonder_scene == 1:
                print('#',wonder_scene,'에서 당신의 연인은 당신에게',save_scoresquence['score_answer1'],'점만큼 만족하였습니다.')
            if wonder_scene == 2:
                print('#',wonder_scene,'에서 당신의 연인은 당신에게',save_scoresquence['score_answer2'],'점만큼 만족하였습니다.')
            if wonder_scene == 3:
                print('#',wonder_scene,'에서 당신의 연인은 당신에게',save_scoresquence['score_answer3'],'점만큼 만족하였습니다.')
            wonder = input('다른 scene의 점수도 보시겠습니까? 1.yes 2.no')
            while not isNumber_TwoChoices(wonder):
                wonder = input('다른 scene의 점수도 보시겠습니까?(1,2중에서만 선택해주세요) 1.yes 2.no')
            wonder = int(wonder)
        return 1

    if score>=9:
        print('며칠 뒤', 연인,'에게서 카톡이 왔습니다.')
        print(연인, ':', name,'씨, 우리 사귈래요?' )
        print('당신의 최종 점수는', score,'입니다.')
        print('데이트 성공!')
        score_wonder()
    
    elif score>=5:
        print('며칠 뒤', 연인,'에게서 카톡이 왔습니다.')
        print(연인, ':', name,'씨, 혹시 내일 시간되요?' )
        print('당신의 최종 점수는', score,'입니다.')
        print('데이트 반은?성공!')
        score_wonder()
    else :
        print('며칠 뒤', 연인,'에게서 카톡이 왔습니다.')
        print(연인, ':', name,'씨, 우리 이제 그만만나요.' )
        print('당신의 최종 점수는', score,'입니다.')
        print('데이트 실패!')
        score_wonder()

    return 1

cnt = 0
l = input('데이트를 수락하시겠습니까? 1.yes 2.no')
while not isNumber_TwoChoices(l):
    l = input('데이트를 수락하시겠습니까?(1 또는 2만 입력해주세요) 1.yes 2.no')
l = int(l)
while l != 2:
    if l == 1:   
        cnt = cnt +1
        start()
        top_score(cnt)
        l = input('한번 더 데이트를 가시겠습니까? 1.yes 2.no')
        while not isNumber_TwoChoices(l):
            l = input('한번 더 데이트를 가시겠습니까?(1또는 2만 입력해주세요) 1.yes 2.no')
        l = int(l)
    else:
        l = input('한번 더 데이트를 가시겠습니까?(1또는 2만 입력해주세요) 1.yes 2.no')
        while not isNumber_TwoChoices(l):
            l = input('한번 더 데이트를 가시겠습니까?(1또는 2만 입력해주세요) 1.yes 2.no')
        l = int(l)

if l == 2:
    if cnt == 0:
        print('데이트 기회를 날린 당신은 평생 솔로가 되었습니다.')
    else :
        for i in range(1,cnt+1,1):
            unsorted_score.append(result_score['{0}번째 데이트의 점수'.format(i)])
        for x in range(1,cnt+1,1):
            for y in range(0,x-1,1):
                if unsorted_score[y] > unsorted_score[y+1]:
                    TMP = unsorted_score[y]
                    unsorted_score[y] = unsorted_score[y+1]
                    unsorted_score[y+1] = TMP
        sorted_score = unsorted_score
        
        print('당신은 총', cnt,'번의 데이트를 했습니다.')
        if cnt == 1:
            print('당신은 한번의 데이트에서', score, '점을 받았습니다.')
            reminiscence = input('회상하시겠습니까? 1.yes 2.no')
            while not isNumber_TwoChoices(reminiscence):
                reminiscence = input('회상하시겠습니까?(1 또는 2만 입력해주세요) 1.yes 2.no')
                reminiscence = int(reminiscence)
            if reminiscence == 1:
                print(unsorted_reminiscence[0])        
        if cnt >= 2 :
        
            best_score = sorted_score[cnt-1]
            worst_score = sorted_score[0]
        
            sorted_score_reversed = []
            for f in range(0,cnt,1):
                sorted_score_reversed.append(sorted_score[cnt-1-f])

            def draw():
                global cnt
                turtle.showturtle()
                turtle.goto(0,0)
                turtle.pendown()
                turtle.goto(0,150)
                turtle.goto(0,0)
                turtle.setheading(90)
                for i in range(1,13,1):
                    turtle.goto(0,i*10)
                    turtle.pendown()
                    turtle.setheading(180)
                    turtle.forward(10)
                    turtle.penup()
                turtle.penup()
                for i in range (1, cnt+1, 1):
                    turtle.pendown()
                    turtle.setheading(0)
                    turtle.forward(10)
                    turtle.setheading(90)
                    turtle.forward(10)
                    turtle.penup()
                    turtle.goto(i*10,0)
                turtle.penup()
                turtle.goto(0,0)
                turtle.pendown()
                turtle.setheading(0)
                turtle.forward(10)
                turtle.setheading(90)
                turtle.forward(10)
                turtle.penup()
                for i in range(1,cnt+1,1):
                    turtle.goto(i*10,10*result_score['{0}번째 데이트의 점수'.format(i)])
                    turtle.pendown()
                    turtle.dot(0.5*10,'red')                 
                    
                turtle.penup()
                turtle.goto(-30,150)
                turtle.pendown()
                turtle.write('score')
                turtle.penup()
                turtle.goto(10*(cnt+1),-30)
                turtle.pendown()
                turtle.write('데이트 순서')
                turtle.penup()
        
            draw()
        
        print('당신의 총',cnt,'번의 데이트 중 최고점은', best_score, '입니다.')

        print('당신의 총',cnt,'번의 데이트 중 최저점은', worst_score, '입니다.')

        ask = input('각각의 데이트에서 받은 점수가 궁금하십니까? 1.yes 2.no')
        while not isNumber_TwoChoices(ask):
            ask = input('각각의 데이트에서 받은 점수가 궁금하십니까?(1 또는 2만 입력해주세요) 1.yes 2.no')
        ask = int(ask)
        while ask != 2:
            ask_squence_date = input('몇 번째 데이트의 점수가 궁금하십니까? : ')
            while not isNumber_count(ask_squence_date):
                ask_squence_date = input('몇 번째 데이트의 점수가 궁급하십니까? (데이트 횟수 이하의 자연수만 입력해주세요) : ')
            ask_squence_date = int(ask_squence_date)
            print('당신의',ask_squence_date,'번째 데이트의 점수는', result_score['{0}번째 데이트의 점수'.format(ask_squence_date)], '입니다.')
            ask = input('다른 데이트의 점수도 궁금하십니까? 1.yes 2.no')
            while not isNumber_TwoChoices(ask):
                ask = input('다른 데이트의 점수도 궁금하십니까?(1 또는 2만 입력해주세요) 1.yes 2.no')
            ask = int(ask)
        reminiscence = input('당신의 데이트를 회상하시겠습니까? 1.yes 2.no')
        while not isNumber_TwoChoices(reminiscence):
            reminiscence = input('당신의 데이트를 회상하시겠습니까?(1또는 2만 입력해주세요) 1.yes 2.no')
        reminiscence = int(reminiscence)

        while reminiscence !=2:
            reminiscence_num = input('몇 번째 데이트를 기억하고 싶나요? : ')
            while not isNumber_count(reminiscence_num):
                reminiscence_num = input('몇 번째 데이트를 기억하고 싶나요? (데이트 횟수 이하의 자연수만 입력해주세요): ')
            reminiscence_num = int(reminiscence_num)
            print(reminiscence_num,'번째의 데이트에서', unsorted_reminiscence[reminiscence_num - 1])
            reminiscence = input('다른 데이트를 회상하시겠습니까? 1.yes 2.no')
            while not isNumber_TwoChoices(reminiscence):
                reminiscence = input('다른 데이트를 회상하시겠습니까?(1또는 2만 입력해주세요) 1.yes 2.no')
            reminiscence = int(reminiscence)

        print('어쨋든 당신은 솔로가 되었습니다.')
        
        
        
