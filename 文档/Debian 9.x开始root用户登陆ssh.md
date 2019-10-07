# Debian 9.x开始root用户登陆ssh

网上许多的教程还是基于老版本的Debian系统开始root用户登陆权限，在尝试了许多后发现在Debian9中许多设置都已经发生了改变。
首先Debian 9.x的ssh配置文件应该是

> sshd_config

具体地址如下

```
/etc/ssh/sshd.config
```



编辑文件

```
vi /etc/ssh/sshd.config
```



找到选项

> PermitRootLogin

把前面的注释#删除，后面改成yes即可，保存退出

使用

```
ifconfig
```



查看当前主机网络IP即可使用SSH连接（前提是你安装了SSH服务端）
**Kali Linux还需要如下设置**
将#PasswordAuthentication yes前的注释符#去掉
将#PermitRootLogin prohibit-password前的注释符#去掉
将prohibit-password改为yes
执行service ssh start启动ssh服务