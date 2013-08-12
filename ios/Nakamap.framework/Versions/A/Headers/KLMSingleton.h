
#import <Foundation/Foundation.h>


@interface KLMSingleton : NSObject

+ (id)instance;
+ (id)allocWithZone:(NSZone *)zone;
- (id)copyWithZone:(NSZone*)zone;
- (id)retain;
- (unsigned)retainCount;
- (id)autorelease;
- (void)release;

+ (void)kill;
@end
