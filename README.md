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
