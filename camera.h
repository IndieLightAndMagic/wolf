        #ifndef __CAMERA_H__
#define __CAMERA_H__

#include <QMatrix4x4>

class Camera {

    bool m_dirty{true};
    
    QMatrix4x4 m_tmppers{};
    QMatrix4x4 m_tmptrans{};

    QMatrix4x4 m_camera;
    float m_verticalFov {60.0f};
    float m_aspectRatio {16.0f / 9.0f};
    float m_nearPlane {0.1f};
    float m_farPlane {100.0f};

public:

    float m_x {0.0f};
    float m_y {0.0f};
    float m_z {-0.625f};
    void setCamera(
        float verticalFov = 60.0f,
        float aspectRatio = 4.0f / 3.0f,
        float nearPlane = 0.1f,
        float farPlane = 100.0f,
        float x = 0.0f,
        float y = 0.0f,
        float z = -0.625f);

    const QMatrix4x4& getCamera();

    void setCameraPosition(float x = 0.0f, float y = 0.0f, float z = -0.625f);
    void setCameraPositionDelta(float x = 0.0f, float y = 0.0f, float z = 0.0f);


};


#endif /*__CAMERA_H__*/