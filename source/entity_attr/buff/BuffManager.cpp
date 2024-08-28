#include "../../../include/entity/Entity.h"
#include "../../../include/entity_attr/buff/BuffManager.h"

void PBuffManager::CheckBuffs(PEntity* e) {
	ApplyBuffs(e);
}

void PBuffManager::ApplyBuffs(PEntity* e) {
	if (isIgnited) {
		//ϣ���л��ü�ʱ�����˽���ĳ�1s����һ��
		//ϣ���л��ü�ʱ�����˽���ĳ�1s����һ��
		//ϣ���л��ü�ʱ�����˽���ĳ�1s����һ��
		e->changeHealth(-1);
	}
	if (isPoison) {
		//ϣ���л��ü�ʱ�����˽���ĳ�1s����һ��
		//ϣ���л��ü�ʱ�����˽���ĳ�1s����һ��
		//ϣ���л��ü�ʱ�����˽���ĳ�1s����һ��
		if (e->GetHealth() > 1)
			e->changeHealth(-1 * Poison_level);
	}
	if (isWither) {
		//ϣ���л��ü�ʱ�����˽���ĳ�1s����һ��
		//ϣ���л��ü�ʱ�����˽���ĳ�1s����һ��
		//ϣ���л��ü�ʱ�����˽���ĳ�1s����һ��
		e->changeHealth(-1 * Wither_level);
	}
}