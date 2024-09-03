#pragma once

#ifndef _PSCENE_H
#define _PSCENE_H

#include"GUIManager.h"

///A class to progress game frame update while combining gui system. 
///For usage, implement _OnMessage(), _OnDraw(),...,_OnExit()
class PScene {
public:
	///see SetDrawPolicy()
	enum DrawPolicy {
		ContentAbove,
		GUIAbove
	};

protected:
	bool _isActivated;
	DrawPolicy _drawPolicy;

protected:
	using callback_t = std::function<void()>;
	//custom callback function for user
	callback_t _callback;

protected:
	//called when OnXXX() is called, should be implemented by user

	virtual void _OnMessage(ExMessage& Message) {}
	virtual void _OnDraw(PDevice* Device) {}
	virtual void _OnUpdate(float deltaTime) {}
	virtual void _OnEnter() {}
	virtual void _OnExit() {}

public:
	PGUIManager* ui;

public:
	PScene()
		:ui(new PGUIManager()), _isActivated(false), _drawPolicy(DrawPolicy::GUIAbove), _callback(nullptr) {
	}

	virtual ~PScene() { if (ui) delete ui; }

	//PGUIManager methods

	void AddObject(PGUIObject* Object) {
		ui->AddObject(Object);
	}
	void RemoveObject(PGUIObject* Object) {
		ui->RemoveObject(Object);
	}

	void RaiseAsFocus(PGUIObject* Object) {
		ui->RaiseAsFocus(Object);
	}
	void UnfocusObject(PGUIObject* Object) {
		ui->UnfocusObject(Object);
	}
	PGUIObject* GetFocusingObject() {
		return ui->GetFocusingObject();
	}

public:
	//use these functions in your Loop() part

	void OnMessage(ExMessage& Message) {
		_OnMessage(Message);
		ui->OnMessage(Message);
	}

	void OnDraw(PDevice* Device) {
		if (_drawPolicy == DrawPolicy::ContentAbove) {
			ui->OnDraw(Device);
			_OnDraw(Device);
		}
		else {
			_OnDraw(Device);
			ui->OnDraw(Device);
		}
	}

	void OnUpdate(float deltaTime) {
		_OnUpdate(deltaTime);
	}

	//use these when switching scenes

	void OnEnter() {
		_OnEnter();
	}
	void OnExit() {
		_OnExit();
	}

public:
	//check if the scene should be running (just a user symbol, not yet used)
	bool IsActivated()const { return _isActivated; }
	//set Activate state
	void SetActivate(bool Activate) { _isActivated = Activate; }

	/// <summary>
	/// Set the draw Policy. The default is GUIAbove.
	/// </summary>
	/// <param name=" ">
	/// <para>ContentAbove:</para><para>gui objects are drawn below</para>
	/// <para>GUIAbove:</para><para>gui objects are drawn above</para>
	/// </param>
	void SetDrawPolicy(DrawPolicy Policy) {
		_drawPolicy = Policy;
	}

public:
	//Set a callback function for user (like switching scenes)
	void SetCustomCallback(const callback_t& Callback) {
		_callback = Callback;
	}

	
	// Z：给Scene添加了可以获取窗口大小的api
public:
	void setWindowHeight(int iWindowHeight) { m_iWindowHeight = iWindowHeight; }
	void setWindowWidth(int iWindowWidth) { m_iWindowWidth = iWindowWidth; }
	int getWindowHeight() const { return m_iWindowHeight; }
	int getWindowWidth() const { return m_iWindowWidth; }


protected:
	int m_iWindowWidth = 0;
	int m_iWindowHeight = 0;
};


#endif