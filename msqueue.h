/*******************************************************************
*
*  DESCRIPTION: Atomic Model MSQueue
*
*  AUTHOR: Amir Barylko & Jorge Beyoglonian 
*
*  EMAIL: mailto://amir@dc.uba.ar
*         mailto://jbeyoglo@dc.uba.ar
*
*  DATE: 27/6/1998
*
*******************************************************************/

#ifndef __QUEUE_H
#define __QUEUE_H

#include <list>
#include "atomic.h"     // class Atomic

class MSQueue : public Atomic
{
public:
	MSQueue( const string &name = "MSQueue" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &in;
	//const Port &stop;
	const Port &next;
	Port &out;
	Time preparationTime;
	typedef list<Value> ElementList ;
	ElementList elements ;

	Time timeLeft;

};	// class MSQueue

// ** inline ** // 
inline
string MSQueue::className() const
{
	return "MSQueue" ;
}

#endif   //__QUEUE_H
