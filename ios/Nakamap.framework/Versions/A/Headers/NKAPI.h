    #import <Foundation/Foundation.h>
#import "NKConst.h"
#import "NKRanking.h"

@interface NKAPI : NSObject

+ (void)callAPI:(NSString *)path
         method:(NKHTTPMethod)method
         params:(NSDictionary *)params
        handler:(void (^)(NKAPIStatusCode code, id response))handler;

#pragma mark - manage account

+ (void)signupWithBaseName:(NSString *)baseName handler:(void (^)(NKAPIStatusCode code, id response))handler;
+ (void)signupWithBaseName:(NSString *)baseName
       encryptedExternalID:(NSString *)encryptedExternalID
                        IV:(NSString *)IV
                   handler:(void (^)(NKAPIStatusCode code, id response))handler;

+ (void)updateEncryptedExternalID:(NSString *)encryptedExternalID
                               IV:(NSString *)IV
                          handler:(void(^)(NKAPIStatusCode code, id response))handler;

+ (void)updateUserIcon:(UIImage *)icon handler:(void (^)(NKAPIStatusCode code, id response))handler;

+ (void)updateUserName:(NSString *)name handler:(void (^)(NKAPIStatusCode code, id response))handler;

#pragma mark - create/delete group

+ (void)createGroupWithExternalID:(NSString *)groupExternalID
                        groupName:(NSString *)groupName
                          handler:(void(^)(NKAPIStatusCode code, id response))handler;

+ (void)createGroupWithExternalID:(NSString *)groupExternalID
                        groupName:(NSString *)groupName
                 invitePermission:(NKPermissionType)invitePermission
             addMembersPermission:(NKPermissionType)addMembersPermission
                   joinPermission:(NKPermissionType)joinPermission
                          handler:(void(^)(NKAPIStatusCode code, id response))handler;

+ (void)updateGroupWithExternalID:(NSString *)groupExternalID
                        groupName:(NSString *)groupName
                      description:(NSString *)description
                          handler:(void (^)(NKAPIStatusCode code, id response))handler;

+ (void)deleteGroupWithExternalID:(NSString *)groupExternalID handler:(void(^)(NKAPIStatusCode code, id response))handler;

+ (void)fetchGroupWithExternalID:(NSString *)externalID handler:(void(^)(NKAPIStatusCode code, id response))handler;

//create group without externalGroupID
+ (void)makeGroupWithName:(NSString *)name
              externalIDs:(NSArray *)externalIDs
                  handler:(void(^)(NKAPIStatusCode code, id response))handler;

#pragma mark - join/part group

+ (void)joinGroupWithExternalID:(NSString *)groupExternalID
                      groupName:(NSString *)groupName
                        handler:(void(^)(NKAPIStatusCode code, id response))handler;

+ (void)partGroupWithExternalID:(NSString *)groupExternalID handler:(void(^)(NKAPIStatusCode code, id response))handler;

#pragma mark - manage members of the group

+ (void)addGroupMembersWithExternalIDs:(NSArray *)userExternalIDs
                       groupExternalID:(NSString *)groupExternalID
                               handler:(void(^)(NKAPIStatusCode code, id response))handler;

+ (void)kickUserWithExternalID:(NSString *)userExternalID
               groupExternalID:(NSString *)groupExternalID
                       handler:(void(^)(NKAPIStatusCode code, id response))handler;

+ (void)changeLeaderWithExternalID:(NSString *)leaderExternalID
                   groupExternalID:(NSString *)groupExternalID
                           handler:(void(^)(NKAPIStatusCode code, id response))handler;

#pragma mark - manage friends

+ (void)addFriendsWithExternalIDs:(NSArray *)externalIDs handler:(void(^)(NKAPIStatusCode code, id response))handler;
+ (void)removeFriendsWithExternalID:(NSString *)externalID handler:(void(^)(NKAPIStatusCode code, id response))handler;

#pragma mark - stamp achievement

+ (void)unlockStamp:(NSString *)stampID handler:(void (^)(NKAPIStatusCode code, id response))handler;
+ (void)askStampUnlocked:(NSString *)stampID handler:(void (^)(NKAPIStatusCode code, id response))handler;

#pragma mark - ranking
// ランキング送信
+ (void)sendRanking:(NSString *)rankingID
              score:(int64_t)score
               save:(BOOL)save
            handler:(void (^)(NKAPIStatusCode code, id response))handler;

// ランキング再送信
+ (void)sendRankingSavedScores:(void (^)(NKAPIStatusCode code, id response))handler;

// ランキング詳細取得
+ (void)getRanking:(NSString *)rankingID
              type:(KLMRankingRange)type
            origin:(KLMRankingCursorOrigin)origin
            cursor:(NSInteger)cursor
             limit:(NSInteger)limit
           handler:(void (^)(NKAPIStatusCode code, id response))handler;

// すべてのランキングを取得する
+ (void)getRankingList:(KLMRankingRange)type
               handler:(void (^)(NKAPIStatusCode code, id response))handler;

+ (void)getRankingList:(KLMRankingRange)type
                  user:(NSString*)uid
               handler:(void (^)(NKAPIStatusCode code, id response))handler;

#pragma mark - app data
// アプリデータ送信
+ (void)sendAppData:(NSString *)data
            handler:(void (^)(NKAPIStatusCode code, id response))handler;

// アプリデータ取得
+ (void)getAppData:(NSArray *)fields
           handler:(void (^)(NKAPIStatusCode code, id response))handler;

// アプリデータ削除
+ (void)removeAppData:(NSArray *)fields
              handler:(void (^)(NKAPIStatusCode code, id response))handler;

#pragma mark - depricated

+ (BOOL)askEncryptedIDDidSent UNAVAILABLE_ATTRIBUTE;
+ (void)sendEncryptedExternalID:(NSString *)externalID IV:(NSString *)IV UNAVAILABLE_ATTRIBUTE;

#pragma mark - unread count
+ (void)getUnreadCountGroupWithExternalID:(NSString *)externalID
                                  handler:(void(^)(NKAPIStatusCode code, id response))handler;

@end
