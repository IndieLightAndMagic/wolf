
#include "util.h"
#include "shader.h"


#include <utility>

#include <QMap>
#include <QList>

HDC::ShaderProgram::ShaderProgram():ObjId([&](bool isValid){
    
    if (!isValid) {
        std::cout << "\n\tThere was a problem with the shader program!" << std::endl;
        if (m_qprogram) std::cout << "\n\tInfo: " <<  m_qprogram->log().toStdString() << std::endl;
        else std::cout << "\n\tShader Program object was not created" << std::endl;
    }

}){
    m_qprogram = new QOpenGLShaderProgram();
    if (m_qprogram){
        m_valid = true;
        m_value = m_qprogram->programId();
    } else { Invalidate(); }
}

bool HDC::ShaderProgram::AddShader(const ShaderProgram::ShaderType shaderType, const char* filename){

    if (!IsValid()) return false;
    
    auto addShaderOk = m_qprogram->addShaderFromSourceFile(stype_stype_map[shaderType],
        HDC::Utility::GetAbsolutePath(filename));

    if (!addShaderOk){
    
        Invalidate();
        return false;
    
    } else {
    
        return true;
    
    }

}
HDC::ShaderProgram::~ShaderProgram(){

    m_qprogram->removeAllShaders();

}
QOpenGLShaderProgram* HDC::ShaderProgram::GetProgram() const{
    if (!IsValid()) return nullptr;
    return m_qprogram;    
}