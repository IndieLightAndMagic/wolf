#ifndef __HDC_SHADER_H__
#define __HDC_SHADER_H__

#include "objid.h"

#include <QImage>
#include <QRectF>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>


namespace HDC {
    
    class ShaderProgram : public ObjId{

        QOpenGLShaderProgram* m_qprogram{nullptr};
        QOpenGLShader* m_vtxShader{nullptr};
        QOpenGLShader* m_frgShader{nullptr};

    public:
        enum class ShaderType{
            VTX,
            FRG,
            GMT
        };
        QMap<ShaderProgram::ShaderType, QOpenGLShader::ShaderType> stype_stype_map {
            std::make_pair(ShaderProgram::ShaderType::VTX, QOpenGLShader::Vertex),
            std::make_pair(ShaderProgram::ShaderType::FRG, QOpenGLShader::Fragment),
        };
        QMap<QOpenGLShader::ShaderType, QString> stype_string_map {
            std::make_pair(QOpenGLShader::Vertex, QString("Vertex Shader")),
            std::make_pair(QOpenGLShader::Fragment, QString("Fragment Shader")),
        };
        ShaderProgram();
        bool AddShader(const ShaderProgram::ShaderType, const char*);
        ~ShaderProgram();

        QOpenGLShaderProgram* GetProgram() const;



            
    };
}

#endif //__SHADER_H__
