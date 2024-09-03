#include "../../include/entity/ZFish.h"
#include "../../include/game/collision/CollisionManager.h"
#include "../../include/game/PResourseManager.h"
#include "../../include/entity/ZHook.h"

ZFish::ZFish() :
	m_iWidth(getwidth() / 13.f),
	m_iHeight(getwidth() / 13.f)
{
	// Ëæ»ú³¯Ïò
	if (rand() % 2) facingDir = 1;			// ÓÒ
	else facingDir = -1;					// ×ó

	// Åö×²Ïä
	hb = PGetSingleton<CollisionManager>().createHitbox();
	if (facingDir == -1) hb->position.x = (float)getwidth();
	else hb->position.x = -hb->size.x * 1.0f;
	hb->position.y = (float)((rand() % (getheight() / 5 * 4)) + getheight() / 5);
	hb->size = { m_iWidth * 1.f, m_iHeight * 1.f };

	hb->layerSrc = CollisionLayer::EnemyLayer;
	hb->layerDst = CollisionLayer::PlayerLayer;
	hb->setOnCollide([&]() {
		if (eCurrentState == ZFishState::Idle) {
			setCurrentState(ZFishState::BeCaught);
		}
	});
	hb->acceleration = { 0.0f, 0.0f };
	hb->velocity = { (100 + rand() % 100) * facingDir * 1.f, 0.0f };

	// ¶¯»­»ú
	PResourseManager* manager = &PGetSingleton<PResourseManager>();
	PAnimation<PImage> animation = anim.createAnimation("skin");
	animation.addFrame(manager->findImage("flyingfish"));
	animation.addFrame(manager->findImage("fish_pufferfish_raw"));
	animation.addFrame(manager->findImage("fish_clownfish_raw"));
	animation.addFrame(manager->findImage("ish_salmon_raw"));
	animation.addFrame(manager->findImage("fish_cod_raw"));
	animation.addFrame(manager->findImage("bat_fish"));
	m_iFrameIndex = rand() % 6;		// Ëæ»úÍ¼Æ¬

	// »æÖÆimageLabel
	imageLabel = new PImageLabel(animation.getFrame(m_iFrameIndex));
	imageLabel->Resize(m_iWidth, m_iHeight);
}

ZFish::~ZFish() {
	if (hb != nullptr) PGetSingleton<CollisionManager>().destroyHitbox(hb);
	delete imageLabel;
}


void ZFish::draw(const RenderInfo& renderInfo) {
	imageLabel->Move((int)hb->position.x, (int)hb->position.y);
	imageLabel->OnDraw();
	
	// »æÖÆÅö×²Ïä
	// rectangle(hb->position.x, hb->position.y, hb->position.x + hb->size.x, hb->position.y + hb->size.y);
}

void ZFish::update(float deltaTime) {
	if (eCurrentState == ZFishState::Idle) {
		if (facingDir == 1) {	// ÏòÓÒÒÆ¶¯µ½ÖÕµã
			if (hb->position.x >= getwidth()) eCurrentState = ZFishState::Disappear;
		} 
		else {
			if (hb->position.x < -hb->size.x) eCurrentState = ZFishState::Disappear;
		}
	}
	else if (eCurrentState == ZFishState::BeCaught) {
		if (pZHook != nullptr) {
			if (pZHook->getCurrentState() == ZHook::ZHookState::Idle) {
				eCurrentState = ZFishState::Death;
			}
			else {
				double hookVelocity = pZHook->getLengthVelocity() / deltaTime;
				double hookAngle = pZHook->getAngle();
				hb->velocity = { -(float)(hookVelocity * cos(hookAngle)), -(float)(hookVelocity * sin(hookAngle)) };
			}
		}
	}
}