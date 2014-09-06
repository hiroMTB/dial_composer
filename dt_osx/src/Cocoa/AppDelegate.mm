#include "ofMain.h"
#include "ofApp.h"
#include "dt_circle_all_containers.h"
#include "dt_circle_container.h"

#import "AppDelegate.h"
#import "MainWindowController.h"
#import "GeneralViewController.h"


@implementation AppDelegate

@synthesize mainWindowController;

- (void)dealloc {
    [super dealloc];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    if( !mainWindowController ){
        mainWindowController = [[MainWindowController alloc] initWithWindowNibName:@"MainWindow"];
        [mainWindowController showWindow:self];
        
        NSLog(@"AppDelegate::applicationDidFinishLaunching");
    }
}

- (void)update_ui {
    
    int circle_num = ofApp::getInstance()->all_containers.note_on_container->circles.size();
    float fps = ofGetFrameRate();
    
    [[mainWindowController generalViewController] update_circle_num:circle_num];
    [[mainWindowController generalViewController] update_fps:fps];
    
}

@end
