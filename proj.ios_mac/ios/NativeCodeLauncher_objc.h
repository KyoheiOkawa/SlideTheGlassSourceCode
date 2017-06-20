//
//  NativeCodeLauncher_objc.h
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/27.
//
//

#ifndef NativeCodeLauncher_objc_h
#define NativeCodeLauncher_objc_h

@interface NativeCodeLauncher : NSObject

// GameCenter
+(void)loginGameCenter;
+(void)openRanking;
+(void)postHighScore:(NSNumber *)kind score:(NSNumber *)score;
+(void)openAchievement;
+(void)postAchievement:(NSNumber *)kind percent:(NSNumber *)percentComplete;

@end

#endif /* NativeCodeLauncher_objc_h */
