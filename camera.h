#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <QMatrix4x4>

class Camera {


    QMatrix4x4 m_camera;
    float m_verticalFov {60.0f};
    float m_aspectRatio {16.0f / 9.0f};
    float m_nearPlane {0.1f};
    float m_farPlane {100.0f};
    float m_x {0.0f};
    float m_y {0.0f};
    float m_z {-0.625f};

public:

    const QMatrix4x4& SetCamera(
        float verticalFov = 60.0f,
        float aspectRatio = 4.0f / 3.0f,
        float nearPlane = 0.1f,
        float farPlane = 100.0f,
        float x = 0.0f,
        float y = 0.0f,
        float z = -0.625f);
    const QMatrix4x4& GetCamera();


};


#endif /*__CAMERA_H__*/