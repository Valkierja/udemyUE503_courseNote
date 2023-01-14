# test_muti_4

Developed with Unreal Engine 5

這裏直接就當作小筆記區域了

# git-windows在http/https下傳輸大文件時會報錯
由於本項目較大, 因此需要手動修改傳輸buffer 同時手動指定HTTP/1.1協議
如果覺得這樣太麻煩, 也可以采用ssh-git的方式, 這種方式不會遇到上述報錯
postBuffer可以調整更大一些, 如果你的項目有更大的文件存在

```
[http]                                                                                                                         
  version = HTTP/1.1                                                                                                      
  postBuffer  = 524288000                                                                                                 
  proxy = socks5://127.0.0.1:10808                                                                                
[https]                                                                                                                        
  postBuffer = 524288000                                                                                                  
  proxy = socks5://127.0.0.1:10808                                                                                ~                                         
```

# implementation of a bp-callable function

just declare like
```cpp
	UFUNCTION(BlueprintCallable)
	void openLobby();

```

UFUNCTION is a macro, it will be replaced before compile

# find a build-in function's .h include file

just search in offical doc

![image-20230113144946659](https://raw.githubusercontent.com/KSroido/ALLPIC/main/img/202301131449705.png)

# why ServerTravel function only need ID parameter, but not IP:port

I once thought UE engineer used some built-in protocol, But it seems that they just brute forced try a range of port, then decide to use which one, but I dont know how does it work when mutil-instance is running

![image-20230113144853485](https://raw.githubusercontent.com/KSroido/ALLPIC/main/img/202301131449172.png)



after testing, am pretty sure that it's a range of port used, incresing from port UDP::7777

the first initiated game instance will be arange to UPD 7777 and the first conducting linking processing game instance will first trying to link UDP port7777, But I cant test the behavior of 2nd conducting linking processing game instance, due to limited computer CPU and Mem

ADD: if there were 2 listening instances and 2 performing linking instances,  linking instances will always link to the first listen instance which has been aranged UDP 7777 port



# what is World context OBJ

什么是世界上下文物件?

以下内容没有经过大范围搜索,可能是错误的, 简单看了以下虚幻引擎的源代码

关键似乎在于这个内部函数`GetWorldFromContextObject`

![image-20230113162909593](https://raw.githubusercontent.com/KSroido/ALLPIC/main/img/202301131629688.png)

它的主要作用是通过输入一个指向任何物体的指针, 返回这个物体所在世界的世界指针

创造这样的函数的原因可能是因为开发者认为指定一个世界是confused, 而寻找特定世界的任意物件是reasonable



# openlevel和clientTravel的区别

当二者都用于LAN网络下的游戏远程连接时, 二者都相当于`CallClientTravel` 然后`SetClientTravel` 函数

推荐用后者, 除非必须要用前者, 这里是我看源代码半猜测的, 不一定正确, 没有找到特别可信的英文资料

似乎 clientTravel等同于有多种标识符的openlevel

另外clientTravel在设计上就是和serverTravel成对使用的

![image-20230113163710426](https://raw.githubusercontent.com/KSroido/ALLPIC/main/img/202301131637484.png)

![image-20230113163741690](https://raw.githubusercontent.com/KSroido/ALLPIC/main/img/202301131637757.png)



# 为什么 openlevel需要传入context this指针而ClientTravel不需要传入

我猜测可能是和所在类有关的

ClientTravel是playerController的成员函数

而openlevel是UBlueprintFunctionLibrary的派生类UGameplayStatics的成员函数

ClientTravel里面自行调用了getWorld,因为他是作用于Actor

而openlevel从源代码上来看, 似乎是可以作用于一般性obj的(但我没做过实际测试) 

![image-20230113164740023](https://raw.githubusercontent.com/KSroido/ALLPIC/main/img/202301131647060.png)

所以前者不需要传入this指针,因为在函数内会自动getworld操作

但是后者需要传入一个指针,然后验证其是否存在于一个合法的world

# getWorld源码解析

`GetWorldFromContextObject` 和getWorld都会调用 getlevel

但是getlevel没太看懂, 似乎意味着UE4引擎底层允许level的嵌套, 类似链表那样

最外层的level定义为 world

但是我这边没找到如何嵌套两层以上level的办法,似乎在引擎中的正常做法就是一层level+一层world,顶层的level又称作world

![image-20230113170344755](https://raw.githubusercontent.com/KSroido/ALLPIC/main/img/202301131703782.png)

![image-20230113170354887](https://raw.githubusercontent.com/KSroido/ALLPIC/main/img/202301131703917.png)

![image-20230113170519288](https://raw.githubusercontent.com/KSroido/ALLPIC/main/img/202301131705337.png)

另外actor和obj的底层区别在world层面也是存在的, 但是还看不太懂, 似乎普通的obj只可能存在于一层或两层的level中

而actor可以存在于任意深的level

源代码似乎是这样的意思,但是具体还是不太看得懂



# 添加steam网络连接插件到build文件中

首先在插件里面enable online subsystem steam插件

然后再游戏源码里面 .build.cs文件中

加入public dependency

![image-20230113175045140](https://raw.githubusercontent.com/KSroido/ALLPIC/main/img/202301131750229.png)

![image-20230113175145966](https://raw.githubusercontent.com/KSroido/ALLPIC/main/img/202301131751998.png)

这里需要添加两个插件 这两个插件是完全不同的, 是两个不同的抽象层, 我们只需要对Onlinesubsystem抽象层负责, 该抽象层需要对OnlinesubsystemSteam负责, 而后者需要对steam服务器层负责



然后打开defaultEngin.ini

添加:(自行去除注释, 那些注释是非法内容(中文))

```
[/Script/Engine.GameEngine]//加入特定网络环境需要的驱动文件, 提示编译器需要将其编入
+NetDriverDefinitions=(DefName="GameNetDriver",DriverClassName="OnlineSubsystemSteam.SteamNetDriver",DriverClassNameFallback="OnlineSubsystemUtils.IpNetDriver")

[OnlineSubsystem]//定义添加的网络环境
DefaultPlatformService=Steam


[OnlineSubsystemSteam]
bEnabled=true//启动该网路环境, 使其合法
SteamDevAppId=480

; If using Sessions
; bInitServerOnClient=true

[/Script/OnlineSubsystemSteam.SteamNetDriver]
NetConnectionClassName="OnlineSubsystemSteam.SteamNetConnection"
```

另外需要注意的一点是, 在编辑器中的游戏是预览版, 无法连接至steam api

# TSharedPtr的一个未遇到的问题

在一些写于UE5.0.0的教程中, 需要这样定义一个onlineInterface

```cpp
class IOnlineSessionPtr OnlineSessionInterface;
```

但是似乎在5.0.3中不能这样写

![image-20230113195249159](https://raw.githubusercontent.com/KSroido/ALLPIC/main/img/202301131952225.png)

必须要把elaborated type specifier去除

报错提示为: already typedef-ed

看起来十分矛盾



发现这个问题的原始原因了, 是include结构的问题, 只需要恰当include就可以避免, 所以可以当作没看见本条

# 打印 steam连接 debug log

```cpp
GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Blue,
				FString::Printf(TEXT("Found Online subsystem %s"), *OnlineSubsystem->GetSubsystemName().ToString())
			);
```

# 如何让win10原始账户获取C盘完全访问权

由于UE5默认放在C盘, 有的时候会没有权限操作

对于专业版win10解决办法很简单

gpedit.msc打开策略组

禁用这两个东西

![image-20230113233437808](https://raw.githubusercontent.com/KSroido/ALLPIC/main/img/202301132335862.png)

重启

非专业版请自行搜索解决

# 委托: 什么是委托

委托简单来说就是一种对回调函数的包装

其本质是储存一个或多个函数指针的数据结构

该数据结构, 即委托存储了这些函数指针, 但是并不关心这些函数指针所指向的函数的作用或者副作用

当特定回调事件触发时, 委托化身为另一层包装: 通信组件

如果做过linux或者安卓开发的话可能更容易理解

简单来说就是委托除了储存一个或一些函数指针外, 还需要储存这些函数指针负责的对象, 当回调事件触发时, 向这些对象发出信号



理论如上, 工程实现请看图

![image-20230115060551243](C:/Users/91410/AppData/Roaming/Typora/typora-user-images/image-20230115060551243.png)

简单来说就是, 回调函数塞到委托里面, 委托塞到interface里面

这样当interface创建会话成功后, 就会去list的委托里面找委托, 委托就会找回调函数并且调用

# ThisClass 保留字

在UE中 ThisClass是一个保留字, 用来指代当前所在文件

比如, 如果你在角色蓝图对应的cpp文件里面, 这个保留字就相当于角色类





# 在屏幕上添加debug信息

```cpp
if (GEngine){//检查GEngine是否存在, 虽然我也不知道什么情况下会不存在
	GEngine->AddOnScreenDebugMessage(
		-1,//暂时不清楚作用
		15.f,//消息持续时间
		FColor::Blue,//消息颜色
		FString::Printf(TEXT("Found subsystem %s"), *OnlineSubsystem->GetSubsystemName().ToString())
		//Printf的函数签名返回值类型不是void 而是FString
		//GetSubsystemName() getXXXName 返回的是FName 所以需要ToString转换成FString
		//但是由于被Printf接收格式化参数, 所以需要转换成C-style, 前面加个dereference
		//Printf会将格式化后的结果输出一个FString类型的字符串作为参数传递给AddOnScreenDebugMessage
	);
}
```

