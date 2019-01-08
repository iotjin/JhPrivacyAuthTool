# JhPrivacyAuthTool
隐私权限判断 - 封装了几种常用的隐私权限判断(定位服务,通讯录, 日历,提醒事项, 照片, 蓝牙共享,麦克风, 相机)和通知的注册和判断。<br> 
定位服务,蓝牙共享是单独调用的,  有两种提示权限的方式,一种是跳转去开启,一种是只提示信息,<br> 
可以在 - (void)pushSetting:(BOOL)isPushSetting 方法中添加自己习惯使用的弹框提示没有开启权限

![](https://raw.githubusercontent.com/iotjin/JhPrivacyAuthTool/master/JhPrivacyAuthTool/screenshots/0.png)  <br> 
![](https://raw.githubusercontent.com/iotjin/JhPrivacyAuthTool/master/JhPrivacyAuthTool/screenshots/1.png)  <br> 
![](https://raw.githubusercontent.com/iotjin/JhPrivacyAuthTool/master/JhPrivacyAuthTool/screenshots/2.png)  <br> 
![](https://raw.githubusercontent.com/iotjin/JhPrivacyAuthTool/master/JhPrivacyAuthTool/screenshots/3.png)  

## Examples


* 通用
```

         __block BOOL boolValue = NO;
        [[JhPrivacyAuthTool shareInstance]CheckPrivacyAuthWithType:JhPrivacyType_Photos isPushSetting:NO withHandle:^(BOOL granted, JhAuthStatus status) {
            boolValue = granted;
            NSLog(@" 授权状态 %ld ",(long)status);
        }];
        NSLog(@" 是否授权: %@", boolValue ? @"YES" : @"No");
        if(boolValue ==YES){
            //要进行的操作
        }

```
* 定位
```
 [[JhPrivacyAuthTool shareInstance]CheckLocationAuthWithisPushSetting:YES withHandle:^(JhLocationAuthStatus status) {
            NSLog(@" 定位服务授权状态 %ld ",(long)status);
            
        }];
```
* 蓝牙
```
 [[JhPrivacyAuthTool shareInstance]CheckBluetoothAuthWithisPushSetting:YES withHandle:^(JhCBManagerStatus status) {
            NSLog(@" 蓝牙授权状态 %ld ",(long)status);
        }];
```



* 通知注册
```
   [JhPrivacyAuthTool RequestNotificationAuth];
   
```

* 检查通知权限
```
[[JhPrivacyAuthTool shareInstance]CheckNotificationAuthWithisPushSetting:YES];

```
