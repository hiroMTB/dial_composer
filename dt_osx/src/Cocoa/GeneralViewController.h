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
}

@property (assign) IBOutlet NSSlider *bpm_sl;
@property (assign) IBOutlet NSTextField *bpm_tx;

@end
