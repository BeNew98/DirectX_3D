#pragma once
#include "TriggerBase.h"

enum class StartState
{
	OPEN,
	CLOSE,
};

// ���� :
class ShortCutDoor : public TriggerBase
{
public:
	// constrcuter destructer
	ShortCutDoor();
	~ShortCutDoor();

	// delete Function
	ShortCutDoor(const ShortCutDoor& _Other) = delete;
	ShortCutDoor(ShortCutDoor&& _Other) noexcept = delete;
	ShortCutDoor& operator=(const ShortCutDoor& _Other) = delete;
	ShortCutDoor& operator=(ShortCutDoor&& _Other) noexcept = delete;

	void SetState(StartState _State)
	{
		m_eStartState = _State;
		switch (m_eStartState)
		{
		case StartState::OPEN:
		{
			m_pRenderer->ChangeAnimation("OPEN_STILL");
		}
			break;
		case StartState::CLOSE:

		{
			m_pRenderer->ChangeAnimation("ROCKED");
		}
			break;
		default:
			break;
		}
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void InitComponent() override;
	void InitAnimation();

private:
	void SetFSMFUNC();

	std::shared_ptr<class ContentFBXRenderer> m_pRenderer1 = nullptr;
	StartState m_eStartState = StartState::CLOSE;
};