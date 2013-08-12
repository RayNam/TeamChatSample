//
//  KLMPopOverController.h
//  Nakamap
//
//  Created by takahashi-kohei on 2013/07/04.
//
//

#import <Foundation/Foundation.h>
#import "KLMSingleton.h"

typedef enum {
    KLMPopOverArrowDirectionUp,
    KLMPopOverArrowDirectionLeft,
    KLMPopOverArrowDirectionRight,
} KLMPopOverArrowDirection;

@interface KLMPopOverController : KLMSingleton
@property (assign, nonatomic) CGPoint origin;
@property (assign, nonatomic) KLMPopOverArrowDirection direction;
+ (void) ignition;
+ (instancetype)instance;
- (void)showInView:(UIView*)view withController:(UIViewController*)viewController;
- (UIPopoverController*)popoverController;
- (float)popoverDiff;

@end
