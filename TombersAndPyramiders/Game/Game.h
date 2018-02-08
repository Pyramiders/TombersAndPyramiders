#include "Updateable.h"

class Game : public Updateable
{
public:
	void onStart();
	void onUpdate(int ticks);
	void onEnd();
};