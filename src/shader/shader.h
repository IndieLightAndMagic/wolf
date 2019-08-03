#ifndef __HDC_SHADER_H__
#define __HDC_SHADER_H__

#include "util.h"

#include <QImage>
#include <QRectF>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>


namespace QQE {
    
    enum class ShaderType{
        VTX,
        FRG,
        GMT
    };
    
    static QMap<QQE::ShaderType, QOpenGLShader::ShaderType> stype_stype_map {
        std::make_pair(QQE::ShaderType::VTX, QOpenGLShader::Vertex),
        std::make_pair(QQE::ShaderType::FRG, QOpenGLShader::Fragment),
    };
    static QMap<QOpenGLShader::ShaderType, QString> stype_string_map {
        std::make_pair(QOpenGLShader::Vertex, QString("Vertex Shader")),
        std::make_pair(QOpenGLShader::Fragment, QString("Fragment Shader")),
    };
    
    class ShaderSource : public QQE::AFile{
        
        std::shared_ptr<QOpenGLShader>  m_shader{nullptr};
        unsigned int    m_shaderid; 
    
    public:
        ShaderSource(const char* path, ShaderType shaderType = ShaderType::VTX);
        QOpenGLShader* operator()(){
            return m_shader.get();
        }
    };

    class ShaderProgram : public ObjId{

        std::shared_ptr<ShaderSource> m_vtx_shader{};
        std::shared_ptr<ShaderSource> m_frg_shader{};
        std::shared_ptr<QOpenGLShaderProgram> m_program_shader{};

    public:
        
        ShaderProgram(const char* vertexshaderpath = nullptr, const char* fragmentshaderpath = nullptr);
        ~ShaderProgram();
        QOpenGLShaderProgram* operator()(){
            return m_program_shader.get();
        }
        
            
    };
    using PShaderProgram = std::shared_ptr<ShaderProgram>;
}

#endif //__SHADER_H__
