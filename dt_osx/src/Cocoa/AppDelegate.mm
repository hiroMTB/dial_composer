#import "AppDelegate.h"
#import "MainWindowController.h"

@implementation AppDelegate

- (void)dealloc
{
    [super dealloc];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    mainWindowController = [[MainWindowController alloc] initWithWindowNibName:@"MainWindow"];
    [mainWindowController showWindow:self];
}

@end
