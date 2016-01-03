#include "Animation.h"
#include <fstream>
#include "basics.h"
#include "BitmapLoader.h"


//animationFilm routine implementation
byte AnimationFilm::GetTotalFrames (void) 	const { 
	return boxes.size(); 
}

BITMAP* AnimationFilm::GetBitmap (void) const { 
	return bitmap; 
}

const std::string AnimationFilm::GetId (void) const { 
	return id; 
}

const Rect	AnimationFilm::GetFrameBox (byte frameNo) const {
	assert(boxes.size()>frameNo); return boxes[frameNo]; 
}

AnimationFilm::AnimationFilm (BITMAP* film, const std::vector<Rect> boxes, const std::string& id) {
	this->bitmap = film;
	this->boxes = boxes;
	this->id = id;
}

void AnimationFilm::DisplayFrame (BITMAP* dest, int at_x, int at_y, byte frameNo) const {
	Rect area = GetFrameBox(frameNo);
	masked_blit(this->bitmap, dest, area.getX1(), area.getY1(), at_x, at_y, area.getWidth(), area.getHeight());
}


//AnimationFilmHolder routine implemantaion 

AnimationFilm* AnimationFilmHolder::GetFilm (const std::string id) const {
	FilmMap::const_iterator i = filmMap.find(id);
	assert(i!=filmMap.end());
	return &(*i->second);
}

AnimationFilmHolder::AnimationFilmHolder (const char* path,BitmapLoader* b) // Decoder constructor.
{
	ifstream infile, boxfile;
	infile.open("films.txt");
	int numFilms=-1; 
	string filmFile; int filmFrames; string filmBoxes;

	infile >> numFilms;
	cout << numFilms;

	int i;
	for (i=0;i<numFilms;i++) {
		cout <<"\n"<< "film " << i;
		infile >> filmFile; infile >> filmFrames; infile >> filmBoxes;
		cout <<"\n"<< filmFile; cout << " ";
		cout << filmFrames; cout << " ";
		cout << filmBoxes; cout << " ";
		
		cout <<"\n"<<"Reading bounding boxes from "<<filmBoxes <<"\n";
		boxfile.open(filmBoxes.c_str());
		vector<Rect> boundingBoxes;
		boundingBoxes.clear();
		while (!boxfile.eof()) {
			int x1=-1,y1=-1,x2=-1,y2=-1;
			
			boxfile >> x1; boxfile >> y1; 
			boxfile >> x2; boxfile >> y2;
			cout << "\n" << x1 << " " << y1 << " " << x2 << " " << y2;
			boundingBoxes.push_back(Rect(x1,y1,x2,y2));
		}
		cout << "Read boxes";
		boxfile.close();
		boxfile.clear();
	
    	AnimationFilm* filmLoaded = new AnimationFilm(b->Load(filmFile.c_str())
									/*load_bitmap(filmFile.c_str(), NULL)*/,boundingBoxes, filmFile.c_str());
		
		
        filmMap.insert(make_pair(filmLoaded->GetId(), filmLoaded));
	}
	infile.close();

}

AnimationFilmHolder::~AnimationFilmHolder(){ 
	filmMap.clear(); 
	delete[] filmMem; 
}


animid_t Animation::GetId (void) { return id;}
Animation::Animation (animid_t _id) : id(_id){}

offset_t	MovingAnimation::GetDx (void) const { return dx; }
void	    MovingAnimation::SetDx (offset_t v) { dx = v; }
offset_t  	MovingAnimation::GetDy (void) const { return dy; }
void	    MovingAnimation::SetDy (offset_t v) { dy = v; }
delay_t   	MovingAnimation::GetDelay (void) const { return delay; }
void	    MovingAnimation::SetDelay (delay_t v) { delay = v; }
bool		MovingAnimation::GetContinuous (void) const { return continuous; }
void	 	MovingAnimation::SetContinuous (bool v) { continuous = v; }
Animation* MovingAnimation::Clone (animid_t newId) const
    { return new MovingAnimation(dx, dy, delay, continuous, newId); }
MovingAnimation::MovingAnimation (
	offset_t _dx, offset_t _dy, delay_t _delay, bool c, animid_t _id
): dx(_dx), dy(_dy), delay(_delay), continuous(c), Animation(_id){}


void Animator::Stop (void) {
	if (!HasFinished()) {
		state = ANIMATOR_STOPPED;
		NotifyStopped();
	}
}

bool Animator::HasFinished (void) const{ 
	return state != ANIMATOR_RUNNING; 
}

void Animator::NotifyStopped (void) {
	if (onFinish)
		(*onFinish)(this, finishClosure);
}

void Animator::SetOnFinish (FinishCallback f, void* c) { 
	onFinish = f, finishClosure = c; 
}

void Animator::TimeShift (timestamp_t offset){ 
	lastTime += offset; 
}

Animator::Animator (void):
    lastTime(0), state(ANIMATOR_FINISHED), 
    onFinish((FinishCallback) 0), finishClosure((void*) 0){
}





