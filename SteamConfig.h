// Copyright (C) 2021 Nejcraft Do Not Redistribute


#pragma once

#include "Engine/Core/ISerializable.h"
#include "Engine/Core/Types/BaseTypes.h"
#include "Engine/Content/Assets/Model.h"
#include "Engine/Scripting/ScriptingType.h"

/// <summary>
/// SteamConfig Json Asset. 
/// </summary>
API_CLASS() class STEAMWORKSFLAX_API SteamConfig : public ISerializable
{
    API_AUTO_SERIALIZATION();
    DECLARE_SCRIPTING_TYPE_NO_SPAWN(SteamConfig);
public:
	// Custom float value.
    API_FIELD(Attributes = "EditorDisplay(\"AppID\")") 
    int AppID = 0;
};
