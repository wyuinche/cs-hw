import math
class Circle:
    def __init__(self):
        self.radius = input('원의 반지름을 입력하세요.')
        self.radius = float(self.radius)

    def printarea(self):
        return self.radius * math.pi * 2

    def printlen(self):
        return(self.radius*self.radius)* math.pi

my_circle = Circle()

print('둘레 :', my_circle.printarea() )
print('넓이 :', my_circle.printlen())
        
