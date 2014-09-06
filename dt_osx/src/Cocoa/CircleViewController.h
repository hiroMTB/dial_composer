//
//  CircleViewController.h
//  dial
//
//  Created by hiroshi matoba on 9/4/14.
//
//

#import <Cocoa/Cocoa.h>

@interface CircleViewController : NSViewController{
    NSSlider    *beat_sl, *speed_sl, *rotate_sl, *shape_sl, *edge_sl, *side_sl, *ch_sl;
    NSTextField *beat_tx, *speed_tx, *rotate_tx, *shape_tx, *edge_tx, *side_tx, *ch_tx;
    NSColorWell *color;
}

- (void)update_ui;

@property (assign) IBOutlet NSSlider *beat_sl;
@property (assign) IBOutlet NSSlider *speed_sl;
@property (assign) IBOutlet NSSlider *rotate_sl;
@property (assign) IBOutlet NSSlider *shape_sl;
@property (assign) IBOutlet NSSlider *edge_sl;
@property (assign) IBOutlet NSSlider *side_sl;
@property (assign) IBOutlet NSSlider *ch_sl;

@property (assign) IBOutlet NSTextField *beat_tx;
@property (assign) IBOutlet NSTextField *speed_tx;
@property (assign) IBOutlet NSTextField *rotate_tx;
@property (assign) IBOutlet NSTextField *shape_tx;
@property (assign) IBOutlet NSTextField *edge_tx;
@property (assign) IBOutlet NSTextField *side_tx;
@property (assign) IBOutlet NSTextField *ch_tx;

@property (assign) IBOutlet NSColorWell *color;

- (IBAction)change_beat:(id)sender;
- (IBAction)change_speed:(id)sender;
- (IBAction)change_rotate:(id)sender;
- (IBAction)change_shape:(id)sender;
- (IBAction)change_edge:(id)sender;
- (IBAction)change_side:(id)sender;
- (IBAction)change_ch:(id)sender;
- (IBAction)change_color:(id)sender;

@end
