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
    IBOutlet NSButton *SidePanelSelector4;
    IBOutlet NSButton *SidePanelSelector5;

    NSViewController *myCurrentViewController;

    @public
    GeneralViewController *generalViewController;
    CircleViewController *circleViewController;
    OscOutViewController *oscOutViewController;
    OscInViewController *oscInViewController;

    int currentViewType;
}

@property (nonatomic, assign) NSViewController *myCurrentViewController;
@property (nonatomic, strong) GeneralViewController *generalViewController;
@property (nonatomic, strong) CircleViewController *circleViewController;
@property (nonatomic, strong) OscOutViewController *oscOutViewController;
@property (nonatomic, strong) OscInViewController *oscInViewController;

- (IBAction)SelectSideP1:(id)sender;
- (IBAction)SelectSideP2:(id)sender;
- (IBAction)SelectSideP3:(id)sender;
- (IBAction)SelectSideP4:(id)sender;
- (IBAction)SelectSideP5:(id)sender;
- (IBAction)hide_side_panel:(id)sender;
- (NSViewController *)viewController;

- (void)update_ui;

@end
