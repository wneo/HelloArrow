//
//  GLView.h
//  HelloArrow
//
//  Created by neo on 13-8-31.
//  Copyright (c) 2013年 neo. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
@interface GLView : UIView
@property (nonatomic, strong) EAGLContext *glContext;
@end
