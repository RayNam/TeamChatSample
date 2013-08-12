#import <Foundation/Foundation.h>

@interface NKUser : NSObject <NSCoding>

@property (nonatomic, retain) NSString *uid;
@property (nonatomic, retain) NSString *name;
@property (nonatomic, retain) NSString *profile;
@property (nonatomic, retain) NSURL    *iconURL;

+ (NKUser *)currentUser;
+ (NKUser *)userWithDictionary:(NSDictionary *)dictionary;

@end
