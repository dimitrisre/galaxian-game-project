#include "Animation.h"
#include <fstream>
#include "basics.h"
#include "BitmapLoader.h"

const std::list<frame_t>& FrameListAnimation::GetFrames(void)const{return frames;}

void FrameListAnimation::SetFrames (const std::list<frame_t>& f) { frames.clear(); frames = f; }

Animation* FrameListAnimation::Clone (animid_t newId) const {
	return new FrameListAnimation(
	    frames, GetDx(), GetDy(), GetDelay(), GetContinuous(), newId,0);
}

FrameListAnimation::FrameListAnimation (
	const std::list<frame_t>& _frames, 
	offset_t dx, offset_t dy, delay_t d, bool c, animid_t id,frame_t _noFrames
    ): frames(_frames), MovingAnimation(dx, dy, d, c, id){currFrame = 0; noFrames = _noFrames;
}

unsigned int FrameListAnimation::GetNoFrames(void){
    return noFrames;
}

frame_t FrameListAnimation::GetCurrFrame(void){
        return currFrame;
}

void FrameListAnimation::SetCurrFrame(frame_t t){
     currFrame=t;
}
