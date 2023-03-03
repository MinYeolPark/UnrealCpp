#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CGameMode.generated.h"

UCLASS()
class UNREALCPPPROJ2_API ACGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACGameMode();	

	virtual void PostLogin(APlayerController* NewPlayer) override;
};
