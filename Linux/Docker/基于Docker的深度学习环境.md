# 基于Docker的深度学习环境

> 安装docker: 参考文章：https://www.runoob.com/docker/ubuntu-docker-install.html
>
> `curl -fsSL https://get.docker.com | bash -s docker --mirror Aliyun`
>
> 首先，我们安装完docker之后，我们现在虽然说可以下载相应的镜像来部署我们的深度学习容器，但是这个时候我们的容器还不能去访问我们的显卡。所以说，要想进一步的使得我们的docker容器可以访问我们的显卡的话，需要进一步的设置。

# 1. Setting up NVIDIA Container ToolKit

> 参考官方文档：https://docs.nvidia.com/datacenter/cloud-native/container-toolkit/install-guide.html#docker

***1. Setup the package repository and the GPG key:***

```shell
distribution=$(. /etc/os-release;echo $ID$VERSION_ID) \
      && curl -fsSL https://nvidia.github.io/libnvidia-container/gpgkey | sudo gpg --dearmor -o /usr/share/keyrings/nvidia-container-toolkit-keyring.gpg \
      && curl -s -L https://nvidia.github.io/libnvidia-container/$distribution/libnvidia-container.list | \
            sed 's#deb https://#deb [signed-by=/usr/share/keyrings/nvidia-container-toolkit-keyring.gpg] https://#g' | \
            sudo tee /etc/apt/sources.list.d/nvidia-container-toolkit.list
```

***2. Install the `nvidia-container-toolkit` package (and dependencies) after updating the package listing:***

```shell
sudo apt-get update

sudo apt-get install -y nvidia-container-toolkit
```

***3. Configure the Docker daemon to recognize the NVIDIA Container Runtime:***

```shell
sudo nvidia-ctk runtime configure --runtime=docker
```

如果执行成功的话，会输出下面的结果：

```output
# sudo nvidia-ctk runtime configure --runtime=docker

INFO[0000] Loading docker config from /etc/docker/daemon.json 
INFO[0000] Successfully loaded config                   
INFO[0000] Flushing docker config to /etc/docker/daemon.json 
INFO[0000] Successfully flushed config                  
INFO[0000] Wrote updated config to /etc/docker/daemon.json 
INFO[0000] It is recommended that the docker daemon be restarted. 
```

***4. Restart the Docker daemon to complete the installation after setting the default runtime:***

```shell
sudo systemctl restart docker
```

***5. At this point, a working setup can be tested by running a base CUDA container:***

```
sudo docker run --rm --runtime=nvidia --gpus all nvidia/cuda:11.6.2-base-ubuntu20.04 nvidia-smi
```

> 参看文章： https://zhuanlan.zhihu.com/p/616208372
>
> 其中`--gpus all`参数就是设置我们的容器和我们宿主机显卡之间的联系的。
>
> 我们使用容器之后，我们可以指定文件路径、CPU资源、内存资源、以及最重要的指定相应的显卡。
>
> 比如说我们将上面的`--gpus all `参数可以替换为显卡的编号，这样的话我们就可以在多卡机器中指定某一张卡来运行程序：
>
> ```shell
> docker run --gpus "0" --ipc=host --ulimit memlock=-1 --ulimit stack=67108864 -it --rm nvcr.io/nvidia/pytorch:23.02-py3
> ```
>
> 如果你想要八卡的机器只有单数卡能够被容器访问，可以调整为参数：
>
> ```shell
> --gpus "1,3,5,7"
> ```

This should result in a console output shown below:

```output
+-----------------------------------------------------------------------------+
| NVIDIA-SMI 450.51.06    Driver Version: 450.51.06    CUDA Version: 11.0     |
|-------------------------------+----------------------+----------------------+
| GPU  Name        Persistence-M| Bus-Id        Disp.A | Volatile Uncorr. ECC |
| Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |
|                               |                      |               MIG M. |
|===============================+======================+======================|
|   0  Tesla T4            On   | 00000000:00:1E.0 Off |                    0 |
| N/A   34C    P8     9W /  70W |      0MiB / 15109MiB |      0%      Default |
|                               |                      |                  N/A |
+-------------------------------+----------------------+----------------------+

+-----------------------------------------------------------------------------+
| Processes:                                                                  |
|  GPU   GI   CI        PID   Type   Process name                  GPU Memory |
|        ID   ID                                                   Usage      |
|=============================================================================|
|  No running processes found                                                 |
+-----------------------------------------------------------------------------+
```

> ***寻找合适的镜像版本：***
>
> NVIDIA提供了许多的tag，对应了各种的环境，我们的目标是要选择一个已经安装了`cuda toolkit`和`cudnn`，并且设置了`cudnn`环境变量的镜像，所以选择下面的标签：
>
> `11.7.0-cudnn8-devel-ubuntu18.04`
>
> 11.7.0: 标识`cuda toolkit`的版本,需要我们执行`nvidis-smi`命令输出结果中的`CUDA Version`一样。
>
> `cudnn8`: 标识镜像包含`cudnn`；
>
> `devel` : 想要包含nvcc工具、include、lib64内容；
>
> ubuntu: 镜像所使用的的系统版本；
