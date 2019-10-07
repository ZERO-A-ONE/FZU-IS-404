# macOS终端服务提示远程主机识别更改

今天服务器出了些难以解决的错误，就重置了服务器，然而再次连接时macOS的终端给出了这样的信息：

```
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@    WARNING: REMOTE HOST IDENTIFICATION HAS CHANGED!     @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
IT IS POSSIBLE THAT SOMEONE IS DOING SOMETHING NASTY!
Someone could be eavesdropping on you right now (man-in-the-middle attack)!
It is also possible that a host key has just been changed.
The fingerprint for the ECDSA key sent by the remote host is
SHA256:3EkUYe8b2chPhf2V5+LlSwXIfEKthgufBcVrPMaPKc8.
Please contact your system administrator.
Add correct host key in /Users/syc/.ssh/known_hosts to get rid of this message.
Offending ECDSA key in /Users/syc/.ssh/known_hosts:1
ECDSA host key for 45.63.55.211 has changed and you have requested strict checking.
Host key verification failed.
```



解决方法很简单，只需要把缓存的hosts删除就好了
可以看到hosts的文件地址在

```
/Users/syc/.ssh/
```

我们只需要进入到.ssh目录移除known_hosts文件即可

```
cd /Users/syc/.ssh
rm known_hosts
```