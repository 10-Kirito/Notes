# 1. 设置`zsh` 和 `ohmyzsh` 各种插件

***第一步：***

访问网站： https://github.com/ohmyzsh/ohmyzsh/wiki/Installing-ZSH#how-to-install-zsh-on-many-platforms

根据自己的平台选择合适的安装方法，比如说Ubuntu很简单，就是简单的`sudo apt insatll zsh`。

*刚安装之后可能并不会发生变化，这个时候需要我们去重新启动一下终端。*

***第二步：***

访问网站： https://github.com/ohmyzsh/ohmyzsh

去安装一下`zsh`的插件管理软长度件, 用来管理我们`zsh`的配置文件的。

有很多方法：

```linux
wget https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh
sh install.sh
```

***第三步：***

从官网上我们就可以查看到许多的`zsh`的插件，我们选择下载安装即可。

***主题下载：***

> 注意：这里安装主题之前，先去网上下载Nerd字体。

https://github.com/romkatv/powerlevel10k#oh-my-zsh

***插件下载：***

[zsh-autosuggestions](https://github.com/zsh-users/zsh-autosuggestions)

一个自动提示的插件：

```linux
git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions
```

[zsh-syntax-highlighting](https://github.com/zsh-users/zsh-syntax-highlighting)

一个高亮显示插件：

```linux
git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting
```



# 2. 关于`wget:unable to resolve host address `问题

***解决办法：***

这个问题的原因是DNS服务器没有配置好的问题，我们只需要将`/etc/resolv.conf`文件中的`nameserver`地址修改为谷歌的一组解析服务器：

```linux
nameserver 8.8.8.8
nameserver 8.8.4.4
```

# 3. Ubuntu更换软件源

> 参看网站即可：
>
> https://mirrors.tuna.tsinghua.edu.cn/help/ubuntu/

***最后一步：***

```cmd
sudo apt-get update // 更新软件列表

sudo apt-get upgrade // 更新软件
```

***可能会遇到的问题：***

![FAQ3](.\pictures\FAQ3.png)

***解决方案：***

```cmd
sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 40976EAF437D05B5

sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 3B4FE6ACC0B21F32

// 视情况进行选择
```

# 4. nodejs 安装与升级

```c++
// 升级nodejs
sudo npm install -g n
// 将nodejs 升级到最新版本
n latest
```

