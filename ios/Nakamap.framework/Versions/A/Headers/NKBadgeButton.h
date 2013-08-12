#import <UIKit/UIKit.h>

@interface NKBadgeButton : UIButton

@property (assign, nonatomic) CGPoint offsetToHide;
@property (readonly, retain, nonatomic) UILabel *countLabel;

- (void)refreshTitleString;

@end
