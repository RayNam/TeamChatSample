#import <Foundation/Foundation.h>
#import "NKInvitation.h"
#import "NKGroupInfo.h"

@interface NKConfiguration : NSObject

@property (retain, nonatomic) NSString *clientID;
@property (retain, nonatomic) NSString *accountBaseName;
@property (retain, nonatomic) NSString *encryptedID;
@property (retain, nonatomic) NSString *encryptIV;

@property (retain, nonatomic) NKInvitation *invitation;

+ (NKConfiguration *)currentConfiguration;

@end
