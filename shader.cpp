
#include "util.h"
#include "shader.h"


#include <utility>

#include <QMap>
#include <QList>

HDC::ShaderProgram::ShaderProgram(const char* vertexshaderpath, const char* fragmentshaderpath):ObjId(){

    m_vtx_shader = std::make_shared<ShaderSource>(vertexshaderpath, HDC::ShaderType::VTX);
    m_frg_shader = std::make_shared<ShaderSource>(fragmentshaderpath, HDC::ShaderType::FRG);

    if (!m_vtx_shader && !m_frg_shader) {
        Invalidate();
        return;
    }

    auto program = (*this)();
    program->addShader(m_vtx_shader.get()[0]());
    program->addShader(m_frg_shader.get()[0]());

}

HDC::ShaderProgram::~ShaderProgram(){


}

