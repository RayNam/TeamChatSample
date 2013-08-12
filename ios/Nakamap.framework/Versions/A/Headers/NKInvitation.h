#import <Foundation/Foundation.h>

@interface NKInvitation : NSObject

@property (nonatomic, retain) NSString *title;
@property (nonatomic, retain) NSString *code;
@property (nonatomic, retain) NSURL *URL;

@property (nonatomic, retain) NSURL *receivedURL;
@property (nonatomic, retain, readonly) NSString *URLQuery;
@property (nonatomic, retain, readonly) NSString *receivedMessage;

+ (NKInvitation *)invitationWithTitle:(NSString *)title
                                       URL:(NSURL *)URL;
+ (NKInvitation *)invitationWithTitle:(NSString *)title
                                       URL:(NSURL *)URL
                                      code:(NSString *)code;

@end
