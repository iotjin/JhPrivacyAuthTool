//
//  ViewController.m
//  JhPrivacyAuthTool
//
//  Created by Jh on 2018/12/20.
//  Copyright © 2018 Jh. All rights reserved.
//

#import "ViewController.h"
#import "JhPrivacyAuthTool.h"


#define Kwidth  [UIScreen mainScreen].bounds.size.width
#define Kheight  [UIScreen mainScreen].bounds.size.height

@interface ViewController ()<UITableViewDelegate,UITableViewDataSource>

@property (nonatomic, strong) UITableView *tableView;
@property (nonatomic, strong) NSArray *modelArr;

@end

@implementation ViewController

-(NSArray *)modelArr{
    if (!_modelArr) {
        
        _modelArr = @[@"定位服务(单独调用)",@"通讯录", @"日历",@"提醒事项", @"照片", @"蓝牙共享(单独调用)",@"麦克风",@"语音识别(没写)", @"相机",@"健康",@"家庭",@"媒体与Apple Music",@"运动与健身",@"注册通知",@"检查通知权限"];
        
    }
    return _modelArr;
}



-(UITableView *)tableView{
    if (!_tableView) {
        
        self.tableView = [[UITableView alloc]initWithFrame:CGRectMake(0, 64, Kwidth, Kheight-64)];
        //self.tableView.separatorStyle = UITableViewCellSeparatorStyleNone;
        self.tableView.showsVerticalScrollIndicator = NO;
        self.tableView.dataSource=self;
        self.tableView.delegate=self;
        self.tableView.tableHeaderView = [[UIView alloc]initWithFrame:CGRectMake(0,0,0,15)];
        self.tableView.tableFooterView = [UIView new];
        [self.view addSubview:self.tableView];
        
    }
    return _tableView;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.title =@"隐私权限判断";
    [self tableView];
    
    
    
}

#pragma mark - Table view data source
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    
    return self.modelArr.count;
}


#pragma mark - 每行显示内容
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    //定义一个cell的标识
    NSString *ID = [NSString stringWithFormat:@"cell%ld%ld",(long)indexPath.section,(long)indexPath.row];
    // 2.从缓存池中取出cell
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:ID];
    // 3.如果缓存池中没有cell, 判断为空进行初始化  --（当拉动页面显示超过主页面内容的时候就会重用之前的cell，而不会再次初始化）
    if (!cell) {
        //设置样子为副标题在右侧
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:ID];
        
    }
    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator; //显示最右边的箭头
    cell.textLabel.textColor = [UIColor blackColor];
    cell.textLabel.font = [UIFont systemFontOfSize:15];
    //不显示选中颜色
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    cell.textLabel.text = self.modelArr[indexPath.row];
    return cell;
}

#pragma mark - 返回每一行对应的高度
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return 44;
}


#pragma mark - 选中某行的点击操作
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [tableView deselectRowAtIndexPath:indexPath animated:YES];// 取消选中
    
    //获取选中cell的textLabel
    UITableViewCell *cell = [tableView cellForRowAtIndexPath:[NSIndexPath indexPathForRow:indexPath.row inSection:indexPath.section]];
    
    NSString *text = cell.textLabel.text;
    
    NSLog(@" 选中cell  %@ ",text);
    NSLog(@" row --  %ld ,",(long)indexPath.row);
    
    if([text isEqualToString:@"定位服务(单独调用)"]){
        
        [[JhPrivacyAuthTool shareInstance]CheckLocationAuthWithisPushSetting:YES withHandle:^(JhLocationAuthStatus status) {
            NSLog(@" 定位服务授权状态 %ld ",(long)status);
            
        }];
        
        
    }else if([text isEqualToString:@"蓝牙共享(单独调用)"]){
        
        [[JhPrivacyAuthTool shareInstance]CheckBluetoothAuthWithisPushSetting:NO withHandle:^(JhCBManagerStatus status) {
            NSLog(@" 蓝牙授权状态 %ld ",(long)status);
        }];
        
    }else if([text isEqualToString:@"注册通知"]){
        
        [JhPrivacyAuthTool RequestNotificationAuth];
        
    }else if([text isEqualToString:@"检查通知权限"]){
        
        [[JhPrivacyAuthTool shareInstance]CheckNotificationAuthWithisPushSetting:YES];
        
    }else{
        
        int type = (int)indexPath.row;
        
        __block BOOL boolValue;
        [[JhPrivacyAuthTool shareInstance]CheckPrivacyAuthWithType:type isPushSetting:YES withHandle:^(BOOL granted, JhAuthStatus status) {
            boolValue = granted;
            NSLog(@" 授权状态 %ld ",(long)status);
        }];
        NSLog(@" 是否授权: %@", boolValue ? @"YES" : @"No");
        if(boolValue ==NO){
            return;
        }
        
        NSLog(@" 234129473871293847197834918232134123412341432 ");
        
    }
    
    
    
    
}

@end
