#pragma once

#include "Component.h"
#include <DxLib.h>

class UIRenderer : public Component
{
public:
    UIRenderer(Actor* owner)
        :Component(owner)
    {

    }
    ~UIRenderer();
    //void Draw() override;

private:

};