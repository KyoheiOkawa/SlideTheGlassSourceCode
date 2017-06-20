//
//  NativeCodeLauncher_objc.m
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/27.
//
//

#import <Foundation/Foundation.h>
#import <GameKit/GameKit.h>
#import "AppController.h"

@implementation NativeCodeLauncher

// GameCenterへのログインチェック
+(void)loginGameCenter
{
    GKLocalPlayer *localPlayer = [GKLocalPlayer localPlayer];
    [localPlayer authenticateWithCompletionHandler:^(NSError *error) {
        if(localPlayer.authenticated)
        {
            
        }
        else
        {
            
        }
    }];
}
// Leaderboardを開く
+(void)openRanking
{
    GKLocalPlayer *localPlayer = [GKLocalPlayer localPlayer];
    if(localPlayer.authenticated)
    {
        AppController *appController = (AppController *)[UIApplication sharedApplication].delegate;
        
        GKLeaderboardViewController *leaderboardController = [[GKLeaderboardViewController alloc]init];
        leaderboardController.timeScope = GKLeaderboardTimeScopeAllTime;
        leaderboardController.leaderboardDelegate = appController.viewController;
        
        [appController.viewController presentModalViewController:leaderboardController animated:YES];
    }
    else
    {
        NSString *alertTitle = @"";
        NSString *alertMessage = @"Login Game Center\nGame Centerへのログインが必要です。";
        UIAlertView *alertView = [[UIAlertView alloc]initWithTitle:alertTitle message:alertMessage
                                                          delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
        [alertView show];
    }
}
// Leaderboardへの得点送信
+(void)postHighScore:(NSNumber *)kind score:(NSNumber *)score;
{
    GKLocalPlayer *localPlayer = [GKLocalPlayer localPlayer];
    if([localPlayer isAuthenticated])
    {
        NSString *idName = @"";
        
        switch ([kind intValue]) {
            case 1:
                idName = @"MyIDName";
                break;
            case 2:
                idName = @"YYY";
                break;
            default:
                break;
        }
        
        GKScore *gkScore = [[GKScore alloc]initWithCategory:idName];
        gkScore.value = [score longLongValue];
        gkScore.context = 1;
        [gkScore reportScoreWithCompletionHandler:^(NSError *error) {
            if(error)
            {
                NSLog(@"Error : %@",error);
            }
            else
            {
                NSLog(@"Sent highscore.");
            }
        }];
    }
    else
    {
        NSLog(@"Gamecenter not authenticated.");
    }
}
// Achievementを開く
+(void)openAchievement
{
    GKLocalPlayer *localPlayer = [GKLocalPlayer localPlayer];
    if(localPlayer.authenticated)
    {
        AppController *appController = (AppController *)[UIApplication sharedApplication].delegate;
        
        GKAchievementViewController *achievementController = [[GKAchievementViewController alloc]init];
        achievementController.achievementDelegate = appController.viewController;
        
        [appController.viewController presentModalViewController:achievementController animated:YES];
        
    }
    else
    {
        NSString *alertTitle = @"";
        NSString *alertMessage = @"Game Centerへのログインが必要です。";
        UIAlertView *alertView = [[UIAlertView alloc]initWithTitle:alertTitle message:alertMessage
                                                          delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
        [alertView show];
    }
}
// 達成項目の達成度を送信
+(void)postAchievement:(NSNumber *)kind percent:(NSNumber *)percentComplete
{
    GKLocalPlayer *localPlayer = [GKLocalPlayer localPlayer];
    if([localPlayer isAuthenticated])
    {
        NSString *idName = @"";
        
        switch ([kind intValue]) {
            case 1:
                idName = @"XXX";
                break;
            case 2:
                idName = @"YYY";
                break;
            default:
                break;
        }
        
        GKAchievement *achievement = [[GKAchievement alloc] initWithIdentifier:idName];
        achievement.percentComplete = [percentComplete doubleValue];
        achievement.showsCompletionBanner = YES;
        [achievement reportAchievementWithCompletionHandler:^(NSError *error) {
            if(error)
            {
                NSLog(@"Error : %@",error);
            }
            else
            {
                NSLog(@"Sent Achievement.");
            }
        }];
    }
    else
    {
        NSLog(@"Gamecenter not authenticated.");
    }
}

@end
