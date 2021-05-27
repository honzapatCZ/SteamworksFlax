// Copyright (C) 2021 Nejcraft Do Not Redistribute

#include "SteamOnlinePlatform.h"


extern "C" void __cdecl SteamAPIDebugTextHook(int nSeverity, const char* pchDebugText)
{
	LOG_STR(Warning, String(pchDebugText));

	if (nSeverity >= 1)
	{
		// place to set a breakpoint for catching API errors
		int x = 3;
		(void)x;
	}
}

bool SteamOnlinePlatform::Init()
{
    bool ret = SteamAPI_Init();

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

void SteamOnlinePlatform::Deinit()
{
    SteamAPI_Shutdown();
}

bool SteamOnlinePlatform::VerifyOwnership()
{
    return !SteamAPI_RestartAppIfNecessary(config->AppID);
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
	String& val = GetAchievementNameInSteam(identifier);
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
	for (int i = 0; i < parent->mSteamUserStats->GetNumAchievements(); i++) {
		arr.Add(String(parent->mSteamUserStats->GetAchievementName(i)));
	}	
    return arr;
}

float SteamAchievementService::GetAchievementProgress(const String& identifier)
{
    return 0;
}

bool SteamAchievementService::GetAchievement(const String& identifier)
{
	String& val = GetAchievementNameInSteam(identifier);
	bool achieved = false;
	parent->mSteamUserStats->GetAchievement((char*)val.Get(), &achieved);
    return achieved;
}