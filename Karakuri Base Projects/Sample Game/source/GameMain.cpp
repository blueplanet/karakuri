/*!
    @file   GameMain.cpp
    @author ___FULLUSERNAME___
    @date   ___DATE___
 */

#include "GameMain.h"
#include "Globals.h"

#include "LogoWorld.h"
#include "LoadingWorld.h"
#include "TitleWorld.h"
#include "PlayWorld.h"

#include "Player.h"
#include "Enemy1.h"
#include "Enemy2.h"


GameMain::GameMain()
{
    ///// Main Settings

    setTitle("My Karakuri Game");           // Game title (iOS won't use this setting)

    setScreenSize(480, 320);                // iPhone Size (Horizontal use)
    //setScreenSize(320, 480);                // iPhone Size (Vertical use. Don't forget to remove Default.png and rename Default_V.png to Default.png.)
    //setScreenSize(1024, 768);               // iPad size (Horizontal use. Don't forget to remove Default-Portrait.png.)
    //setScreenSize(768, 1024);               // iPad size (Vertical use. Don't forget to remove Default-Landscape.png.)

    setFrameRate(60.0);                     // Refresh rate
    setAudioMixType(KRAudioMixTypeAmbient); // Audio mixing

    setShowsMouseCursor(true);              // Mouse cursor should be shown (iOS won't use this setting)
    setShowsFPS(true);                      // Realtime FPS information (Debug build only)

    // Set max animation character count
    setMaxChara2DCount(1024);
    
    // Update max animation character class size
    updateMaxChara2DSize(sizeof(Player));
    updateMaxChara2DSize(sizeof(Enemy1));
    updateMaxChara2DSize(sizeof(Enemy2));
    
    // TODO: Edit "Target" setting to change the bundle name, which will be shown in Finder or iPhone Desktop.

    ///// Add any code here for creating your objects
}

GameMain::~GameMain()
{
    // Add any code here for cleaning up your objects
}

void GameMain::setupResources()
{
    ///// Add all required resources at this point.

    // Load integrated resource file.
    addResources("resource.krrs");

    // Logo and Loading Worlds
    if (KRCheckDeviceType(KRDeviceTypeIPad)) {
        gKRTex2DMan->addTexture(GroupID::LogoAndLoading,
                                TexID::Logo,
                                (gKRScreenSize.x > gKRScreenSize.y)? "Default-Landscape.png": "Default-Portrait.png");
    } else {
        gKRTex2DMan->addTexture(GroupID::LogoAndLoading, TexID::Logo, "Default.png");
    }

    gKRTex2DMan->addTexture(GroupID::LogoAndLoading, TexID::LoadingText, "loading_text.png");
    gKRTex2DMan->addTexture(GroupID::LogoAndLoading, TexID::LoadingChara, "loading_chara.png");
    gKRTex2DMan->addTexture(GroupID::LogoAndLoading, TexID::LoadingOff, "loading_off.png");
    gKRTex2DMan->addTexture(GroupID::LogoAndLoading, TexID::LoadingOn, "loading_on.png");
    gKRAudioMan->addBGM(GroupID::LogoAndLoading, BGM_ID::Loading, "bgm_loading.caf");

    // Title World
    gKRTex2DMan->addTexture(GroupID::Title, TexID::Title, "title.png");
    gKRAudioMan->addBGM(GroupID::Title, BGM_ID::Title, "bgm_title.caf");

    // Play World
    gKRAudioMan->addBGM(GroupID::Play, BGM_ID::Play, "bgm_play.caf");
    gKRAudioMan->addSE(GroupID::Play, SE_ID::Burn, "se_burn.caf");
    
    // Load logo and loading worlds resources
    loadResourceGroup(GroupID::LogoAndLoading);
}

std::string GameMain::setupWorlds()
{
    // Add world instances with name
    addWorld("logo", new LogoWorld());
    addWorld("load", new LoadingWorld());
    addWorld("title", new TitleWorld());
    addWorld("play", new PlayWorld());
    
    // Return the first world name
    return "logo";
}

