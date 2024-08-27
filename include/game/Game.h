///
/// The game window of papercraft
///

#pragma once

#include "../gui/Input.h"
#include "../gui/Button.h"
#include "../gui/TextLabel.h"
#include "../gui/ProgressBar.h"
#include "../gui/ImageLabel.h"
#include "../assets/AssetManager.h"
#include "../singleton/Singleton.h"
#include "../gui/GUIManager.h"
#include "../../thirdparty/mINI/src/mini/ini.h"
#include "../EasyXBase.h"
#include "../gui/Scene.h"
#include "../scene/MainScene.h"
#include "../scene/LoadScene.h"
#include "../scene/GameScene.h"
#include "../scene/FishingScene.h"


/// The main window
class PLGame : public PWindow
{
public:
    /// Create the game window
    PLGame(const int &Width, const int &Height, const PString &PlayerName);
    ~PLGame();

public:
    /// Enter the main loop of game window
    void Loop();

    void SetCurrentScene(PScene* scene);
    void SwitchToGameScene();
    void SwitchToMainScene();

private:
    PString _playerName;
    PDevice* _windowDevice;    

private:
    PAssetManager& _assetManager;

    MainScene* mainScene;
    LoadScene* loadScene;
    GameScene* gameScene;
    PScene* currentScene;
    PScene* fishingScene;
};