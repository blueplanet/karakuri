/*!
    @file   LoadingWorld.cpp
    @author numata
    @date   10/02/13
 */

#include "LoadingWorld.h"
#include "Globals.h"


void LoadingWorld::becameActive()
{
    mCount = 0;
    mDirection = 1;

    gKRAudioMan->playBGM(BGM_ID::Loading);
}

void LoadingWorld::resignedActive()
{
    gKRAudioMan->stopBGM();
}

void LoadingWorld::updateModel(KRInput* input)
{
    mCount += mDirection;
    if (mCount == 60 || mCount == 0) {
        mDirection *= -1;
    }

    double progress = getLoadingProgress();
    gKRAudioMan->setBGMVolume(1.0-progress);
    
#if _DEBUG
#error TEST
#endif
}

void LoadingWorld::drawView(KRGraphics* g)
{
    double progress = getLoadingProgress();
    
    g->clear(KRColor::White);
    
    double alpha = (double)mCount / 60;
    
    gKRTex2DMan->drawAtPoint(TexID::LoadingText, KRVector2D(gKRScreenSize.x-200, 0), alpha);
    gKRTex2DMan->drawAtPoint(TexID::LoadingChara, KRVector2D(gKRScreenSize.x-200, 50));
    
    KRVector2D barSize = gKRTex2DMan->getTextureSize(TexID::LoadingOn);
    gKRTex2DMan->drawAtPoint(TexID::LoadingOff, KRVector2D(10, 10));
    gKRTex2DMan->drawAtPointEx2(TexID::LoadingOn, KRVector2D(10, 10), KRRect2D(0, 0, (int)(barSize.x*progress+0.5), barSize.y),
                                0.0, KRVector2DZero, KRVector2DOne);
}


