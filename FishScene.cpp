//#include "../scene/FishingScene.h"
#include "../../../include/scene/FishingScene.h"
#include "iostream"
#include <fstream>
#include <sstream>

void FishingScene::_OnMessage(ExMessage& Message)
{
	//esc键返回主菜单
	if (Message.message == WM_KEYDOWN && Message.vkcode == VK_ESCAPE) {
		if (_callback) _callback();
	}

	//
	if (fish_scene == fishScene::fish)
	{
		if (Message.message == WM_LBUTTONUP)
		{
			if (Message.x >= minX && Message.x <= maxX && Message.y >= minY && Message.y <= maxY && isFishing == false)
			{
				isFishingpointExsits = true;
				fishingPoint.x = Message.x;
				fishingPoint.y = Message.y;
			}
			if (Message.x >= minX && Message.x <= maxX && Message.y >= minY && Message.y <= maxY)
			{
				fishingPoint.x = Message.x;
				fishingPoint.y = Message.y;
			}
		}

		if (isFishingpointExsits && Message.message == WM_KEYDOWN && Message.vkcode == VK_SPACE)
		{
			if (!isFishing)
			{
				//随机的鱼鱼生成点
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
	else
	{
		if (isFishingpointExsits && Message.message == WM_KEYDOWN && Message.vkcode == VK_SPACE)
		{
			double checkLineCenter_x = check_line.position_x + check_line.width / 2;
			if(checkLineCenter_x>=beat_block.position_x&& checkLineCenter_x <= beat_block.position_x+beat_block.width)
			{
				fish_scene = fishScene::fish;
				std::cout << "钓到咯" << current_fish->name << std::endl;
				beat_block.is_active = false;
				isFishing = false;
			}
			else
			{
				fish_scene = fishScene::fish;
				std::cout << "鱼跑了" << current_fish->name << std::endl;
				isFishing = false;
			}
		}
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
	setlinestyle(PS_SOLID,10);
	fillcircle(fishingPoint.x, fishingPoint.y, 5);




	/////下面都是节奏方块的绘制
	//打击方块的范围
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID,40);
	line(100, 40, 480, 40);
	
	/*setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 20);
	line(130, 40, 135, 40);*/


	if (beat_block.is_active)
	{
		setfillcolor(YELLOW);
		setlinecolor(YELLOW);
		setlinestyle(PS_SOLID, 5);
		// 绘制一个实心矩形，左上角(100, 100)，右下角(300, 300)
		fillrectangle(beat_block.position_x, beat_block.position_y,
			beat_block.position_x + beat_block.width, beat_block.position_y + beat_block.height);
	}
	setfillcolor(WHITE);
	setlinecolor(WHITE);
	setlinestyle(PS_SOLID, 5);
	// 绘制一个实心矩形，左上角(100, 100)，右下角(300, 300)
	fillrectangle(check_line.position_x,check_line.position_y, 
		check_line.position_x+ check_line.width, check_line.position_y+ check_line.height);



}

void FishingScene::_OnUpdate(float deltaTime)
{


	if (fish_scene == fishScene::fish)
	{
		if (isFishing)
		{
			if (index < path.size() - 1)
				index++;
			else
			{
				endFishing(false);
			}
			fishPoint = path[index];
			current_fish->image->Move(fishPoint.x, fishPoint.y);
			if (current_fishing_state == FishingState::SavingYourLive)
			{
				if (current_fish->special_flag == FishFlag::savelive)
					is_saved = HasSaved::Successed;
			}
		}
	}
	//打击对应的方块逻辑
	else
	{
		if (check_line.is_facing_right)
		{
			if (check_line.position_x + check_line.velocity * deltaTime > 480.0f)
			{
				check_line.position_x = 480.0f;
				check_line.is_facing_right = false;
			}
			else
			{
				check_line.position_x += check_line.velocity * deltaTime;
			}
		}
		else
		{
			if(check_line.position_x + check_line.velocity * deltaTime < 100.0f)
			{
				check_line.position_x = 100;
				check_line.is_facing_right = true;
			}
			else
			{
				check_line.position_x -= check_line.velocity * deltaTime;
			}
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