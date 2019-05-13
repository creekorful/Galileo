#ifndef GALILEO_CAMERACONTROLLER_H
#define GALILEO_CAMERACONTROLLER_H


#include "../Engine/Core/Component.h"

#define CAMERA_SPEED 0.005f

class CameraController : public Component
{
public:
    void Update(Window& window, float dt) override;

    void SetGameObject(GameObject* pGameObject) override;

private:
    GameObject* _pGameObject;
    Vector2d _mousePos;
};


#endif //GALILEO_CAMERACONTROLLER_H
