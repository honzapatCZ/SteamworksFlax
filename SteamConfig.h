// Copyright (C) 2021 Nejcraft Do Not Redistribute


#pragma once

#include "Engine/Core/ISerializable.h"
#include "Engine/Core/Types/BaseTypes.h"
#include "Engine/Content/Assets/Model.h"
#include "Engine/Core/Collections/Dictionary.h"
#include "Engine/Scripting/ScriptingType.h"

/// <summary>
/// SteamConfig Json Asset. 
/// </summary>
API_CLASS() class STEAMWORKSFLAX_API SteamConfig : public ISerializable
{
    API_AUTO_SERIALIZATION();
    DECLARE_SCRIPTING_TYPE_NO_SPAWN(SteamConfig);
public:
    /// <summary>
    /// The associated steam AppID. Will be used for verifying ownership at start of the game
    /// </summary>
    API_FIELD(Attributes = "Tooltip(\"The associated steam AppID. Will be used for verifying ownership at start of the game\")")
    int AppID = 0;

    /// <summary>
    /// Mapping from your universal achievement name to steam specific achievement name, if both names matches you dont have to put them here
    /// </summary>
    API_FIELD(Attributes = "Tooltip(\"Mapping from your universal achievement name to steam specific achievement name, if both names matches you dont have to put them here.\")")
    Dictionary<String, String> AchievementNameMapping;
};
