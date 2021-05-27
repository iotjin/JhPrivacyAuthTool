//
//  JhPrivacyAuthTool.h
//
//
//  Created by Jh on 2018/12/18.
//  Copyright © 2018 Jh. All rights reserved.
//


#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, JhPrivacyType) {
    JhPrivacyTypeLocationServices      = 0,    // 定位服务
    JhPrivacyTypeContacts                 ,    // 通讯录
    JhPrivacyTypeCalendars                ,    // 日历
    JhPrivacyTypeReminders                ,    // 提醒事项
    JhPrivacyTypePhotos                   ,    // 照片
    JhPrivacyTypeBluetoothSharing         ,    // 蓝牙共享
    JhPrivacyTypeMicrophone               ,    // 麦克风
    JhPrivacyTypeSpeechRecognition        ,    // 语音识别 >= iOS10
    JhPrivacyTypeCamera                   ,    // 相机
    JhPrivacyTypeHealth                   ,    // 健康 >= iOS8.0 ，需要证书
    JhPrivacyTypeHomeKit                  ,    // 家庭 >= iOS8.0 ，需要证书
    JhPrivacyTypeMediaAndAppleMusic       ,    // 媒体与Apple Music >= iOS9.3
    JhPrivacyTypeMotionAndFitness         ,    // 运动与健身 >= iOS11.0
};

//对应类型权限状态，参考PHAuthorizationStatus等
typedef NS_ENUM(NSInteger, JhAuthStatus) {
    /** 用户从未进行过授权等处理，首次访问相应内容会提示用户进行授权 */
    JhAuthStatusNotDetermined  = 0,
    /** 已授权 */
    JhAuthStatusAuthorized     = 1,
    /** 拒绝 */
    JhAuthStatusDenied         = 2,
    /** 应用没有相关权限，且当前用户无法改变这个权限，比如:家长控制 */
    JhAuthStatusRestricted     = 3,
    /** 硬件等不支持 */
    JhAutStatus_NotSupport      = 4,
};

//定位权限状态，参考CLAuthorizationStatus
typedef NS_ENUM(NSUInteger, JhLocationAuthStatus) {
    JhLocationAuthStatusNotDetermined         = 0, // 用户从未进行过授权等处理，首次访问相应内容会提示用户进行授权
    JhLocationAuthStatusAuthorized            = 1, // 一直允许获取定位 ps：< iOS8用
    JhLocationAuthStatusDenied                = 2, // 拒绝
    JhLocationAuthStatusRestricted            = 3, // 应用没有相关权限，且当前用户无法改变这个权限，比如:家长控制
    JhLocationAuthStatusNotSupport            = 4, // 硬件等不支持
    JhLocationAuthStatusAuthorizedAlways      = 5, // 一直允许获取定位
    JhLocationAuthStatusAuthorizedWhenInUse   = 6, // 在使用时允许获取定位
};

//蓝牙状态，参考 CBManagerState
typedef NS_ENUM(NSUInteger, JhCBManagerStatus) {
    JhCBManagerStatusUnknown         = 0,        // 未知状态
    JhCBManagerStatusResetting       = 1,        // 正在重置，与系统服务暂时丢失
    JhCBManagerStatusUnsupported     = 2,        // 不支持蓝牙
    JhCBManagerStatusUnauthorized    = 3,        // 未授权
    JhCBManagerStatusPoweredOff      = 4,        // 关闭
    JhCBManagerStatusPoweredOn       = 5,        // 开启并可用
};


/**
 对应类型隐私权限状态回调block
 
 @param granted 是否授权
 @param status 授权的具体状态
 */
typedef void (^ResultBlock) (BOOL granted, JhAuthStatus status);


/**
 定位状态回调block
 
 @param status 授权的具体状态
 */
typedef void(^LocationResultBlock)(JhLocationAuthStatus status);


/**
 蓝牙状态回调block
 
 @param status 授权的具体状态
 */
typedef void(^BluetoothResultBlock)(JhCBManagerStatus status);

@class HKObjectType;
@interface JhPrivacyAuthTool : NSObject

+ (instancetype)shareInstance;

@property (nonatomic, assign) JhPrivacyType PrivacyType;
@property (nonatomic, assign) JhAuthStatus AuthStatus;
@property (nonatomic, assign) JhCBManagerStatus CBManagerStatus;


/**
 检查和请求对应类型的隐私权限（定位、蓝牙不通过这个方法，单独调用）
 
 @param type 类型
 @param isPushSetting 当拒绝时是否跳转设置界面开启权限 (为NO时 只提示信息)
 @param block 对应类型状态回调
 */
- (void)CheckPrivacyAuthWithType:(JhPrivacyType)type
                   isPushSetting:(BOOL)isPushSetting
                           block:(ResultBlock)block;


/**
 检查和请求 定位权限
 
 @param isPushSetting 当拒绝时是否跳转设置界面开启权限 (为NO时 只提示信息)
 @param block 定位状态回调
 */
- (void)CheckLocationAuth:(BOOL)isPushSetting
                    block:(LocationResultBlock)block;


/**
 检查和请求 蓝牙权限
 
 @param isPushSetting 当拒绝时是否跳转设置界面开启权限 (为NO时 只提示信息)
 @param block 蓝牙状态回调
 */
- (void)CheckBluetoothAuth:(BOOL)isPushSetting
                     block:(BluetoothResultBlock)block;


/**
 检测通知权限状态
 
 @param isPushSetting 当拒绝时是否跳转设置界面开启权限 (为NO时 只提示信息)
 @param block 回调
 */
- (void)CheckNotificationAuth:(BOOL)isPushSetting
                        block:(ResultBlock)block;

/** 注册通知  */
+ (void)RequestNotificationAuth;


/**
 检查和请求 健康权限，需要证书 （也可以通过上面的方法调用）
 
 @param isPushSetting 当拒绝时是否跳转设置界面开启权限 (为NO时 只提示信息)
 @param hkObjectType  类型，传空默认为步数
 @param block 蓝牙状态回调
 */
- (void)CheckHealthAuth:(BOOL)isPushSetting
           hkObjectType:(HKObjectType * __nullable)hkObjectType
                  block:(ResultBlock)block;



@end



NS_ASSUME_NONNULL_END


/** 使用
 
 __block BOOL boolValue;
 [[JhPrivacyAuthTool shareInstance]CheckPrivacyAuthWithType:type isPushSetting:NO block:^(BOOL granted, JhAuthStatus status) {
 boolValue = granted;
 NSLog(@" 授权状态 %ld ",(long)status);
 if (granted == YES) {
 NSLog(@" 已授权 ");
 }
 }];
 NSLog(@" 是否授权: %@", boolValue ? @"YES" : @"No");
 if (boolValue == NO) {
 return;
 }
 
 [[JhPrivacyAuthTool shareInstance]CheckLocationAuth:YES block:^(JhLocationAuthStatus status) {
 NSLog(@" 定位服务授权状态 %ld ",(long)status);
 }];
 [[JhPrivacyAuthTool shareInstance]CheckBluetoothAuth:YES block:^(JhCBManagerStatus status) {
 NSLog(@" 蓝牙授权状态 %ld ",(long)status);
 }];
 
 //注册通知
 [JhPrivacyAuthTool RequestNotificationAuth];
 //检查通知权限
 [[JhPrivacyAuthTool shareInstance]CheckNotificationAuth:YES block:^(BOOL granted, JhAuthStatus status) {
 NSLog(@" 通知授权状态 %ld ",(long)status);
 }];
 
 */


/**
 Info.plist 隐私权限配置
 
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
 
 */
