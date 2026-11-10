

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Enemigos.generated.h"

UCLASS()
class LABORATORIO_2_API AEnemigos : public AActor
{
    GENERATED_BODY()

public:
    AEnemigos();

    // Identifica a que cuadrilla pertenece el enemigo
    void ConfigurarEnemigo(
        int32 Numero,
        float NuevaVelocidad,
        float NuevoTiempoVida
    );

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemigo")
        UStaticMeshComponent* MallaEnemigo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movimiento")
        float Velocidad;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tiempo")
        float TiempoVida;

    // NUEVAS VARIABLES PARA EL MOVIMIENTO ALEATORIO
    FVector DireccionMovimiento;
    FVector PosicionInicial;

    float TiempoCambioDireccion;
    float IntervaloCambioDireccion;
    float RadioMovimiento;

    // Variables que ya tenías
    int32 NumeroCuadrilla;

    FTimerHandle TimerDesaparicion;

    void Desaparecer();

public:
    virtual void Tick(float DeltaTime) override;
};
