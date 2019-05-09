#ifndef _Scene_H_
#define _Scene_H_
#include "openglwindow.h"

class Scene : public OpenGLWindow
{
    int m_frame{0};

public:
    InputManager m_im;

    Scene();

    void initialize() override;
    void render() override;



};
#endif /* _Scene_H_ */
