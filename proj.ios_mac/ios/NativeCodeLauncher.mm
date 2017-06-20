#import "NativeCodeLauncher_objc.h"
#import "NativeCodeLauncher.h"

// GameCenterにログイン
static void static_loginGameCenter()
{
    [NativeCodeLauncher loginGameCenter];
}
// Leaderboard表示
static void static_openRanking()
{
    [NativeCodeLauncher openRanking];
}
// ハイスコアを送信
static void static_postHighScore(int kind,int score)
{
    [NativeCodeLauncher postHighScore:[NSNumber numberWithInt:kind]
                                score:[NSNumber numberWithInt:score]];
}
// Achievement表示
static void static_openAchievement()
{
    [NativeCodeLauncher openAchievement];
}
// 達成項目を送信
static void static_postAchievement(int kind,int percentComplete)
{
    [NativeCodeLauncher postAchievement:[NSNumber numberWithInt:kind]
                                percent:[NSNumber numberWithInt:percentComplete]];
}

namespace Cocos2dExt
{
    // GameCenter
    void NativeCodeLauncher::loginGameCenter()
    {
        static_loginGameCenter();
    }
    void NativeCodeLauncher::openRanking()
    {
        static_openRanking();
    }
    void NativeCodeLauncher::postHighScore(int kind, int score)
    {
        static_postHighScore( kind, score);
    }
    void NativeCodeLauncher::openAchievement()
    {
        static_openAchievement();
    }
    void NativeCodeLauncher::postAchievement(int kind, int percentComplete)
    {
        static_postAchievement(kind,percentComplete);
    }
}
