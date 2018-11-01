e = open("1.txt","r")
str = e.read()
e.close()
a = b = 0
for i in str:
    if 'A' <= i <= 'Z':
        a += 1
    elif 'a' <= i <= 'z':
        b += 1
list1 = list(str)
c =len(str)-1
list2 = []
for i in list1:
    if not i in list2:
        list2.append(i)
str2="".join(list2)
d=0
di={}
while d <= c:
    di[d]=str[d]
    d=d+1
print(str2)
print (di)
print("有{0}个大写字母".format(a))
print("有{0}个小写字母".format(b))
