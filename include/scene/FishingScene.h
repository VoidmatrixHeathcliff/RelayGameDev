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
/// ��Ӧ�Ĵ����ɫ����λ�ã���100.40��~��480.40����
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
/// ��Ӧ�Ĵ�����ֿ�
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
	judge,			//�����Ӧ�İ׿��ж�
	fish			//�����ĵ���

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
	FishType type;								//�������
	int power;									//����ֵ�Ȩ��
	float velocity;								//���ζ����ٶ�
	float angle;								//���ζ�ת��ĽǶ�
	std::string name;							//�������
	PImageLabel* image;							//���ͼƬ
	FishFlag special_flag = FishFlag::none;		//��������־
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
	const float fish_size = 40;	//������ж���Χ
	const float a = getwidth() / 640;
	const float minX = 300.0f * a;
	const float maxX = 640.0f * a;
	const float minY = 0.0f * a;
	const float maxY = 480.0f * a;
public:
	
	void _OnEnter()
	{
		//�ú�����ִ�У����ǲ�֪��Ϊʲôû��Ч��
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
		// ʹ�ù̶���Χ�����Ƿ��ڷ�Χ��
		return (p.x >= minX && p.x <= maxX && p.y >= minY && p.y <= maxY);
	}

	void generatePath(Point start, Point end) {
		path.clear();
		const int random_step = 300;	//����ȫ����ƶ��Ĵ������ﵽ�ô������㽫�����������յ��ƶ���
		const int max_step = 1000;		//
		int index = 0;	//	Ŀǰ·���ϵ������
		static Point current_direction;	//	�㵱ǰ���ƶ�����

		//������ĳ�ʼ����Ϊ�����յ�
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

			//���ﴦ��2�Ǿ����ܷ�ֹ���������ǲ���·��
			if (distance(current, end) <  fish_size / 2)
			{
				is_end_in_path = true;
			}
			
			index++;			

			//�����Ƿ������ȥ��·�����ɵĴ���
			//// ���㳯���յ�ĽǶ�
			//float targetAngle = atan2(end.y - current.y, end.x - current.x);

			//// ���������Ŀ�귽���ϣ�����ƫ����
			//float randomFactor = (static_cast<float>(rand()) / RAND_MAX - 0.5f) * 3.14159 / 4; // ���ƫ����
			//float angle = targetAngle + randomFactor;

			//next.x = current.x + step_size * cos(angle);
			//next.y = current.y + step_size * sin(angle);

			//if (isWithinBounds(next)) {
			//	current = next;
			//	path.push_back(current);
			//}
		}

		const int max_remain_step = 50;	//	���������˶�����+50
		int remain_step = rand() % max_remain_step + 50;	//���ʱ����ʱ��ʧ
		for (int i = 0; i < remain_step ; i++)
		{
			//ͬ�ϣ������������
			float random_angle = (static_cast<float>(rand()) / RAND_MAX - 0.5f) * current_fish->angle * (3.14159 / 180);
			float current_angle = atan2(current_direction.y, current_direction.x);

			current_direction.x = cos(random_angle + current_angle);
			current_direction.y = sin(random_angle + current_angle);

			next.x = current.x + current_fish->velocity * current_direction.x;
			next.y = current.y + current_fish->velocity * current_direction.y;


			current = next;
			path.push_back(current);
		}
		// ���һ��ֱ�ӵ����յ�,�������ҵ�СС���ƣ������⣨

	}

	void endFishing(bool flag=true)
	{
		if (!flag)
		{
			std::cout << "û����" << std::endl;
			is_saved = HasSaved::Failed;
			isFishing = false;
			return;
		}
		//�����ⷶΧ*1.5����Ϊһ���ķ�Χ�ҵ����������˾��ǿ��ˣ����Ǹ��ֿ�������1����Χ���ж�
		if (distance(fishingPoint, fishPoint) < fish_size * 1.5)
		{
			fish_scene = fishScene::judge;
			beat_block.is_active = true;
			beat_block.position_x = rand() % 380 + 100.0f;
			
			//::cout << "������" << current_fish->name << std::endl;
			//currentFishType = lastFishType;
		}
		else
		{
			std::cout << "û����" << std::endl;
			is_saved = HasSaved::Failed;
		}
		isFishing = false;
	}

	//PImageLabel* getRandomFish()
	//{
	//	int a = rand() % 16;

	//	if (a == 1)
	//	{
	//		name = "������!!!!!!!!!!!!!!";
	//		lastFishType = FishType::flyingfish;
	//		return fishPool.find(FishType::flyingfish)->second;
	//	}
	//	else if (a == 2 || a == 3)
	//	{
	//		name = "����";
	//		lastFishType = FishType::pufferfish;
	//		return fishPool.find(FishType::pufferfish)->second;
	//	}
	//	else if (a == 4 || a == 5)
	//	{
	//		name = "С����";
	//		lastFishType = FishType::clownfish;
	//		return fishPool.find(FishType::clownfish)->second;
	//	}
	//	else if (a == 6 || a == 7 || a == 8)
	//	{
	//		name = "����";
	//		lastFishType = FishType::salmon;
	//		return fishPool.find(FishType::salmon)->second;
	//	}
	//	else
	//	{
	//		name = "����";
	//		lastFishType = FishType::cod;
	//		return fishPool.find(FishType::cod)->second;
	//	}
	//}

	Point getRandomPointInRange() {
		Point randomPoint;
		srand(time(0));
		while (true)
		{// ����ָ����Χ�ڵ����x��y����
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



	checkline check_line;			//��Ҫ����İ�ɫ����λ��
	fishScene fish_scene = fishScene::fish;	//��ǰ����
	beatBlock beat_block;
	
private:
	void initialize_fish();			//��ʼ����Ĳ���
	int get_total_power();			//��ȡ�������Ȩ��
	void new_fish();				//������һ���㣨���ʣ�����current_fish)
};