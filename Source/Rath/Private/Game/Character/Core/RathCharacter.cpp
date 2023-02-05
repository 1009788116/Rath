// Copyright Epic Games, Inc. All Rights Reserved.
#include "Rath/Public/Game/Character/Core/RathCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Game/Ability/AttributeSet/AttributeSet_Base.h"
#include "Game/UMG/GAS/UMG_Attributes.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Rath/Public/Game/Inventory/InventoryComponent.h"

ARathCharacter::ARathCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rate for input
	TurnRateGamepad = 50.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("背包组件"));

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("技能系统组件"));
}

//////////////////////////////////////////////////////////////////////////
// Input

void ARathCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("UI",IE_Pressed,this,&ARathCharacter::UI);
	
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &ARathCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &ARathCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &ARathCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &ARathCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ARathCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ARathCharacter::TouchStopped);
}

UInventoryComponent* ARathCharacter::GetInventoryComponent()
{
	return InventoryComponent;
}

void ARathCharacter::ClientCallServerSwapInventory(int I, int J)
{
	GetInventoryComponent()->SwepInventoryItem(I,J);
}

UAbilitySystemComponent* ARathCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ARathCharacter::HandleHealthChanged(float DeltaValue, const FGameplayTagContainer& SourceTags)
{
	UE_LOG(LogTemp,Warning,TEXT("Health:%d"),DeltaValue)
}

void ARathCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));

	if(AbilitySystemComponent!=nullptr)
	{
		//修改：给ASC赋予技能
		if(HasAuthority()&&RathAbilities.Num()>0)
		{
			for(auto i = 0;i<RathAbilities.Num();i++)
			{
				if(RathAbilities[i] == nullptr)
				{
					UE_LOG(LogTemp,Warning,TEXT("The %d ability is null"),&i);
					continue;
				}
				AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(RathAbilities[i].GetDefaultObject(),1,0));
				UE_LOG(LogTemp,Warning,TEXT("%s"),*FString("Have given ASC ability"));
			}
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("%s"),*FString("AbilityTarry is empty"));
		}
		//修改：初始化ASC
		AbilitySystemComponent->InitAbilityActorInfo(this,this);
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("%s"),*FString("Can not find ability component!"));
	}
	for(TSubclassOf<UAttributeSet>& Set:RathAttributeSets)
	{
		AbilitySystemComponent->InitStats(Set,nullptr);
	}
}

void ARathCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void ARathCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void ARathCharacter::UI()
{
	if(bShowCur)//关闭鼠标
	{
		bShowCur = false;
		UKismetSystemLibrary::PrintString(GetWorld(),TEXT("关闭鼠标"));
		PlayerController->SetShowMouseCursor(bShowCur);
	}
	else//打开鼠标
	{
		bShowCur = true;
		UKismetSystemLibrary::PrintString(GetWorld(),TEXT("打开鼠标"));
		PlayerController->SetShowMouseCursor(bShowCur);
	}
}

void ARathCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ARathCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ARathCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ARathCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
