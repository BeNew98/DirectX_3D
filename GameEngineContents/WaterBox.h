#pragma once
#include <GameEngineCore/GameEngineRenderer.h>

class WaterBox : public GameEngineRenderer
{

public:

	WaterBox();
	~WaterBox();

	WaterBox(const WaterBox& _Other) = delete;
	WaterBox(WaterBox&& _Other) noexcept = delete;
	WaterBox& operator=(const WaterBox& _Other) = delete;
	WaterBox& operator=(WaterBox&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineRenderUnit> Unit;

	float4 BlurColor = float4::ZERO;
	float4 ClipData = {0, 0, 1, 1};
};

