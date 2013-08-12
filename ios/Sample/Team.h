//
//  Team.h
//  Sample
//
//  Created by SOMTD on 2013/08/12.
//  Copyright (c) 2013年 Yosuke Ishikawa. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Team : NSObject

//{ id: Int, owner_user_id: Int }

@property (nonatomic, copy) NSString *team_id;
@property (nonatomic, copy) NSString *owner_user_id;

- (id)initWithDictionary:(NSDictionary *)dictionary;

@end
