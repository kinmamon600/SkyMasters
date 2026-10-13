#ifndef _COMPONENT_H
#define _COMPONENT_H

class Component
{
public:
	virtual ~Component() = default;

	virtual void Update(){}
	virtual void Draw(){}

	
};

#endif
