#import <Cocoa/Cocoa.h>
@class MainWindowController;

@interface AppDelegate : NSObject {
    MainWindowController *mainWindowController;
}

@property (nonatomic, strong) MainWindowController * mainWindowController;

- (void)update_ui;
- (void)update_ui_every_frame;
@end
