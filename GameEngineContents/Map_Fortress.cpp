#include "PrecompileHeader.h"
#include "Map_Fortress.h"

#include "FortressLevel.h"

#include "ContentFBXRenderer.h"

// physX
#include "PhysXTriangleComponent.h"
#include "PhysXBoxComponent.h"
#include "PhysXCapsuleComponent.h"

#include "SecretTile.h"
#include "Crate.h"
#include "Ladder.h"


Map_Fortress::Map_Fortress()
{
}

Map_Fortress::~Map_Fortress()
{
}

void Map_Fortress::NaviRenderSwitch()
{
	if (nullptr != m_pNaviRenderer)
	{
		if (true == m_pNaviRenderer->IsUpdate())
		{
			m_pNaviRenderer->Off();
		}
		else
		{
			m_pNaviRenderer->On();
		}
	}
}

void Map_Fortress::Start()
{
	// 컴포넌트 초기화 
	InitComponent();
	Create_StaticObject();
	Create_ActiveObject();
}

void Map_Fortress::Update(float _DeltaTime)
{
	
}

void Map_Fortress::InitComponent()
{
	// 바닥 
	Create_Ground();

	// 파티션 분할 
	Create_Partition();

	// 네비메쉬  
	Create_PhysXComponent();
}

void Map_Fortress::Create_Ground()
{
	// 맵 렌더러 
	m_pRenderer_Section1 = CreateComponent<ContentFBXRenderer>();
	m_pRenderer_Section1->SetFBXMesh("Fortress_Section_1.fbx", "ContentMeshDeffered");
	m_pRenderer_Section1->GetTransform()->SetLocalRotation(m_MapRot);
	m_pRenderer_Section1->GetTransform()->SetLocalPosition(float4{ -4770, 19317, 4610 });
	m_pRenderer_Section1->CalculateUnitPos();

	m_pRenderer_Cube = CreateComponent<ContentFBXRenderer>();
	m_pRenderer_Cube->SetFBXMesh("Fortress_Cube.fbx", "ContentMeshDeffered");
	m_pRenderer_Cube->GetTransform()->SetLocalRotation(m_MapRot);
	m_pRenderer_Cube->GetTransform()->SetLocalPosition(float4{ -3910, -800, -300 });
	m_pRenderer_Cube->CalculateUnitPos();

	m_pRenderer_Cube2 = CreateComponent<ContentFBXRenderer>();
	m_pRenderer_Cube2->SetFBXMesh("Fortress_Cube_2.fbx", "ContentMeshDeffered");
	m_pRenderer_Cube2->GetTransform()->SetLocalRotation(m_MapRot);
	m_pRenderer_Cube2->GetTransform()->SetLocalPosition(float4{ -11735, -120, 18625 });
	m_pRenderer_Cube2->CalculateUnitPos();

	m_pRenderer_Section2 = CreateComponent<ContentFBXRenderer>();
	m_pRenderer_Section2->SetFBXMesh("Fortress_Section_2.fbx", "ContentMeshDeffered");
	m_pRenderer_Section2->GetTransform()->SetLocalRotation(m_MapRot);
	m_pRenderer_Section2->GetTransform()->SetLocalPosition(float4{ -5894, -8, 3716 });
	m_pRenderer_Section2->CalculateUnitPos();

	m_pRenderer_Section3 = CreateComponent<ContentFBXRenderer>();
	m_pRenderer_Section3->SetFBXMesh("Fortress_Section_3.fbx", "ContentMeshDeffered");
	m_pRenderer_Section3->GetTransform()->SetLocalRotation(m_MapRot);
	m_pRenderer_Section3->GetTransform()->SetLocalPosition(float4{ -1900, -604, 3160 });
	m_pRenderer_Section3->CalculateUnitPos();

	//auto AllUnit = m_pRenderer_Part3->GetAllRenderUnit();
	//auto UnTextureUnit = m_pRenderer_Part3->GetUnTexturedUnit();
	//
	//AllUnit[47][0]->ShaderResHelper.SetTexture("DiffuseTexture", "Ground_AncientBlueStone_ForestDungeon_Var02_DIFF_brightness.png");
	//AllUnit[48][0]->ShaderResHelper.SetTexture("DiffuseTexture", "Ground_AncientBlueStone_ForestDungeon_Var02_DIFF_brightness.png");
	//AllUnit[49][0]->ShaderResHelper.SetTexture("DiffuseTexture", "Ground_AncientBlueStone_ForestDungeon_Var02_DIFF_brightness.png");

}

void Map_Fortress::Create_Partition()
{
	m_pRenderer_Part1 = CreateComponent<ContentFBXRenderer>();
	m_pRenderer_Part1->SetFBXMesh("Fortress_Part_1.fbx", "ContentMeshDeffered");
	m_pRenderer_Part1->GetTransform()->SetLocalRotation(m_MapRot);
	m_pRenderer_Part1->GetTransform()->SetLocalPosition(float4{ -330, 300, 430 });
	m_pRenderer_Part1->CalculateUnitPos();

	m_pRenderer_Part2 = CreateComponent<ContentFBXRenderer>();
	m_pRenderer_Part2->SetFBXMesh("Fortress_Part_2.fbx", "ContentMeshDeffered");
	m_pRenderer_Part2->GetTransform()->SetLocalRotation(m_MapRot);
	m_pRenderer_Part2->GetTransform()->SetLocalPosition(float4{ -9190, 328, 11669 });
	m_pRenderer_Part2->CalculateUnitPos();

	m_pRenderer_Part3 = CreateComponent<ContentFBXRenderer>();
	m_pRenderer_Part3->SetFBXMesh("Fortress_Part_3.fbx", "ContentMeshDeffered");
	m_pRenderer_Part3->GetTransform()->SetLocalRotation(m_MapRot);
	m_pRenderer_Part3->GetTransform()->SetLocalPosition(float4{ -8566, 336, 13834});
	m_pRenderer_Part3->CalculateUnitPos();

	m_pRenderer_Part4 = CreateComponent<ContentFBXRenderer>();
	m_pRenderer_Part4->SetFBXMesh("Fortress_Part_4.fbx", "ContentMeshDeffered");
	m_pRenderer_Part4->GetTransform()->SetLocalRotation(m_MapRot);
	m_pRenderer_Part4->GetTransform()->SetLocalPosition(float4{ -12870, -16, 10350});
	m_pRenderer_Part4->CalculateUnitPos();

	m_pRenderer_Part5 = CreateComponent<ContentFBXRenderer>();
	m_pRenderer_Part5->SetFBXMesh("Fortress_Part_5.fbx", "ContentMeshDeffered");
	m_pRenderer_Part5->GetTransform()->SetLocalRotation(m_MapRot);
	m_pRenderer_Part5->GetTransform()->SetLocalPosition(float4{ -9160, 324, 14630 });
	m_pRenderer_Part5->CalculateUnitPos();

	m_pRenderer_Part6 = CreateComponent<ContentFBXRenderer>();
	m_pRenderer_Part6->SetFBXMesh("Fortress_Part_6.fbx", "ContentMeshDeffered");
	m_pRenderer_Part6->GetTransform()->SetLocalRotation(m_MapRot);
	m_pRenderer_Part6->GetTransform()->SetLocalPosition(float4{ -13380, 93, 10940 });
	m_pRenderer_Part6->CalculateUnitPos();

	m_pRenderer_Part7 = CreateComponent<ContentFBXRenderer>();
	m_pRenderer_Part7->SetFBXMesh("Fortress_Part_7.fbx", "ContentMeshDeffered");
	m_pRenderer_Part7->GetTransform()->SetLocalRotation(m_MapRot);
	m_pRenderer_Part7->GetTransform()->SetLocalPosition(float4{ -14480, -3, 11935 });
	m_pRenderer_Part7->CalculateUnitPos();

	m_pRenderer_Part8 = CreateComponent<ContentFBXRenderer>();
	m_pRenderer_Part8->SetFBXMesh("Fortress_Part_8.fbx", "ContentMeshDeffered");
	m_pRenderer_Part8->GetTransform()->SetLocalRotation(m_MapRot);
	m_pRenderer_Part8->GetTransform()->SetLocalPosition(float4{ -10560, 200, 15170 });
	m_pRenderer_Part8->CalculateUnitPos();

	m_pRenderer_Part9 = CreateComponent<ContentFBXRenderer>();
	m_pRenderer_Part9->SetFBXMesh("Fortress_Part_9.fbx", "ContentMeshDeffered");
	m_pRenderer_Part9->GetTransform()->SetLocalRotation(m_MapRot);
	m_pRenderer_Part9->GetTransform()->SetLocalPosition(float4{ -9600, 155, 17837 });
	m_pRenderer_Part9->CalculateUnitPos();

	m_pRenderer_Part10 = CreateComponent<ContentFBXRenderer>();
	m_pRenderer_Part10->SetFBXMesh("Fortress_Part_10.fbx", "ContentMeshDeffered");
	m_pRenderer_Part10->GetTransform()->SetLocalRotation(m_MapRot);
	m_pRenderer_Part10->GetTransform()->SetLocalPosition(float4{ -14460, -80, 13570 });
	m_pRenderer_Part10->CalculateUnitPos();

	m_pRenderer_Part11 = CreateComponent<ContentFBXRenderer>();
	m_pRenderer_Part11->SetFBXMesh("Fortress_Part_11.fbx", "ContentMeshDeffered");
	m_pRenderer_Part11->GetTransform()->SetLocalRotation(m_MapRot);
	m_pRenderer_Part11->GetTransform()->SetLocalPosition(float4{ -16020, 113, 13870 });
	m_pRenderer_Part11->CalculateUnitPos();

	m_pRenderer_Part12 = CreateComponent<ContentFBXRenderer>();
	m_pRenderer_Part12->SetFBXMesh("Fortress_Part_12.fbx", "ContentMeshDeffered");
	m_pRenderer_Part12->GetTransform()->SetLocalRotation(m_MapRot);
	m_pRenderer_Part12->GetTransform()->SetLocalPosition(float4{ -9970, 284, 11910 });
	m_pRenderer_Part12->CalculateUnitPos();

	m_pRenderer_Part13 = CreateComponent<ContentFBXRenderer>();
	m_pRenderer_Part13->SetFBXMesh("Fortress_Part_13.fbx", "ContentMeshDeffered");
	m_pRenderer_Part13->GetTransform()->SetLocalRotation(m_MapRot);
	m_pRenderer_Part13->GetTransform()->SetLocalPosition(float4{ -10980, 400, 18075 });
	m_pRenderer_Part13->CalculateUnitPos();

	m_pRenderer_Part14 = CreateComponent<ContentFBXRenderer>();
	m_pRenderer_Part14->SetFBXMesh("Fortress_Part_14.fbx", "ContentMeshDeffered");
	m_pRenderer_Part14->GetTransform()->SetLocalRotation(m_MapRot);
	m_pRenderer_Part14->GetTransform()->SetLocalPosition(float4{ -9156, -50, 16337 });
	m_pRenderer_Part14->CalculateUnitPos();

	m_pRenderer_Part15 = CreateComponent<ContentFBXRenderer>();
	m_pRenderer_Part15->SetFBXMesh("Fortress_Part_15.fbx", "ContentMeshDeffered");
	m_pRenderer_Part15->GetTransform()->SetLocalRotation(m_MapRot);
	m_pRenderer_Part15->GetTransform()->SetLocalPosition(float4{ -14090, 250, 19250 });
	m_pRenderer_Part15->CalculateUnitPos();

	m_pRenderer_Part16 = CreateComponent<ContentFBXRenderer>();
	m_pRenderer_Part16->SetFBXMesh("Fortress_Part_16.fbx", "ContentMeshDeffered");
	m_pRenderer_Part16->GetTransform()->SetLocalRotation(m_MapRot);
	m_pRenderer_Part16->GetTransform()->SetLocalPosition(float4{ -14782, 285, 17658 });
	m_pRenderer_Part16->CalculateUnitPos();

}

void Map_Fortress::Create_PhysXComponent()
{
	// 네비메쉬 위치확인용 렌더러 
	m_pNaviRenderer = CreateComponent<ContentFBXRenderer>();
	m_pNaviRenderer->SetFBXMesh("Fortress_FullMap_NavMesh.fbx", "ContentMeshDeffered");
	m_pNaviRenderer->GetTransform()->SetLocalRotation(m_MapRot);
	m_pNaviRenderer->GetTransform()->SetLocalPosition(m_MapPos);
	// m_pNaviRenderer->Off();

	m_pTriangleComp = CreateComponent<PhysXTriangleComponent>();
	m_pTriangleComp->SetPhysxMaterial(0.f, 0.f, 0.f);
	m_pTriangleComp->CreatePhysXActors("Fortress_FullMap_NavMesh.fbx", true);
	m_pTriangleComp->GetStatic()->setGlobalPose(float4::PhysXTransformReturn(m_MapRot, m_MapPos));
}

void Map_Fortress::Create_StaticObject()
{
	GameEngineLevel* CurLevel = GetLevel();
	if (nullptr == CurLevel)
	{
		MsgAssert("현재 레벨이 nullptr 입니다.");
		return;
	}
}

void Map_Fortress::Create_ActiveObject()
{
	
	
}

void Map_Fortress::Create_TransformWall(std::shared_ptr<class GameEngineLevel> _CurLevel)
{
}
