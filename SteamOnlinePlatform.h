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

	ISteamClient* mSteamClient;
	ISteamUser* mSteamUser;
	ISteamFriends* mSteamFriends;
	ISteamUtils* mSteamUtils;
	ISteamMatchmaking* mSteamMatchmaking;
	ISteamUserStats* mSteamUserStats;
	ISteamApps* mSteamApps;
	ISteamMatchmakingServers* mSteamMatchmakingServers;
	ISteamNetworking* mSteamNetworking;
	ISteamRemoteStorage* mSteamRemoteStorage;
	ISteamScreenshots* mSteamScreenshots;
	ISteamGameSearch* mSteamGameSearch;
	ISteamHTTP* mSteamHTTP;
	ISteamController* mController;
	ISteamUGC* mSteamUGC;
	ISteamAppList* mSteamAppList;
	ISteamMusic* mSteamMusic;
	ISteamMusicRemote* mSteamMusicRemote;
	ISteamHTMLSurface* mSteamHTMLSurface;
	ISteamInventory* mSteamInventory;
	ISteamVideo* mSteamVideo;
	ISteamParentalSettings* mSteamParentalSettings;
	ISteamInput* mSteamInput;
	ISteamParties* mSteamParties;
	ISteamRemotePlay* mSteamRemotePlay;
	ISteamNetworkingUtils* mSteamNetworkingUtils;
	ISteamNetworkingSockets* mSteamNetworkingSockets;
	ISteamNetworkingMessages* mSteamNetworkingMessages;
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
	FORCE_INLINE String GetAchievementNameInSteam(String normalizedName) {
		if (parent->config->AchievementNameMapping.ContainsKey(normalizedName)) {
			return parent->config->AchievementNameMapping[normalizedName];
		}
		return normalizedName;
	}

	void SetAchievementProgress(const String& identifier, float value) override;

	void SetAchievement(const String& identifier, bool value) override;

	Array<String> GetAchievements() override;

	float GetAchievementProgress(const String& identifier) override;

	bool GetAchievement(const String& identifier) override;
};