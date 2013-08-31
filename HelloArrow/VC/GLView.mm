//
//  GLView.m
//  HelloArrow
//
//  Created by neo on 13-8-31.
//  Copyright (c) 2013年 neo. All rights reserved.
//

#import "GLView.h"

@implementation GLView

#pragma mark - init & dealloc
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
        glGenFramebuffersOES(1, &frameBuffer);//创建frame(帧)缓冲区
        glGenRenderbuffersOES(1, &renderBuffer);//创建render（渲染）缓冲区
        //绑定管线
        glBindFramebufferOES(GL_FRAMEBUFFER_OES, frameBuffer);
        glBindRenderbufferOES(GL_RENDERBUFFER_OES, renderBuffer);
        //分配存储空间
        [self.glContext renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:eaglLayer];
        //绑定 frame 和 render
        glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, renderBuffer);
        //构建坐标系统
        glViewport(0, 0, CGRectGetWidth(frame), CGRectGetHeight(frame));
        [self drawView];
    }
    return self;
}

- (void)dealloc
{
    if ([EAGLContext currentContext] == self.glContext) {
        [EAGLContext setCurrentContext:nil];
    }
    self.glContext = nil;
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


#pragma mark - draw
//这里相当于原ios里的drawRect, 但更提升一层性能（缓冲操作）
- (void)drawView
{
    glClearColor(0.5f, 0.5f, 0.5f, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    //推送到屏幕
    [self.glContext presentRenderbuffer:GL_RENDERBUFFER_OES];
    
}


@end
