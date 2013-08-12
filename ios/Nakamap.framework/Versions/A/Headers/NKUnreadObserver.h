#import <Foundation/Foundation.h>

@interface NKUnreadObserver : NSObject

@property NSTimeInterval refreshInterval;
@property (readonly, nonatomic) BOOL observing;
@property (readonly, nonatomic) NSInteger count;
@property (readonly, retain, nonatomic) NSString *countString;
@property (nonatomic)           BOOL ignoreOfficialGroups;

+ (NKUnreadObserver *)sharedObserver;
- (void)startObserving;
- (void)stopObserving;
- (void)updateUnreadCount;
- (void)refresh;
- (void)setSelfCounter;

@end
