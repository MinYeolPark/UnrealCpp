#pragma once

#include "CoreMinimal.h"
#include "Characters/CEnemy.h"
#include "CBoss.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCPPPROJ2_API ACBoss : public ACEnemy
{
	GENERATED_BODY()

public:
	ACBoss();
	
	virtual void BeginPlay();
};
