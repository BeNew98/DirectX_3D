#include "PrecompileHeader.h"
#include "OfficeLevel.h"

#include "Map_Office.h"
#include "Player.h"
#include "PhysXCapsuleComponent.h"
#include "PhysXTestActor.h"


OfficeLevel::OfficeLevel()
{
}

OfficeLevel::~OfficeLevel()
{
}

void OfficeLevel::Start()
{
	SetLevelType(PacketLevelType::OfficeLevel);
	InitKey();
}

void OfficeLevel::Update(float _DeltaTime)
{
	KeyUpdate(_DeltaTime);

	// test 
	if (false == GetMainCamera()->IsFreeCamera())
	{
		GetMainCamera()->GetTransform()->SetWorldPosition(m_pTestActor->GetTransform()->GetWorldPosition() + float4 { 0, 1200, -1200 });
	}


}

void OfficeLevel::LevelChangeStart()
{
	CreateScene();

	// camera pos test 
	/*float4 CameraPos = float4{ 1700, 3800, 4000 };
	float4 CamRot = float4{ 90, 0, 0 };*/


	GetMainCamera()->SetProjectionType(CameraType::Perspective);
	GetMainCamera()->GetTransform()->SetLocalRotation(m_CameraRot);
	GetMainCamera()->GetTransform()->SetLocalPosition(m_CameraPos);


	CreateActor<GameEngineLight>();
	m_pMap = CreateActor<Map_Office>();

	m_pTestActor = CreateActor<PhysXTestActor>();
	m_pTestActor->GetCapsule()->SetPlayerStartPos(m_StartPos);
	// 플레이어 생성후 Set_StartPos함수 호출하면 해당 위치에 세팅
	//std::shared_ptr<Player> Obj = CreateActor<Player>();
	//Set_StartPos(Obj);
}

void OfficeLevel::LevelChangeEnd()
{
	AllActorDestroy();
}

void OfficeLevel::InitKey()
{
	if (false == GameEngineInput::IsKey("NaviMesh_Switch"))
	{
		GameEngineInput::CreateKey("NaviMesh_Swtich", 'M');
	}
}

void OfficeLevel::KeyUpdate(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("NaviMesh_Swtich"))
	{
		if (nullptr != m_pMap)
		{
			m_pMap->NaviRenderSwitch();
		}
	}
}

void OfficeLevel::Set_StartPos(std::shared_ptr<Player> _Player)
{
	if (nullptr == _Player)
	{
		MsgAssert("Player 가 nullptr 입니다.");
		return;
	}

	std::shared_ptr<PhysXCapsuleComponent> Comp = _Player->GetPhysXComponent();

	if (nullptr == Comp)
	{
		MsgAssert("Player 의 PhysXComponent가 nullptr 입니다.");
		return;
	}
	
	Comp->GetDynamic()->setGlobalPose(float4::PhysXTransformReturn(float4::ZERO, m_StartPos));
}
