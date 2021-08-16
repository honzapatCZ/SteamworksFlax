// Copyright (C) 2021 Nejcraft Do Not Redistribute


#include "Test.h"

Test::Test(const SpawnParams& params)
    : Script(params)
{
    // Enable ticking OnUpdate function
    _tickUpdate = true;
}

void Test::OnEnable()
{
    auto ass = asset.Get();
    if (ass && ass->WaitForLoaded())
        ass = nullptr;

    if (!ass)
    {
        LOG_STR(Info, TEXT("Could not load Steam Settings"));
        return;
    }

    SteamConfig* conf = (SteamConfig*)ass->Instance;

    platform = New<SteamOnlinePlatform>(conf);
    
    if (platform->Init()) {
        LOG_STR(Info, TEXT("Init OK"));

        String owner = platform->VerifyOwnership() ? TEXT("OK") : TEXT("Nope");
        LOG_STR(Info, TEXT("Ownership ") +  owner);

        for each (String var in platform->GetAchievementService()->GetAchievements())
        {
            LOG_STR(Info, var);
        }
    }
    else {
        LOG_STR(Info, TEXT("Init Failed"));
    }

    // Here you can add code that needs to be called when script is enabled (eg. register for events)
}

void Test::OnDisable()
{
    platform->Deinit();
    // Here you can add code that needs to be called when script is disabled (eg. unregister from events)
}

void Test::OnUpdate()
{
    platform->Update();
    // Here you can add code that needs to be called every frame
}
