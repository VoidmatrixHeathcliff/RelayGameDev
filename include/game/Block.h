///
/// The block structure in the Game(游戏中的区块结构)
///

#pragma once

#include "../EasyXBase.h"
#include"./collision/Hitbox.h"
#include<vector>
#include"collision/CollisionManager.h"
#include"../render/RenderInfo.h"
#include "../gui/ImageLabel.h"




/// Yeah, that is actually the "block" hitbox
class PBlockHitboxComponents {
	/// TODO
};

/// The basic block class in the paper craft(paper craft中的基本方块类)
class PBlock {
public:
	/// Construct the block with the texture		(用纹理构建方块)
	/// @param Texture The block's texture pointer	(纹理块的纹理指针)
	//	PBlock(BlockType Texture, const Vec2& position) { //--杭：如果打算用枚举来生成对应方块图片可以试试
		PBlock(PImageLabel* Texture, const Vec2& position) {
			_Texture = Texture;

		hb = PGetSingleton<CollisionManager>().createHitbox();
		hb->type = HitboxType::Static;
		hb->size = { 1.f,1.f };
		hb->position = position;
		hb->addLayerDst(CollisionLayer::EnemyLayer);
		hb->addLayerDst(CollisionLayer::PlayerLayer);
		hb->layerSrc = CollisionLayer::BlockLayer;
	}
	~PBlock() = default;

public:
	/// Whether the block is half brick, if the block is half brick,(方块是否是半砖，如果方块是半砖)
	/// the hitbox of the block on vertical will be cut by half		(垂直方向上的方块将被切成两半)
	/// @return If the block is half brick, return false, nor true	(如果方块是半砖，则返回false，否则返回true)
	virtual bool IsHalfBrick() {
		return false;
	}
	/// Whether this block is liquid, the block's hitbox will be changed as
	/// liquid hitbox													(无论此方块是否为液体，方块的hitbox都将更改为液体hitbox)
	/// @return If the block is liquid, return true, nor return false	(如果方块是液体，则返回true，否则返回false)
	virtual bool IsLiquid() {
		return false;
	}
	/// Whether this block is plant, if it is, this block can be destroyed by
	/// water and has only 1 hardness	(这个方块是否是植物，如果是，这个块会被水破坏，硬度只有1)
	/// @return If the block is			(如果方块是植物，则返回true，否则返回false)
	virtual bool IsPlant() {
		return false;
	}

	int GetIdFrame() const {
		return id_frame;// ID序列号
	}

	void Hurt() {
		//isRemoved = true;//受伤状态
	}

	void Removing() {
		//不知道怎么写好
		//TODO
	}

	virtual void draw(const RenderInfo& renderInfo);

	virtual void update(float deltaTime) {}

private:
	//std::vector<PImageLabel*> block_assets;
	PImageLabel* _Texture;

	bool isRemoved = false;				 //方块的状态，这个是指放置时状态，只有方块放置才有效，为true是被移除，
	int id_frame;						 //放置方块的序列号
	TCHAR blockName[128];				 //方块的名字
	int blockHealth = 10;			     //方块的血量?,你可以改为你跟喜欢的名字
	bool isBeingRemoved = false;		 //方块是否正在被移除
	//BlockType blockname;				 //方块的名字

	Hitbox* hb;							 //方块的碰撞箱

};