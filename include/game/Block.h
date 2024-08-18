///
/// The block structure in the Game
///

#pragma once

#include "../EasyXBase.h"
#include<vector>


/// Yeah, that is actually the "block" hitbox
class PBlockHitboxComponents
{
/// TODO
};

/// The basic block class in the paper craft
class PBlock
{
public:
    /// Construct the block with the texture
    /// @param Texture The block's texture pointer
    PBlock(PImage* Texture);
    ~PBlock() = default;

public:
    /// Whether the block is half brick, if the block is half brick,
    /// the hitbox of the block on vertical will be cut by half
    /// @return If the block is half brick, return false, nor true
    virtual bool IsHalfBrick()
    {
        return false;
    }
    /// Whether this block is liquid, the block's hitbox will be changed as
    /// liquid hitbox
    /// @return If the block is liquid, return true, nor return false
    virtual bool IsLiquid()
    {
        return false;
    }
    /// Whether this block is plant, if it is, this block can be destroyed by
    /// water and has only 1 hardness
    /// @return If the block is 
    virtual bool IsPlant()
    {
        return false;
    }

    /// <summary>
    /// """?????""
    /// </summary>
    int GetIdFrame() {
        return id_frame;// ID序列号
    }

    void Hurt() {
        RemoveBlock = true;//受伤状态
    }


    void Removing() {
        //不知道怎么写好
        //TODO
    }



private:
    PImage* _texture;

    /// <summary>
    /// """?????""
    /// </summary>
    bool RemoveBlock;   //方块的状态，这个是指放置时状态，只有方块放置才有效，为true是被移除，
    int id_frame;   //放置方块的序列号
    TCHAR BlockName[128];    //方块的名字
    int BlockBlood;  //方块的血量?,你可以改为你跟喜欢的名字
    bool RemovingBlock;  //方块是否正在被移除

};