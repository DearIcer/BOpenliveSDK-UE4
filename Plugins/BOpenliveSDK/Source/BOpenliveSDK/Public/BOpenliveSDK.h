// Copyright 2022 Tangcl, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FBOpenliveSDKModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
