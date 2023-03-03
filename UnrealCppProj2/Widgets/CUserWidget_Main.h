#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Main.generated.h"

UCLASS()
class UNREALCPPPROJ2_API UCUserWidget_Main : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FName Name = "Code Story";
protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnEnterButton();

	UFUNCTION()
		void SetName(FName NewName);
		
	UFUNCTION()
		FName GetName() { return Name; }

	UPROPERTY(EditAnywhere)
		class UEditableTextBox* TextField;
	UPROPERTY(EditAnywhere)
		class UButton* EnterButton;
};
