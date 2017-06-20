//
//  NativeCodeLauncher.h
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/27.
//
//

#ifndef NativeCodeLauncher_h
#define NativeCodeLauncher_h

namespace Cocos2dExt {
    class NativeCodeLauncher
    {
    public:
        // GameCenter
        static void loginGameCenter();
        static void openRanking();
        static void postHighScore(int kind,int score);
        static void openAchievement();
        static void postAchievement(int kind,int percentComplete);
    };
}

#endif /* NativeCodeLauncher_h */
