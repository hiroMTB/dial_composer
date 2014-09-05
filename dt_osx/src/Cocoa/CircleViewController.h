//
//  CircleViewController.h
//  dial
//
//  Created by hiroshi matoba on 9/4/14.
//
//

#import <Cocoa/Cocoa.h>


@interface CircleViewController : NSViewController{
    NSSlider *beat_sl;
    NSTextField *beat_tx;
    
    NSSlider *speed_sl;
    NSTextField *speed_tx;
    
    NSSlider *rotate_sl;
    NSTextField *rotate_tx;

    NSSlider *shape_sl;
    NSTextField *shape_tx;
    NSSlider *edge_sl;
    NSTextField *edge_tx;
    NSSlider *side_sl;
    NSTextField *side_tx;
    NSSlider *ch_sl;
    NSTextField *ch_tx;
    NSColorWell *color;
}


- (void)update_ui;

@property (assign) IBOutlet NSSlider *beat_sl;
@property (assign) IBOutlet NSTextField *beat_tx;
- (IBAction)change_beat:(id)sender;


@property (assign) IBOutlet NSSlider *speed_sl;
@property (assign) IBOutlet NSTextField *speed_tx;
- (IBAction)change_speed:(id)sender;

@property (assign) IBOutlet NSSlider *rotate_sl;
@property (assign) IBOutlet NSTextField *rotate_tx;
- (IBAction)change_rotate:(id)sender;


@property (assign) IBOutlet NSSlider *shape_sl;
@property (assign) IBOutlet NSTextField *shape_tx;
- (IBAction)change_shape:(id)sender;

@property (assign) IBOutlet NSSlider *edge_sl;
@property (assign) IBOutlet NSTextField *edge_tx;
- (IBAction)change_edge:(id)sender;

@property (assign) IBOutlet NSSlider *side_sl;
@property (assign) IBOutlet NSTextField *side_tx;
- (IBAction)change_side:(id)sender;


@property (assign) IBOutlet NSSlider *ch_sl;
@property (assign) IBOutlet NSTextField *ch_tx;
- (IBAction)change_ch:(id)sender;

@property (assign) IBOutlet NSColorWell *color;
- (IBAction)change_color:(id)sender;


@end
