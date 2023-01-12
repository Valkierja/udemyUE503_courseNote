# test_muti_4

Developed with Unreal Engine 5

這裏直接就當作小筆記區域了

# git-windows在http/https下傳輸大文件時會報錯
由於本項目較大, 因此需要手動修改傳輸buffer 同時手動指定HTTP/1.1協議
如果覺得這樣太麻煩, 也可以采用ssh-git的方式, 這種方式不會遇到上述報錯
```
[http]                                                                                                                         
  version = HTTP/1.1                                                                                                      
  postBuffer = 524288000                                                                                                 
  proxy = socks5://127.0.0.1:10808                                                                                
[https]                                                                                                                        
  postBuffer = 524288000                                                                                                  
  proxy = socks5://127.0.0.1:10808                                                                                ~                                         
