#import <UIKit/UIKit.h>

@interface NKCloseButton : UIButton

@property (readonly, retain, nonatomic) UIActivityIndicatorView *indicatorView;

- (void)showIndicator;
- (void)hideIndicator;

@end
