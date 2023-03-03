#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CPlayerState.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FOnPlayerStateChangedDelegate);
UCLASS()
class UNREALCPPPROJ2_API ACPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ACPlayerState();

	int32 GetGameScore() const;
	int32 GetGameHighScore() const;
	FString SaveSlotName;
	int32 GetCharacterLevel() const;
	int32 GetCharacterIndex() const;
	float GetExpRatio() const;
	bool AddExp(int32 IncomeExp);
	void AddGameScore();

	void InitPlayerData();
	void SavePlayerData();

	FOnPlayerStateChangedDelegate OnPlayerStateChanged;

protected:
	UPROPERTY(Transient)
		int32 GameScore;

	UPROPERTY(Transient)
		int32 GameHighScore;

	UPROPERTY(Transient)
		int32 CharacterLevel;

	UPROPERTY(Transient)
		int32 Exp;

	UPROPERTY(Transient)
		int32 CharacterIndex;

private:
	void SetCharacterLevel(int32 NewCharacterLevel);
	
};
