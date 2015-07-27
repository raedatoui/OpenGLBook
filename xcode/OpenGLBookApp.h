//
//  OpenGLBookApp.h
//  OpenGLBook
//
//  Created by Raed Atoui on 7/26/15.
//
//

#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include <OpenGL/glu.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


using namespace ci;
using namespace ci::app;
using namespace std;

class OpenGLBookApp : public App {
public:
    static void prepareSettings(Settings *settings);
    void setup() override;
    void mouseDown( MouseEvent event ) override;
    void update() override;
    void draw() override;
    void resize() override;
    void quit() override;
    
    virtual void Cleanup() = 0;
    virtual void CreateVBO() = 0;
    virtual void DestroyVBO() = 0;
    virtual void LoadShaders() = 0;
    virtual void CreateShaders() = 0;
    virtual void DestroyShaders() = 0;
    
protected:
    GLuint
    VertexShaderId,
    FragmentShaderId,
    ProgramId,
    VaoId,
    VboId,
    ColorBufferId;
    const GLchar* VertexShader;
    const GLchar* FragmentShader;
    
};
