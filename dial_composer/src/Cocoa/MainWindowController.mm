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
#import "CircleViewController.h"
#import "OscOutViewController.h"
#import "OscInViewController.h"

@implementation MainWindowController

NSString *const CircleViewTitle		= @"CircleView";
NSString *const OscOutViewTitle		= @"OscOutView";
NSString *const OscInViewTitle		= @"OscInView";

@synthesize myCurrentViewController;
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
    [self SelectSideP1:self];
	
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
            if(circleViewController == nil)
                circleViewController = [[CircleViewController alloc] initWithNibName:CircleViewTitle bundle:nil];
            myCurrentViewController = self.circleViewController;
            [self.myCurrentViewController setTitle:CircleViewTitle];
            break;
            
        case 2:
            if(oscOutViewController == nil)
                oscOutViewController = [[OscOutViewController alloc] initWithNibName:OscOutViewTitle bundle:nil];
            myCurrentViewController = self.oscOutViewController;
            [self.myCurrentViewController setTitle:OscOutViewTitle];
            break;
            
        case 3:
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

- (IBAction)hide_side_panel:(id)sender {

}

- (IBAction)push_play:(id)sender {
    dt_config::DT_PLAY_GEN_RHYTHM = true;
}

- (IBAction)push_stop:(id)sender {
    dt_config::DT_PLAY_GEN_RHYTHM = false;
}

- (IBAction)change_bpm:(id)sender {
    int bpm = [sender intValue];
    [bpm_sl setIntValue:bpm];
    [bpm_tx setIntValue:bpm];
    ofApp * app = ofApp::app;
    if( app ){
        app->sequence_thread.change_bpm( bpm );
        app->clock_sender_audio_pulse.change_bpm( bpm );
    }
    
}

- (IBAction)step_bpm:(id)sender {
    ofApp * app = ofApp::app;
    if( app ){
        int step = [sender intValue];
        int bpm = app->sequence_thread.bpm + step;
        app->sequence_thread.change_bpm( bpm );
        app->clock_sender_audio_pulse.change_bpm( bpm );
        [bpm_sl setIntValue:bpm];
        [bpm_tx setIntValue:bpm];
        [sender setIntValue:0];
    }
}

- (void)deselect_all_side_panel {
    [SidePanelSelector1 setState: NSOffState ];
    [SidePanelSelector2 setState: NSOffState ];
    [SidePanelSelector3 setState: NSOffState ];
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
	
	ofApp::app->backingScaleChanged( newBackingScaleFactor, oldBackingScaleFactor );
}

- (NSArray *)toolbarAllowedItemIdentifiers:(NSToolbar *)toolbar {
    NSLog(@"Toolbar requesting allowed items.");
    NSMutableArray *array = [NSMutableArray array];
    [array addObject:@"TPUpToolbarItem"];
    [array addObject:@"TPDownToolbarItem"];
    [array addObject:@"TPResetToolbarItem"];
    [array addObject:@"TPSpeedToolbarItem"];
    [array addObject:@"TPGroupToolbarItem"];
    [array addObject:@"TPBackgroundToolbarItem"];
    [array addObject:NSToolbarShowFontsItemIdentifier];
    [array addObject:@"TPFlipHToolbarItem"];
    [array addObject:@"TPFlipVToolbarItem"];
    [array addObject:NSToolbarFlexibleSpaceItemIdentifier];
    [array addObject:NSToolbarSpaceItemIdentifier];
    [array addObject:NSToolbarSeparatorItemIdentifier];
    [array addObject:NSToolbarShowColorsItemIdentifier];
    [array addObject:NSToolbarPrintItemIdentifier];
    return array;
}

- (NSArray *)toolbarDefaultItemIdentifiers:(NSToolbar *)toolbar {
    NSLog(@"Toolbar requesting default items.");
    NSMutableArray *array = [NSMutableArray array];
    [array addObject:@"TPUpToolbarItem"];
    [array addObject:@"TPDownToolbarItem"];
    [array addObject:@"TPResetToolbarItem"];
    [array addObject:@"TPSpeedToolbarItem"];
    [array addObject:@"TPGroupToolbarItem"];
    [array addObject:@"TPBackgroundToolbarItem"];
    [array addObject:NSToolbarShowFontsItemIdentifier];
    [array addObject:@"TPFlipHToolbarItem"];
    [array addObject:@"TPFlipVToolbarItem"];
    [array addObject:NSToolbarFlexibleSpaceItemIdentifier];
    [array addObject:NSToolbarSpaceItemIdentifier];
    [array addObject:NSToolbarSeparatorItemIdentifier];
    [array addObject:NSToolbarShowColorsItemIdentifier];
    [array addObject:NSToolbarPrintItemIdentifier];
    return array;
}

- (void)update_ui{
    if( self.myCurrentViewController ){

        switch ( currentViewType ) {
            case 1:
                [self.circleViewController update_ui];
                break;
                
            case 2:
                [self.oscOutViewController update_ui];
                break;
                
            case 3:
                [self.oscInViewController update_ui];
                break;
                
            default:
                break;
        }
    }
    
    if( ofApp::app ){
        [bpm_sl setFloatValue:ofApp::app->sequence_thread.bpm];
        [bpm_tx setFloatValue:ofApp::app->sequence_thread.bpm];
    }
}

-(void)update_ui_every_frame{
    if( self.myCurrentViewController ){
        
        switch ( currentViewType ) {
            case 2:
                [self.oscOutViewController update_ui_every_frame];
                break;
                
            case 3:
                [self.oscInViewController update_ui_every_frame];
                break;
                
            default:
                break;
        }
    }
}

@end
