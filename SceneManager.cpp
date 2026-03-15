#include "SceneManager.h"
#include "SceneFactory.h"
#include <DxLib.h>



namespace
{
	int* m_currentName; // 現在のシーンの名称
	int* m_nextName;    // 次のシーンの名称
	SceneBase* m_currentScene; // 今のシーンのインスタンスを保持
	SceneFactory* m_factory;   // シーン切り替え用のFactoryのポインター
	bool m_exitRequest;
};

void SceneManager::Initialize()
{
	m_currentName = new int;
	m_nextName = new int;
	*m_nextName = -1;
	*m_currentName = -1;

	m_factory = new SceneFactory();
	// 最初に動くシーンを、SceneFactoryに作ってもらう
	m_currentScene = m_factory->Create(SCENE_NAME::TITLE_SCENE);
	m_exitRequest = false;
}

void SceneManager::Update()
{
	if (*m_nextName != *m_currentName)
	{ // シーン切り替えの指定があったので
		if (m_currentScene != nullptr)
		{ // 今までのシーンを解放
			delete m_currentScene;
			m_currentScene = nullptr;
			ObjectManager::DeleteAllGameObject();
		}
		m_currentScene = m_factory->Create((SCENE_NAME)*m_nextName); // 次のシーンを作成
		*m_currentName = *m_nextName;
	}
	if (m_currentScene != nullptr)
	{
		m_currentScene->Update();
	}
}

void SceneManager::Draw()
{
	if (m_currentScene != nullptr)
	{
		m_currentScene->Draw();
	}
}

void SceneManager::Release()
{
	if (m_currentScene != nullptr)
	{
		delete m_currentScene;
		m_currentScene = nullptr;
	}
	if (m_factory != nullptr)
	{
		delete m_factory;
		m_factory = nullptr;
	}
	delete m_currentName;
	delete m_nextName;
}

void SceneManager::ChangeScene(const SCENE_NAME& sceneName)
{
	*m_nextName = sceneName;
}

SceneBase* SceneManager::CurrentScene()
{
	return m_currentScene;
}

void SceneManager::Exit()
{
	m_exitRequest = true;
}

bool SceneManager::IsExit()
{
	return m_exitRequest;
}
