//
//  GeneralViewController.h
//  dial
//
//  Created by hiroshi matoba on 9/4/14.
//
//

#import <Cocoa/Cocoa.h>

@interface GeneralViewController : NSViewController {
    NSSlider *bpm_sl;
    NSTextField *bpm_tx;
    NSColorWell *bg_color;
    NSTextField *fps_tx;
    NSTextField *circle_num_tx;
}

@property (assign) IBOutlet NSSlider *bpm_sl;
@property (assign) IBOutlet NSTextField *bpm_tx;
@property (assign) IBOutlet NSColorWell *bg_color;

@property (assign) IBOutlet NSTextField *fps_tx;
@property (assign) IBOutlet NSTextField *circle_num_tx;

- (IBAction)change_bpm:(id)sender;
- (IBAction)change_bg_color:(id)sender;

- (void)update_ui;

@end
