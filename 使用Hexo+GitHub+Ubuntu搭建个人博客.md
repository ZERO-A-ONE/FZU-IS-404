# 使用Hexo+GitHub+Ubuntu搭建个人博客
## Hexo基础环境的搭建
### 1.安装NVM和Nodejs
* 安装NVM
1. curl -o- https://raw.githubusercontent.com/creationix/nvm/v0.33.11/install.sh | bash
2. source .profile
3. command -v nvm
4. reboot
* 安装Nodejs
1. nvm install stable
2. sudo apt-get install nodejs
### 2.安装NPM
1. sudo apt-get install npm
### 3.配置Hexo
* 安装Hexo
1. npm install -g hexo-cli
* 初始化Hexo
在root目录下建立文件夹"MyHexoBlog"
1. hexo init MyHexoBlog
2. cd ~/MyHexoBlog/
3. npm install
* 安装hexo server
1. sudo npm install hexo-server
## 配置Git
* 安装Git
1. sudo apt-get install git
* 配置GitHub账户
1. git config --global user.name "Your Name"——用户名
2. git config --global user.email "youremail@domain.com"——注册邮箱
3. git init 
4. git remote add origin git@github.com:liminhu/test.git
* 查看配置信息
5.git config --list
若显示如下信息则成功
```
user.name=Your Name 
user.email=youremail@domain.com
```
* 生成SSH-Key
1. ssh-keygen
2. cat ~/.ssh/id_rsa.pub
将生成的SSH-Key添加到自己的GitHub账户
* 上传到GitHub
1. 切回到MyHexoBlog下 
cd root/MyHexoBlog/
2. 修改_config.yml配置文件
vim _config.yml
```
deploy:
  type: git
  repo: https://github.com/yourname/yourname.github.io.git
  branch: master
```
3.npm install hexo-deployer-git --save
4.hexo deploy 
## 配置个人域名访问
* 通过Ping命令获取GitHub分配的IP地址
1. Ping yourname.github.
* 将自己的域名解析为分配的IP地址
* 在GitHub的仓库中GitHub Pages填入私人域名
## 配置SSL与HTTPS
1. 安装 acme.sh
2. 生成证书
3. copy 证书到 nginx/apache 或者其他服务
## 参考
1. ACME仓库-https://github.com/Neilpang/acme.sh/wiki/%E8%AF%B4%E6%98%8E
2. HEXO官网-https://hexo.io/zh-cn/docs/
3. 如何生成SSH-Key-https://www.cnblogs.com/yeshaoxiang/p/7839603.html
4. Ubuntu安装git-https://blog.csdn.net/abclixu123/article/details/46464089
5. HEXO个人域名-https://blog.csdn.net/wolf6699/article/details/78653547
6. Linux下使用Hexo搭建github博客-https://blog.csdn.net/u010725842/article/details/80672739