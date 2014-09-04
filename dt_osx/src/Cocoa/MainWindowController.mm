//
//  MainWindowController.m
//  dial
//
//  Created by hiroshi matoba on 9/4/14.
//
//
#include "ofMain.h"
#import "MainWindowController.h"
#import "GeneralViewController.h"
#import "CircleViewController.h"
#import "OscViewController.h"

@implementation MainWindowController

NSString *const GeneralViewTitle	= @"GeneralView";
NSString *const CircleViewTitle		= @"CircleView";
NSString *const OscViewTitle		= @"OscView";

@synthesize myCurrentViewController;

@synthesize generalViewController;
@synthesize circleViewController;
@synthesize oscViewController;

- (id)initWithWindow:(NSWindow *)window
{
    self = [super initWithWindow:window];
    [self changeViewController:1];
    return self;
}

- (void)windowDidLoad
{
    [super windowDidLoad];
}

- (void)changeViewController:(NSInteger)whichViewTag
{
    
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
            if(oscViewController == nil)
                oscViewController = [[OscViewController alloc] initWithNibName:OscViewTitle bundle:nil];
            myCurrentViewController = self.oscViewController;
            [self.myCurrentViewController setTitle:OscViewTitle];
            break;
            
        case 4:
            break;

        case 5:
            break;

        default:
            break;

    }

    
    [SidePanel addSubview:[self.myCurrentViewController view]];
    
    [[self.myCurrentViewController view] setFrame:[SidePanel bounds]];
	
	[self.myCurrentViewController setRepresentedObject:[NSNumber numberWithUnsignedInteger:[[[self.myCurrentViewController view] subviews] count]]];
    
    [self didChangeValueForKey:@"viewController"];
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


- (void)deselect_all_side_panel{
    [SidePanelSelector1 setState: NSOffState ];
    [SidePanelSelector2 setState: NSOffState ];
    [SidePanelSelector3 setState: NSOffState ];
    [SidePanelSelector4 setState: NSOffState ];
    [SidePanelSelector5 setState: NSOffState ];
}

- (NSViewController *)viewController
{
	return self.myCurrentViewController;
}


@end
