//
//  GeneralViewController.h
//  dial
//
//  Created by hiroshi matoba on 9/4/14.
//
//

#import <Cocoa/Cocoa.h>

@interface GeneralViewController : NSViewController {
    IBOutlet  NSSlider *bpm_sl;
    IBOutlet NSTextField *bpm_tx;
    IBOutlet NSColorWell *bg_color;
    IBOutlet NSTextField *fps_tx;
    IBOutlet NSTextField *circle_num_tx;
}

- (IBAction)change_bpm:(id)sender;
- (IBAction)change_bg_color:(id)sender;

- (void)update_ui;

@end
