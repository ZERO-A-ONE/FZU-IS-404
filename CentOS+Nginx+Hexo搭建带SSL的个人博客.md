# CentOS+Nginx+Hexo搭建带SSL的个人博客
## 安装CentOS系统镜像
自行安装，需开放端口，腾讯云在安全策略
## 安装Git+Node+Nvm环境
* 安装Git
```
yum install -y git
```
* 安装Nvm
```
wget -qO- https://raw.github.com/creationix/nvm/master/install.sh | sh
```
安装完成后需重启VPS
* 安装Node
```
nvm install stable
```
* 检查是否配置成功
```
git --version
node --version
```
如果正常显示git和node的版本则可以继续下面的操作
## 配置Hexo
* 安装Hexo
```
npm install -g hexo-cli
```
* 配置Hexo
初始化Hexo
```
hexo init 文件夹名称
cd 文件夹名称
npm install
```
生成静态文件
```
hexo generate
```
## 安装Nginx
安装Nginx
```
yum install -y nginx
```
启动Nginx
```
service nginx start
```
## 服务访问配置
* 配置域名解析服务
* 获取SSL证书
> 可从腾讯云或者阿里云申请免费的SSL证书
* 上传SSL证书至VPS
* 配置Nginx配置文件
```
……
 server {
        listen       443    //监听端口号;
        server_name  您的域名;
        root        Hexo Public的绝对路径;
        index        index.html index.htm;
        ssl on;
        ssl_certificate   您的CRT证书绝对路径;
        ssl_certificate_key  Key的绝对路径;
        ssl_session_timeout 5m;
        ssl_ciphers ALL:!ADH:!EXPORT56:RC4+RSA:+HIGH:+MEDIUM:+LOW:+SSLv2:+EXP;
        ssl_protocols SSLv2 SSLv3 TLSv1;
        ssl_prefer_server_ciphers on;
        # Load configuration files for the default server block.
        include /etc/nginx/default.d/*.conf;
location / {
        root /root/myweb/public;
        index index.html index.htm;
        }
……
```
修改配置完成后，重启 nginx 服务
```
nginx -s reload　　　　　　//使配置生效
```
# 享受你的个人博客之旅