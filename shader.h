#ifndef __SHADER_H__
#define __SHADER_H__

#include <QImage>
#include <QRectF>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>


namespace HDC {
    
    class Shader {
        QOpenGLShader* m_qshader{nullptr};
        unsigned int m_shader{0};
    public:
        enum class ShaderType{
            VTX,
            FRG,
            GMT
        };
        Shader(ShaderType shaderType, const char* path);
        unsigned int GetId();
    };
    class ShaderProgram {
        unsigned int m_program{0};
        QOpenGLShaderProgram* m_qprogram{nullptr};
    public:
        ShaderProgram(){
            m_qprogram = new QOpenGLShaderProgram();
        }
        AddShader(const Shader& shader);
        unsigned int GetId();
    }; 
}

#endif //__SHADER_H__