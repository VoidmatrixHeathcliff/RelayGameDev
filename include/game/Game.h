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

/// The game window
class PLGame : public PWindow
{
public:
    /// Create the game window
    PLGame(const int &Width, const int &Height, const PString &PlayerName);

public:
    /// Enter the message loop of game window
    void Loop();
    
private:
    /// Init the fake load UI
    void InitFakeLoadUI();
    /// Load the menu UI
    void InitLoadMenuUI();

private:
    /// This functino give a smooth interpolation for progress bar
    /// @param X The X parameter of the smooth function
    /// @return The result of the interpolation
    float SmoothInterpolation(const float &X) const;
    /// Read the puns from the assets
    void ReadPuns();

private:
    PString _playerName;
    PDevice* _windowDevice;    
private:
    std::vector<PGUIObject *> _fakeLoadUI;
    PImageLabel*              _logo;
    PProgressBar*             _progressBar;

private:
    std::vector<PGUIObject *> _menuUI;
    PImageLabel*              _backgroundImage;
    PImageLabel*              _gameLogoImage;
    PButton*                  _playButton;
    PButton*                  _settingButton;
    PButton*                  _quitButton;

private:
    std::vector<std::wstring> _punList;
    
private:
    PAssetManager& _assetManager;
    PGUIManager*   _manager;
};