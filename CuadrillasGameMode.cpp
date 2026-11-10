
#include "CuadrillasGameMode.h"

#include "EAHelicoptero.h"
#include "EAAvion.h"
#include "EADron.h"

#include "ETSoldado.h"
#include "ETTanque.h"
#include "ETCamion.h"
#include "ETBlindado.h"

#include "EABarco.h"
#include "EALancha.h"
#include "EAMotoAcuatica.h"

#include "Engine/World.h"

ACuadrillasGameMode::ACuadrillasGameMode()
{
    bSegundaGenerada = false;
}

void ACuadrillasGameMode::BeginPlay()
{
    Super::BeginPlay();

    // Genera la primera cuadrilla al iniciar el juego
    GenerarCuadrilla(1);

    // Comprueba cada medio segundo si ya desaparecieron sus miembros
    GetWorldTimerManager().SetTimer(
        TimerComprobacion,
        this,
        &ACuadrillasGameMode::ComprobarCuadrilla,
        0.5f,
        true
    );
}

void ACuadrillasGameMode::GenerarCuadrilla(int32 NumeroCuadrilla)
{
    TArray<TSubclassOf<AEnemigos>> Clases;

    Clases.Add(AEAHelicoptero::StaticClass());
    Clases.Add(AEAAvion::StaticClass());
    Clases.Add(AEADron::StaticClass());

    Clases.Add(AETSoldado::StaticClass());
    Clases.Add(AETTanque::StaticClass());
    Clases.Add(AETCamion::StaticClass());
    Clases.Add(AETBlindado::StaticClass());

    Clases.Add(AEABarco::StaticClass());
    Clases.Add(AEALancha::StaticClass());
    Clases.Add(AEAMotoAcuatica::StaticClass());

    for (int32 i = 0; i < Clases.Num(); i++)
    {
        float PosicionY = (i - 4.5f) * 180.0f;

        FVector Posicion(
            0.0f,
            PosicionY,
            200.0f
        );

        FTransform Transform(FRotator::ZeroRotator, Posicion);

        AEnemigos* Enemigo = GetWorld()->SpawnActorDeferred<AEnemigos>(
            Clases[i],
            Transform,
            this,
            nullptr,
            ESpawnActorCollisionHandlingMethod::AlwaysSpawn
            );

        if (Enemigo)
        {
            float NuevaVelocidad = 120.0f + i * 20.0f;
            float NuevoTiempoVida = 6.0f + i * 0.5f;

            Enemigo->ConfigurarEnemigo(
                NumeroCuadrilla,
                NuevaVelocidad,
                NuevoTiempoVida
            );

            Enemigo->FinishSpawning(Transform);

            if (NumeroCuadrilla == 1)
            {
                EnemigosPrimeraCuadrilla.Add(Enemigo);
            }
        }
    }
}

void ACuadrillasGameMode::ComprobarCuadrilla()
{
    if (bSegundaGenerada)
    {
        return;
    }

    bool QuedanEnemigos = false;

    for (const TWeakObjectPtr<AEnemigos>& Enemigo
        : EnemigosPrimeraCuadrilla)
    {
        if (Enemigo.IsValid())
        {
            QuedanEnemigos = true;
            break;
        }
    }

    if (!QuedanEnemigos)
    {
        bSegundaGenerada = true;

        GetWorldTimerManager().ClearTimer(TimerComprobacion);

        // La segunda cuadrilla aparece solo cuando la primera termina
        GenerarCuadrilla(2);
    }
}
