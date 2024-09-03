//#include "../scene/FishingScene.h"
#include "../../../include/scene/FishingScene.h"
#include "iostream"
#include <fstream>
#include <sstream>

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
			new_fish();

			//currentFishImage = getRandomFish();
			current_fish->image->Move(fishPoint.x, fishPoint.y);
			generatePath(fishPoint, fishingPoint);
			index = 0;
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
		current_fish->image->OnDraw();

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
		current_fish->image->Move(fishPoint.x, fishPoint.y);
		if (current_fishing_state==FishingState::SavingYourLive)
		{
			if (current_fish->special_flag == FishFlag::savelive)
				is_saved = HasSaved::Successed;
		}
	}
}



FishingScene::FishingScene()
{
	
	initialize_fish();
	background = new PImageLabel("./assets/flyingfish/background.png");
	background->Resize(getwidth(), getheight());

	fishingRob = new PImageLabel("./assets/flyingfish/fishingrod.png");
	fishingRob->Resize(getwidth() * 0.1125, getheight() / 12);
	fishingRob->Move(90*getwidth()/640, 240*getheight()/480);

	//fishPool[FishType::clownfish] = new PImageLabel("./assets/flyingfish/fish_clownfish_raw.png");
	//fishPool.find(FishType::clownfish)->second->Resize(40 * a, 40 * a);

	//fishPool[FishType::cod] = new PImageLabel("./assets/flyingfish/fish_cod_raw.png");
	//fishPool.find(FishType::cod)->second->Resize(40 * a, 40 * a);

	//fishPool[FishType::pufferfish] = new PImageLabel("./assets/flyingfish/fish_pufferfish_raw.png");
	//fishPool.find(FishType::pufferfish)->second->Resize(40 * a, 40 * a);

	//fishPool[FishType::salmon] = new PImageLabel("./assets/flyingfish/fish_salmon_raw.png");
	//fishPool.find(FishType::salmon)->second->Resize(40 * a, 40 * a);

	//fishPool[FishType::flyingfish] = new PImageLabel("./assets/flyingfish/flyingfish.png");
	//fishPool.find(FishType::flyingfish)->second->Resize(40 * a, 40 * a);
}

FishingScene::~FishingScene()
{

}

void FishingScene::initialize_fish()
{
	std::ifstream file(fish_data_path);
	if (!file.good())
		return;

	std::string str_line;

	int fish_id;
	int fish_power;
	float fish_velocity; 
	float fish_angle;
	std::string fish_name;
	std::string fish_image_path;
	FishFlag fish_special_flag;
	while (std::getline(file, str_line))
	{
		std::string str_data;
		std::stringstream str_stream(str_line);
		{
			if (std::getline(str_stream, str_data, ','))
				fish_id = std::stoi(str_data);
			if (std::getline(str_stream, str_data, ','))
				fish_power = std::stoi(str_data);
			if (std::getline(str_stream, str_data, ','))
				fish_velocity = std::stoi(str_data);
			if (std::getline(str_stream, str_data, ','))
				fish_angle = std::stoi(str_data);
			if (std::getline(str_stream, str_data, ','))
				fish_image_path = str_data;
			if (std::getline(str_stream, str_data, ','))
				fish_name = str_data;
			if (std::getline(str_stream, str_data, ','))
				fish_special_flag = (FishFlag)std::stoi(str_data);
			fish_data_map[fish_id] = new FishData(fish_id, fish_power, fish_velocity,
				fish_angle, fish_name, fish_image_path, fish_special_flag);
		}
	}

	file.close();
}

int FishingScene::get_total_power()
{
	int result = 0;

	for (std::pair<FishType, FishData*> kv : fish_data_map)
	{
		result += kv.second->power;
	}
	return result;
}

void FishingScene::new_fish()
{
	int random_num = rand() % get_total_power();
	for (std::pair<FishType, FishData*> kv : fish_data_map)
	{
		random_num -= kv.first;
		if (random_num < 0)
		{
			current_fish = kv.second;
			break;
		}
	}
}