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
   // ofRunApp(app);
}


- (void)update {
    if(app) app->update();
}

- (void)draw {
  if(app) app->draw();
}

- (void)exit {
    if(app){        
        app->exit();
        delete app;
        app = NULL;
    }
}

- (void)keyPressed:(int)key {
    if(app) app->keyPressed(key);
}

- (void)keyReleased:(int)key {
    if(app) app->keyReleased(key);
}

- (void)mouseMoved:(NSPoint)p {
    if(app) app->mouseMoved(p.x, p.y);
}

- (void)mouseDragged:(NSPoint)p button:(int)button {
    if(app) app->mouseDragged(p.x, p.y, button);
}

- (void)mousePressed:(NSPoint)p button:(int)button {
    if(app) app->mousePressed(p.x, p.y, button);
}

- (void)mouseReleased:(NSPoint)p button:(int)button {
    if(app) app->mouseReleased(p.x, p.y, button);
}

- (void)windowResized:(NSSize)size {
    if(app) app->windowResized(size.width, size.height);
}

@end
