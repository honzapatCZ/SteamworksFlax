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

	bool CheckDll();

	void Deinit() override;

	void Update() override;

	bool VerifyOwnership() override;

	IAchievementService* cachedAchievement = nullptr;

	IAchievementService* GetAchievementService() override;

	ISteamClient* mSteamClient = nullptr;
	ISteamUser* mSteamUser = nullptr;
	ISteamFriends* mSteamFriends = nullptr;
	ISteamUtils* mSteamUtils = nullptr;
	ISteamMatchmaking* mSteamMatchmaking = nullptr;
	ISteamUserStats* mSteamUserStats = nullptr;
	ISteamApps* mSteamApps = nullptr;
	ISteamMatchmakingServers* mSteamMatchmakingServers = nullptr;
	ISteamNetworking* mSteamNetworking = nullptr;
	ISteamRemoteStorage* mSteamRemoteStorage = nullptr;
	ISteamScreenshots* mSteamScreenshots = nullptr;
	ISteamGameSearch* mSteamGameSearch = nullptr;
	ISteamHTTP* mSteamHTTP = nullptr;
	ISteamController* mController = nullptr;
	ISteamUGC* mSteamUGC = nullptr;
	ISteamAppList* mSteamAppList = nullptr;
	ISteamMusic* mSteamMusic = nullptr;
	ISteamMusicRemote* mSteamMusicRemote = nullptr;
	ISteamHTMLSurface* mSteamHTMLSurface = nullptr;
	ISteamInventory* mSteamInventory = nullptr;
	ISteamVideo* mSteamVideo = nullptr;
	ISteamParentalSettings* mSteamParentalSettings = nullptr;
	ISteamInput* mSteamInput = nullptr;
	ISteamParties* mSteamParties = nullptr;
	ISteamRemotePlay* mSteamRemotePlay = nullptr;
	ISteamNetworkingUtils* mSteamNetworkingUtils = nullptr;
	ISteamNetworkingSockets* mSteamNetworkingSockets = nullptr;
	ISteamNetworkingMessages* mSteamNetworkingMessages = nullptr;
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

	/// <summary>
	/// Converts normalized name to steam achievement name using the mapping specified in this config or input value if it couldnt be found
	/// </summary>
	/// <param name="">Normalized input</param>
	/// <returns>The value in the mapping or input if it couldnt be found</returns>
	FORCE_INLINE SteamAchievementInfo GetAchievementNameInSteam(String normalizedName) {
		if (parent->config->AchievementNameMapping.ContainsKey(normalizedName)) {
			return parent->config->AchievementNameMapping[normalizedName];
		}
		auto info = New<SteamAchievementInfo>();
		info->apiName = normalizedName;
		
		return *info;
	}
	/// <summary>
	/// Converts normalized name to steam achievement name using the mapping specified in this config or input value if it couldnt be found
	/// </summary>
	/// <param name="">Normalized input</param>
	/// <returns>The value in the mapping or input if it couldnt be found</returns>
	FORCE_INLINE String GetNormalizedNameFromSteam(String steamName) {
		Array<SteamAchievementInfo> infos;
		parent->config->AchievementNameMapping.GetValues(infos);
		Array<String> keys;
		parent->config->AchievementNameMapping.GetKeys(keys);
		for (int i = 0; i < infos.Count(); )
		{
			if (infos[i].apiName == steamName) {
				return keys[i];
			}
		}

		return steamName;
	}

	void SetAchievementProgress(const String& identifier, int value) override;

	void SetAchievement(const String& identifier, bool value) override;

	Array<String> GetAchievements() override;

	int GetAchievementProgress(const String& identifier) override;

	bool GetAchievement(const String& identifier) override;
};