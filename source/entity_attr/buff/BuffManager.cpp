#include "../../../include/entity/Entity.h"
#include "../../../include/entity_attr/buff/BuffManager.h"

void PBuffManager::CheckBuffs(PEntity* e) {
	ApplyBuffs(e);
}

void PBuffManager::ApplyBuffs(PEntity* e) {
	if (isIgnited) {
		//希望有会用计时器的人将其改成1s运行一次
		//希望有会用计时器的人将其改成1s运行一次
		//希望有会用计时器的人将其改成1s运行一次
		e->changeHealth(-1);
	}
	if (isPoison) {
		//希望有会用计时器的人将其改成1s运行一次
		//希望有会用计时器的人将其改成1s运行一次
		//希望有会用计时器的人将其改成1s运行一次
		if (e->GetHealth() > 1)
			e->changeHealth(-1 * Poison_level);
	}
	if (isWither) {
		//希望有会用计时器的人将其改成1s运行一次
		//希望有会用计时器的人将其改成1s运行一次
		//希望有会用计时器的人将其改成1s运行一次
		e->changeHealth(-1 * Wither_level);
	}
}