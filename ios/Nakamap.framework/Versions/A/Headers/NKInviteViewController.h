//
//  NKInviteViewController.h
//  Nakamap
//
//  Created by SOMTD on 2013/06/10.
//
//

#import <UIKit/UIKit.h>

@interface NKInviteViewController : UIViewController<UIWebViewDelegate>

@property (retain, nonatomic) IBOutlet UINavigationBar *navigationBar;
@property (retain, nonatomic) IBOutlet UIWebView *webView;

+ (NKInviteViewController *)create;
- (void)prepareInviteWithURL:(NSURL *)url;

@end
