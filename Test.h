// Copyright (C) 2021 Nejcraft Do Not Redistribute


#pragma once

#include "Engine/Scripting/Script.h"
#include "SteamOnlinePlatform.h"
#include "Engine/Content/JsonAsset.h"

API_CLASS() class STEAMWORKSFLAX_API Test : public Script
{
API_AUTO_SERIALIZATION();
DECLARE_SCRIPTING_TYPE(Test);

public:
    API_FIELD() AssetReference<JsonAsset> asset;
    SteamOnlinePlatform* platform;
    // [Script]
    void OnEnable() override;
    void OnDisable() override;
    void OnUpdate() override;
};
