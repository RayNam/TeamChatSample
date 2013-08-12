//
//  TeamChatAPIClient.m
//  Sample
//
//  Created by SOMTD on 2013/08/09.
//  Copyright (c) 2013年 Yosuke Ishikawa. All rights reserved.
//

#import "TeamChatAPIClient.h"
#import "AFNetworking.h"


//TeamChatAPIBaseURLStringはご自身のサーバーのURLを指定してください。
#define TeamChatAPIBaseURLString @"http://localhost:5000/"

@implementation TeamChatAPIClient

+ (id)sharedInstance {
    
    static TeamChatAPIClient *__sharedInstance;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        __sharedInstance = [[TeamChatAPIClient alloc] initWithBaseURL:[NSURL URLWithString:TeamChatAPIBaseURLString]];
    });
    
    return __sharedInstance;
}

- (id)initWithBaseURL:(NSURL *)url {
    
    self = [super initWithBaseURL:url];
    if (self) {
        
        //custom settings
        [self registerHTTPOperationClass:[AFJSONRequestOperation class]];
    }
    
    return self;
}
@end
