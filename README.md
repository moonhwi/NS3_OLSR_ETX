

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
    │   ├── simple-wifi-mesh.cc 
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
    │   └── olsr
* scratch文件夹存放运行的脚本文件  
  1.*simple-olsr*：本脚本描述了简单的P2P网络，用于验证增加了etx度量后的olsr路由协议的功能正确性。  
  2.*unknown*：本脚本描述了简单的spectrumwifiphy模型下的mesh网络，使用Friis衰落模型与网格移动模型控制网络拓扑。
* src/olsr目录中包含了对于olsr协议源码的修改，增加了ETX度量

### 部署
**运行后效果图**
* simple-olsr 脚本
```Shell
limenghui@limenghui-TianYi510Pro-18ICB:~/NS3/ns-allinone-3.33/ns-3.33$ sudo ./waf --run scratch/simple-olsr.cc     
Waf: Entering directory `/home/limenghui/NS3/ns-allinone-3.33/ns-3.33/build'  
Waf: Leaving directory `/home/limenghui/NS3/ns-allinone-3.33/ns-3.33/build'  
Build commands will be stored in build/compile_commands.json  
'build' finished successfully (1.008s)   
```
* simple-wifi-mesh 脚本
```Shell
limenghui@limenghui-TianYi510Pro-18ICB:~/NS3/ns-allinone-3.33/ns-3.33$ sudo ./waf --run scratch/unknown.cc 
Waf: Entering directory `/home/limenghui/NS3/ns-allinone-3.33/ns-3.33/build'
Waf: Leaving directory `/home/limenghui/NS3/ns-allinone-3.33/ns-3.33/build'
Build commands will be stored in build/compile_commands.json
'build' finished successfully (0.812s)
Run Simulation.
Flow 1 (195.1.2.4 -> 195.1.2.1)
  Tx Packets:   1953
  Rx Packets:   1953
  last Delay:   0.000110771
  delay: 0.000117861 s
  lostpackets: 0 
  Throughput: 0.805694 Mbps
```


