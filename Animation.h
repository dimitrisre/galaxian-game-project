#pragma once
#include "basics.h"
#include "Rect.h"
#include "BitmapLoader.h"

typedef signed char	offset_t;
typedef unsigned short	delay_t;
typedef unsigned short	animid_t;
typedef unsigned short frame_t;

class AnimationFilm {
    vector<Rect> boxes;
    BITMAP*	bitmap;
    string	id;

    public:
		byte GetTotalFrames (void) const;
		BITMAP*	GetBitmap (void) const; 
		const std::string GetId (void) const;
		const Rect GetFrameBox (byte frameNo) const;
		void DisplayFrame (BITMAP* d, int at_x,int at_y, byte frameNo) const;
		AnimationFilm (BITMAP*, const std::vector<Rect>, const std::string&);
};

class AnimationFilmHolder {
    typedef std::map<std::string, AnimationFilm*> FilmMap;
    FilmMap	filmMap;
    AnimationFilm* filmMem; // All films allocated as array

    public:
		AnimationFilm* GetFilm (const std::string id) const;
		AnimationFilmHolder (const char* path,BitmapLoader* b); // Decoder constructor.
		~AnimationFilmHolder();
};

class Animation  {
	animid_t id;

	public:
		animid_t GetId (void);
		virtual Animation* Clone (animid_t newId) const = 0;
		Animation (animid_t _id);
		virtual ~Animation() {}
};

class MovingAnimation : public Animation {
    offset_t dx, dy;
    delay_t	delay;
    bool continuous;

	public:
		offset_t GetDx (void) const;
		void	 SetDx (offset_t v);
		offset_t GetDy (void) const;
		void	 SetDy (offset_t v);
		delay_t  GetDelay (void) const;
		void	 SetDelay (delay_t v);
		bool	 GetContinuous (void) const;
		void	 SetContinuous (bool v); 
		Animation* Clone (animid_t newId) const;
		MovingAnimation (
			offset_t _dx, offset_t _dy, delay_t _delay, bool c, animid_t _id
		);
};

class FrameListAnimation : public MovingAnimation {
        std::list<frame_t> frames;
        frame_t currFrame;
        unsigned int noFrames;
        
        public:
                const std::list<frame_t>& GetFrames (void) const;
                void SetFrames (const std::list<frame_t>& f);
                unsigned int GetNoFrames(void);
                frame_t GetCurrFrame(void);
                void SetCurrFrame(frame_t t);
                Animation* Clone (animid_t newId) const; 
                FrameListAnimation (const std::list<frame_t>& _frames, 
    	                           offset_t dx, offset_t dy, delay_t d, bool c, animid_t id,frame_t _noFrames);
};

struct PathEntry {
    offset_t 	dx, dy;
    frame_t 	frame;
    delay_t	delay;
    PathEntry (void) : dx(0), dy(0), frame(0xff), delay(0){}
    PathEntry (const PathEntry& p) :
	dx(p.dx), dy(p.dy), frame(p.frame),delay(p.delay){}
};

class MovingPathAnimation : public MovingAnimation {
	std::list<PathEntry> path;
    bool continuous;
	int curPath;
public:
    const std::list<PathEntry>& GetPath (void) const;
	
    void SetPath (const std::list<PathEntry>& p);

    Animation* Clone (animid_t newId) const;
	
	int GetCurPath(void);
	
	void SetCurPath(int _curPath);
	
    MovingPathAnimation (const std::list<PathEntry>& _path, animid_t id, bool c,int _curPath);
};


typedef unsigned long timestamp_t;

enum animatorstate_t {
	ANIMATOR_FINISHED	= 0,
	ANIMATOR_RUNNING	= 1,
	ANIMATOR_STOPPED	= 2
};

class Animator {

	public:
		typedef void (*FinishCallback)(Animator*,void*);

	protected:
		timestamp_t		lastTime;
		animatorstate_t		state;
		FinishCallback		onFinish;
		void*			finishClosure;
		void NotifyStopped (void);

	public:
		void Stop (void);
		bool HasFinished (void) const; 
		virtual void TimeShift (timestamp_t offset);
		virtual void Progress (timestamp_t currTime)=0;
		void SetOnFinish (FinishCallback f, void* c); 
		
		Animator (void); 
		virtual ~Animator(){};
};
