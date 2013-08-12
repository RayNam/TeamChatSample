//
//  TeamChatAPIClient.h
//  Sample
//
//  Created by SOMTD on 2013/08/09.
//  Copyright (c) 2013年 Yosuke Ishikawa. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AFHTTPClient.h"

@interface TeamChatAPIClient : AFHTTPClient

+ (id)sharedInstance;

@end