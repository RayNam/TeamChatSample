#import <Foundation/Foundation.h>

// ランキング取得設定
// ランキング期間
typedef NS_ENUM(NSUInteger, KLMRankingRange){
    KLMRankingRangeToday = 0,
    KLMRankingRangeWeek,
    KLMRankingRangeAll,
    KLMRankingRangeLastWeek,
};

// ランキングカーソル位置
typedef NS_ENUM(NSUInteger, KLMRankingCursorOrigin){
    KLMRankingCursorOriginTop = 0,
    KLMRankingCursorOriginSelf,
};

@interface NKRanking : NSObject

+ (NKRanking *)sharedRanking;

-(void)deleteSavedRankings;

-(NSString *)rankingRangeToString:(KLMRankingRange) range;
-(NSString *)cursorOriginToString:(KLMRankingCursorOrigin) cursorOrigin;

@end
