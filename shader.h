#ifndef __HDC_SHADER_H__
#define __HDC_SHADER_H__

#include "util.h"

#include <QImage>
#include <QRectF>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>


namespace HDC {
    
    enum class ShaderType{
        VTX,
        FRG,
        GMT
    };
    
    class ShaderSource : public HDC::AFile{

    public:
        ShaderSource(const char* path, ShaderType shaderType = ShaderType::VTX);

    };

    class ShaderProgram : public ObjId{

        QOpenGLShaderProgram* m_qprogram{nullptr};
        QOpenGLShader* m_vtxShader{nullptr};
        QOpenGLShader* m_frgShader{nullptr};

    public:
        
        QMap<HDC::ShaderType, QOpenGLShader::ShaderType> stype_stype_map {
            std::make_pair(HDC::ShaderType::VTX, QOpenGLShader::Vertex),
            std::make_pair(HDC::ShaderType::FRG, QOpenGLShader::Fragment),
        };
        QMap<QOpenGLShader::ShaderType, QString> stype_string_map {
            std::make_pair(QOpenGLShader::Vertex, QString("Vertex Shader")),
            std::make_pair(QOpenGLShader::Fragment, QString("Fragment Shader")),
        };
        ShaderProgram();
        bool AddShader(const HDC::ShaderType, const char*);
        ~ShaderProgram();

        QOpenGLShaderProgram* GetProgram() const;



            
    };
}

#endif //__SHADER_H__
