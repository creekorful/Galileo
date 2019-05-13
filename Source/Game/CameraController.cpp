#include "CameraController.h"

void CameraController::Update(Window& window, float dt)
{
    // Update position if needed
    if (window.IsKeyPressed(GLFW_KEY_Q))
        _pGameObject->Move(-CAMERA_SPEED * dt, 0, 0);
    else if (window.IsKeyPressed(GLFW_KEY_D))
        _pGameObject->Move(CAMERA_SPEED * dt, 0, 0);
    else if (window.IsKeyPressed(GLFW_KEY_Z))
        _pGameObject->Move(0, 0, -CAMERA_SPEED * dt);
    else if (window.IsKeyPressed(GLFW_KEY_S))
        _pGameObject->Move(0, 0, CAMERA_SPEED * dt);
    else if (window.IsKeyPressed(GLFW_KEY_SPACE))
        _pGameObject->Move(0, CAMERA_SPEED * dt, 0);
    else if (window.IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
        _pGameObject->Move(0, -CAMERA_SPEED * dt, 0);

    // Compute mouse movement
    Vector2d newMousePosition = window.GetMousePos();
    Vector2d mouseOffset = (newMousePosition - _mousePos).Normalize();
    _mousePos = newMousePosition;

    // Update camera rotation based on mouse
    if (mouseOffset.y < 0)
        _pGameObject->Rotate(-1, 0, 0);
    else if (mouseOffset.y > 0)
        _pGameObject->Rotate(1, 0, 0);
    else if (mouseOffset.x < 0)
        _pGameObject->Rotate(0, -1, 0);
    else if (mouseOffset.x > 0)
        _pGameObject->Rotate(0, 1, 0);
}

void CameraController::SetGameObject(GameObject* pGameObject)
{
    _pGameObject = pGameObject;
}
