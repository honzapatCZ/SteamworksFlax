// Copyright (C) 2021 Nejcraft Do Not Redistribute

#include "SteamOnlinePlatform.h"


extern "C" void __cdecl SteamAPIDebugTextHook(int nSeverity, const char* pchDebugText)
{
	LOG_STR(Warning, TEXT("SteamApi: ") + String(pchDebugText));

	if (nSeverity >= 1)
	{
		// place to set a breakpoint for catching API errors
		int x = 3;
		(void)x;
	}
}

bool SteamOnlinePlatform::Init()
{
	if (!CheckDll()) {
		LOG_STR(Error, TEXT("CheckDll() failed"));
		return false;
	}

	if (!SteamAPI_Init()) {
		LOG_STR(Error, TEXT("SteamAPI_Init() failed"));
		return false;
	}

	mSteamClient = SteamClient();
	if (mSteamClient == nullptr) { return false; }

	mSteamClient->SetWarningMessageHook(&SteamAPIDebugTextHook);

	mSteamUser = SteamUser();
	if (mSteamUser == nullptr) { return false; }
	mSteamFriends = SteamFriends();
	if (mSteamFriends == nullptr) { return false; }
	mSteamUtils = SteamUtils();
	if (mSteamUtils == nullptr) { return false; }
	mSteamMatchmaking = SteamMatchmaking();
	if (mSteamMatchmaking == nullptr) { return false; }
	mSteamUserStats = SteamUserStats();
	if (mSteamUserStats == nullptr) { return false; }
	mSteamApps = SteamApps();
	if (mSteamApps == nullptr) { return false; }
	mSteamMatchmakingServers = SteamMatchmakingServers();
	if (mSteamMatchmakingServers == nullptr) { return false; }
	mSteamNetworking = SteamNetworking();
	if (mSteamNetworking == nullptr) { return false; }
	mSteamRemoteStorage = SteamRemoteStorage();
	if (mSteamRemoteStorage == nullptr) { return false; }
	mSteamScreenshots = SteamScreenshots();
	if (mSteamScreenshots == nullptr) { return false; }
	mSteamGameSearch = SteamGameSearch();
	if (mSteamGameSearch == nullptr) { return false; }
	mSteamHTTP = SteamHTTP();
	if (mSteamHTTP == nullptr) { return false; }
	mController = SteamController();
	if (mController == nullptr) { return false; }
	mSteamUGC = SteamUGC();
	if (mSteamUGC == nullptr) { return false; }
	mSteamAppList = SteamAppList();
	if (mSteamAppList == nullptr) { return false; }
	mSteamMusic = SteamMusic();
	if (mSteamMusic == nullptr) { return false; }
	mSteamMusicRemote = SteamMusicRemote();
	if (mSteamMusicRemote == nullptr) { return false; }
	mSteamHTMLSurface = SteamHTMLSurface();
	if (mSteamHTMLSurface == nullptr) { return false; }
	mSteamInventory = SteamInventory();
	if (mSteamInventory == nullptr) { return false; }
	mSteamVideo = SteamVideo();
	if (mSteamVideo == nullptr) { return false; }
	mSteamParentalSettings = SteamParentalSettings();
	if (mSteamParentalSettings == nullptr) { return false; }
	mSteamInput = SteamInput();
	if (mSteamInput == nullptr) { return false; }
	mSteamParties = SteamParties();
	if (mSteamParties == nullptr) { return false; }
	mSteamRemotePlay = SteamRemotePlay();
	if (mSteamRemotePlay == nullptr) { return false; }
	mSteamNetworkingUtils = SteamNetworkingUtils();
	if (mSteamNetworkingUtils == nullptr) { return false; }
	mSteamNetworkingSockets = SteamNetworkingSockets();
	if (mSteamNetworkingSockets == nullptr) { return false; }
	mSteamNetworkingMessages = SteamNetworkingMessages();
	if (mSteamNetworkingMessages == nullptr) { return false; }
    return true;
}

bool SteamOnlinePlatform::CheckDll()
{
	if (sizeof(void*) == 4) {
		
	}
	else {

	}

	return true;
}

void SteamOnlinePlatform::Deinit()
{
    SteamAPI_Shutdown();
}

void SteamOnlinePlatform::Update()
{
	SteamAPI_RunCallbacks();
}

bool SteamOnlinePlatform::VerifyOwnership()
{
	if (config->ForceAppToLaunchInSteam && SteamAPI_RestartAppIfNecessary(config->AppID)) {
		return false;
	}
	if (mSteamApps != nullptr) {
		return mSteamApps->BIsSubscribed() && mSteamApps->BIsSubscribedApp(config->AppID);
	}
	return false;
}

IAchievementService* SteamOnlinePlatform::GetAchievementService()
{
    if (cachedAchievement == nullptr)
    {
        cachedAchievement = New<SteamAchievementService>(this);
    }
    return cachedAchievement;
}

void SteamAchievementService::SetAchievementProgress(const String& identifier, int value)
{
	SteamAchievementInfo& val = GetAchievementNameInSteam(identifier);
	int min;
	int max;
	parent->mSteamUserStats->GetAchievementProgressLimits((char*)val.apiName.Get(), &min, &max);
	parent->mSteamUserStats->SetStat((char*)val.optionalStatName.Get(), value);
	parent->mSteamUserStats->IndicateAchievementProgress((char*)val.apiName.Get(), value < min ? min : value, max);

	parent->mSteamUserStats->StoreStats();
}

void SteamAchievementService::SetAchievement(const String& identifier, bool value)
{
	String& val = GetAchievementNameInSteam(identifier).apiName;
	if (value) {
		parent->mSteamUserStats->ClearAchievement((char*)val.Get());
	}
	else {
		parent->mSteamUserStats->SetAchievement((char*)val.Get());
	}
	parent->mSteamUserStats->StoreStats();
}

Array<String> SteamAchievementService::GetAchievements()
{
	auto arr = Array<String>();
	LOG_STR(Info, String::Format(TEXT("Num of ach: {0}"), parent->mSteamUserStats->GetNumAchievements()));

	for (uint32 i = 0; i < parent->mSteamUserStats->GetNumAchievements(); i++) {
		String name = String(parent->mSteamUserStats->GetAchievementName(i));
		LOG_STR(Info, TEXT("Testing: ") + name);
		arr.Add(GetNormalizedNameFromSteam(name));
	}	
    return arr;
}

int SteamAchievementService::GetAchievementProgress(const String& identifier)
{
	SteamAchievementInfo& val = GetAchievementNameInSteam(identifier);
	int min;
	int max;
	parent->mSteamUserStats->GetAchievementProgressLimits((char*)val.apiName.Get(), &min, &max);
	int data = 0;
	parent->mSteamUserStats->GetStat((char*)val.optionalStatName.Get(), &data);
	if (max < data)
		return max;
	return data;
}

bool SteamAchievementService::GetAchievement(const String& identifier)
{
	String& val = GetAchievementNameInSteam(identifier).apiName;
	bool achieved = false;
	parent->mSteamUserStats->GetAchievement((char*)val.Get(), &achieved);
    return achieved;
}