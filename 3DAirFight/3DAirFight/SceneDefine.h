#ifndef _SCENEDEFINE_H
#define _SCENEDEFINE_H

enum class SceneType
{
    TitleMenuScene,
    SelectMenuScene,
    GameScene,
    CreditScene,
    Exit,
};

enum class SceneStep
{
    Initialize,
    Execute,
    Terminate,
    // Load,
};

#endif