# macOS环境下利用Github和Hexo部署博客

### 1.安装Xcode（Hexo需要使用到Xcode的编译环境）

在Mac App Store下载安装

### 2.安装Node.js

1. 可以直接到[Node.js官网](https://nodejs.org/en/)下载安装
2. 【个人推荐】通过Homebrew安装

```
brew install node
```

安装完node后建议设置[npm淘宝镜像](http://npm.taobao.org/)以加速后面的过程（或使用科学上网工具）。注意：不要使用cnpm！cnpm安装的模块路径比较奇怪，packager不能正常识别！[链接](https://reactnative.cn/docs/getting-started.html)

```
npm config set registry https://registry.npm.taobao.org --global
npm config set disturl https://npm.taobao.org/dist --global
```

### 3.安装Hexo

```
npm install -g hexo-cli
hexo -v                  // 查看版本号
```

创建一个你的博客文件夹(必须是空文件夹)，如放在桌面`~/Desktop/hexo-blog`，并进入这个文件夹,示例如下

```
cd ~/Desktop/hexo-blog
```

执行命令

```
hexo init
npm install
hexo generate          // hexo g 也可以
hexo server
```

### 4.部署Github仓库

登录 GitHub 个人账号以后，在首页右上角会有 New repository，新建一个代码仓库，名为**用户名.github.io**，这是固定写法，如我的仓库是KevinCoderX.github.io

`cd`到你的博客文件夹，内容如下

```
_config.yml 
db.json 
node_modules 
package.json
scaffolds
source
themes
```

`vim`打开`_config.yml`，命令如下：

```
vim _config.yml
```

打开后往下滑到最后，修改成下边的样子：

```
deploy:
  type: git
  repository: https://github.com/KevinCoderX/KevinCoderX.github.io.git
  branch: master
```

按`i`可以修改vim内容，并且以上内容空格不能少，`repository:`后面的链接改成自己的仓库地址，修改好后第一步在终端按`esc`，然后输入`:wq`并回车（保存并退出vim）

执行命令

```
hexo generate
hexo deploy            // 或者：hexo d
```

若执行命令`hexo deploy`报错：`ERROR Deployer not found: git`，则执行如下命令来安装`hexo-deployer-git`：

```
npm install hexo-deployer-git --save
```

再次执行`hexo generate`和`hexo deploy`命令

若你未关联**Github**，则执行`hexo deploy`命令时终端会提示你输入**Github**的用户名和密码，输入用户名和密码成功后，打开`https://kevincoderx.github.io`，能看到之前`http://localhost:4000`一样的页面

> 此时你的博客就已经建立好了

### 5.装饰你的博客

你可以到[Hexo官网主题页](https://hexo.io/themes/)去搜寻自己喜欢的theme，这里以[hexo-theme-next](http://theme-next.iissnan.com/)为例

`cd`到你的博客文件夹

执行命令

```
git clone https://github.com/theme-next/hexo-theme-next themes/next
```

将你的博客文件夹目录下`_config.yml`里`theme`的名称`landscape`修改为`next`，然后执行`cd`到你的博客文件夹目录下执行如下命令：

```
hexo clean   //清除缓存文件 (db.json) 和已生成的静态文件 (public)
hexo g       //生成缓存和静态文件
hexo d       //重新部署到服务器
```

每次修改`_config.yml`，都要执行上面3个命令，至于其他修改，[Next使用文档](http://theme-next.iissnan.com/)里有极详细的介绍

### 6.写下你的博客

`cd`到你的博客文件夹

```
hexo new post "我的第一篇博客"      //名字可以自己取
```

执行完以上命令，得到Markdown文件，内容如下需要保留。

```
---
title: Homebrew
date: 2018-02-08 18:54:25        
tags:                            //定义了博文的标签
---
```

### 7.给博客添加图片

1. 第一步

`Hexo`提供了一种更方便管理`Asset`的设定：`post_asset_folder`，设置hexo主题`_config.yml`的`post_asset_folder`为`true`参数，不是主题的`_config.yml`。设置后`Hexo`会自动建立一个与文章同名的文件夹，您可以把与该文章相关的所有资源都放到那个文件夹，如此一来，您便可以更方便的使用资源。

引用图片的时候如下

```
{% asset_img hexoLocal.png hexo初始的样子 %}
```

**hexo初始的样子**是对图片的描述

### 8.迁移博客到其他电脑

1. 在你博客部署的GitHub仓库建立一个分支，可以命名为：`hexo`

2. 将你的`hexo`分支**clone**到本地，我是通过[sourceTree](https://www.sourcetreeapp.com/)去操作的

3. 将**clone**到本地的`hexo`分支，除了`.git`文件夹，其余的全部删掉

4. 将这份操作保存到`git`暂存区，并推送到**Github**仓库，再去刷新**Github**仓库`hexo`分支，该分支已经清空把之前剩下的`.git`文件夹复制到你旧电脑的博客文件夹目录下，这样我们可以认为旧电脑的博客文件夹与`hexo`分支建立了关联。以后我们修改博客等操作，需要先推送到`hexo`分支，再执行`hexo g`和`hexo d`。

5. 将`themes`目录以内中的主题的`.git`文件夹删除（如果有），因为一个git仓库中不能包含另一个git仓库，提交主题文件夹会失败。（可能有人会问，删除了`themes`目录中的`.git`不就不能推送更新主题了吗，很简单，需要更新主题时在另一个地方 `git clone`下来该主题的最新版本，然后将内容拷到当前主题目录即可。）新电脑接着写博客在新电脑中先安装`hexo`

   ```
   brew install node
   npm config set registry https://registry.npm.taobao.org --global
   npm config set disturl https://npm.taobao.org/dist --global
   npm install -g hexo-cli
   ```

   **clone**`hexo分支`到本地，`cd`本地`hexo分支仓库`，执行`npm install`。本地部署完成，可以正常写博客发博客了。

   两点建议
   1、直接用系统的文本编辑器就可以修改 _config.yml文件了，不需要通过vim这么慢
   2、那三个命令可以合成一个命令，hexo clean && hexo g && hexo d