// Fill out your copyright notice in the Description page of Project Settings.

#include "Brick.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Ball.h"
#include "utils/Logs.h"
#include "ArkanoidUE5GameModeBase.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ABrick::ABrick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SM_Brick = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Brick"));
	SM_Brick->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Box_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	Box_Collision->SetBoxExtent(FVector(25.0f, 10.0f, 10.0f));
	RootComponent = SM_Brick;
	Box_Collision->SetupAttachment(SM_Brick);
	
	OnMaterial = CreateDefaultSubobject<UMaterial>(TEXT("OnMaterial"));
	OffMaterial = CreateDefaultSubobject<UMaterial>(TEXT("OffMaterial"));
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BrickMesh(TEXT("/Script/Engine.StaticMesh'/Game/Assets/Meshes/SM_Brick.SM_Brick'"));

	if (BrickMesh.Succeeded())
	{
		SM_Brick->SetStaticMesh(BrickMesh.Object);
		SM_Brick->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		SM_Brick->SetWorldScale3D(FVector(1.f));
	}

	//TCHAR* SoundPath = L"/Script/Engine.SoundWave'/Game/Assets/Audio/253172__suntemple__retro-bonus-pickup-sfx.253172__suntemple__retro-bonus-pickup-sfx'";
	//auto AmmoPickupSoundAsset = ConstructorHelpers::FObjectFinder<USoundBase>(TEXT("/Script/Engine.SoundWave'/Game/Assets/Audio/253172__suntemple__retro-bonus-pickup-sfx.253172__suntemple__retro-bonus-pickup-sfx'"));

	//if (AmmoPickupSoundAsset.Object != nullptr)
	//{
		//OverlapSound = AmmoPickupSoundAsset.Object;
	//}

	FString Path = TEXT("/Script/Engine.SoundWave'/Game/Assets/Audio/253172__suntemple__retro-bonus-pickup-sfx.253172__suntemple__retro-bonus-pickup-sfx'");
	OverlapSound = LoadAssetFromPath<USoundBase>(FName(*Path));

//	FString  Path1 = TEXT("/Script/Engine.ParticleSystem'/Game/Assets/Particles/P_Explosion.P_Explosion''");
//	
//	DeathParticleSystem = LoadAssetFromPath<UParticleSystem>(FName(*Path1));
	//PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyPSC"));
//	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("/Script/Engine.ParticleSystem'/Game/Assets/Particles/P_Explosion.P_Explosion'"));
//	DeathParticleSystem = CreateDefaultSubobject<UParticleSystem>(TEXT("MyPSC"));
	DeathParticleSystem  = LoadObject<UParticleSystem>(nullptr, TEXT("/Script/Engine.ParticleSystem'/Game/Assets/Particles/P_Explosion.P_Explosion'"));
	

//	PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyPSC"));

//	PSC->SetTemplate(PS.Object);

	//check(PCS);
}

// Called when the game starts or when spawned
void ABrick::BeginPlay()
{
	Super::BeginPlay();
	Box_Collision->OnComponentBeginOverlap.AddDynamic(this, &ABrick::OnOverlapBegin);

	//SM_Brick->CreateAndSetMaterialInstanceDynamic(0);
	//SM_Brick->CreateDynamicMaterialInstance(OffMaterial, FName("MyDynMat"));
	TestMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Script/Engine.Material'/Game/Assets/Materials/b.b'"));

	if (TestMaterial)
	{
		MI_TestMaterial = UMaterialInstanceDynamic::Create(TestMaterial, this);
		//MI_TestMaterial->SetScalarParameterValue(TEXT("Radius"), 0.0f);
	}

	SM_Brick->SetMaterial(0, MI_TestMaterial);

	//FString s = "delegate";

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *MI_TestMaterial->GetName());

	UWorld* World = GetWorld();

	if (World)
	{
		AGameModeBase* GameMode = World->GetAuthGameMode();
		if (GameMode)
		{
			mode = Cast<AArkanoidUE5GameModeBase>(GameMode);
	

		}
	}
}

// Called every frame
void ABrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABrick::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType, bool bFromSweep,
	const FHitResult& SweepResult)
{

	if (OtherActor->ActorHasTag("Ball")) {

		ABall* MyBall = Cast<ABall>(OtherActor);
		const FVector Location = GetActorLocation();
		FVector BallVelocity = MyBall->GetVelocity();
		BallVelocity *= (SpeedModifierOnBounce - 1.0f);
		MyBall->GetBall()->SetPhysicsLinearVelocity(BallVelocity, true);
		mode->UpdateScore();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathParticleSystem, Location);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), OverlapSound, GetActorLocation());
		FString s = "cplision";
		//Logs::printOnScreen(*BallVelocity.ToString());
		
		FTimerHandle UnusedHandle;
		float timeTudestroy = 0.5f;

		//UStaticMeshComponent* sphere = this->FindComponentByClass<UStaticMeshComponent>();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, MI_TestMaterial->GetName());
		//SM_Brick->SetMaterial(0, OnMaterial);
		MI_TestMaterial->SetVectorParameterValue(FName(TEXT("Color")), FLinearColor(0.9f, 0.1f, 0.1f));

		//UE_LOG(LogTemp, Warning, TEXT("%s"), *MI_TestMaterial->GetName());
		Logs::Log(MI_TestMaterial->GetName());

		//DrawDebugSphere(GetWorld(), GetActorLocation(), 10, 26, FColor(181, 0, 0), true, -1, 0, 2);
		mode->RemoveBrick(this);
		///DrawDebugBox(GetWorld(), GetActorLocation(), FVector(10, 10, 10), FColor::White, true, -1, 0, 10);
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &ABrick::DestroyBrick, timeTudestroy, false);


	}

}

void ABrick::DestroyBrick()
{
	this->Destroy();
}

