/*******************************************************************
*
*  DESCRIPTION: Atomic Model MAQueue
*
*  AUTHOR: Amir Barylko & Jorge Beyoglonian 
*
*  EMAIL: mailto://amir@dc.uba.ar
*         mailto://jbeyoglo@dc.uba.ar
*
*  DATE: 27/6/1998
*
*******************************************************************/

/** include files **/
#include "msqueue.h"      // class MSQueue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: MSQueue
* Description: 
********************************************************************/
MSQueue::MSQueue( const string &name )
: Atomic( name )
, in( addInputPort( "in" ) )
, next( addInputPort( "next" ) )
, out( addOutputPort( "out" ) )
, preparationTime( 0, 0, 5, 0 )
{
	string time( MainSimulator::Instance().getParameter( description(), "preparation" ) ) ;

	if( time != "" )
		preparationTime = time ;
}

/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &MSQueue::initFunction()
{
	elements.erase( elements.begin(), elements.end() ) ;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &MSQueue::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == in )
	{
		elements.push_back( msg.value() ) ;
		if( elements.size() == 1 )
			holdIn( active, preparationTime );
	}

	if( msg.port() == next)
	{
	
			holdIn( active, preparationTime );
                                
                       
	}

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &MSQueue::internalFunction( const InternalMessage & )
{
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &MSQueue::outputFunction( const InternalMessage &msg )
{            if(elements.empty())
                     sendOutput(msg.time(), out,  0);
              else{
	      sendOutput( msg.time(), out, elements.front() ) ;
                      elements.pop_front() ;
                  }
	return *this ;
}
