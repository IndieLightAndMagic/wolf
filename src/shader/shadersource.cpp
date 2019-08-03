#include "shader.h"


QQE::ShaderSource::ShaderSource(const char* path, QQE::ShaderType shaderType):
    QQE::AFile(path)
{
    
    m_shader = std::make_shared<QOpenGLShader>(QQE::stype_stype_map[shaderType]);

    auto source = this->data();
    auto ok     = m_shader.get()->compileSourceCode(source);
    
    if (!ok){
        set_invalid_object_handle([&, this](bool isValid){
                if (!isValid) {
                    auto shaderPtr = m_shader.get();
                    std::cout << "\n\tThere was a problem with the shader program!" << std::endl;
                    if (shaderPtr->isCompiled()) std::cout << "\n\tInfo: " <<  shaderPtr->log().toStdString() << std::endl;
                    else std::cout << "\n\tShader Program object was not created" << std::endl;

                    for(auto index = 0; index < this->size(); ++index) std::cout << source[index];
                    std::cout << std::endl;

                }
            }
        );
        Invalidate();
    }

}
