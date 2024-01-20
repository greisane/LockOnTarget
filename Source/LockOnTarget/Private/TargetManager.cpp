// Copyright 2022-2023 Ivan Baktenkov. All Rights Reserved.

#include "TargetManager.h"
#include "Engine/World.h"

UTargetManager::UTargetManager()
{
	RegisteredTargets.Reserve(30);
}

UTargetManager& UTargetManager::Get(UWorld& InWorld)
{
	checkf(InWorld.GetSubsystem<ThisClass>(), TEXT("Unable to access the TargetManager subsystem."));
	return *InWorld.GetSubsystem<ThisClass>();
}

bool UTargetManager::DoesSupportWorldType(const EWorldType::Type Type) const
{
	return Type == EWorldType::Game || Type == EWorldType::PIE;
}

bool UTargetManager::RegisterTarget(UTargetComponent* Target)
{
	bool bHasAlreadyBeen = true;

	if (Target)
	{
		RegisteredTargets.Add(Target, &bHasAlreadyBeen);
	}

	return !bHasAlreadyBeen;
}

bool UTargetManager::UnregisterTarget(UTargetComponent* Target)
{
	return RegisteredTargets.Remove(Target) > 0;
}
