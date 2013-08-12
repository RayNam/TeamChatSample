#import "ISViewController.h"
#import <Nakamap/Nakamap.h>
#import <Nakamap/KLMPopOverController.h>
#import "TeamChatAPIClient.h"
#import "AFNetworking.h"
#import "Team.h"

@interface ISViewController()
@property (nonatomic, copy) NSString *user_id;
@property (nonatomic, copy) NSString *encrypted_user_id;
@property (nonatomic, copy) NSString *encrypted_iv;
@property (nonatomic, copy) NSString *user_token;
@property (nonatomic, copy) NSString *group_ex_id;
@property (nonatomic, copy) NSMutableArray *array;
@property (weak, nonatomic) IBOutlet UITableView *teamListView;
@property (weak, nonatomic) IBOutlet UIBarButtonItem *signupButton;
@property (weak, nonatomic) IBOutlet UIBarButtonItem *createButton;
@end

@implementation ISViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    _array = [[NSMutableArray alloc]init];
    
    if ([[NSUserDefaults standardUserDefaults]objectForKey:@"sample_user_token"]) {
        self.user_token = [[NSUserDefaults standardUserDefaults]objectForKey:@"sample_user_token"];
        _signupButton.enabled = NO;
        _createButton.enabled = YES;
        [self getTeamList];
    } else {
        _signupButton.enabled = YES;
        _createButton.enabled = NO;
    }
}

- (void)showNakamapView
{
    NKNakamapViewController *navigationController = [[NKNakamapViewController alloc] init];
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
        UIViewController *rootViewController = [UIApplication sharedApplication].keyWindow.rootViewController;
        [KLMPopOverController instance].direction = KLMPopOverArrowDirectionLeft;
        [KLMPopOverController instance].origin    = CGPointMake(50, 50);
        [[KLMPopOverController instance] showInView:rootViewController.view withController:navigationController];
    } else {
        [self presentViewController:navigationController animated:YES completion:^{
            //
        }];
    }
}

- (IBAction)onSignupButton:(id)sender
{
    //実装例では/signupにPOSTすることで{"iv","group_id","cipher","id","token"}を取得します。
    
    [[TeamChatAPIClient sharedInstance] postPath:@"signup"
                                      parameters:nil
                                         success:^(AFHTTPRequestOperation *operation, id responseObject) {
                                             
                                             NSLog(@"Response: %@",operation.responseString);
                                             NSDictionary *jsonDictionary = [NSJSONSerialization
                                                                             JSONObjectWithData:operation.responseData
                                                                             options:0
                                                                             error:nil];
                                             NSLog(@"encoded");
                                             
                                             self.user_id           = jsonDictionary[@"user"][@"id"];
                                             self.user_token        = jsonDictionary[@"user"][@"token"];
                                             self.encrypted_user_id = jsonDictionary[@"user"][@"cipher"];
                                             self.encrypted_iv      = jsonDictionary[@"user"][@"iv"];
                                             self.group_ex_id       = jsonDictionary[@"user"][@"group_id"];
                                            
                                             //サインアップしたことを覚えさせておく。
                                             [[NSUserDefaults standardUserDefaults]setObject:self.user_token forKey:@"sample_user_token"];
                                             [[NSUserDefaults standardUserDefaults]synchronize];
                                             
                                             _createButton.enabled = YES;
                                             _signupButton.enabled = NO;
                                             

                                             [NKAPI signupWithBaseName:@"sample_user"
                                                   encryptedExternalID:self.encrypted_user_id
                                                                    IV:self.encrypted_iv
                                                               handler:^(NKAPIStatusCode code, id response) {
                                                                   if (code == NKAPIStatusCodeFatalError) {
                                                                       return ;
                                                                   }
                                                                   NSLog(@"Response: %@",response);
                                                                   //サインアップに成功したら所属可能なグループ一覧を表示する
                                                                   [self getTeamList];
                                                               }];
                                             
                                         } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
                                             NSLog(@"signup error");
                                             NSLog(@"%@", error);
                                         }];
}


- (IBAction)onCreateButton:(id)sender
{
    if (!self.user_token) {
        return;
    }
    
    NSDictionary *params = @{@"token":self.user_token};
    [[TeamChatAPIClient sharedInstance] postPath:@"teams"
                                      parameters:params
                                         success:^(AFHTTPRequestOperation *operation, id responseObject) {

                                             NSDictionary *jsonDictionary = [NSJSONSerialization
                                                                             JSONObjectWithData:operation.responseData
                                                                             options:0
                                                                             error:nil];
                                             self.group_ex_id       = jsonDictionary[@"team"][@"id"];
                                             NSLog(@"Create Success! Team %@",self.group_ex_id);
                                             [self getTeamList];
                                         } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
                                             NSLog(@"signup error");
                                             NSLog(@"%@", error);
                                         }];
}

- (void)getTeamList
{
    if (!self.user_token) {
        return;
    }
    NSDictionary *params = @{@"token":self.user_token};
    [[TeamChatAPIClient sharedInstance] getPath:@"teams"
                                     parameters:params
                                        success:^(AFHTTPRequestOperation *operation, id responseObject) {
                                            
                                            _array = [NSMutableArray array];
                                            NSDictionary *jsonDictionary = [NSJSONSerialization
                                                                            JSONObjectWithData:operation.responseData
                                                                            options:0
                                                                            error:nil];
                                            
                                            NSArray *teams = jsonDictionary[@"teams"];
                                            NSLog(@"teams:%@",teams[0]);
                                            
                                            if ([teams[0] count]==0) {
                                                return;
                                            }
                                            for (NSDictionary *teamDictionary in teams[0]) {
                                                Team *team = [[Team alloc] initWithDictionary:teamDictionary];
                                                NSLog(@"team:%@",team);
                                                [_array addObject:team];
                                            }
                                            [self.teamListView reloadData];
                                            
                                         } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
                                             NSLog(@"signup error");
                                             NSLog(@"%@", error);
                                         }];
}


#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    // Return the number of sections.
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    // Return the number of rows in the section.
    return [_array count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:CellIdentifier];
        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    }
    Team *team = [_array objectAtIndex:indexPath.row];
    cell.textLabel.text = [NSString stringWithFormat:@"Team ID:%@",team.team_id];
    cell.detailTextLabel.text = [NSString stringWithFormat:@"Team Owner:%@",team.owner_user_id];
    return cell;
}

#pragma mark - Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    Team *team = [_array objectAtIndex:indexPath.row];
    NSString *joinTeam = team.team_id;
    if (!self.user_token) {
        return;
    }
    NSString *path = [NSString stringWithFormat:@"teams/%@/join",joinTeam];
    NSDictionary *params = @{@"token":self.user_token};
    
    [[TeamChatAPIClient sharedInstance] postPath:path
                                      parameters:params
                                         success:^(AFHTTPRequestOperation *operation, id responseObject) {
                                             NSLog(@"Response: %@",operation.responseString);
                                             NKNakamapViewController *navigationController = [[NKNakamapViewController alloc] init];
                                             navigationController.defaultGroupInfo = [NKGroupInfo infoWithExternalID:joinTeam baseName:nil];
                                             [self presentViewController:navigationController animated:YES completion:^{
                                                 //
                                             }];                                             
                                         } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
                                             NSLog(@"join error");
                                             NSLog(@"%@", error);
                                         }];
}


#pragma mark - interface orientation

- (NSUInteger)supportedInterfaceOrientations
{
    return UIInterfaceOrientationMaskAll;
}

- (BOOL)shouldAutorotate
{
    return YES;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation
{
    // iOS 4,5 only
    return YES;
}


@end
