

# NS3_OLSR_ETX

本项目旨在将ETX度量融合进OLSR路由，通过NS3仿真平台实现MRMC的路由功能验证。  
参考文献：  
*De Couto, D. S., Aguayo, D., Bicket, J., & Morris, R. (2003, September). A high-throughput path metric for multi-hop wireless routing. In Proceedings of the 9th annual international conference on Mobile computing and networking (pp. 134-146).*

 
## 目录

- [上手指南](#上手指南)
  - [开发前的配置要求](#开发前的配置要求)
  - [安装步骤](#安装步骤)
- [文件目录说明](#文件目录说明)
- [部署](#部署)

### 上手指南
* NS3项目主页地址：https://www.nsnam.org/  
* NS3安装wiki：https://www.nsnam.org/wiki/Installation#Ubuntu.2FDebian.2FMint  

#### 开发前的配置要求

* Ubuntu 20.04
* NS-3.33
* 内存>=2G 
#在安装目录中运行
* 可以利用Visual Studio Code的Remote-Development插件实现远程开发，方便调试

#### **安装步骤**

* 首先根据NS3安装wiki在服务器端或Ubuntu客户端安装好NS3
* 下载本项目源码到NS3安装目录，替换所有相同目录的同名文件。
* 在NS3安装目录的终端中输入  
```python
#在安装目录的终端中运行
sudo ./waf --run scratch/simple-olsr.cc 
```

### 文件目录说明



    filetree 
    ├── scratch
    │   ├── scratch-simulator.cc
    │   ├── simple-olsr.cc
    │   └── subdir
    ├── simple-olsr
    │   ├── routes.route
    │   ├── simple-point-to-point-olsr-0-1.pcap
    │   ├── simple-point-to-point-olsr-1-1.pcap
    │   ├── simple-point-to-point-olsr-2-1.pcap
    │      ├── simple-point-to-point-olsr-2-2.pcap
    │   ├── simple-point-to-point-olsr-2-3.pcap
    │   ├── simple-point-to-point-olsr-3-1.pcap
    │   ├── simple-point-to-point-olsr-3-2.pcap
    │   ├── simple-point-to-point-olsr-4-1.pcap
    │   └── simple-point-to-point-olsr.tr
    ├── src
    │   ├── olsr
* scratch文件夹存放运行的脚本文件
* src/olsr目录中包含了对于olsr协议源码的修改，增加了ETX度量

### 部署
* 运行后效果图
```Shell
limenghui@limenghui-TianYi510Pro-18ICB:~/NS3/ns-allinone-3.33/ns-3.33$ sudo ./waf --run scratch/simple-olsr.cc     
Waf: Entering directory `/home/limenghui/NS3/ns-allinone-3.33/ns-3.33/build'  
Waf: Leaving directory `/home/limenghui/NS3/ns-allinone-3.33/ns-3.33/build'  
Build commands will be stored in build/compile_commands.json  
'build' finished successfully (1.008s)   
```


