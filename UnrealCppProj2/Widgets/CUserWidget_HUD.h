#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_HUD.generated.h"

UCLASS()
class UNREALCPPPROJ2_API UCUserWidget_HUD : public UUserWidget
{
	GENERATED_BODY()

public:
	//void BindCharacterStat(class UABCharacterStatComponent* CharacterStat);
	void BindPlayerState(class ACPlayerState* PlayerState);
	void UpdatePlayerName(FText NewName);

protected:
	virtual void NativeConstruct() override;
	void UpdateCharacterStat();
	void UpdatePlayerState();
private:
	//TWeakObjectPtr<class UCCharacterStatComponent> CurrentCharacterStat;
	//TWeakObjectPtr<class ACPlayerState> CurrentPlayerState;

	UPROPERTY()
		class UProgressBar* HPBar;

	UPROPERTY()
		class UProgressBar* ExpBar;

	UPROPERTY()
		class UTextBlock* PlayerName;

	UPROPERTY()
		class UTextBlock* PlayerLevel;

	UPROPERTY()
		class UTextBlock* CurrentScore;

	UPROPERTY()
		class UTextBlock* HighScore;
};
