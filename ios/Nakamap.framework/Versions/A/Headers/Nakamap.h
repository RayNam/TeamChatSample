#import <UIKit/UIKit.h>

#import "NKConst.h"
#import "NKAPI.h"
#import "NKUser.h"
#import "NKInvitation.h"
#import "NKBadgeButton.h"
#import "NKCloseButton.h"
#import "NKUnreadObserver.h"
#import "NKConfiguration.h"
#import "NKNakamapViewController.h"

@interface Nakamap : NSObject

+ (BOOL)isReady;
+ (BOOL)isInstalled;
+ (BOOL)handleOpenURL:(NSURL *)URL;
+ (NSString *)appFromURL:(NSURL *)URL;
+ (NSString *)exprofileFromURL:(NSURL *)URL;
+ (BOOL)invitedFromURL:(NSURL *)URL;
+ (void)inviteInfoFromURL:(NSURL *)URL handler:(void (^)(BOOL enableInvited, NSDictionary *inviteInfo))handler;
+ (void)openInvitedGroup:(NSDictionary *)inviteInfo withController:(NKNakamapViewController *)controller;
+ (BOOL)isBindSuccess:(NSURL *)URL;
+ (void)debugReset;
+ (void)userReset;

#pragma mark - deprecated

+ (void)clear DEPRECATED_ATTRIBUTE;

// default group (use NKNakamapViewController.defaultGroupInfo)
+ (void)setGroupWithExternalID:(NSString *)externalID name:(NSString *)name UNAVAILABLE_ATTRIBUTE;

// account infomation (use [NKUser currentUser])
+ (NSString *)uid UNAVAILABLE_ATTRIBUTE;

// configuration (use NKConfiguration)
@property (nonatomic, retain) NSString *accountBaseName UNAVAILABLE_ATTRIBUTE;
@property (nonatomic, retain) NKInvitation *invitation UNAVAILABLE_ATTRIBUTE;

+ (Nakamap *)sharedClient UNAVAILABLE_ATTRIBUTE;
+ (void)setupWithClientID:(NSString *)clientID accountBaseName:(NSString *)newAccountBaseName DEPRECATED_ATTRIBUTE;

// friend chat (use NKAPI)
+ (BOOL)sentEncryptedID UNAVAILABLE_ATTRIBUTE;
+ (void)sendEncryptedExternalID:(NSString *)externalID IV:(NSString *)IV UNAVAILABLE_ATTRIBUTE;
+ (void)addFriendsWithExternalIDs:(NSArray *)externalIDs handler:(void (^)(BOOL succeeded))handler DEPRECATED_ATTRIBUTE;
+ (void)removeFriendsWithExternalID:(NSString *)externalID handler:(void (^)(BOOL succeeded))handler DEPRECATED_ATTRIBUTE;
+ (void)makeGroupWithName:(NSString *)name
              externalIDs:(NSArray *)externalIDs
                  handler:(void (^)(BOOL succeeded))handler DEPRECATED_ATTRIBUTE;

// stamp achievement (use NKAPI)
+ (void)unlockStamp:(NSString *)stampID handler:(void (^)(BOOL succeeded))handler DEPRECATED_ATTRIBUTE;
+ (void)askStampUnlocked:(NSString *)stampID handler:(void (^)(BOOL succeeded, BOOL unlocked))handler DEPRECATED_ATTRIBUTE;

@end
