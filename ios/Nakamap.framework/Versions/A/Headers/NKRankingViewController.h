//
//  NKRankingViewController.h
//  Nakamap
//
//  Created by organlounge on 2013/05/23.
//
//

#import <UIKit/UIKit.h>

#import "NKRanking.h"

@interface NKRankingViewController : UIViewController <UIWebViewDelegate>

@property (retain, nonatomic) IBOutlet UINavigationBar *navigationBar;
@property (retain, nonatomic) IBOutlet UIWebView *webView;

+ (NKRankingViewController *)create;

- (void)openRankingList;
- (void)openRankingListWithUser:(NSString *)uid;
- (void)openRankingEntriesWithRankingID:(NSString *)rankingID
                                   type:(KLMRankingRange)type
                                 origin:(KLMRankingCursorOrigin)origin
                                 cursor:(NSInteger)cursor
                                  limit:(NSInteger)limit;

@end
