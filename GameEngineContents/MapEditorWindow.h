#pragma once
#include <GameEngineCore/GameEngineGUI.h>
#include "MapEditGlobalValue.h"

enum class EditOption
{
	Scale,
	Rot,
	Pos,
};

class MapEditorWindow : public GameEngineGUIWindow
{
public:
	static MapEditorWindow* EditorGUI;
	// constrcuter destructer
	MapEditorWindow() ;
	~MapEditorWindow();

	// delete Function
	MapEditorWindow(const MapEditorWindow& _Other) = delete;
	MapEditorWindow(MapEditorWindow&& _Other) noexcept = delete;
	MapEditorWindow& operator=(const MapEditorWindow& _Other) = delete;
	MapEditorWindow& operator=(MapEditorWindow&& _Other) noexcept = delete;

	void ReleaseMapEditor();

protected:
	void Start() override;
	void OnGUI(std::shared_ptr<GameEngineLevel> Level, float _DeltaTime) override;

private:

	//editor Info
	std::map<int, std::shared_ptr<class GameEngineActor>> EditorActorInfo;
	std::map<int, SponeMapActor> EditorSturctInfo;

	int lastindex = 0;
	int CurIndex = -1;
	bool ReadCSV = false;
	std::string AccessIndex = "                              ";
	float UnitScale = 10.0f;
		// Transform
	EditOption CurOption = EditOption::Pos;
	std::string recvUnit = "1000.000000";//1000.000000
	std::string Ratio = "1.000000";
	float4 CurRot = float4::ZERO;
	float4 CurPos = float4::ZERO;


	std::string RevRotationX = "0000.000000";
	std::string RevRotationY = "0000.000000";
	std::string RevRotationZ = "0000.000000";
	
	std::string RevPositionX = "0000.000000";
	std::string RevPositionY = "0000.000000";
	std::string RevPositionZ = "0000.000000";

	//editor func
	void SettingCurActor(std::shared_ptr<class GameEngineLevel> Level);
	void EditCurActor(std::shared_ptr<class GameEngineLevel> Level);
	void EditTransform();
	void EditTransformMouseControl();
	void ResetValue();
	void CreateSetCurActor(int _ActorType, std::shared_ptr<class GameEngineLevel> Level);

	void ShowFBXINfo();

	// ReSource Info
	bool IsSetFilePath = false;
	GameEnginePath FilePath;
	std::string FileName = "                              ";

	// Resource Func
	void SetReadWriteFilePath(std::shared_ptr<class GameEngineLevel> Level);
	void Explorer(std::string& _Name, const std::string_view& _StartPath = "");

	// Actor Info
	std::shared_ptr<class GameEngineActor> CurActor = nullptr;
	std::string FBXName = "                              ";
	std::string MeterialName = "MeshTexture";

	// read & save func
	void ReadActor(std::shared_ptr<class GameEngineLevel> Level);
	void SaveActors();
	void ClearCurFile();





};