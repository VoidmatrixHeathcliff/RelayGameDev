#pragma once

#include"../gui/Scene.h"
#include "../gui/ImageLabel.h"
#include "../gui/ProgressBar.h"

class LoadScene :public PScene {
private:
	std::vector<PGUIObject*> _fakeLoadUI;
	PProgressBar* _progressBar;
	PImageLabel* _logo;
	std::atomic_bool musicLoadDone = false;
	float progress = 0.0;

protected:
	void _OnUpdate(float deltaTime)override;

public:
	LoadScene();

	void OnProgressBarFinish(int);
};