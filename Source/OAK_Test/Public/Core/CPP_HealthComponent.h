// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPP_HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OAK_TEST_API UCPP_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCPP_HealthComponent();

	UFUNCTION(BlueprintCallable)
	void DamagePlayer(float Damage, APlayerController* DamageCauser);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	const float MaxHealth = 100.0f;
	UPROPERTY(Replicated,VisibleAnywhere,BlueprintReadOnly,Category="Health",meta=(AllowPrivateAccess="true"))
	float Health = MaxHealth;

	ACharacter* OwnerCharacter;
};
