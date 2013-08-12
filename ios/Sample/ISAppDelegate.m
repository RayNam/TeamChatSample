#import "ISAppDelegate.h"
#import "ISViewController.h"
#import <Nakamap/Nakamap.h>
#import <Nakamap/KLMPopOverController.h>

@implementation ISAppDelegate

- (void)dealloc
{
    self.window = nil;
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // NSURL *downloadURL = [NSURL URLWithString:@"http://www.example.com"];
#warning ご自身のLobiSDKのclient_idに置き換えて下さい。
    NKConfiguration *configuration = [NKConfiguration currentConfiguration];
    configuration.clientID = @"REPLACE_ME";
    configuration.accountBaseName = @"name";
    
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    self.window.backgroundColor = [UIColor whiteColor];
    self.window.rootViewController = [[ISViewController alloc] initWithNibName:@"ISViewController" bundle:nil];
    [self.window makeKeyAndVisible];
    
    return YES;
}

- (BOOL)application:(UIApplication *)application
            openURL:(NSURL *)url
  sourceApplication:(NSString *)sourceApplication
         annotation:(id)annotation
{
    if ([Nakamap handleOpenURL:url])
    {
        if ([Nakamap appFromURL:url])
        {
            NSLog(@"%@",[Nakamap appFromURL:url]);
            
            //developer edit
            
            return YES;
        }
        else if ([Nakamap invitedFromURL:url])
        {
            [Nakamap inviteInfoFromURL:url handler:^(BOOL enableInvited, NSDictionary *inviteInfo) {
                if (!enableInvited) {
                    return;
                }
                //developer edit
                UIViewController *yourRootViewController = self.window.rootViewController; // <-replace your rootViewCOntroller
                
                NKNakamapViewController *vc = [[NKNakamapViewController alloc] init];
                if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
                    [[KLMPopOverController instance] showInView:yourRootViewController.view withController:vc];
                } else {
                    [yourRootViewController presentViewController:vc animated:NO completion:^{
                        //
                    }];
                }
                [Nakamap openInvitedGroup:inviteInfo withController:vc];
                return;
            }];
            return YES;
        }
    }
    return NO;
}

@end
