//
//  dt_GLView.m
//  dialt_osx_cocoa
//
//  Created by mtb on 2014/07/07.
//
//

#import "dt_GLView.h"

@implementation dt_GLView

- (void)setup {
    string newPath = [[NSString stringWithFormat:@"%@/../data/", [[NSBundle mainBundle] bundlePath]] UTF8String];
    ofSetDataPathRoot(newPath);	
    app = ofApp::init();
    app->setup();
}

- (void)update {
    app->update();
}

- (void)draw {
    app->draw();
}

- (void)exit {
    app->exit();
}

- (void)keyPressed:(int)key {
    app->keyPressed(key);
}

- (void)keyReleased:(int)key {
    app->keyReleased(key);
}

- (void)mouseMoved:(NSPoint)p {
    app->mouseMoved(p.x, p.y);
}

- (void)mouseDragged:(NSPoint)p button:(int)button {
    app->mouseDragged(p.x, p.y, button);
}

- (void)mousePressed:(NSPoint)p button:(int)button {
    app->mousePressed(p.x, p.y, button);
}

- (void)mouseReleased:(NSPoint)p button:(int)button {
    app->mouseReleased(p.x, p.y, button);
}

- (void)windowResized:(NSSize)size {
    if(app) app->windowResized(size.width, size.height);
}

@end
