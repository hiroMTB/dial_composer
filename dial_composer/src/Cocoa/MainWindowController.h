//
//  MainWindowController.h
//  dial
//
//  Created by hiroshi matoba on 9/4/14.
//
//

#import <Cocoa/Cocoa.h>

@class GeneralViewController, CircleViewController, OscOutViewController, OscInViewController;
@class dt_GLView;

@interface MainWindowController : NSWindowController {
    IBOutlet dt_GLView *glView;
    IBOutlet NSView *SidePanel;
    IBOutlet NSButton *SidePanelSelector1;
    IBOutlet NSButton *SidePanelSelector2;
    IBOutlet NSButton *SidePanelSelector3;

    IBOutlet NSSlider *bpm_sl;
    IBOutlet NSTextField *bpm_tx;
    NSViewController *myCurrentViewController;

    @public
    CircleViewController *circleViewController;
    OscOutViewController *oscOutViewController;
    OscInViewController *oscInViewController;

    int currentViewType;
}

@property (nonatomic, assign) NSViewController *myCurrentViewController;
@property (nonatomic, strong) CircleViewController *circleViewController;
@property (nonatomic, strong) OscOutViewController *oscOutViewController;
@property (nonatomic, strong) OscInViewController *oscInViewController;

- (IBAction)SelectSideP1:(id)sender;
- (IBAction)SelectSideP2:(id)sender;
- (IBAction)SelectSideP3:(id)sender;
- (IBAction)hide_side_panel:(id)sender;
- (IBAction)push_play:(id)sender;
- (IBAction)push_stop:(id)sender;
- (IBAction)change_bpm:(id)sender;
- (IBAction)step_bpm:(id)sender;
- (NSViewController *)viewController;

- (void)update_ui;
- (void)update_ui_every_frame;
@end
