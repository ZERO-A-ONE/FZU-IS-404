import itertools
pm =['A','2','3','4','5','6','7','8','9','10','J','Q','K']
flower = ['diamond','club','spades','hearts']
list1 =[]
for x in pm:
    for i in flower:
        ltup = (x,i)
        list1.append(ltup)
print(list1)

