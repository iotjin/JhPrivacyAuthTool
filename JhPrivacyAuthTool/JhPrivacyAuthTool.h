//
//  JhPrivacyAuthTool.h
//  
//
//  Created by Jh on 2018/12/18.
//  Copyright © 2018 Jh. All rights reserved.
//

/**

 __block BOOL boolValue;
 [[JhPrivacyAuthTool shareInstance]CheckPrivacyAuthWithType:type isPushSetting:NO withHandle:^(BOOL granted, JhAuthStatus status) {
 boolValue = granted;
 NSLog(@" 授权状态 %ld ",(long)status);
 }];
 NSLog(@" 是否授权: %@", boolValue ? @"YES" : @"No");
 if(boolValue ==NO){
 return;
 }
 
 [[JhPrivacyAuthTool shareInstance]CheckLocationAuthWithisPushSetting:YES withHandle:^(JhLocationAuthStatus status) {
 NSLog(@" 定位服务授权状态 %ld ",(long)status);
 }];
 
 [[JhPrivacyAuthTool shareInstance]CheckBluetoothAuthWithisPushSetting:YES withHandle:^(JhCBManagerStatus status) {
 NSLog(@" 蓝牙授权状态 %ld ",(long)status);
 }];

 return;
 


 */


#import <Foundation/Foundation.h>



typedef NS_ENUM(NSInteger, JhPrivacyType)
{
    JhPrivacyType_LocationServices       =0,    // 定位服务
    JhPrivacyType_Contacts                 ,    // 通讯录
    JhPrivacyType_Calendars                ,    // 日历
    JhPrivacyType_Reminders                ,    // 提醒事项
    JhPrivacyType_Photos                   ,    // 照片
    JhPrivacyType_BluetoothSharing         ,    // 蓝牙共享
    JhPrivacyType_Microphone               ,    // 麦克风
    JhPrivacyType_SpeechRecognition        ,    // 语音识别 >= iOS10
    JhPrivacyType_Camera                   ,    // 相机
    JhPrivacyType_Health                   ,    // 健康 >= iOS8.0
    JhPrivacyType_HomeKit                  ,    // 家庭 >= iOS8.0
    JhPrivacyType_MediaAndAppleMusic       ,    // 媒体与Apple Music >= iOS9.3
    JhPrivacyType_MotionAndFitness         ,    // 运动与健身

};

//对应类型权限状态，参考PHAuthorizationStatus等
typedef NS_ENUM(NSInteger, JhAuthStatus)
{
    /** 用户从未进行过授权等处理，首次访问相应内容会提示用户进行授权 */
    JhAuthStatus_NotDetermined  = 0,
    /** 已授权 */
    JhAuthStatus_Authorized     = 1,
    /** 拒绝 */
    JhAuthStatus_Denied         = 2,
    /** 应用没有相关权限，且当前用户无法改变这个权限，比如:家长控制 */
    JhAuthStatus_Restricted     = 3,
    /** 硬件等不支持 */
    JhAutStatus_NotSupport     = 4,
    
};

//定位权限状态，参考CLAuthorizationStatus
typedef NS_ENUM(NSUInteger, JhLocationAuthStatus){
    JhLocationAuthStatus_NotDetermined         = 0, // 用户从未进行过授权等处理，首次访问相应内容会提示用户进行授权
    JhLocationAuthStatus_Authorized            = 1, // 一直允许获取定位 ps：< iOS8用
    JhLocationAuthStatus_Denied                = 2, // 拒绝
    JhLocationAuthStatus_Restricted            = 3, // 应用没有相关权限，且当前用户无法改变这个权限，比如:家长控制
    JhLocationAuthStatus_NotSupport            = 4, // 硬件等不支持
    JhLocationAuthStatus_AuthorizedAlways      = 5, // 一直允许获取定位
    JhLocationAuthStatus_AuthorizedWhenInUse   = 6, // 在使用时允许获取定位
};

//蓝牙状态，参考 CBManagerState
typedef NS_ENUM(NSUInteger, JhCBManagerStatus){
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
typedef void (^ResultBlock) (BOOL granted,JhAuthStatus status);



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





@interface JhPrivacyAuthTool : NSObject

+(instancetype)shareInstance;

@property (nonatomic, assign) JhPrivacyType PrivacyType;
@property (nonatomic, assign) JhAuthStatus AuthStatus;
@property (nonatomic, assign) JhCBManagerStatus CBManagerStatus;


/**
 检查和请求对应类型的隐私权限

 @param type 类型
 @param isPushSetting 当拒绝时是否跳转设置界面开启权限 (为NO时 只提示信息)
 @param ResultBlock 对应类型状态回调
 */
- (void)CheckPrivacyAuthWithType:(JhPrivacyType)type
                   isPushSetting:(BOOL)isPushSetting
                      withHandle:(ResultBlock)ResultBlock;



/**
 检查和请求 定位权限
 
 @param isPushSetting 当拒绝时是否跳转设置界面开启权限 (为NO时 只提示信息)
 @param ResultBlock 定位状态回调
 */
- (void)CheckLocationAuthWithisPushSetting:(BOOL)isPushSetting
                                 withHandle:(LocationResultBlock)ResultBlock;


/**
 检查和请求 蓝牙权限

 @param isPushSetting 当拒绝时是否跳转设置界面开启权限 (为NO时 只提示信息)
 @param ResultBlock 蓝牙状态回调
 */
- (void)CheckBluetoothAuthWithisPushSetting:(BOOL)isPushSetting
                      withHandle:(BluetoothResultBlock)ResultBlock;



/**
 检测通知权限状态

 @param isPushSetting 当拒绝时是否跳转设置界面开启权限 (为NO时 只提示信息)
 */
- (void)CheckNotificationAuthWithisPushSetting:(BOOL)isPushSetting;


/**
 注册通知
 */
+(void)RequestNotificationAuth;

@end


