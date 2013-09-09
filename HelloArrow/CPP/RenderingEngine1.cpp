//
//  RenderingEngine1.cpp
//  HelloArrow
//
//  Created by neo on 13-8-31.
//  Copyright (c) 2013年 neo. All rights reserved.
//

#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include "IRenderingEngine.hpp"

class RenderingEngine1 : public IRenderingEngine {
private:
    GLuint m_frameBuffer;
    GLuint m_renderBuffer;
    
public:
    RenderingEngine1();
    void Initalize(int width, int height);
    void Render() const;
    void UpdataAnimation(float timeStep);
    void OnRotate(DeviceOrientation newOrientation);
};

IRenderingEngine *CreateRenderer1()
{
    return new RenderingEngine1();
}

//顶点
struct Vertex {
    float Position[2];
    float Color[4];
};

const Vertex Vertices[] = {
    {{-0.5, -0.866}, {1, 1, 0.5f, 1}},
    {{ 0.5, -0.866}, {1, 1, 0.5f, 1}},
    {{0, 1},         {1, 1, 0.5f, 1}},
    {{-0.5, -0.866}, {0.5f, 0.5f, 0.5f}},
    {{ 0.5, -0.866}, {0.5f, 0.5f, 0.5f}},
    {{0, -0.4f},	 {0.5f, 0.5f, 0.5f}},
};

RenderingEngine1::RenderingEngine1()
{
	// Create & bind the color buffer so that the caller can allocate its space.
    glGenRenderbuffersOES(1, &m_renderBuffer);//创建render（渲染）缓冲区
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, m_renderBuffer);//绑定管线
}
void RenderingEngine1::Initalize(int width, int height)
{
    //create the frameBuffer object and attach the color buffer
    glGenFramebuffersOES(1, &m_frameBuffer);//创建frame(帧)缓冲区
    glBindFramebufferOES(GL_FRAMEBUFFER_OES, m_frameBuffer);//绑定管线
    
    //绑定 frame 和 render
    glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES,
                                 GL_COLOR_ATTACHMENT0_OES,
                                 GL_RENDERBUFFER_OES,
                                 m_renderBuffer);
    //构建坐标系统
    glViewport(0, 0, width, height);
    
    //initialize the projection matrix
    const float maxX = 2;
    const float maxY = 3;
    glOrthof(-maxX, +maxX, -maxY, +maxY, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void RenderingEngine1::Render() const
{
    //利用灰色清除缓冲区
    glClearColor(0.5f, 0.5f, 0.5f, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    //设置顶点属性
    glEnableClientState(GL_VERTEX_ARRAY);//位置
    glEnableClientState(GL_COLOR_ARRAY);//颜色
    //设置数据格式
    glVertexPointer(2, GL_FLOAT, sizeof(Vertex), &Vertices[0].Position[0]);
    glColorPointer(4, GL_FLOAT, sizeof(Vertex), &Vertices[0].Color[0]);
    //以顶点属性绘制三角形
    GLsizei vertexCount = sizeof(Vertices) / sizeof(Vertex);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);//从0起点开始绘制三角形
    //关闭顶点属性 (后续不会继续使用时关闭)
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void RenderingEngine1::UpdataAnimation(float timeStep)
{
    
}

void RenderingEngine1::OnRotate(DeviceOrientation newOrientation)
{
    
}

