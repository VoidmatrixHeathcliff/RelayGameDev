#include "../../include/scene/LoadScene.h"
#include "../../include/assets/AssetManager.h"
#include "../../include/singleton/Singleton.h"

/// This functino give a smooth interpolation for progress bar
/// @param X The X parameter of the smooth function
/// @return The result of the interpolation
static float SmoothInterpolation(const float& X) {
	return pow(X, 1.5f);
}

void LoadScene::_OnUpdate(float deltaTime) {
	if (_progressBar->GetPercentage() >= 100) {
		return;
	}

	_progressBar->SetPercentage(SmoothInterpolation(progress));

	// We are actually loading resource of music :)
	if ((progress >= 70.f && musicLoadDone) || progress < 70.f) {
		progress += 0.1f;
	}
	
	//Sleep(16)
}

LoadScene::LoadScene() {
	_logo = new PImageLabel("./assets/ui/voidjang.png");
	_progressBar = new PProgressBar((int)(getwidth() * 0.8), 20);
	_logo->Resize((int)(getwidth() * 0.4), (int)(getheight() * 0.5333));
	_logo->Move(getwidth() / 2 - _logo->GetWidth() / 2, getheight() / 2 - _logo->GetHeight() / 2);
	_progressBar->Move(getwidth() / 2 - _progressBar->GetWidth() / 2, _logo->GetY() + _logo->GetHeight());
	_progressBar->OnFinished.Connect(this, &LoadScene::OnProgressBarFinish);

	_fakeLoadUI.emplace_back(_logo);
	_fakeLoadUI.emplace_back(_progressBar);

	ui->AddObject(_logo);
	ui->AddObject(_progressBar);

	std::thread([this]() {
		PGetSingleton<PAssetManager>().LoadSounds();
		musicLoadDone = true;
	}).detach();

	SetDrawPolicy(DrawPolicy::ContentAbove);
}

void LoadScene::OnProgressBarFinish(int) {
	if (_callback) {
		_callback();
	}
	else throw std::runtime_error("callback is nullptr");
}
