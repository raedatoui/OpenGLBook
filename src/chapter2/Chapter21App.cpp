//
//  Chapter2.cpp
//  OpenGLBook
//
//  Created by Raed Atoui on 7/26/15.
//
//

#include "OpenGLBookApp.h"

class Chapter21App : public OpenGLBookApp {

public:

    void Cleanup() override;
    void CreateVBO() override;
    void DestroyVBO() override;
    void LoadShaders() override;
    void CreateShaders() override;
    void DestroyShaders() override;

};
    
void OpenGLBookApp::setup()
{
    LoadShaders();
    CreateShaders();
    CreateVBO();
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void OpenGLBookApp::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void OpenGLBookApp::prepareSettings(Settings *settings)
{
    settings->setTitle("OpenGLBook");
    settings->setFrameRate( 60.0f );
    settings->setWindowSize(800, 600);
}

void OpenGLBookApp::resize()
{
    glViewport(0, 0, getWindowWidth(), getWindowHeight());
}


void OpenGLBookApp::quit()
{
    Cleanup();
}

void Chapter21App::Cleanup()
{
    DestroyShaders();
    DestroyVBO();
}

void Chapter21App::CreateVBO()
{
    GLfloat Vertices[] = {
        -0.8f, -0.8f, 0.0f, 1.0f,
        0.0f,  0.8f, 0.0f, 1.0f,
        0.8f, -0.8f, 0.0f, 1.0f
    };
    
    GLfloat Colors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f
    };
    
    GLenum ErrorCheckValue = glGetError();
    
    glGenVertexArrays(1, &VaoId);
    glBindVertexArray(VaoId);
    
    glGenBuffers(1, &VboId);
    glBindBuffer(GL_ARRAY_BUFFER, VboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    
    glGenBuffers(1, &ColorBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);
    
    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        fprintf(
                stderr,
                "ERROR: Could not create a VBO: %s \n",
                gluErrorString(ErrorCheckValue)
                );
        
        exit(-1);
    }
}

void Chapter21App::DestroyVBO()
{
    GLenum ErrorCheckValue = glGetError();
    
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glDeleteBuffers(1, &ColorBufferId);
    glDeleteBuffers(1, &VboId);
    
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VaoId);
    
    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        fprintf(
                stderr,
                "ERROR: Could not destroy the VBO: %s \n",
                gluErrorString(ErrorCheckValue)
                );
        
        exit(-1);
    }
}

void Chapter21App::LoadShaders()
{
    VertexShader =
    {
        "#version 400\n"\
        
        "layout(location=0) in vec4 in_Position;\n"\
        "layout(location=1) in vec4 in_Color;\n"\
        "out vec4 ex_Color;\n"\
        
        "void main(void)\n"\
        "{\n"\
        "  gl_Position = in_Position;\n"\
        "  ex_Color = in_Color;\n"\
        "}\n"
    };
    
    FragmentShader =
    {
        "#version 400\n"\
        
        "in vec4 ex_Color;\n"\
        "out vec4 out_Color;\n"\
        
        "void main(void)\n"\
        "{\n"\
        "  out_Color = ex_Color;\n"\
        "}\n"
    };
}

void Chapter21App::CreateShaders()
{
    GLenum ErrorCheckValue = glGetError();
    
    VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
    glCompileShader(VertexShaderId);
    
    FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
    glCompileShader(FragmentShaderId);
    
    ProgramId = glCreateProgram();
    glAttachShader(ProgramId, VertexShaderId);
    glAttachShader(ProgramId, FragmentShaderId);
    glLinkProgram(ProgramId);
    glUseProgram(ProgramId);
    
    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        fprintf(
                stderr,
                "ERROR: Could not create the shaders: %s \n",
                gluErrorString(ErrorCheckValue)
                );
        
        exit(-1);
    }
}

void Chapter21App::DestroyShaders()
{
    GLenum ErrorCheckValue = glGetError();
    
    glUseProgram(0);
    
    glDetachShader(ProgramId, VertexShaderId);
    glDetachShader(ProgramId, FragmentShaderId);
    
    glDeleteShader(FragmentShaderId);
    glDeleteShader(VertexShaderId);
    
    glDeleteProgram(ProgramId);
    
    ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
        fprintf(
                stderr,
                "ERROR: Could not destroy the shaders: %s \n",
                gluErrorString(ErrorCheckValue)
                );
        
        exit(-1);
    }
}

CINDER_APP( Chapter21App,RendererGl( RendererGl::Options().msaa( 16 ) ), &Chapter21App::prepareSettings );
