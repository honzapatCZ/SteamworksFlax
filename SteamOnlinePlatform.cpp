// Copyright (C) 2021 Nejcraft Do Not Redistribute

#include "SteamOnlinePlatform.h"


bool SteamOnlinePlatform::Init()
{
    bool ret = SteamAPI_Init();
    return ret;
    //return true;
}

void SteamOnlinePlatform::Deinit()
{
}

bool SteamOnlinePlatform::VerifyOwnership()
{
    return !SteamAPI_RestartAppIfNecessary(config->AppID);
    //return true;
}

IAchievementService* SteamOnlinePlatform::GetAchievementService()
{
    if (cachedAchievement == nullptr)
    {
        cachedAchievement = New<SteamAchievementService>(this);
    }
    return cachedAchievement;
}


void SteamAchievementService::SetAchievementProgress(StringView& identifier, float value)
{
    return;
}

void SteamAchievementService::SetAchievement(StringView& identifier, bool value)
{
    return;
}

float SteamAchievementService::GetAchievementProgress(StringView& identifier)
{
    return 0;
}

bool SteamAchievementService::GetAchievement(StringView& identifier)
{
    return false;
}