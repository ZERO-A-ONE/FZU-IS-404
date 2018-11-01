class Human:
    def __init__(self,sex,height):
        self.sex=sex
        self.height=height
class Sutdent(Human):
    def __init__(self,sex,height,Class,Grade):
        Human.sex = sex
        Human.height = height
        self.Class=Class
        self.Grade=Grade
    def set(self, name):
        self.name = name
    def get(self):
        return self.name
Tony=Sutdent('man','90','1','2018')
Tony.set('Toq')
print(Tony.get())

