#import <Foundation/Foundation.h>

@interface NKGroupInfo : NSObject

@property (retain, nonatomic) NSString *externalID;
@property (retain, nonatomic) NSString *baseName;
@property (retain, nonatomic) NSString *message;

+ (NKGroupInfo *)infoWithExternalID:(NSString *)externalID baseName:(NSString *)baseName;
+ (NKGroupInfo *)infoWithExternalID:(NSString *)externalID;
+ (NKGroupInfo *)infoWithExternalID:(NSString *)externalID message:(NSString *)message;
+ (NKGroupInfo *)infoWithDictionary:(NSDictionary *)dictionary;

- (NSDictionary *)dictionary;
@end
