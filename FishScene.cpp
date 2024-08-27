#include "../scene/FishingScene.h"
#include "iostream"

void FishingScene::_OnMessage(ExMessage& Message)
{
	if (Message.message == WM_LBUTTONUP)
	{
		if (Message.x >= minX && Message.x <= maxX && Message.y >= minY && Message.y <= maxY&&isFishing==false)
		{
			isFishingpointExsits = true;
			fishingPoint.x = Message.x;
			fishingPoint.y = Message.y;
		}
	}

	if (isFishingpointExsits&&Message.message == WM_KEYUP && Message.vkcode == VK_SPACE)
	{
		if (!isFishing)
		{
			fishPoint = getRandomPointInRange();
			currentFishImage = getRandomFish();
			currentFishImage->Move(fishPoint.x, fishPoint.y);
			path = generatePath(fishPoint, fishingPoint, 0.11);
			isFishing = true;
		}
		else
			endFishing();

	}
	
}

void FishingScene::_OnDraw(PDevice* Device)
{
	background->OnDraw();
	fishingRob->OnDraw();

	if (isFishing)
		currentFishImage->OnDraw();

	setlinecolor(RED);
	setfillcolor(RED);
	fillcircle(fishingPoint.x, fishingPoint.y, 10);

}

void FishingScene::_OnUpdate(float deltaTime)
{
	if (isFishing)
	{
		if (index < path.size()-1)
			index++;
		else
		{
			endFishing(false);
		}
		fishPoint = path[index];
		currentFishImage->Move(fishPoint.x, fishPoint.y);
	}
}



FishingScene::FishingScene()
{

	background = new PImageLabel("./assets/flyingfish/background.png");
	background->Resize(getwidth(), getheight());

	fishingRob = new PImageLabel("./assets/flyingfish/fishingrod.png");
	fishingRob->Resize(getwidth() * 0.1125, getheight() / 12);
	fishingRob->Move(90*getwidth()/640, 240*getheight()/480);

	fishPool[FishType::clownfish] = new PImageLabel("./assets/flyingfish/fish_clownfish_raw.png");
	fishPool.find(FishType::clownfish)->second->Resize(40 * a, 40 * a);

	fishPool[FishType::cod] = new PImageLabel("./assets/flyingfish/fish_cod_raw.png");
	fishPool.find(FishType::cod)->second->Resize(40 * a, 40 * a);

	fishPool[FishType::pufferfish] = new PImageLabel("./assets/flyingfish/fish_pufferfish_raw.png");
	fishPool.find(FishType::pufferfish)->second->Resize(40 * a, 40 * a);

	fishPool[FishType::salmon] = new PImageLabel("./assets/flyingfish/fish_salmon_raw.png");
	fishPool.find(FishType::salmon)->second->Resize(40 * a, 40 * a);

	fishPool[FishType::flyingfish] = new PImageLabel("./assets/flyingfish/flyingfish.png");
	fishPool.find(FishType::flyingfish)->second->Resize(40 * a, 40 * a);

	currentFishImage = fishPool.find(FishType::cod)->second;

}

FishingScene::~FishingScene()
{

}

