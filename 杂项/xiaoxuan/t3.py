#coding=utf8
import re, time, _thread,urllib.request,smtplib
from bs4 import BeautifulSoup
from email.mime.text import MIMEText
from email.header import Header

import sys
import codecs
sys.stdout = codecs.getwriter("utf-8")(sys.stdout.detach())

ALERTAUDIOFILEPATH = 'MengHuiTangKa.wav'
TABLEURL = "https://gpoticket.globalinterpark.com/Global/Play/Book/Lib/BookInfoXml.asp?Flag=SeatGradeBlock&PlaceCode=19001504&LanguageType=G2001&MemBizCode=10965&Tiki=N&BizCode=10965&PlaySeq=001&TmgsOrNot=D2003"
BLOCKURL = "https://gpoticket.globalinterpark.com/Global/Play/Book/BookSeatDetail.asp?PlaceCode=19001504&LanguageType=G2001&MemBizCode=10965&PlaySeq=001&SeatGrade=&TmgsOrNot=D2003&LocOfImage=&Tiki=N&UILock=Y&SessionId=8647CB8EEFF042B2ACF86C8B1586FBC0&BizCode=10965&GoodsBizCode=12930"


BLOCK = {"101":"A1","102":"A2","103":"A3","104":"A4","105":"A5","106":"A6","107":"A7","108":"A8"
         ,"110":"A10","111":"A11","112":"A12","113":"A13","114":"A14","115":"A15","116":"A16","117":"A17"
         ,"118":"A18","201":"B1","202":"B2","203":"B3","204":"B4","205":"B5","206":"B6","207":"B7"
,"208":"B8","209":"B9","210":"B10","211":"B11","212":"B12","213":"B13","214":"B14","215":"B15","216":"B16"
,"217":"B17","218":"B18","219":"B19","220":"B20","221":"B21","222":"B22","223":"B23"
         }
P = {"0207":"2月7日","0206":"2月6日","0208":"2月8日","0209":"2月9日","gala":"gala","package":"package"}

### Goods code on interpark
goodsCode0206 = "19016425"
goodsCode0207 = "19016426"
goodsCode0208 = "19016427"
goodsCode0209 = "19016428"
goodsCodeGALA = "19016424"
goodsCodePACK = "19016423"

def mail(data,block):
    # 发信方的信息：发信邮箱，QQ 邮箱授权码
    from_addr = '929672159@qq.com'
    password = 'zdxykuxiamembcec'
    # 收信方邮箱
    to_addr = 'suyuchenglz@163.com'
    # 发信服务器
    smtp_server = 'smtp.qq.com'
    # 邮箱正文内容，第一个参数为内容，第二个参数为格式(plain 为纯文本)，第三个参数为编码
    msg = MIMEText('send by suyucheng', 'plain', 'utf-8')
    # 邮件头信息
    msg['From'] = Header(from_addr)
    msg['To'] = Header(to_addr)
    msg['Subject'] = Header("日期:"+P[data]+"座位块："+block+'已经有余票')
    # 开启发信服务，这里使用的是加密传输
    server = smtplib.SMTP_SSL(smtp_server)
    server.connect(smtp_server, 465)
    # 登录发信邮箱
    server.login(from_addr, password)
    # 发送邮件
    server.sendmail(from_addr, to_addr, msg.as_string())
    # 关闭服务器
    server.quit()


def urlRequest(url):
    tmp = urllib.request.urlopen(url).read()
    return tmp.decode('utf-8')

def getTabelPathInfo(goodsCode, ticketType):
    # 请求URL地址
    url = TABLEURL + "&GoodsCode=" + goodsCode + "&SeatGrade=" + str(ticketType) + "&SeatGradeIdx=" + str(ticketType)
    # print(url)
    # 解析XML
    pageInfo = urlRequest(url)
    soup = BeautifulSoup(pageInfo, "html.parser")
    # B12 = 212 A10 = 110
    blockNameList = soup.find_all('selfdefineblock')  # 获取所有观看台区块号
    blockRemainCntList = soup.find_all('totalremaincnt')  # 获取所有对应余票数

    assert (len(blockNameList) == len(blockRemainCntList))

    return blockNameList, blockRemainCntList

def getRemainTabelList(blockNameList, remainCntList):
    res = []
    for i in range(len(blockNameList)):
        if str(remainCntList[i]) != "<totalremaincnt>0</totalremaincnt>":  # 如果余票不等于0的区块
            res.append(str(re.findall(r"<selfdefineblock>(.+?)</selfdefineblock>", str(blockNameList[i]))[0]))  # 提取出块名称
    return res

def getRemainBlockList(remainList, isPlayed, ticketType, goodsCode):
    url = BLOCKURL + "&GoodsCode=" + goodsCode + "&Block="
    for block in remainList:
        # 获取网页数据
        detailInfo = urllib.request.urlopen(url + block).read()
        detailInfo = str(detailInfo.decode('utf-8'))

        if detailInfo.find("<span class='SeatN' id=\"Seats\"") > 0:  # 如果有座位
            if not isPlayed:
                isPlayed = True
            mail(ticketType,BLOCK[block])
            print(ticketType + "\t" + BLOCK[block] + "有余票")

    return isPlayed

def main(ticketType, goodsCode):
    isPlayed = False
    count = 0
    while (not isPlayed):
        print(P[ticketType] + "\t查找次数： " + str(count))
        count += 1

        ### ticketType: 1-gold, 2-silver
        goldBlockNameList, goldRemainCntList = getTabelPathInfo(goodsCode, 1)  # 金票
        silverBlockNameList, silverRemainCntList = getTabelPathInfo(goodsCode, 2)  # 银票

        goldRemainList = getRemainTabelList(goldBlockNameList, goldRemainCntList)
        silverRemainList = getRemainTabelList(silverBlockNameList, silverRemainCntList)

        isPlayed = getRemainBlockList(goldRemainList, isPlayed, ticketType, goodsCode)
        isPlayed = getRemainBlockList(silverRemainList, isPlayed, ticketType, goodsCode)

if __name__ == '__main__':
    type = {"0207": "19016426", "0209": "19016428", "gala": "19016424", "package": "19016423"}
    for key in type:
        _thread.start_new_thread(main, (key, type[key]))
    while 1:
        var = 0

