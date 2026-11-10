
#include "Enemigos.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"

AEnemigos::AEnemigos()
{
    PrimaryActorTick.bCanEverTick = true;

    MallaEnemigo = CreateDefaultSubobject<UStaticMeshComponent>(
        TEXT("MallaEnemigo")
        );

    SetRootComponent(MallaEnemigo);

    // Asigna un cubo basico a todos los enemigos
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Cubo(
        TEXT("/Engine/BasicShapes/Cube.Cube")
    );

    if (Cubo.Succeeded())
    {
        MallaEnemigo->SetStaticMesh(Cubo.Object);
    }

    Velocidad = 300.0f;
    TiempoVida = 25.0f;
    NumeroCuadrilla = 0;

    // Valores iniciales del movimiento aleatorio
    DireccionMovimiento = FVector::ForwardVector;
    PosicionInicial = FVector::ZeroVector;

    TiempoCambioDireccion = 0.0f;
    IntervaloCambioDireccion = 1.5f;
    RadioMovimiento = 5000.0f;
}

void AEnemigos::BeginPlay()
{
    Super::BeginPlay();

    // Guarda la posicion inicial de este enemigo
    PosicionInicial = GetActorLocation();

    // Cada enemigo comienza con una direccion aleatoria
    DireccionMovimiento = FVector(
        FMath::FRandRange(-1.0f, 1.0f),
        FMath::FRandRange(-1.0f, 1.0f),
        FMath::FRandRange(-0.25f, 0.25f)
    ).GetSafeNormal();

    TiempoCambioDireccion = FMath::FRandRange(0.5f, 1.5f);

    // Temporizador individual para desaparecer
    if (TiempoVida > 0.0f)
    {
        GetWorldTimerManager().SetTimer(
            TimerDesaparicion,
            this,
            &AEnemigos::Desaparecer,
            TiempoVida,
            false
        );
    }
}

void AEnemigos::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Cuenta el tiempo hasta el siguiente cambio de direccion
    TiempoCambioDireccion -= DeltaTime;

    FVector PosicionActual = GetActorLocation();

    FVector DireccionHaciaCentro =
        PosicionInicial - PosicionActual;

    // Si se aleja demasiado, vuelve hacia su zona inicial
    if (DireccionHaciaCentro.Size() > RadioMovimiento)
    {
        DireccionMovimiento =
            DireccionHaciaCentro.GetSafeNormal();

        TiempoCambioDireccion = 1.0f;
    }
    else if (TiempoCambioDireccion <= 0.0f)
    {
        // Elige una nueva direccion aleatoria
        DireccionMovimiento = FVector(
            FMath::FRandRange(-1.0f, 1.0f),
            FMath::FRandRange(-1.0f, 1.0f),
            FMath::FRandRange(-0.25f, 0.25f)
        ).GetSafeNormal();

        TiempoCambioDireccion =
            FMath::FRandRange(0.8f, 2.0f);
    }

    // Movimiento independiente de cada enemigo
    FVector Desplazamiento =
        DireccionMovimiento * Velocidad * DeltaTime;

    AddActorWorldOffset(Desplazamiento);
}

void AEnemigos::Desaparecer()
{
    Destroy();
}

void AEnemigos::ConfigurarEnemigo(
    int32 Numero,
    float NuevaVelocidad,
    float NuevoTiempoVida
)
{
    NumeroCuadrilla = Numero;
    Velocidad = NuevaVelocidad;
    TiempoVida = NuevoTiempoVida;
}
