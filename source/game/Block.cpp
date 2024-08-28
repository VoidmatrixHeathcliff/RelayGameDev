#include "../../include/game/Block.h"
void PBlock::draw(const RenderInfo& renderInfo) {
	//if (block_assets[(int)blockname] == nullptr) {
	if (_Texture == nullptr) {
		setfillcolor(BLACK);
		setlinecolor(LIGHTGRAY);
		setlinestyle(PS_SOLID, 3);
		float scale = renderInfo.scale;
		fillrectangle((int)(scale * hb->position.x),
			(int)(scale * hb->position.y),
			(int)(scale * (hb->position.x + hb->size.x)),
			(int)(scale * (hb->position.y + hb->size.y)));
	}
	else {
		_Texture->Move(hb->position.x * 40, hb->position.y * 40);
		_Texture->OnDraw();
		/*
		block_assets[(int)blockname]->Move(hb->position.x * 40, hb->position.y * 40);
		block_assets[(int)blockname]->OnDraw();
		*/
		
	}
}


