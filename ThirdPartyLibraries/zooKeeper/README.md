# zooKeeper

## 1. How to install?

从官网上下载zooKeeper[源码](https://zookeeper.apache.org/releases.html)以及编译之后的服务端:

```shell
$ wget https://www.apache.org/dyn/closer.lua/zookeeper/zookeeper-3.9.2/apache-zookeeper-3.9.2-bin.tar.gz
$ wget https://www.apache.org/dyn/closer.lua/zookeeper/zookeeper-3.9.2/apache-zookeeper-3.9.2.tar.gz
```

解压相应的文件并且进行对应目录当中:

```shell
$ tar -zxvf apache-zookeeper-3.9.2-bin.tar.gz
$ cd apache-zookeeper-3.9.2-bin
$ ll
total 52
drwxrwxr-x  7 kirito kirito  4096 Mar 25 15:57 ./
drwxrwxr-x 12 kirito kirito  4096 Mar 25 16:06 ../
drwxr-xr-x  2 kirito kirito  4096 Feb 13 04:48 bin/
drwxr-xr-x  2 kirito kirito  4096 Mar 25 15:56 conf/
drwxr-xr-x  5 kirito kirito  4096 Feb 13 04:48 docs/
drwxrwxr-x  2 kirito kirito  4096 Mar 25 15:56 lib/
-rw-r--r--  1 kirito kirito 11358 Feb 13 04:48 LICENSE.txt
drwxr-xr-x  2 root   root    4096 Mar 25 15:57 logs/
-rw-r--r--  1 kirito kirito  2084 Feb 13 04:48 NOTICE.txt
-rw-r--r--  1 kirito kirito  2335 Feb 13 04:48 README.md
-rw-r--r--  1 kirito kirito  3570 Feb 13 04:48 README_packaging.md
$ cd conf
$ mv zoo_sample.cfg zoo.cfg
$ sudo mkdir -p /data/zookeeper
$ sudo chown kirito:kirito /data/zookeeper
$ # 修改zoo.cfg文件里面的内容，将里面数据存储路径修改为`/data/zookeeper`
$ cd bin
$ sudo ./zkServre.sh start
# 成功运行zooKeeper服务器
```

接下来安装相应的开发包来供我们开发客户端：

https://zookeeper.apache.org/doc/r3.9.2/zookeeperProgrammers.html#Installation(写的跟屎一样)

```shell
$ tar -zxvf apache-zookeeper-3.9.2.tar.gz
$ cd apache-zookeeper-3.9.2
$ mvn -pl zookeeper-jute compile # generate some need files 
# 切换到相应的源代码目录当中:
$ cd zookeeper-client/zookeeper-client-c
$ sudo autoreconf -if # generate autoconf, automake, libtool
$ sudo ./configure
$ sudo make 
$ sudo make install
# finish
```

> [!NOTE]
>
> 安装开发包的时候，有可能会遇到一些库没有安装的提示：
>
> - cppunit: https://freedesktop.org/wiki/Software/cppunit/;

## 2. How to use the server-cli?

https://www.runoob.com/w3cnote/zookeeper-bs-command.html

```shell
# 添加环境变量
$ export PATH=$PATH:/home/kirito/github/apache-zookeeper-3.9.2-bin/bin
$ zkCli.sh 
```

`ls`:查看指定路径下的节点:

```shell
[zk: localhost:2181(CONNECTED) 2] ls /
[zookeeper]
# -------------------------------------------------
[zk: localhost:2181(CONNECTED) 19] ls
ls [-s] [-w] [-R] path
# -------------------------------------------------
[zk: localhost:2181(CONNECTED) 7] ls /
[testpath, zookeeper]
# -------------------------------------------------
[zk: localhost:2181(CONNECTED) 20] ls -s /zookeeper 
[config, quota]
cZxid = 0x0
ctime = Thu Jan 01 08:00:00 CST 1970
mZxid = 0x0
mtime = Thu Jan 01 08:00:00 CST 1970
pZxid = 0x0
cversion = -2
dataVersion = 0
aclVersion = 0
ephemeralOwner = 0x0
dataLength = 0
numChildren = 2
# -------------------------------------------------
[zk: localhost:2181(CONNECTED) 21] ls -s /testpath 
[] # 存储数据的地方，比如说IP:PORT等信息
cZxid = 0x4
ctime = Mon Mar 25 17:43:37 CST 2024
mZxid = 0x4
mtime = Mon Mar 25 17:43:37 CST 2024
pZxid = 0x4
cversion = 0
dataVersion = 0
aclVersion = 0
ephemeralOwner = 0x0
dataLength = 0
numChildren = 0
# ------------------------------------------------
[zk: localhost:2181(CONNECTED) 32] ls -R /zookeeper 
/zookeeper
/zookeeper/config
/zookeeper/quota
# ------------------------------------------------
[zk: localhost:2181(CONNECTED) 33] ls -w /zookeeper 
[config, quota]
```

`create`:创建节点:

```shell
[zk: localhost:2181(CONNECTED) 6] create /testpath
Created /testpath
# ------------------------------------------------
[zk: localhost:2181(CONNECTED) 23] create /testpath/testdata hello

WATCHER::

WatchedEvent state:SyncConnected type:NodeChildrenChanged path:/testpath zxid: 5
Created /testpath/testdata
# ------------------------------------------------
[zk: localhost:2181(CONNECTED) 24] ls /testpath 
[testdata]
# ------------------------------------------------
[zk: localhost:2181(CONNECTED) 25] ls /testpath/testdata
[]
# ------------------------------------------------
[zk: localhost:2181(CONNECTED) 26] ls -s /testpath/testdata
[]
cZxid = 0x5
ctime = Mon Mar 25 17:51:14 CST 2024
mZxid = 0x5
mtime = Mon Mar 25 17:51:14 CST 2024
pZxid = 0x5
cversion = 0
dataVersion = 0
aclVersion = 0
ephemeralOwner = 0x0
dataLength = 5
numChildren = 0
# ----------------------------------------------
[zk: localhost:2181(CONNECTED) 28] get /testpath/testdata 
hello
```

`get`: 获取存储在节点的数据与状态信息:

```shell
[zk: localhost:2181(CONNECTED) 34] get /testpath/testdata 
hello

```

`stat`:查看节点状态信息:

```shell
[zk: localhost:2181(CONNECTED) 36] stat /testpath/testdata
cZxid = 0x5
ctime = Mon Mar 25 17:51:14 CST 2024
mZxid = 0x5
mtime = Mon Mar 25 17:51:14 CST 2024
pZxid = 0x5
cversion = 0
dataVersion = 0
aclVersion = 0
ephemeralOwner = 0x0
dataLength = 5
numChildren = 0
```

`set`: 用于修改节点存储的数据:

```shell
[zk: localhost:2181(CONNECTED) 37] get /testpath/testdata 
hello
[zk: localhost:2181(CONNECTED) 38] set /testpath/testdata world
[zk: localhost:2181(CONNECTED) 39] get /testpath/testdata 
world
```

`delete`:用于删除某一个节点:

```shell
[zk: localhost:2181(CONNECTED) 40] ls /testpath
[testdata]
[zk: localhost:2181(CONNECTED) 41] delete /testpath/testdata 

WATCHER::

WatchedEvent state:SyncConnected type:NodeDeleted path:/testpath/testdata zxid: 7
[zk: localhost:2181(CONNECTED) 42] ls /testpath
[]
```



