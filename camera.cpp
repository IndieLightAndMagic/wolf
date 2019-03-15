#include "camera.h"

void Camera::SetCamera(
    float verticalFov,
    float aspectRatio,
    float nearPlane,
    float farPlane,
    float x,
    float y,
    float z){

    m_camera.setToIdentity();
    
    m_camera.perspective(
        verticalFov,
        aspectRatio,
        nearPlane,
        farPlane);
    
    m_verticalFov = verticalFov;
    m_aspectRatio = aspectRatio;
    m_nearPlane = nearPlane;
    m_farPlane = farPlane;
    
    m_camera.translate(
        x,
        y,
        z);
    m_x = x;
    m_y = y;
    m_z = z;
}

const QMatrix4x4& Camera::GetCamera(){
    return m_camera;
}

void Camera::SetCameraPosition(float x, float y, float z){

    m_camera.setToIdentity();
    
    m_camera.perspective(
        m_verticalFov,
        m_aspectRatio,
        m_nearPlane,
        m_farPlane);
    m_camera.translate(x,y,z);

    m_x = x;
    m_y = y;
    m_z = z;

}

