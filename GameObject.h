#pragma once
/// <summary>
/// ゲームオブジェクトの基底クラス
/// </summary>
/// <author>H.suginuma</author>

#include<string>
#include"ObjectManager.h"
#include"globals.h"
#include"Math2D.h"
#include"Input.h"

/// <summary>
/// これを継承したクラスのインスタンスは、ObjectManagerで管理され、
/// Update()とDraw()が自動で呼ばれます
/// </summary>
class GameObject
{
public:
	GameObject() 
		: destroy(false), 
		dontDestroy(false), 
		drawOrder(0) 
	{
		ObjectManager::Push(this); 
	}
	virtual ~GameObject() 
	{
		ObjectManager::Pop(this); 
	}

	/// <summary>
	/// 毎フレームの更新処理のために呼ばれます
	/// </summary>
	virtual void Update() {}

	/// <summary>
	/// 毎フレームの描画処理のために呼ばれます
	/// </summary>
	virtual void Draw() {}

	/// <summary>
	/// 自分のインスタンスを削除する時に呼び出してください
	/// 次回のUpdateの前に削除されます
	/// </summary>
	void DestroyMe() { destroy = true; }

	/// <summary>
	/// DestroyMeされているか調べる
	/// この関数はObjectManagerが使っています。
	/// </summary>
	/// <returns>DestroyMeされているとtrue</returns>
	inline bool DestroyRequested() const { return destroy; }

	/// <summary>
	/// シーンチェンジするときに、削除されなくする
	/// </summary>
	/// <param name="sw">書かなければtrue、falseにすると削除される</param>
	void DontDestroyOnSceneChange(bool sw = true) { dontDestroy = sw; }

	/// <summary>
	/// DontDestroyが設定されているか調べる
	/// この関数はObjectManagerが使っています
	/// </summary>
	/// <returns>DontDetroyになっていればtrue</returns>
	bool IsDontDestroy() const { return dontDestroy; }

	/// <summary>
	/// 描画の優先順位を指定します
	/// 数値が高いほど、先に描画されるので、
	/// 2Dであれば、奥に表示されます
	/// 何も指定しなければ０です
	/// </summary>
	/// <param name="odr">描画順位</param>
	void SetDrawOrder(int order)
	{
		drawOrder = order;
		ObjectManager::SortByDrawOrder();
	}

	/// <summary>
	/// 描画の優先順位を取得します
	/// </summary>
	/// <returns>描画優先順位</returns>
	inline int GetDrawOrder() const { return drawOrder; }

private:
	bool destroy;
	bool dontDestroy;
	int drawOrder;
	//画像保存用関数（未定）
	int hImage = -1;
};