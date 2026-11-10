
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Enemigos.h"
#include "TimerManager.h"
#include "CuadrillasGameMode.generated.h"

UCLASS()
class LABORATORIO_2_API ACuadrillasGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ACuadrillasGameMode();

protected:
    virtual void BeginPlay() override;

    void GenerarCuadrilla(int32 NumeroCuadrilla);
    void ComprobarCuadrilla();

    FTimerHandle TimerComprobacion;

    TArray<TWeakObjectPtr<AEnemigos>> EnemigosPrimeraCuadrilla;

    bool bSegundaGenerada;
};
