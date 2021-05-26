// Copyright (C) 2021 Nejcraft Do Not Redistribute
#pragma once

#include "Engine/Scripting/Script.h"
#include <FlaxOnlineSubsystem/IOnlinePlatform.h>
#include "include/steam_api.h"
#include "SteamConfig.h"

/// <summary>
/// Main steam platform implementation
/// </summary>
API_CLASS(NoSpawn, Sealed) class STEAMWORKSFLAX_API SteamOnlinePlatform : public IOnlinePlatform
{
	DECLARE_SCRIPTING_TYPE_NO_SPAWN(SteamOnlinePlatform)
protected:
	explicit SteamOnlinePlatform() : 
		IOnlinePlatform(SpawnParams(Guid::New(), TypeInitializer)) {
	}
public:
	explicit SteamOnlinePlatform(SteamConfig* config) :	SteamOnlinePlatform(){
		cachedConfig = config;
	}
	SteamConfig* cachedConfig;

	bool Init() override;

	bool VerifyOwnership() override;

	IAchievementService* cachedAchievement = nullptr;

	IAchievementService* GetAchievementService() override;
};

/// <summary>
/// The steam achievements implementation
/// </summary>
API_CLASS(NoSpawn, Sealed) class STEAMWORKSFLAX_API SteamAchievementService : public IAchievementService
{
	DECLARE_SCRIPTING_TYPE_NO_SPAWN(SteamAchievementService)
protected:
	explicit SteamAchievementService() : 
		IAchievementService(SpawnParams(Guid::New(), TypeInitializer)) {
	}

public:
	explicit SteamAchievementService(SteamOnlinePlatform* parent) : SteamAchievementService() {
		steamPlatform = parent;
	}
	SteamOnlinePlatform* steamPlatform;

	void SetAchievementProgress(StringView& identifier, float value) override;

	void SetAchievement(StringView& identifier, bool value) override;

	//API_FUNCTION() virtual Array<MonoString*> GetAchievements() = 0;

	float GetAchievementProgress(StringView& identifier) override;

	bool GetAchievement(StringView& identifier) override;
};