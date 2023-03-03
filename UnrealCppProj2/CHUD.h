#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CHUD.generated.h"

UCLASS()
class UNREALCPPPROJ2_API ACHUD : public AHUD
{
	GENERATED_BODY()

public:
	ACHUD();
	virtual void DrawHUD() override;

private:
	UPROPERTY(EditDefaultsOnly)
		class UTexture2D* Texture;

private:
	bool bDraw;

public:
	FORCEINLINE void SetDraw() { bDraw = true; }
	FORCEINLINE void SetNotDraw() { bDraw = false; }
};
