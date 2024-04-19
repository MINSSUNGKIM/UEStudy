/*
생성자와 beginplay()의 차이에 대한 이해.
생성자(Constructor)
생성자는 오브젝트가 메모리에 처음 생성될 때 호출됩니다. 이는 게임 실행 전, 에디터 내에서 오브젝트를 배치할 때도 호출됩니다.
생성자는 기본 값 설정, 변수 초기화 등을 수행합니다. 상호 작용은 제한적입니다.
BeginPlay()
BeginPlay() 함수는 게임 플레이가 시작되고 나서, 오브젝트가 게임 월드에 활성화되고 난 직후에 호출됩니다.
이 함수는 오브젝트가 실제 게임 환경에서 사용될 준비가 완료되었을 때 실행되며, 런타임에서 초기화 작업을 수행합니다. 
예를 들어, 레벨에서 다른 오브젝트들과의 동적 상호작용 설정이나, 게임 시작 시 필요한 리소스 로딩 등을 여기서 처리합니다.
순서적 관점:

생성자가 먼저 호출되어 객체의 기본적인 설정을 구성합니다.
게임이 시작되면, 모든 설정된 오브젝트에 대해 BeginPlay()가 호출되어 추가적인 초기화 및 게임 특정 로직이 실행됩니다.
이러한 차이점은 게임의 로직과 오브젝트의 생명주기 관리에 있어서 중요하며,
특히 멀티플레이어 게임과 같이 동적인 요소가 많은 환경에서는 더욱 신중하게 고려해야 합니다. 
생성자와 BeginPlay() 각각에서 어떤 종류의 작업을 수행해야 하는지를 명확히 구분하는 것이 중요합니다.
*/
#include "GameFramework/Actor.h"
#include "CoreMinimal.h"

// MyGameObject 클래스 정의
class AMyGameObject : public AActor
{
    GENERATED_BODY()

public:
    // 생성자
    AMyGameObject()
    {
        // 기본 속성 초기화
        PrimaryActorTick.bCanEverTick = true;

        // 컴포넌트 생성 및 설정
        MyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
        RootComponent = MyMeshComponent;

        // 기본 메시 설정 (에디터 내에서 메시를 지정할 수 있도록)
        static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/Path/To/Mesh"));
        if (Mesh.Succeeded())
        {
            MyMeshComponent->SetStaticMesh(Mesh.Object);
        }
    }

    // BeginPlay 함수 오버라이드
    virtual void BeginPlay() override
    {
        Super::BeginPlay();

        // 게임 시작 시 로직
        DebugLogStart();
    }

protected:
    // 컴포넌트 포인터
    UStaticMeshComponent* MyMeshComponent;

private:
    // 디버그 로그 출력 함수
    void DebugLogStart()
    {
        UE_LOG(LogTemp, Warning, TEXT("MyGameObject is now active!"));
    }
};



/*
충돌 타입에 대하여,
Q: Pawn Type 의 캐릭터와의 충돌은 무시하면서, pawn type의 enemey 와의 충돌은 발생하게 하는 setting 은 어떻게 해야 하는가?
A: Collison channel 을 새로 만들어서 적용한다. 
    방법 - 새로운 collision 타입 추가
만약 게임에 특정한 적의 타입을 추가하고 싶다면, Unreal Engine에서는 새로운 오브젝트 타입을 프로젝트 설정을 통해 추가할 수 있습니다.

프로젝트 설정 열기:
에디터 상단의 메뉴에서 Edit > Project Settings를 선택합니다.
Collision 설정 접근:
왼쪽 메뉴에서 Engine 섹션 하위의 Collision을 선택합니다.
Object Channels 추가:
Collision 섹션에서 Object Channels를 찾습니다.
New Object Channel... 버튼을 클릭합니다.
팝업 창에서 새 오브젝트 타입의 이름(예: Enemy)과 기본 반응(예: Block, Ignore)을 설정합니다.
저장 및 적용:
설정을 저장하고 블루프린트로 돌아가 새로 생성한 오브젝트 타입을 해당 적 캐릭터의 콜리전 컴포넌트에 설정합니다.
    */
