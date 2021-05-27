# JhPrivacyAuthTool

iOS隐私权限判断 - 封装了常用的隐私权限判断(定位服务,通讯录, 日历,提醒事项, 照片, 蓝牙,麦克风, 语音识别,相机,健康,媒体与Apple Music)和通知的注册和判断。<br> 

## [iOS - Info.plist 隐私权限配置(持续更新)](https://blog.csdn.net/iotjin/article/details/117284738)

 <br> 

 ## 注： <br> 

- 定位服务、蓝牙共享是单独调用的
- 健康有两种调用方式，默认是步数，单独调用可设置类型
- 有两种提示权限的方式：一种是跳转去开启，一种是只提示信息。
- 健康和HomeKit需要配置证书
- 可以在 `- (void)pushSetting:(BOOL)isPushSetting` 方法中改为自己熟悉的弹框来处理没有开启权限的情况
<br> 
<br> 



<details>
   <summary><strong>Info.plist 隐私权限配置</strong></summary>

```objc
<key>NSLocationWhenInUseUsageDescription</key>
 <string>APP需要您的同意，才能在使用时获取位置信息，以便于搜索附近的xxx位置</string>
 <key>NSLocationAlwaysAndWhenInUseUsageDescription</key>
 <string>App需要您的同意，才能访问位置信息，以便于搜索附近的xxx位置</string>
 <key>NSLocationAlwaysUsageDescription</key>
 <string>App需要您的同意，才能始终访问位置信息，以便于搜索附近的xxx位置</string>
 <key>NSLocationUsageDescription</key>
 <string>APP需要您的同意，才能访问位置信息，以便于搜索附近的xxx位置</string>
 <key>NSContactsUsageDescription</key>
 <string>APP需要您的同意，才能访问通讯录 (通讯录信息仅用于查找联系人，并会得到严格保密)</string>
 <key>NSCalendarsUsageDescription</key>
 <string>APP需要您的同意，才能访问日历，以便于获取更好的使用体验</string>
 <key>NSRemindersUsageDescription</key>
 <string>APP需要您的同意，才能访问提醒事项，以便于获取更好的使用体验</string>
 <key>NSPhotoLibraryUsageDescription</key>
 <string>APP需要您的同意，才能访问相册，以便于图片选取、上传、发布</string>
 <key>NSPhotoLibraryAddUsageDescription</key>
 <string>APP需要您的同意，才能访问相册，以便于保存图片</string>
 <key>NSBluetoothPeripheralUsageDescription</key>
 <string>APP需要您的同意，才能使用蓝牙</string>
 <key>NSBluetoothAlwaysUsageDescription</key>
 <string>APP需要您的同意，才能始终使用蓝牙</string>
 <key>NSLocalNetworkUsageDescription</key>
 <string>App不会连接到您所用网络上的设备，只会检测与您本地网关的连通性。用户也可以在 iOS 设备的设置-隐私-本地网络界面修改此App的权限设置。</string>
 <key>NSMicrophoneUsageDescription</key>
 <string>APP需要您的同意，才能使用麦克风，以便于视频录制、语音识别、语音聊天</string>
 <key>NSSpeechRecognitionUsageDescription</key>
 <string>APP需要您的同意，才能进行语音识别，以便于获取更好的使用体验</string>
 <key>NSCameraUsageDescription</key>
 <string>APP需要您的同意，才能使用摄像头，以便于相机拍摄，上传、发布照片</string>
 
 <key>NSFaceIDUsageDescription</key>
 <string>APP需要您的同意，才能获取人脸识别权限</string>
 <key>NSSiriUsageDescription</key>
 <string>APP需要您的同意，才能获取Siri使用权限</string>
 
 <key>NSHealthClinicalHealthRecordsShareUsageDescription</key>
 <string>APP需要您的同意，才能获取健康记录权限</string>
 <key>NSHealthShareUsageDescription</key>
 <string>APP需要您的同意，才能获取健康分享权限</string>
 <key>NSHealthUpdateUsageDescription</key>
 <string>APP需要您的同意，才能获取健康更新权限</string>
 <key>NSHomeKitUsageDescription</key>
 <string>APP需要您的同意，才能获取HomeKit权限</string>
 <key>NSMotionUsageDescription</key>
 <string>APP需要您的同意，才能获取运动与健身权限</string>
 <key>kTCCServiceMediaLibrary</key>
 <string>APP需要您的同意，才能获取音乐权限</string>
 <key>NSAppleMusicUsageDescription</key>
 <string>APP需要您的同意，才能获取媒体库权限权限</string>
 <key>NSVideoSubscriberAccountUsageDescription</key>
 <string>APP需要您的同意，才能获取AppleTV使用权限</string>
```
</details>



<br> 

# 效果图

<br> 

| <img src="https://raw.githubusercontent.com/iotjin/JhPrivacyAuthTool/master/JhPrivacyAuthTool/screenshots/0.png" width="187" height="419"> | <img src="https://raw.githubusercontent.com/iotjin/JhPrivacyAuthTool/master/JhPrivacyAuthTool/screenshots/1.png" width="187" height="419"> | <img src="https://raw.githubusercontent.com/iotjin/JhPrivacyAuthTool/master/JhPrivacyAuthTool/screenshots/2.png" width="187" height="419"> |
| ------ | ------ | ------ |
| <img src="https://raw.githubusercontent.com/iotjin/JhPrivacyAuthTool/master/JhPrivacyAuthTool/screenshots/3.png" width="187" height="419"> | <img src="https://raw.githubusercontent.com/iotjin/JhPrivacyAuthTool/master/JhPrivacyAuthTool/screenshots/4.png" width="187" height="419"> | <img src="https://raw.githubusercontent.com/iotjin/JhPrivacyAuthTool/master/JhPrivacyAuthTool/screenshots/5.png" width="187" height="419"> |
| <img src="https://raw.githubusercontent.com/iotjin/JhPrivacyAuthTool/master/JhPrivacyAuthTool/screenshots/6.png" width="187" height="419"> | <img src="https://raw.githubusercontent.com/iotjin/JhPrivacyAuthTool/master/JhPrivacyAuthTool/screenshots/7.png" width="187" height="419"> | <img src="https://raw.githubusercontent.com/iotjin/JhPrivacyAuthTool/master/JhPrivacyAuthTool/screenshots/8.png" width="187" height="419"> |
| <img src="https://raw.githubusercontent.com/iotjin/JhPrivacyAuthTool/master/JhPrivacyAuthTool/screenshots/9.png" width="187" height="419"> | <img src="https://raw.githubusercontent.com/iotjin/JhPrivacyAuthTool/master/JhPrivacyAuthTool/screenshots/10.png" width="187" height="419"> | <img src="https://raw.githubusercontent.com/iotjin/JhPrivacyAuthTool/master/JhPrivacyAuthTool/screenshots/11.png" width="187" height="419">


## Examples

* 通用
```objectivec
__block BOOL boolValue;
[[JhPrivacyAuthTool shareInstance]CheckPrivacyAuthWithType:JhPrivacyType_Photos isPushSetting:YES block:^(BOOL granted, JhAuthStatus status) {
    boolValue = granted;
    NSLog(@" 授权状态 %ld ",(long)status);
    if (granted == YES) {
        NSLog(@" 2222222222222222222222222222222222 ");
        NSLog(@" 已授权 ");
        //要进行的操作
    }
}];
```
* 定位
```objectivec
[[JhPrivacyAuthTool shareInstance]CheckLocationAuth:YES block:^(JhLocationAuthStatus status) {
    NSLog(@" 定位服务授权状态 %ld ",(long)status);
}];
```
* 蓝牙
```objectivec
[[JhPrivacyAuthTool shareInstance]CheckBluetoothAuth:YES block:^(JhCBManagerStatus status) {
    NSLog(@" 蓝牙授权状态 %ld ",(long)status);
}];
```

* 健康
```objectivec
//默认调用，默认为步数
[[JhPrivacyAuthTool shareInstance]CheckPrivacyAuthWithType:JhPrivacyType_Health isPushSetting:YES block:^(BOOL granted, JhAuthStatus status) {
    NSLog(@" 健康授权状态 %ld ",(long)status);
    if (granted == YES) {
        //要进行的操作
    }
}];

//单独调用，设置为心率
[[JhPrivacyAuthTool shareInstance]CheckHealthAuth:YES hkObjectType:[HKObjectType quantityTypeForIdentifier:HKQuantityTypeIdentifierHeartRate] block:^(BOOL granted, JhAuthStatus status) {
    NSLog(@" 健康授权状态 %ld ",(long)status);
    if (granted == YES) {
        //要进行的操作
    }
}];
```

* 通知注册
```objectivec
[JhPrivacyAuthTool RequestNotificationAuth];
```

* 检查通知权限
```objectivec
[[JhPrivacyAuthTool shareInstance]CheckNotificationAuth:YES block:^(BOOL granted, JhAuthStatus status) {
    NSLog(@" 通知授权状态 %ld ",(long)status);
}];
```
