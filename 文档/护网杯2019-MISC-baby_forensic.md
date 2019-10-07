# 护网杯2019-MISC-baby_forensic

这是一题以内存取证为主题，包含着密码学和USB流量分析的杂项题，还是很有趣的，首先我们拿到了一个名为**data.vmem**的内存文件，可以知道这就是内存取证的题目

## 内存取证

我们需要使用到一个叫做**volatility**的内存取证神器

**Volatility**是开源的**Windows**，**Linux**，**macOS**，**Android**的内存取证分析工具，由**Python**编写成，命令行操作，支持各种操作系统

### 使用Volatility

判断镜像信息，获取操作系统类型

```shell
volatility -f ?.img/raw/... imageinfo
```

知道操作系统类型后，用`--profile`指定

```shell
volatility -f ?.img --profile=...
```

查看当前显示的notepad文本

```shell
volatility  -f file.raw --profile=WinXPSP2x86 notepad
```

查看当前运行的进程

```shell
volatility  -f file.raw --profile=WinXPSP2x86 psscan/pslist
```

扫描所有的文件列表(常常结合grep)

```shell
volatility  -f file.raw --profile=WinXPSP2x86 filescan
```

常常配合的grep为

```shell
| grep "doc\|docx\|rtf" //查看文档
```

```shell
| grep "jpg\|jpeg\|png\|tif\|gif\|bmp"//查看图片
```

```shell
| grep "Desktop"//查看桌面
```

根据offset提取出文件

```shell
volatility  -f file.raw --profile=WinXPSP2x86 dumpfiles -D . -Q 0x.....
```

扫描 Windows 的服务

```shell
volatility -f file.raw --profile=WinXPSP2x86 svcscan
```

查看网络连接

```shell
volatility -f file.raw --profile=WinXPSP2x86 connscan
```

查看命令行上的操作

```shell
volatility -f file.raw --profile=WinXPSP2x86 cmdscan
```

根据pid dump出相应的进程

```shell
volatility -f easy_dump.img --profile=Win7SP1x64 memdump -p 2580 -D 目录
```

查看截图

```shell
volatility -f mem.data --profile=Win7SP1x64 screenshot --dump-dir=.
```

获取 IE 浏览器的使用情况

```shell
volatility -f mem.vmem –profile=WinXPSP2x86 iehistory 
```

列举缓存在内存的注册表

```shell
volatility -f mem.vmem –profile=WinXPSP2x86 hivelist
```

打印出注册表中的数据

```shell
volatility -f mem.vmem –profile=WinXPSP2x86 hivedump -o 注册表的 virtual 地址
```

获取SAM表中的用户

```shell
volatility -f mem.vmem –profile=WinXPSP2x86 printkey -K “SAM\Domains\Account\Users\Names”
```

获取最后登录系统的账户

```shell
volatility -f mem.vmem –profile=WinXPSP2x86 printkey -K “SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon” 
```

提取出内存中记录的 当时正在运行的程序有哪些，运行过多少次，最后一次运行的时间等信息 

```shell
volatility -f mem.vmem –profile=WinXPSP2x86 userassist
```

### 取证

#### 获取镜像信息

```shell
Volatility Foundation Volatility Framework 2.6
INFO    : volatility.debug    : Determining profile based on KDBG search...
          Suggested Profile(s) : WinXPSP2x86, WinXPSP3x86 (Instantiated with WinXPSP2x86)
                     AS Layer1 : IA32PagedMemoryPae (Kernel AS)
                     AS Layer2 : FileAddressSpace (/root/文档/baby_forensic/data.vmem)
                      PAE type : PAE
                           DTB : 0xb18000L
                          KDBG : 0x80546ae0L
          Number of Processors : 1
     Image Type (Service Pack) : 3
                KPCR for CPU 0 : 0xffdff000L
             KUSER_SHARED_DATA : 0xffdf0000L
           Image date and time : 2019-09-04 14:28:47 UTC+0000
     Image local date and time : 2019-09-04 22:28:47 +0800
```

可以知道这个镜像是WindowsXP的内存镜像我们接下来继续取证

#### 搜索进程

首先我们要看一下出题人在镜像里干了什么

```shell
Offset(V)  Name                    PID   PPID   Thds     Hnds   Sess  Wow64 Start                          Exit                          
---------- -------------------- ------ ------ ------ -------- ------ ------ ------------------------------ ------------------------------
0x817bd830 System                    4      0     58      173 ------      0                                                              
0x8163eb88 smss.exe                372      4      3       19 ------      0 2019-09-04 14:27:46 UTC+0000                                 
0x814229d8 csrss.exe               460    372     10      400      0      0 2019-09-04 14:27:46 UTC+0000                                 
0x813c1020 winlogon.exe            484    372     24      462      0      0 2019-09-04 14:27:46 UTC+0000                                 
0x81560020 services.exe            668    484     16      270      0      0 2019-09-04 14:27:46 UTC+0000                                 
0x812b7cd0 lsass.exe               680    484     25      359      0      0 2019-09-04 14:27:46 UTC+0000                                 
0x816c8cc8 vmacthlp.exe            836    668      1       25      0      0 2019-09-04 14:27:46 UTC+0000                                 
0x81333b38 svchost.exe             848    668     21      201      0      0 2019-09-04 14:27:46 UTC+0000                                 
0x812fa020 svchost.exe             932    668     11      263      0      0 2019-09-04 14:27:47 UTC+0000                                 
0x80ed83c0 svchost.exe            1028    668     71     1193      0      0 2019-09-04 14:27:47 UTC+0000                                 
0x81559020 svchost.exe            1072    668      5       59      0      0 2019-09-04 14:27:47 UTC+0000                                 
0x81330020 svchost.exe            1116    668     15      201      0      0 2019-09-04 14:27:47 UTC+0000                                 
0x81433420 explorer.exe           1428   1392     15      370      0      0 2019-09-04 14:27:48 UTC+0000                                 
0x81323c20 spoolsv.exe            1564    668     15      138      0      0 2019-09-04 14:27:48 UTC+0000                                 
0x815f2020 svchost.exe            1976    668      5       88      0      0 2019-09-04 14:28:05 UTC+0000                                 
0x815f1da0 VGAuthService.e         188    668      2       60      0      0 2019-09-04 14:28:05 UTC+0000                                 
0x81542da0 vmtoolsd.exe            256    668      9      266      0      0 2019-09-04 14:28:05 UTC+0000                                 
0x80e848b0 wmiprvse.exe            988    848      9      190      0      0 2019-09-04 14:28:13 UTC+0000                                 
0x80e81020 alg.exe                1172    668      7      110      0      0 2019-09-04 14:28:14 UTC+0000                                 
0x81534020 rundll32.exe           1220   1428      4       78      0      0 2019-09-04 14:28:14 UTC+0000                                 
0x815ddda0 vmtoolsd.exe           1660   1428      7      175      0      0 2019-09-04 14:28:14 UTC+0000                                 
0x80e7b020 ctfmon.exe             1668   1428      1       71      0      0 2019-09-04 14:28:14 UTC+0000                                 
0x80eaab78 wscntfy.exe            1088   1028      1       39      0      0 2019-09-04 14:28:15 UTC+0000                                 
0x81528090 cmd.exe                1636   1428      1       34      0      0 2019-09-04 14:28:34 UTC+0000                                 
0x815258b0 conime.exe             1676   1636      1       38      0      0 2019-09-04 14:28:34 UTC+0000                                 
0x80ea56a8 wordpad.exe            1448   1428      4      113      0      0 2019-09-04 14:28:42 UTC+0000                                 
```

可以看到这里有两个值得关注的应用程序进程,分别是**wordpad.exe**、**cmd.exe**，但是我们还是没法得出出题人到底在干嘛，我们进行下一步

#### 查看截图

![](https://github-1251836300.cos.ap-guangzhou.myqcloud.com/%E6%8A%A4%E7%BD%91%E6%9D%AF2019-MISC-baby_forensic/session_0.WinSta0.Default.png)

好像还是不知道在干什么，只可以知道大概是开启了一个**cmd**，然后启动了一个类似**wireshark**的程序，也许正在抓包

#### 查看CMD命令

```shell
**************************************************
CommandProcess: csrss.exe Pid: 460
CommandHistory: 0x36e3850 Application: cmd.exe Flags: Allocated, Reset
CommandCount: 1 LastAdded: 0 LastDisplayed: 0
FirstCommand: 0 CommandCountMax: 50
ProcessHandle: 0x5e0
Cmd #0 @ 0x55d868: hill_matrix 3,2,2,9,7,7,6,4,9
```

这里获得了一个重要的信息：**hill_matrix 3,2,2,9,7,7,6,4,9**

#### 查看可疑文件

查看文档：

```shell
0x000000000181c2c8      1      0 R--rwd \Device\HarddiskVolume1\WINDOWS\system32\shdocvw.dll
0x00000000019333d8      1      0 R--rw- \Device\HarddiskVolume1\WINDOWS\system32\mydocs.dll
0x0000000001a4c658      1      0 R--rwd \Device\HarddiskVolume1\WINDOWS\system32\shdocvw.dll
```

查看图片：

```shell
tures\Administrator.bmp
0x00000000017e02d0      1      0 R--rwd \Device\HarddiskVolume1\WINDOWS\system32\wlnotify.dll
0x0000000001a44f28      1      0 R--rwd \Device\HarddiskVolume1\WINDOWS\Web\Wallpaper\Bliss.bmp
0x0000000001aa0868      1      0 R--rwd \Device\HarddiskVolume1\WINDOWS\system32\wlnotify.dll
```

查看桌面：

```shell
0x00000000012d8ef8      1      0 R--r-- \Device\HarddiskVolume1\Documents and Settings\Administrator\桌面\disk.zip
0x00000000017e1f90      1      0 R--rwd \Device\HarddiskVolume1\Documents and Settings\All Users\「开始」菜单\程序\附件\远程桌面连接.lnk
0x000000000186f6a8      3      1 R--rwd \Device\HarddiskVolume1\Documents and Settings\All Users\桌面
0x000000000186f740      3      1 R--rwd \Device\HarddiskVolume1\Documents and Settings\Administrator\桌面
```

可以发现桌面上存在着一个**disk.zip**，我们把它**dump**出来解压可以得到一个**disk.img**文件，解压我们可以直接得到一个流量抓包文件**usb.pcapng**，这样子验证了我们的猜想，当时的确是再用**wireshark**抓包，且还可知这是一个**USB**协议流量包

## USB流量分析

把拿到的**usb.pcapng**文件拖进wireshark分析

![](https://github-1251836300.cos.ap-guangzhou.myqcloud.com/%E6%8A%A4%E7%BD%91%E6%9D%AF2019-MISC-baby_forensic/QQ%E6%88%AA%E5%9B%BE20190910153112.png)

可以知道这的确是个USB流量，开始前，我们先介绍一些USB的基础知识。USB有不同的规格，以下是使用USB的三种方式：**USB UART、USB HID、USB Memory**

UART或者Universal Asynchronous Receiver/Transmitter。这种方式下，设备只是简单的将USB用于接受和发射数据，除此之外就再没有其他通讯功能了。

HID是人性化的接口。这一类通讯适用于交互式，有这种功能的设备有：键盘，鼠标，游戏手柄和数字显示设备。

最后是USB Memory，或者说是数据存储。External HDD, thumb drive / flash drive,等都是这一类的。

其中使用的最广的不是USB HID 就是USB Memory了。

每一个USB设备（尤其是HID或者Memory）都有一个供应商ID（Vendor Id）和产品识别码（Product Id）。Vendor Id是用来标记哪个厂商生产了这个USB设备。Product Id用来标记不同的产品，他并不是一个特殊的数字，当然最好不同

我们分析可以知道，USB协议的数据部分在Leftover Capture Data域之中，在Mac和Linux下可以用tshark命令可以将 leftover capture data单独提取出来，命令如下：

```shell
tshark -r example.pcap -T fields -e usb.capdata //如果想导入usbdata.txt文件中，后面加上参数：>usbdata.txt
```

USB数据包长度为八个字节，这里我们只关注USB流量中的键盘流量和鼠标流量

键盘数据包的数据长度为**8**个字节，击键信息集中在第**3**个字节，每次**key stroke**都会产生一个**keyboard event usb packet**

鼠标数据包的数据长度为**4**个字节，第**一**个字节代表**按键**，当取**0x00**时，代表**没有按键**、为**0x01**时，代表按**左键**，为**0x02**时，代表当前按键为**右键**。第二个字节可以看成是一个**signed   byte**类型，其最高位为符号位，当这个值为**正**时，代表鼠标**水平右移**多少像素，为**负**时，代表**水平左移**多少像素。第三个字节与第二字节类似，代表**垂直上下移动**的偏移

> usb keyboard的映射表 根据这个映射表将第三个字节取出来，对应对照表得到解码
>
> ![](https://github-1251836300.cos.ap-guangzhou.myqcloud.com/%E6%8A%A4%E7%BD%91%E6%9D%AF2019-MISC-baby_forensic/1100338-20180814105104990-181933183.png)

#### 键盘流量分析

我们可以写出脚本：

```python
mappings = { 0x04:"A",  0x05:"B",  0x06:"C", 0x07:"D", 0x08:"E", 0x09:"F", 0x0A:"G",  0x0B:"H", 0x0C:"I",  0x0D:"J", 0x0E:"K", 0x0F:"L", 0x10:"M", 0x11:"N",0x12:"O",  0x13:"P", 0x14:"Q", 0x15:"R", 0x16:"S", 0x17:"T", 0x18:"U",0x19:"V", 0x1A:"W", 0x1B:"X", 0x1C:"Y", 0x1D:"Z", 0x1E:"1", 0x1F:"2", 0x20:"3", 0x21:"4", 0x22:"5",  0x23:"6", 0x24:"7", 0x25:"8", 0x26:"9", 0x27:"0", 0x28:"n", 0x2a:"[DEL]",  0X2B:"    ", 0x2C:" ",  0x2D:"-", 0x2E:"=", 0x2F:"[",  0x30:"]",  0x31:"\\", 0x32:"~", 0x33:";",  0x34:"'", 0x36:",",  0x37:"." }
nums = []
keys = open('usbdata.txt')
for line in keys:
    if line[0]!='0' or line[1]!='0' or line[3]!='0' or line[4]!='0' or line[9]!='0' or line[10]!='0' or line[12]!='0' or line[13]!='0' or line[15]!='0' or line[16]!='0' or line[18]!='0' or line[19]!='0' or line[21]!='0' or line[22]!='0':
         continue
    nums.append(int(line[6:8],16))
    # 00:00:xx:....
keys.close()
output = ""
for n in nums:
    if n == 0 :
        continue
    if n in mappings:
        output += mappings[n]
    else:
        output += '[unknown]'
print('output :n' + output)
```

如果直接从dat文件开始分析则脚本为：

```python
#!/usr/bin/env python
import sys
import os
DataFileName = "usb.dat"
presses = []
normalKeys = {"04":"a", "05":"b", "06":"c", "07":"d", "08":"e", "09":"f", "0a":"g", "0b":"h", "0c":"i", "0d":"j", "0e":"k", "0f":"l", "10":"m", "11":"n", "12":"o", "13":"p", "14":"q", "15":"r", "16":"s", "17":"t", "18":"u", "19":"v", "1a":"w", "1b":"x", "1c":"y", "1d":"z","1e":"1", "1f":"2", "20":"3", "21":"4", "22":"5", "23":"6","24":"7","25":"8","26":"9","27":"0","28":"<RET>","29":"<ESC>","2a":"<DEL>", "2b":"\t","2c":"<SPACE>","2d":"-","2e":"=","2f":"[","30":"]","31":"\\","32":"<NON>","33":";","34":"'","35":"<GA>","36":",","37":".","38":"/","39":"<CAP>","3a":"<F1>","3b":"<F2>", "3c":"<F3>","3d":"<F4>","3e":"<F5>","3f":"<F6>","40":"<F7>","41":"<F8>","42":"<F9>","43":"<F10>","44":"<F11>","45":"<F12>"}
shiftKeys = {"04":"A", "05":"B", "06":"C", "07":"D", "08":"E", "09":"F", "0a":"G", "0b":"H", "0c":"I", "0d":"J", "0e":"K", "0f":"L", "10":"M", "11":"N", "12":"O", "13":"P", "14":"Q", "15":"R", "16":"S", "17":"T", "18":"U", "19":"V", "1a":"W", "1b":"X", "1c":"Y", "1d":"Z","1e":"!", "1f":"@", "20":"#", "21":"$", "22":"%", "23":"^","24":"&","25":"*","26":"(","27":")","28":"<RET>","29":"<ESC>","2a":"<DEL>", "2b":"\t","2c":"<SPACE>","2d":"_","2e":"+","2f":"{","30":"}","31":"|","32":"<NON>","33":"\"","34":":","35":"<GA>","36":"<","37":">","38":"?","39":"<CAP>","3a":"<F1>","3b":"<F2>", "3c":"<F3>","3d":"<F4>","3e":"<F5>","3f":"<F6>","40":"<F7>","41":"<F8>","42":"<F9>","43":"<F10>","44":"<F11>","45":"<F12>"}
def main():
    # check argv
    if len(sys.argv) != 2:
        print "Usage : "
        print "        python UsbKeyboardHacker.py data.pcap"
        print "Tips : "
        print "        To use this python script , you must install the tshark first."
        print "        You can use `sudo apt-get install tshark` to install it"
        print "Author : "
        print "        Angel_Kitty <angelkitty6698@gmail.com>"
        print "        If you have any questions , please contact me by email."
        print "        Thank you for using."
        exit(1)
    # get argv
    pcapFilePath = sys.argv[1]
    # get data of pcap
    os.system("tshark -r %s -T fields -e usb.capdata > %s" % (pcapFilePath, DataFileName))
    # read data
    with open(DataFileName, "r") as f:
        for line in f:
            presses.append(line[0:-1])
    # handle
    result = ""
    for press in presses:
        Bytes = press.split(":")
        if Bytes[0] == "00":
            if Bytes[2] != "00":
                result += normalKeys[Bytes[2]]
        elif Bytes[0] == "20": # shift key is pressed.
            if Bytes[2] != "00":
                result += shiftKeys[Bytes[2]]
        else:
            print "[-] Unknow Key : %s" % (Bytes[0])
    print "[+] Found : %s" % (result)
    # clean the temp data
    os.system("rm ./%s" % (DataFileName))
if __name__ == "__main__":
    main()
```

运行后我们得到一串信息：**AAAAAAAAAA'ZITLQOSENPPI'.HILLDECODE**

#### 鼠标流量分析

```python
nums = [] 
keys = open('usbdata.txt','r') 
posx = 0 
posy = 0 
for line in keys: 
if len(line) != 12 : 
     continue 
x = int(line[3:5],16) 
y = int(line[6:8],16) 
if x > 127 : 
    x -= 256 
if y > 127 : 
    y -= 256 
posx += x 
posy += y 
btn_flag = int(line[0:2],16)  # 1 for left , 2 for right , 0 for nothing 
if btn_flag == 1 : 
    print posx , posy 
keys.close()
```

## 密码学分析

经过多种密码尝试最终得出这是一个希尔密码，其实特征也很明显，有一个矩阵还有一个密文，这里推介一个希尔密码的在线加解密网站：https://www.dcode.fr/hill-cipher

我们得到一串信息：**AAAAAAAAAA'ZITLQOSENPPI'.HILLDECODE**

在希尔密码中：

**ALPHABET (A=0) ABCDEFGHIJKLMNOPQRSTUVWXYZ**

**ALPHABET (A=1) ZABCDEFGHIJKLMNOPQRSTUVWXY**

而这题我们获得了十个A则可知加密方式为：

**ALPHABET (A=10) QRSTUVWXYZABCDEFGHIJKLMNOP**

我们之前获得了一个重要的信息：**hill_matrix 3,2,2,9,7,7,6,4,9**

![](https://github-1251836300.cos.ap-guangzhou.myqcloud.com/%E6%8A%A4%E7%BD%91%E6%9D%AF2019-MISC-baby_forensic/QQ%E6%88%AA%E5%9B%BE20190910161715.png)

解密可以得到：**ZKNNTCUPZXOU**，这题有一个小坑应全部转为小写才是正确的flag，故真正的flag应为：zknntcupzxou

> 参考文章
>
> 1. 深入理解USB流量数据包的抓取与分析【https://www.cnblogs.com/ECJTUACM-873284962/p/9473808.html】
> 2. CTF MISC-USB流量分析出题记录【https://www.cnblogs.com/hackxf/p/10670844.html】