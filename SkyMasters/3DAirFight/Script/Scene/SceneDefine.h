#ifndef _SCENEDEFINE_H
#define _SCENEDEFINE_H

enum class SceneType
{
    TitleScene,
    GameScene,
    Exit,
};

enum class SceneStep
{
    Initialize,
    Execute,
    Terminate,
    Load,
};

#endif