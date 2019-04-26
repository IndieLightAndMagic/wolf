
#include "util.h"
#include "shader.h"


#include <utility>

#include <QMap>
#include <QList>

HDC::ShaderProgram::ShaderProgram(const char* vertexshaderpath, const char* fragmentshaderpath):ObjId(){

    m_vtx_shader = std::make_shared<ShaderSource>(vertexshaderpath, HDC::ShaderType::VTX);
    m_frg_shader = std::make_shared<ShaderSource>(fragmentshaderpath, HDC::ShaderType::FRG);
    m_program_shader = std::make_shared<QOpenGLShaderProgram>();

    auto vertex_shader_is_valid = m_vtx_shader->IsValid();
    auto fragment_shader_is_valid = m_frg_shader->IsValid();

    if (!vertex_shader_is_valid || !fragment_shader_is_valid) {
        Invalidate();
        return;
    }

    m_program_shader->addShader(m_vtx_shader.get()[0]());
    m_program_shader->addShader(m_frg_shader.get()[0]());
    m_program_shader->link();
    if (!(m_program_shader->isLinked())){
        Invalidate();
    }
}

HDC::ShaderProgram::~ShaderProgram(){



}

