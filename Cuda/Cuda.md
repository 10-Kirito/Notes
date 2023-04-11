# Cuda

# 1. CUDA&CUDNN开发环境

> https://zhuanlan.zhihu.com/p/616208372
>
> https://zhuanlan.zhihu.com/p/580156606

<h2>1.1 安装docker</h2>

<h2>1.2 安装Docker显卡运行时</h2>

我们如果想要在Docker中“调用显卡”，我们需要安装“NVIDIA 容器工具包存储库”，首先添加工具的软件源：

```shell
distribution=$(. /etc/os-release;echo $ID$VERSION_ID) \
      && curl -fsSL https://nvidia.github.io/libnvidia-container/gpgkey | sudo gpg --dearmor -o /usr/share/keyrings/nvidia-container-toolkit-keyring.gpg \
      && curl -s -L https://nvidia.github.io/libnvidia-container/$distribution/libnvidia-container.list | \
            sed 's#deb https://#deb [signed-by=/usr/share/keyrings/nvidia-container-toolkit-keyring.gpg] https://#g' | \
            sudo tee /etc/apt/sources.list.d/nvidia-container-toolkit.list
```

命令执行完毕之后，我们的系统中就添加好了 Lib Nvidia Container 工具的软件源啦，然后更新系统软件列表，使用命令安装 `nvidia-container-toolkit` 即可：

```bash
sudo apt-get update && sudo apt-get install -y nvidia-container-toolkit
```

完成 `nvidia-container-toolkit` 的安装之后，我们继续执行 `nvidia-ctk runtime configure` 命令，为 Docker 添加 `nvidia` 这个运行时。完成后，我们的应用就能在容器中使用显卡资源了：

```bash
sudo nvidia-ctk runtime configure --runtime=docker
```

命令执行成功，我们将看到类似下面的日志输出：

```bash
# sudo nvidia-ctk runtime configure --runtime=docker

INFO[0000] Loading docker config from /etc/docker/daemon.json 
INFO[0000] Successfully loaded config                   
INFO[0000] Flushing docker config to /etc/docker/daemon.json 
INFO[0000] Successfully flushed config                  
INFO[0000] Wrote updated config to /etc/docker/daemon.json 
INFO[0000] It is recommended that the docker daemon be restarted. 
```

在完成配置之后，别忘记重启 docker 服务，让配置生效：

```bash
sudo systemctl restart docker
```

服务重启完毕，我们查看 Docker 运行时列表，能够看到 `nvidia` 已经生效啦。

```bash
# docker info | grep Runtimes

 Runtimes: nvidia runc io.containerd.runc.v2
```

<h2>1.3 拉取docker镜像</h2>

我们首先确定我们的cuda的版本：

```shell
❯ nvidia-smi
Mon Apr  3 20:04:41 2023       
+-----------------------------------------------------------------------------+
| NVIDIA-SMI 515.86.01    Driver Version: 515.86.01    CUDA Version: 11.7     |
|-------------------------------+----------------------+----------------------+
| GPU  Name        Persistence-M| Bus-Id        Disp.A | Volatile Uncorr. ECC |
| Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |
|                               |                      |               MIG M. |
|===============================+======================+======================|
|   0  NVIDIA GeForce ...  Off  | 00000000:01:00.0  On |                  N/A |
| N/A   39C    P8     1W /  N/A |    581MiB /  4096MiB |      1%      Default |
|                               |                      |                  N/A |
+-------------------------------+----------------------+----------------------+
                                                                               
+-----------------------------------------------------------------------------+
| Processes:                                                                  |
|  GPU   GI   CI        PID   Type   Process name                  GPU Memory |
|        ID   ID                                                   Usage      |
|=============================================================================|
|    0   N/A  N/A      1825      G   /usr/lib/xorg/Xorg                183MiB |
|    0   N/A  N/A      2054      G   /usr/bin/gnome-shell              244MiB |
|    0   N/A  N/A      7918      G   ...146000608866429471,131072      117MiB |
|    0   N/A  N/A      9681      G   ...RendererForSitePerProcess       32MiB |
+-----------------------------------------------------------------------------+
```

选择相应的版本：11.7.

> 但是这里要注意了，nvidia提供了非常多的tag，对应了各种不同的环境。我们的目标是要选择已经安装好cuda toolkit与cudnn，并且设置了cudnn环境变量的镜像。所以请选择如下标签：
>
> tag：11.7-cudnn8-devel-ubuntu20.04
>
> 11.7： 表示cuda toolkit的版本，需要与步骤1中的打印信息匹配，在我的环境中，必须使用11.4版本。
>
> cudnn：表示镜像包含cudnn
>
> devel：想要包含nvcc工具、include、lib64内容，必须选择此版本，不然坑死你
>
> ubuntu20.04：表示镜像使用的系统版本
>
> 版本一定注意，需要与自身的驱动环境匹配。

***创建容器：***

```shell
docker run -it --name ubuntu-cuda --gpus all nvidia/cuda:11.7.0-cudnn8-devel-ubuntu18.04 
```

