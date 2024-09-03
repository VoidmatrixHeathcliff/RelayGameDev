#pragma once
#include <conio.h>
#include"../gui/Scene.h"
#include "../EasyXBase.h"
#include "unordered_map"
#include "../gui/ImageLabel.h"
#include "../../include/mic/MCIManager.h"
#include "../../../include/scene/GameScene.h"
#include "iostream"
#include "string"
#include "../../include/game/PResourseManager.h"
#include "../../include/game/collision/CollisionManager.h"


/// <summary>
/// 对应的打击白色线条位置（（100.40）~（480.40））
/// </summary>
struct checkline
{
	int width = 10;
	int height = 40;
	double velocity = 500.0f;
	double position_x = 100.0f;
	double position_y = 20.0f;
	bool is_facing_right = true;

};

/// <summary>
/// 对应的打击音乐块
/// </summary>
struct beatBlock
{
	bool is_active = false;
	int width = 30;
	int height = 40;
	double position_x = 100.0f;
	double position_y = 20.0f;
};

enum fishScene
{
	judge,			//打击对应的白块判断
	fish			//正常的钓鱼

};


struct Point {
    float x, y;
public:
	float get_length()
	{
		return sqrtf(x * x + y * y);
	}
	void normalize()
	{
		float length = get_length();
		x /= length;
		y /= length;
	}

};

typedef int FishType;
//enum class FishType :int
//{
//	clownfish,
//	cod,
//	pufferfish,
//	salmon,
//	flyingfish
//};

enum class FishingState
{
	Play,
	SavingYourLive
};

enum class HasSaved
{
	None,
	Failed,
	Successed
};

enum FishFlag :int
{
	none = 0,
	savelive = 1
};


struct FishData
{
	FishType type;								//鱼的类型
	int power;									//鱼出现的权重
	float velocity;								//鱼游动的速度
	float angle;								//鱼游动转向的角度
	std::string name;							//鱼的名称
	PImageLabel* image;							//鱼的图片
	FishFlag special_flag = FishFlag::none;		//特殊的鱼标志
public:
	FishData(int type,int power, float velocity, float angle, std::string result, std::string image_path, FishFlag special_flag)
		:type(type),power(power), velocity(velocity), angle(angle), name(result), special_flag(special_flag)
	{
		image = new PImageLabel(image_path.c_str());
		image->Resize(40 * getwidth() / 640, 40 * getwidth() / 640);
	}
	FishData() = default;
};





class FishingScene :public PScene
{
	const float fish_size = 40;	//钓点的判定范围
	const float a = getwidth() / 640;
	const float minX = 300.0f * a;
	const float maxX = 640.0f * a;
	const float minY = 0.0f * a;
	const float maxY = 480.0f * a;
public:
	
	void _OnEnter()
	{
		//该函数有执行，但是不知道为什么没有效果
		mci_instance = PMCIManager::OpenBGM("./assets/flyingfish/IgnusNilsenWaltz.mp3", "bgm_fish");
		PMCIManager::Play(mci_instance, nullptr,true);
	}
	void _OnMessage(ExMessage& Message);
	void _OnDraw(PDevice* Device);
	void _OnUpdate(float deltaTime);
	void _OnExit()
	{
		PMCIManager::Close(mci_instance);
	}
public:

	FishingScene();
	~FishingScene();

	float distance(Point a, Point b) {
		return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
	}

	bool isWithinBounds(Point p) {
		// 使用固定范围检查点是否在范围内
		return (p.x >= minX && p.x <= maxX && p.y >= minY && p.y <= maxY);
	}

	void generatePath(Point start, Point end) {
		path.clear();
		const int random_step = 300;	//鱼完全随机移动的次数，达到该次数后，鱼将更倾向于向终点移动！
		const int max_step = 1000;		//
		int index = 0;	//	目前路径上点的数量
		static Point current_direction;	//	鱼当前的移动方向

		//设置鱼的初始方向为朝下终点
		current_direction.x = end.x - start.x;
		current_direction.y = end.y - start.y;
		current_direction.normalize();

		//std::vector<Point> path;
		path.push_back(start);

	
		static Point current = start;
		static Point next;
		srand(time(0));
		bool is_end_in_path = false;
		while (!is_end_in_path) {
			float a = (static_cast<float>(rand()) / RAND_MAX - 0.5f);

			
			float random_angle =  a* current_fish->angle * (3.14159 / 180);

			float current_angle = atan2(current_direction.y, current_direction.x);
			
			current_direction.x = cos(random_angle + current_angle);
			current_direction.y = sin(random_angle + current_angle);
			
			if (index > random_step)
			{
				current_direction.x = current_direction.x + (end.x - current.x);
				current_direction.y = current_direction.y + (end.y - current.y);
				current_direction.normalize();
			}
			next.x = current.x + current_fish->velocity * current_direction.x;
			next.y = current.y + current_fish->velocity * current_direction.y;

			
			current = next;
			path.push_back(current);

			//这里处以2是尽可能防止经过钓点是擦边路过
			if (distance(current, end) <  fish_size / 2)
			{
				is_end_in_path = true;
			}
			
			index++;			

			//以下是飞鱼丸过去的路径生成的代码
			//// 计算朝向终点的角度
			//float targetAngle = atan2(end.y - current.y, end.x - current.x);

			//// 随机方向与目标方向混合，增加偏向性
			//float randomFactor = (static_cast<float>(rand()) / RAND_MAX - 0.5f) * 3.14159 / 4; // 随机偏移量
			//float angle = targetAngle + randomFactor;

			//next.x = current.x + step_size * cos(angle);
			//next.y = current.y + step_size * sin(angle);

			//if (isWithinBounds(next)) {
			//	current = next;
			//	path.push_back(current);
			//}
		}

		const int max_remain_step = 50;	//	鱼最大额外运动步数+50
		int remain_step = rand() % max_remain_step + 50;	//随机时间延时消失
		for (int i = 0; i < remain_step ; i++)
		{
			//同上，让鱼随便走走
			float random_angle = (static_cast<float>(rand()) / RAND_MAX - 0.5f) * current_fish->angle * (3.14159 / 180);
			float current_angle = atan2(current_direction.y, current_direction.x);

			current_direction.x = cos(random_angle + current_angle);
			current_direction.y = sin(random_angle + current_angle);

			next.x = current.x + current_fish->velocity * current_direction.x;
			next.y = current.y + current_fish->velocity * current_direction.y;


			current = next;
			path.push_back(current);
		}
		// 最后一步直接到达终点,这里是我的小小整蛊，请别介意（

	}

	void endFishing(bool flag=true)
	{
		if (!flag)
		{
			std::cout << "没钓到" << std::endl;
			is_saved = HasSaved::Failed;
			isFishing = false;
			return;
		}
		//这里检测范围*1.5是因为一倍的范围我调不来，开了就是开了！你是高手可以试试1被范围的判定
		if (distance(fishingPoint, fishPoint) < fish_size * 1.5)
		{
			fish_scene = fishScene::judge;
			beat_block.is_active = true;
			beat_block.position_x = rand() % 380 + 100.0f;
			
			//::cout << "钓到咯" << current_fish->name << std::endl;
			//currentFishType = lastFishType;
		}
		else
		{
			std::cout << "没钓到" << std::endl;
			is_saved = HasSaved::Failed;
		}
		isFishing = false;
	}

	//PImageLabel* getRandomFish()
	//{
	//	int a = rand() % 16;

	//	if (a == 1)
	//	{
	//		name = "飞鱼丸!!!!!!!!!!!!!!";
	//		lastFishType = FishType::flyingfish;
	//		return fishPool.find(FishType::flyingfish)->second;
	//	}
	//	else if (a == 2 || a == 3)
	//	{
	//		name = "河豚";
	//		lastFishType = FishType::pufferfish;
	//		return fishPool.find(FishType::pufferfish)->second;
	//	}
	//	else if (a == 4 || a == 5)
	//	{
	//		name = "小丑鱼";
	//		lastFishType = FishType::clownfish;
	//		return fishPool.find(FishType::clownfish)->second;
	//	}
	//	else if (a == 6 || a == 7 || a == 8)
	//	{
	//		name = "鲫鱼";
	//		lastFishType = FishType::salmon;
	//		return fishPool.find(FishType::salmon)->second;
	//	}
	//	else
	//	{
	//		name = "鳕鱼";
	//		lastFishType = FishType::cod;
	//		return fishPool.find(FishType::cod)->second;
	//	}
	//}

	Point getRandomPointInRange() {
		Point randomPoint;
		srand(time(0));
		while (true)
		{// 生成指定范围内的随机x和y坐标
			randomPoint.x = minX + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxX - minX)));
			randomPoint.y = minY + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxY - minY)));
			if (distance(randomPoint, fishingPoint) >= 100)
				break;
		}

		return randomPoint;
	}
	
	FishType get_current_fish_type() { return current_fish->type; }
	HasSaved get_is_saved() { return is_saved; }
	void set_fishing_state(FishingState Fs) { current_fishing_state = Fs; }

	void set_is_saved(HasSaved hs) {
		is_saved = hs;
	}

private:
	Point textPoint;
    Point fishingPoint;
	Point fishPoint;
    bool isFishing = false;
	PImageLabel* background;
	PImageLabel* fishingRob;
	bool isFishingpointExsits = false;
	std::vector<Point> path;
	int index = 0;

	//std::unordered_map<FishType, PImageLabel*> fishPool;
	//std::string name;

	//PImageLabel* currentFishImage;
	//FishType currentFishType;
	//FishType lastFishType;
	FishingState current_fishing_state = FishingState::Play;
	HasSaved is_saved = HasSaved::None;

	const std::string fish_data_path = "./assets/flyingfish/fish.cfg";
	typedef std::unordered_map <FishType, FishData*> FishDataMap;
	FishData* current_fish = nullptr;
	FishDataMap fish_data_map;
	PMCIInstance* mci_instance = nullptr;



	checkline check_line;			//需要打击的白色方块位置
	fishScene fish_scene = fishScene::fish;	//当前场景
	beatBlock beat_block;
	
private:
	void initialize_fish();			//初始化鱼的参数
	int get_total_power();			//获取所有鱼的权重
	void new_fish();				//新生成一条鱼（本质：更改current_fish)
};