//
//  Team.m
//  Sample
//
//  Created by SOMTD on 2013/08/12.
//  Copyright (c) 2013年 Yosuke Ishikawa. All rights reserved.
//

#import "Team.h"

@implementation Team

- (id)initWithDictionary:(NSDictionary *)dictionary {
    
    self = [super init];
    if (self) {
        self.team_id           = [dictionary[@"id"] stringValue];
        self.owner_user_id     = [dictionary[@"owner_user_id"] stringValue];
    }
    return self;
}
@end
