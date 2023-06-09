/*******************************************************************
*
*  DESCRIPTION: class Server (processes jobs with a specified
*               distribution)
*
*  AUTHOR: Amir Barylko & Jorge Beyoglonian 
*
*  EMAIL: mailto://amir@dc.uba.ar
*         mailto://jbeyoglo@dc.uba.ar
*
*  DATE: 27/6/1998
*
*******************************************************************/

#ifndef __Server_H
#define __Server_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
class Distribution ;

/** declarations **/
class Server: public Atomic
{
public:
	Server( const string &name = "Server" ) ;	 // Default constructor

	~Server();					// Destructor

	virtual string className() const
		{return "Server";}

protected:
	Model &initFunction();
		//{return *this;}

	Model &externalFunction( const ExternalMessage & );

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage & );

private:
	const Port &in ;
	
                Port &out ;
                Port &ready;
	Distribution *dist ;
	int pid ;

	Distribution &distribution()
			{return *dist;}
};	// class Server


#endif   //__Server_H 
