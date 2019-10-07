# Swift语言学习问题笔记

#### 1.整数类型和字符类型的转换

Int转Character：

Character类没有以Int作为参数的初始化方法，但Character能通过UnicodeScalar类型来初始化，而UnicodeScalar类型又能通过Int类型来初始化。

```swift
//Int转Character代码
//randomNumber是一个介于65~90的整数
var randomNumber = 65 + arc4random() % 26
//转换成randomCharacter，是一个介于A~Z的字符
var randomCharacter = Character( UnicodeScalar(randomNumber)！)
```

Character转Int：

相比之下，Character转Int稍微复杂，没有任何现成的函数可用。只能把Character变量转为String类型，再利用循环取出String里面的唯一一个字符的Unicode编码，最后转为整数。

```swift
//Character转Int代码
//characterB是一个Character变量
var characterB:Character = "B"
//numberFromB用于接收转换后的整数，先暂时初始化为0
var numberFromB = 0
//使用for-in循环遍历转化成String的“B”
for scalar in String(characterB).unicodeScalars
{
    //字符串只有一个字符，这个循环只会执行1次
    numberFromB = Int(scalar.value)
}
//最后得到numberFromB=66
```

但是如果需要频繁将Character转成Int，上述代码使用起来未免太麻烦。一个比较好的做法是把上述运算写成Character类型的一个扩展方法，方便以后直接调用。

```swift
//Character扩展代码
extension Character
{
    func toInt() -> Int
    {
        var intFromCharacter:Int = 0
        for scalar in String(self).unicodeScalars
        {
            intFromCharacter = Int(scalar.value)
        }
        return intFromCharacter
    }
}
 
//以后可以直接对Character变量调用toInt()方法
var characterB:Character = "B"
var numberFromB = characterB.toInt()
//这样就得到numberFromB=66
```

