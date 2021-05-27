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
    SteamAPI_Shutdown();
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


void SteamAchievementService::SetAchievementProgress(const String& identifier, float value)
{

    return;
}

void SteamAchievementService::SetAchievement(const String& identifier, bool value)
{
    return;
}

Array<String> SteamAchievementService::GetAchievements()
{
    return Array<String>();
}

float SteamAchievementService::GetAchievementProgress(const String& identifier)
{
    return 0;
}

bool SteamAchievementService::GetAchievement(const String& identifier)
{
    return false;
}