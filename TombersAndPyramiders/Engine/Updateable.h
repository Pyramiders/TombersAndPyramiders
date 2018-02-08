#pragma once

/*
Base class for all objects that want to have update methods and follow an
OnStart()
OnUpdate()
OnEnd()
pattern.
*/
class Updateable
{
public:
	virtual void onStart() = 0;
	virtual void onUpdate(int ticks) = 0;
	virtual void onEnd() = 0;
};