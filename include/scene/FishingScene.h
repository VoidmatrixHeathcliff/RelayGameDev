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

struct Point {
    float x, y;
};


enum class FishType
{
	clownfish,
	cod,
	pufferfish,
	salmon,
	flyingfish
};

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

class FishingScene :public PScene
{
	const float a = getwidth() / 640;
	const float minX = 300.0f * a;
	const float maxX = 640.0f * a;
	const float minY = 0.0f * a;
	const float maxY = 480.0f * a;
public:

	void _OnMessage(ExMessage& Message);
	void _OnDraw(PDevice* Device);
	void _OnUpdate(float deltaTime);

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

	std::vector<Point> generatePath(Point start, Point end, float step_size) {
		index = 0;

		std::vector<Point> path;
		path.push_back(start);

		Point current = start;
		srand(time(0));

		while (distance(current, end) > step_size) {
			Point next;

			// ���㳯���յ�ĽǶ�
			float targetAngle = atan2(end.y - current.y, end.x - current.x);

			// ���������Ŀ�귽���ϣ�����ƫ����
			float randomFactor = (static_cast<float>(rand()) / RAND_MAX - 0.5f) * 3.14159 / 4; // ���ƫ����
			float angle = targetAngle + randomFactor;

			next.x = current.x + step_size * cos(angle);
			next.y = current.y + step_size * sin(angle);

			if (isWithinBounds(next)) {
				current = next;
				path.push_back(current);
			}
		}

		// ���һ��ֱ�ӵ����յ�,�������ҵ�СС���ƣ������⣨
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);

		path.push_back(end);

		path.push_back(end);

		path.push_back(end);

		path.push_back(end);
		path.push_back(end);

		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);
		path.push_back(end);

		path.push_back(end);



		return path;
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
		if (distance(fishingPoint, fishPoint) < 40)
		{
			std::cout << "������"<<name << std::endl;
			currentFishType = lastFishType;
		}
		else
		{
			std::cout << "û����" << std::endl;
			is_saved = HasSaved::Failed;
		}
		isFishing = false;
	}

	PImageLabel* getRandomFish()
	{
		int a = rand() % 16;

		if (a == 1)
		{
			name = "������!!!!!!!!!!!!!!";
			lastFishType = FishType::flyingfish;
			return fishPool.find(FishType::flyingfish)->second;
		}
		else if (a == 2 || a == 3)
		{
			name = "����";
			lastFishType = FishType::pufferfish;
			return fishPool.find(FishType::pufferfish)->second;
		}
		else if (a == 4 || a == 5)
		{
			name = "С����";
			lastFishType = FishType::clownfish;
			return fishPool.find(FishType::clownfish)->second;
		}
		else if (a == 6 || a == 7 || a == 8)
		{
			name = "����";
			lastFishType = FishType::salmon;
			return fishPool.find(FishType::salmon)->second;
		}
		else
		{
			name = "����";
			lastFishType = FishType::cod;
			return fishPool.find(FishType::cod)->second;
		}
	}

	Point getRandomPointInRange() {
		Point randomPoint;

		while (true)
		{// ����ָ����Χ�ڵ����x��y����
			randomPoint.x = minX + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxX - minX)));
			randomPoint.y = minY + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxY - minY)));
			if (distance(randomPoint, fishingPoint) >= 100)
				break;
		}

		return randomPoint;
	}

	FishType get_current_fish_type() { return currentFishType; }
	HasSaved get_is_saved() { return is_saved; }
	void set_fishing_state(FishingState Fs) { current_fishing_state = Fs; }

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

	std::unordered_map<FishType, PImageLabel*> fishPool;
	std::string name;

	PImageLabel* currentFishImage;
	FishType currentFishType;
	FishType lastFishType;
	FishingState current_fishing_state = FishingState::Play;
	HasSaved is_saved = HasSaved::None;
};