#import <UIKit/UIKit.h>
#import "ISRevealController.h"

@class NKGroupInfo;
@class NKCloseButton;
@class KLMHomeGroupListViewController;

@interface NKNakamapViewController :ISRevealController

@property BOOL autoRotationEnabled;
@property BOOL customTransitionEnabled;
@property BOOL dismissesAtEnteringBackground;
@property (retain, nonatomic) NKGroupInfo *defaultGroupInfo;
@property (readonly, retain, nonatomic) NKCloseButton *closeButton;

- (void)dismiss;
- (void)openURL:(NSURL *)URL;
- (void)openPage:(NKNakamapPageType)type;
- (void)openChatWithGroupID:(NSString *)groupID chatName:(NSString *)name;

@end

