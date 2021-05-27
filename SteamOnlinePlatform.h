// Copyright (C) 2021 Nejcraft Do Not Redistribute
#pragma once

#include "Engine/Scripting/Script.h"
#include <FlaxOnlineSubsystem/IOnlinePlatform.h>
#include "include/steam_api.h"
#include "SteamConfig.h"

/// <summary>
/// Main steam platform implementation
/// </summary>
API_CLASS(NoSpawn) class STEAMWORKSFLAX_API SteamOnlinePlatform : public IOnlinePlatform
{
	DECLARE_SCRIPTING_TYPE_NO_SPAWN(SteamOnlinePlatform)
protected:
	/// <summary>
	/// Dummy initializer, should not be used
	/// </summary>
	explicit SteamOnlinePlatform() : IOnlinePlatform(SpawnParams(Guid::New(), TypeInitializer)), config(nullptr) {}
public:
	explicit SteamOnlinePlatform(SteamConfig* config) :	SteamOnlinePlatform(){
		this->config = config;
	}
	SteamConfig* config;

	bool Init() override;

	void Deinit() override;

	bool VerifyOwnership() override;

	IAchievementService* cachedAchievement = nullptr;

	IAchievementService* GetAchievementService() override;
};

/// <summary>
/// The steam achievements implementation
/// </summary>
API_CLASS(NoSpawn) class STEAMWORKSFLAX_API SteamAchievementService : public IAchievementService
{
	DECLARE_SCRIPTING_TYPE_NO_SPAWN(SteamAchievementService)
protected:
	/// <summary>
	/// Dummy initializer, should not be used
	/// </summary>
	explicit SteamAchievementService() : IAchievementService(SpawnParams(Guid::New(), TypeInitializer)), parent(nullptr) {}

public:
	explicit SteamAchievementService(SteamOnlinePlatform* parent) : SteamAchievementService() {
		this->parent = parent;
	}
	SteamOnlinePlatform* parent;

	void SetAchievementProgress(StringView& identifier, float value) override;

	void SetAchievement(StringView& identifier, bool value) override;

	//API_FUNCTION() virtual Array<MonoString*> GetAchievements() = 0;

	float GetAchievementProgress(StringView& identifier) override;

	bool GetAchievement(StringView& identifier) override;
};