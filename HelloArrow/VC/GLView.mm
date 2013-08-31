//
//  GLView.m
//  HelloArrow
//
//  Created by neo on 13-8-31.
//  Copyright (c) 2013年 neo. All rights reserved.
//

#import "GLView.h"

@implementation GLView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        CAEAGLLayer *eaglLayer = (CAEAGLLayer *)super.layer;
        eaglLayer.opaque = YES;//自己控制 透明度等属性（默认由Quartz控制）， opengl很好控制
        //初始化 context 并设置 opengl api 的版本
        self.glContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
        if ((! self.glContext) || (! [EAGLContext setCurrentContext:self.glContext]))  {
            self = nil;
            return nil;
        }
        //initialize for opengl
        GLuint frameBuffer, renderBuffer;
        
    }
    return self;
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

//覆写该方法， 因为 super 会调用此方法（delagate）来生成 layer
+ (Class)layerClass
{
    return [CAEAGLLayer class];
}

@end
