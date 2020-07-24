import smtplib
from email.mime.text import MIMEText
from email.header import Header
# 用于构建邮件头
'''
def a(str):
    print(str)
b= []
goodsCode0206 = "19016425"
goodsCode0207 = "19016426"
goodsCode0208 = "19016427"
goodsCode0209 = "19016428"
goodsCodeGALA = "19016424"
goodsCodePACK = "19016423"
type = {"0206":"19016425","0207":"19016426","0208":"19016427",
        "0209":"19016428","gala":"19016424","package":"19016423"}
with concurrent.futures.ProcessPoolExecutor() as executor:
    for key in type:
        c = key + ":" + type[key]
        executor.map(a, c)
'''

# 发信方的信息：发信邮箱，QQ 邮箱授权码
from_addr = '929672159@qq.com'
password = 'zdxykuxiamembcec'

# 收信方邮箱
to_addr = 'suyuchenglz@163.com'

# 发信服务器
smtp_server = 'smtp.qq.com'

# 邮箱正文内容，第一个参数为内容，第二个参数为格式(plain 为纯文本)，第三个参数为编码
msg = MIMEText('send by python', 'plain', 'utf-8')

# 邮件头信息
msg['From'] = Header(from_addr)
msg['To'] = Header(to_addr)
msg['Subject'] = Header('已经有余票')

# 开启发信服务，这里使用的是加密传输
server = smtplib.SMTP_SSL(smtp_server)
server.connect(smtp_server, 465)
# 登录发信邮箱
server.login(from_addr, password)
# 发送邮件
server.sendmail(from_addr, to_addr, msg.as_string())
# 关闭服务器
server.quit()