#include "camera.h"

QQE::Camera::Camera(){}
void QQE::Camera::setCamera(
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

QMatrix4x4& QQE::Camera::getCamera(){
    return m_camera;
}

void QQE::Camera::setCameraPosition(float x, float y, float z){

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
void QQE::Camera::setCameraPositionDelta(float x, float y, float z){

    m_camera.setToIdentity();
    
    m_camera.perspective(
        m_verticalFov,
        m_aspectRatio,
        m_nearPlane,
        m_farPlane);
    m_x += x;
    m_y += y;
    m_z += z;
    m_camera.translate(m_x,m_y,m_z);


}

