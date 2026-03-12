#pragma once
enum SceneName
{
	TITLE_SCENE,
	PLAY_SCENE
};
class Scene
{
public:
	Scene();
	~Scene();
	virtual void Update() {}
	virtual void Draw() {}
	SceneName sceneName;
};