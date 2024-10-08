#include "./include/launcher/Launcher.h"
#include "./include/game/Game.h"
#include "./include/game/collision/CollisionManager.h"
#include "./include/notPiano/notPiano.h"
#ifdef _DEBUG
#include<iostream>
#endif
///
/// Feel free to delete the code inside the #ifdef
/// since it is only for demo!
///

#ifdef UIDemo
/// The example class for UI creation
class UIExample {
public:
	UIExample() {
		/// Create a window in specified size
		PWindow window(429, 365, "UI Example");

		// Create a GUI control manager to control repaint progress and message loop
		PGUIManager manager;

		// Get the device wrapper of the PWindow
		//      Actually, you can create a PImage's device by the function:
		//            (static function) PDevice::MakeFromImage
		auto device = window.GetDevice();

		// Createing UI control

		auto imageLabel = new PImageLabel("./assets/ui/title.png");
		auto imageViewText = new PTextLabel("Image View");
		auto normalTextButton = new PTextLabel("Normal Button");
		auto normalButton = new PButton(351, 30, "I am normal button 1");
		auto unlimitedText = new PTextLabel("Unlimited Text");
		auto limitedText = new PTextLabel("Limited Text");
		auto unlimitedInput = new PInput(198, 30, "Unlimited Input");
		auto limitedInput = new PInput(198, 30, "Limited Input");
		auto stressButtonText = new PTextLabel("Stress Button");
		auto stressButton = new PStressButton(187, 36, "Hide the Icon");
		auto normalIconButton = new PButton(187, 36, "Show The Icon");

		_inputText = new PTextLabel("(COLOR TEXT) Input context :");
		// Custom the text's color
		_inputText->FontColor = RGB(240, 56, 67);
		_inputText->Move(20, 328);

		_logo = new PImageLabel("./assets/ui/voidjang.png");
		_logo->Resize(47, 47);
		_logo->Move(333, 309);

		imageLabel->Resize(361, 53);

		unlimitedInput->Move(34, 198);
		unlimitedText->Move(34, 179);

		limitedInput->Move(227, 198);
		limitedText->Move(227, 179);

		normalTextButton->Move(34, 121);
		normalButton->Move(33, 144);

		imageLabel->Move(20, 58);
		imageViewText->Move(35, 35);

		stressButtonText->Move(22, 236);
		stressButton->Move(20, 260);

		normalIconButton->Move(227, 260);

		limitedInput->SetMaxLength(4);

		// Connect UI event, just like the Qt's signal, but little bit difference
		// on usage
		stressButton->OnClick.Connect(this, &UIExample::HideIcon);
		normalIconButton->OnClick.Connect(this, &UIExample::ShowIcon);
		limitedInput->OnFinish.Connect(this, &UIExample::OnLimitedInputChanged);
		limitedInput->OnText.Connect(this, &UIExample::OnLimitedInputChanged);

		// Add to UI manager
		manager.AddObject(imageLabel);
		manager.AddObject(imageViewText);
		manager.AddObject(normalTextButton);
		manager.AddObject(normalButton);
		manager.AddObject(unlimitedText);
		manager.AddObject(limitedText);
		manager.AddObject(unlimitedInput);
		manager.AddObject(limitedInput);
		manager.AddObject(stressButtonText);
		manager.AddObject(stressButton);
		manager.AddObject(normalIconButton);
		manager.AddObject(_logo);
		manager.AddObject(_inputText);

		setbkcolor(RGB(72, 73, 74));

		while (true) {
			ExMessage message;
			while (peekmessage(&message)) {
				// Process message
				manager.OnMessage(message);
			}

			cleardevice();

			manager.OnDraw(device);
			device->Flush();

			Sleep(16);
		}
	}

private:
	void ShowIcon() {
		// Use show/hide function to show or hide a control
		_logo->Show();
	}
	void HideIcon() {
		_logo->Hide();
	}
	void OnLimitedInputChanged(PString Text) {
		// Adjust the text label size to adapt the text size
		_inputText->SetText(ostr::format("(COLOR TEXT) Input context :{}", Text));
		_inputText->ResizeAsText();
	}

private:
	PImageLabel* _logo;
	PTextLabel* _inputText;
};


int WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	UIExample();

}

#else

int WinMain(_In_ HINSTANCE hInstance,
			_In_opt_ HINSTANCE hPrevInstance,
			_In_ LPSTR lpCmdLine,
			_In_ int nShowCmd)		//这个函数相当于主函数
{
	try {
		// not_bmk: a global piano
		NotPiano::Piano notBackGroundPiano;
	#ifndef _DEBUG
		// you cheater !
		auto NGGYU =  NotPiano::Piano::compose("1^. 2^. 5 | 2^. 3^. 5^__ 4^__ 3^__ 1^__ | 1^. 2^. 5 | 5- 5_ 5__ 5__ 6__ 1^__ 6__ 1^__ | 1^. 2^. 5 | 2^. 3^. 5^__ 4^__ 3^__ 1^__ | 1^. 2^. 5 | 5- 5_ 1^__ 1^__ 0_ 1^__ 1^__");
		auto MPMP = NotPiano::Piano::compose("5^ 3^ 1^ 5^ | 5^_ 6^_ 5^_ 4^_ 5^ 5^_ 1^^_ | 7^ 7^_ 6^_ 5^ 4^ | 3^ 4^ 5^-");
		notBackGroundPiano.play(NGGYU, 480, 50);

		PLauncher launcher;
		launcher.Loop();

		notBackGroundPiano.stop();
		// what a lovely flower !
		notBackGroundPiano.play(MPMP, 225, 50);

		auto gameSize = launcher.GetGameScreenSize();
		PLGame gameWindow(std::get<0>(gameSize), std::get<1>(gameSize), launcher.GetPlayerName());
		gameWindow.Loop();

		NotPiano::Piano::clearSheet(NGGYU);
		NotPiano::Piano::clearSheet(MPMP);
	#else

		PLGame gameWindow(640, 480, "Developer");
		gameWindow.Loop();
	#endif
	}
	catch (const std::exception& e) {
		printf("Sorry, but PaperCraft crashed with information:\n%s\n", e.what());
		system("pause");
	}
	return 0;
}

#endif