
#import <UIKit/UIKit.h>

#import "UIViewController+ISReveal.h"


typedef enum {
    ISRevealControllerDirectionNeutral = 0,
    ISRevealControllerDirectionLeft,
    ISRevealControllerDirectionRight
} ISRevealControllerDirection;

typedef enum {
    ISRevealControllerPanOptionDisabled     = 0x00,
    ISRevealControllerPanOptionLeftEnabled  = 0x01,
    ISRevealControllerPanOptionRightEnabled = 0x02
} ISRevealControllerPanOption;

@protocol ISRevealControllerDelegate;


@interface ISRevealController : UIViewController

@property (nonatomic, retain, readonly) UINavigationController      *mainNavigationController;
@property (nonatomic, retain, readonly) UIViewController            *subViewController;
@property (nonatomic, assign, readonly) ISRevealControllerDirection revealDirection;

@property (nonatomic, assign)           ISRevealControllerPanOption panOption;

@property (nonatomic, unsafe_unretained) id<ISRevealControllerDelegate> delegate;

- (id)initWithRootViewController:(UIViewController *)viewController;
- (void)setMainViewController:(UIViewController *)viewController
                     animated:(BOOL)animated
                        leave:(BOOL)leave;
- (void)setSubViewController:(UIViewController *)viewController
                   direction:(ISRevealControllerDirection)direction;
- (void)revealSubViewController:(UIViewController *)viewController
                      direction:(ISRevealControllerDirection)direction
                       animated:(BOOL)animated;
- (void)revealSubViewController:(UIViewController *)viewController
                      direction:(ISRevealControllerDirection)direction
                       animated:(BOOL)animated
                     completion:(void (^)(void))completion;

- (void)hideSubViewControllerAnimated:(BOOL)animated;
- (void)setFullOffsetEnabled:(BOOL)enabled
                    animated:(BOOL)animated
                  completion:(void (^)(void))completion;

@end


@protocol ISRevealControllerDelegate <NSObject>

- (void)revealController:(ISRevealController *)revealController
       didPanToDirection:(ISRevealControllerDirection)direction;

@end
