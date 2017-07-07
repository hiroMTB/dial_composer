#import "AppDelegate.h"
#import "MainWindowController.h"

@implementation AppDelegate

@synthesize mainWindowController;

- (void)dealloc {
    [super dealloc];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    if( !mainWindowController ){
        mainWindowController = [[MainWindowController alloc] initWithWindowNibName:@"MainWindow"];
        [mainWindowController showWindow:nil];
        
        NSLog(@"AppDelegate::applicationDidFinishLaunching");
        [self update_ui];
    }
}

- (void)update_ui {

    if( mainWindowController ){
        [mainWindowController update_ui];
    }
}

- (void)update_ui_every_frame {
    if( mainWindowController ){
        [mainWindowController update_ui_every_frame];
    }
}

-(void)applicationWillTerminate:(NSNotification *)aNotification{
    NSLog(@"applicationWillTerminate");
    [mainWindowController exit];
}

@end
