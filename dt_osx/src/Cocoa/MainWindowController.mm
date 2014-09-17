//
//  MainWindowController.m
//  dial
//
//  Created by hiroshi matoba on 9/4/14.
//
//
#include "ofMain.h"
#include "ofApp.h"

#import "MainWindowController.h"
#import "GeneralViewController.h"
#import "CircleViewController.h"
#import "OscOutViewController.h"
#import "OscInViewController.h"

@implementation MainWindowController

NSString *const GeneralViewTitle	= @"GeneralView";
NSString *const CircleViewTitle		= @"CircleView";
NSString *const OscOutViewTitle		= @"OscOutView";
NSString *const OscInViewTitle		= @"OscInView";

@synthesize myCurrentViewController;
@synthesize generalViewController;
@synthesize circleViewController;
@synthesize oscOutViewController;
@synthesize oscInViewController;

- (id)initWithWindow:(NSWindow *)window {
    self = [super initWithWindow:window];
//    [self changeViewController:1];
    return self;
}

- (void)windowDidLoad {
    [super windowDidLoad];
    [self changeViewController:1];
	
	NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];
	[nc addObserver:self
		   selector:@selector(windowDidChangeBackingProperties:)
			   name:NSWindowDidChangeBackingPropertiesNotification
			 object:self.window];
}

- (void)changeViewController:(NSInteger)whichViewTag {
    
    [self willChangeValueForKey:@"viewController"];
    
    if ([self.myCurrentViewController view] != nil){
        // remove the current view
        [[self.myCurrentViewController view] removeFromSuperview];
    }
    
   	switch(whichViewTag){
            
        case 1:
            if(generalViewController == nil)
                generalViewController = [[GeneralViewController alloc] initWithNibName:GeneralViewTitle bundle:nil];
            myCurrentViewController = self.generalViewController;
            [self.myCurrentViewController setTitle:GeneralViewTitle];
            break;
        case 2:
            if(circleViewController == nil)
                circleViewController = [[CircleViewController alloc] initWithNibName:CircleViewTitle bundle:nil];
            myCurrentViewController = self.circleViewController;
            [self.myCurrentViewController setTitle:CircleViewTitle];
            break;
            
        case 3:
            if(oscOutViewController == nil)
                oscOutViewController = [[OscOutViewController alloc] initWithNibName:OscOutViewTitle bundle:nil];
            myCurrentViewController = self.oscOutViewController;
            [self.myCurrentViewController setTitle:OscOutViewTitle];
            break;
            
        case 4:
            if(oscInViewController == nil)
                oscInViewController = [[OscInViewController alloc] initWithNibName:OscInViewTitle bundle:nil];
            myCurrentViewController = self.oscInViewController;
            [self.myCurrentViewController setTitle:OscInViewTitle];
            break;

        case 5:
            break;

        default:
            break;

    }
    
    currentViewType = whichViewTag;
    
    NSView * contentView = [self.myCurrentViewController view];
    [contentView setAutoresizingMask:NSViewWidthSizable | NSViewHeightSizable];
    [contentView setFrame:[SidePanel bounds]];
    [SidePanel addSubview:contentView];
	[self.myCurrentViewController setRepresentedObject:[NSNumber numberWithUnsignedInteger:[[contentView subviews] count]]];
    [self didChangeValueForKey:@"viewController"];
    [self update_ui];
}

- (IBAction)SelectSideP1:(id)sender {
    [self deselect_all_side_panel];
    [SidePanelSelector1 setState: NSOnState ];
    [self changeViewController : 1];
}

- (IBAction)SelectSideP2:(id)sender {
    [self deselect_all_side_panel];
    [SidePanelSelector2 setState: NSOnState ];
    [self changeViewController : 2];
}

- (IBAction)SelectSideP3:(id)sender {
    [self deselect_all_side_panel];
    [SidePanelSelector3 setState: NSOnState ];
    [self changeViewController : 3];
}

- (IBAction)SelectSideP4:(id)sender {
    [self deselect_all_side_panel];
    [SidePanelSelector4 setState: NSOnState ];
    [self changeViewController : 4];
}

- (IBAction)SelectSideP5:(id)sender {
    [self deselect_all_side_panel];
    [SidePanelSelector5 setState: NSOnState ];
    [self changeViewController : 5];
}

- (void)deselect_all_side_panel {
    [SidePanelSelector1 setState: NSOffState ];
    [SidePanelSelector2 setState: NSOffState ];
    [SidePanelSelector3 setState: NSOffState ];
    [SidePanelSelector4 setState: NSOffState ];
    [SidePanelSelector5 setState: NSOffState ];
}

- (NSViewController *)viewController {
	return self.myCurrentViewController;
}

/*
 *		retina - nonretina change notification
 *		https://developer.apple.com/library/mac/documentation/GraphicsAnimation/Conceptual/HighResolutionOSX/CapturingScreenContents/CapturingScreenContents.html
 */
- (void)windowDidChangeBackingProperties:(NSNotification *)notification {
	
    NSWindow *theWindow = (NSWindow *)[notification object];
    NSLog(@"windowDidChangeBackingProperties: window=%@", theWindow);
	
    CGFloat newBackingScaleFactor = [theWindow backingScaleFactor];
    CGFloat oldBackingScaleFactor = [[[notification userInfo]
									  objectForKey:@"NSBackingPropertyOldScaleFactorKey"]
									 doubleValue];
    if (newBackingScaleFactor != oldBackingScaleFactor) {
        NSLog(@"\tThe backing scale factor changed from %.1f -> %.1f",
			  oldBackingScaleFactor, newBackingScaleFactor);
    }
	
	ofApp::getInstance()->backingScaleChanged( newBackingScaleFactor, oldBackingScaleFactor );
	
	/*
    NSColorSpace *newColorSpace = [theWindow colorSpace];
    NSColorSpace *oldColorSpace = [[notification userInfo]
								   objectForKey:@"NSBackingPropertyOldColorSpaceKey"];
    if (![newColorSpace isEqual:oldColorSpace]) {
        NSLog(@"\tThe color space changed from %@ -> %@", oldColorSpace, newColorSpace);
    }*/
}

- (void)update_ui{
    if( self.myCurrentViewController ){

        switch ( currentViewType ) {
            case 1:
                [self.generalViewController update_ui];
                break;
                
            case 2:
                [self.circleViewController update_ui];
                break;
                
            case 3:
                [self.oscOutViewController update_ui];
                break;
                
            case 4:
                [self.oscInViewController update_ui];
                break;
                
            default:
                break;
        }
    }
}

@end
