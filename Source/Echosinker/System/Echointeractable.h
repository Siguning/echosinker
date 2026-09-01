#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EchoInteractable.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UEchoInteractable : public UInterface
{
	GENERATED_BODY()
};

class ECHOSINKER_API IEchoInteractable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Echo|Interaction")
	void OnInteract(AActor* Interactor);
};