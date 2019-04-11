#include "shader.h"
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
        bool Compile();
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
        bool Link();
        unsigned int GetId();
    }; 

HDC::Shader::Shader(Shader::ShaderType shaderType, const char* path){

	auto filename_shader = std::string{path};
    auto fileptr_shader = std::fopen(filename_shader.c_str(), "r");
    auto ptrCodeBuffer = (type == ShaderType::FRG) ? fragBuffer : vertBuffer;
    std::size_t bytesRead = std::fread(ptrCodeBuffer, 1, 4096, fileptr_shader);
    std::fclose(fileptr_shader);
    auto shaderSource = reinterpret_cast<char*>(ptrCodeBuffer); 

    if (m_program->addShaderFromSourceCode(type, shaderSource)){
    
        std::cout << "\n\tShader [OK]";
    
    } else {
        std::cout << "\n\t" << path << " Shader quite bad....." << std::endl;
        std::cout << "\n\tInfo: " <<  m_program->log().toStdString() << std::endl;
    }
}    