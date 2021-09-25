class BMICalculator:
    def __init__(self):
        self.height = input('키를 입력 하세요')
        self.height = float(self.height)/100
        self.weight = input('몸무게를 입력 하세요')
        self.weight = float(self.weight)
    def getBMI(self):
        BMI = (self.weight / (self.height*self.height))
        return BMI
    def BMICalculate(self):
        if (self.weight / (self.height*self.height)) < 18.5:
            return '저체중'
        elif (self.weight / (self.height*self.height)) < 23:
            return '정상'
        elif (self.weight / (self.height*self.height)) < 25:
            return '과체중'
        elif (self.weight / (self.height*self.height))< 30:
            return '비만'
        else:
            return '고도비만'
        
my_BMI = BMICalculator()

print('BMI is ', my_BMI.getBMI())
print(my_BMI.BMICalculate())
