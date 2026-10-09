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
    Update,
    Terminate,
    Load,
};

#endif