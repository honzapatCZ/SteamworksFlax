// Copyright (C) 2021 Nejcraft Do Not Redistribute
#pragma once

#include "Engine/Scripting/Script.h"
#include <FlaxOnlineSubsystem/IOnlinePlatform.h>
#include "include/steam_api.h"
#include "SteamConfig.h"

API_CLASS(NoSpawn) class ONLINEPLATFORM_API SteamOnlinePlatform : public IOnlinePlatform
{
	DECLARE_SCRIPTING_TYPE_MINIMAL(SteamOnlinePlatform)
public:
	SteamConfig* cachedConfig;
	SteamOnlinePlatform(SteamConfig* config);

	bool Init() override;

	bool VerifyOwnership() override;

	IAchievementService* cachedAchievement = nullptr;

	IAchievementService* GetAchievementService() override;

	IFriendsService* GetFriendsService() override;

};

API_CLASS(NoSpawn) class ONLINEPLATFORM_API SteamAchievementService : public IAchievementService
{
	DECLARE_SCRIPTING_TYPE_MINIMAL(SteamAchievementService)
public:
	SteamAchievementService(SteamOnlinePlatform* parent);

	void SetAchievementProgress(StringView& identifier, float value) override;

	void SetAchievement(StringView& identifier, bool value) override;

	//API_FUNCTION() virtual Array<MonoString*> GetAchievements() = 0;

	float GetAchievementProgress(StringView& identifier) override;

	bool GetAchievement(StringView& identifier) override;
};