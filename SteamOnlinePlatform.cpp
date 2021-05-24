// Copyright (C) 2021 Nejcraft Do Not Redistribute

#include "SteamOnlinePlatform.h"

SteamOnlinePlatform::SteamOnlinePlatform(SteamConfig* config) {
    cachedConfig = config;
}

bool SteamOnlinePlatform::Init()
{
    bool ret = SteamAPI_Init();

}

bool SteamOnlinePlatform::VerifyOwnership()
{
    return SteamAPI_RestartAppIfNecessary(cachedConfig->AppID);
}

IAchievementService* SteamOnlinePlatform::GetAchievementService()
{
    if (cachedAchievement == nullptr)
    {
        cachedAchievement = New<SteamAchievementService>(this);
    }
    return cachedAchievement;    
}

IFriendsService* SteamOnlinePlatform::GetFriendsService()
{
    return nullptr;
}

SteamAchievementService::SteamAchievementService(SteamOnlinePlatform* parent) {

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