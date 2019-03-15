#include "camera.h"

const QMatrix4x4& Camera::SetCamera(
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
    
    m_camera.translate(
        x,
        y,
        z);
    return m_camera;

}
const QMatrix4x4& Camera::GetCamera(){
    return m_camera;
}


