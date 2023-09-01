#include "PrecompileHeader.h"
#include "PhysXMgr.h"

PhysXMgr::PhysXMgr() 
{
}

PhysXMgr::~PhysXMgr() 
{
}


bool PhysXMgr::advance(physx::PxReal _DeltaTime)
{
	m_fWaitTime += _DeltaTime;
	m_fStepSize = 1.0f / 240.0f;

	if (m_fWaitTime < m_fStepSize)
	{
		return false;
	}

	m_fWaitTime -= m_fStepSize;

	m_pScene->simulate(m_fStepSize);

	return true;
}

// 실제로 물리연산을 실행
void PhysXMgr::Simulate(float _DeltaTime)
{
	if (nullptr == m_pPhysics)
	{
		return;
	}

	if (true == advance(_DeltaTime))
	{
		float4 CamPos = GameEngineCore::GetCurLevel()->GetMainCamera()->GetTransform()->GetLocalPosition();
		float4 TargetPos = CamPos + float4(0, 0, 100);
		m_pPvdClient->updateCamera("Test", CamPos.PhysXVec3Return(), { 0,1,0 }, TargetPos.PhysXVec3Return());
		m_pScene->simulate(_DeltaTime);
		m_pScene->fetchResults(true);
	}
}


// 초기화
void PhysXMgr::Initialize()
{
	m_pFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, m_Allocator, m_ErrorCallback);

	if (!m_pFoundation)
	{
		MsgAssert("PxFoundation failed!");
	}

	m_pPvd = PxCreatePvd(*m_pFoundation);

	if (!m_pPvd)
	{
		MsgAssert("PxPvd failed!");
	}

	physx::PxPvdTransport* pTransport = physx::PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);

	if (!pTransport)
	{
		MsgAssert("Transport failed!");
	}

	bool bConnect = m_pPvd->connect(*pTransport, physx::PxPvdInstrumentationFlag::eALL);

	m_pPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_pFoundation, physx::PxTolerancesScale(), true, m_pPvd);

	if (!m_pPhysics)
	{
		MsgAssert("PxPhysics failed!");
	}

	physx::PxSceneDesc SceneDesc(m_pPhysics->getTolerancesScale());
	SceneDesc.gravity = physx::PxVec3(0.f, -SCENE_GRAVITY, 0.0f);
	m_pDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
	SceneDesc.cpuDispatcher = m_pDispatcher;
	m_pSimulationEventCallback = new CustomSimulationEventCallback();
	SceneDesc.simulationEventCallback = m_pSimulationEventCallback;
	SceneDesc.filterShader = CustomFilterShader;
	m_pScene = m_pPhysics->createScene(SceneDesc);

	if (!m_pScene)
	{
		MsgAssert("PxScene failed!");
	}

	
	m_pPvdClient = m_pScene->getScenePvdClient();
	if (m_pPvdClient)
	{
		m_pPvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		m_pPvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		m_pPvdClient->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}

	m_pCooking = PxCreateCooking(PX_PHYSICS_VERSION, *m_pFoundation, physx::PxCookingParams(m_pPhysics->getTolerancesScale()));
	if (!m_pCooking)
	{
		MsgAssert("PxCreateCooking failed!");
	}
}

void PhysXMgr::CreateScene()
{
}



// 메모리 해제
void PhysXMgr::Release()
{
	if (nullptr != m_pSimulationEventCallback)
	{
		delete m_pSimulationEventCallback;
		m_pSimulationEventCallback = nullptr;
	}
	PX_RELEASE(m_pScene);
	PX_RELEASE(m_pDispatcher);
	PX_RELEASE(m_pPhysics);
	PX_RELEASE(m_pCooking);
	if (m_pPvd)
	{
		physx::PxPvdTransport* pTransport = m_pPvd->getTransport();
		m_pPvd->release();
		m_pPvd = nullptr;
		PX_RELEASE(pTransport);
	}
	PX_RELEASE(m_pFoundation);
}
