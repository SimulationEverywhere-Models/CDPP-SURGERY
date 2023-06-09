/*******************************************************************
*
*  DESCRIPTION: Atomic Model Server (use a distributin)
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
#include <math.h>        // fabs( ... )
#include "server.h"           // base header
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator
#include "strutil.h"       // str2float( ... )

/*******************************************************************
* Function Name: Server
* Description: constructor
********************************************************************/
Server::Server( const string &name )
: Atomic( name )
, in( addInputPort( "in" ) )
 ,out( addOutputPort( "out" ) )
, ready( addOutputPort( "ready" ) )
{
	try
	{
		dist = Distribution::create( MainSimulator::Instance().getParameter( description(), "distribution" ) );

		MASSERT( dist );

		for ( register int i = 0 ; i < dist->varCount() ; i++ )
		{
			string parameter( MainSimulator::Instance().getParameter( description(), dist->getVar(i) ) ) ;
			dist->setVar( i, str2float( parameter ) ) ;
		}
	} catch( InvalidDistribution &e )
	{
		e.addText( "The model " + description() + " has distribution problems!" ) ;
		e.print(cerr);
		MTHROW( e ) ;
	} catch( MException &e )
	{
		MTHROW( e ) ;
	}
}

/*******************************************************************
* Function Name: initFunction
* Description: the Server receives one job
********************************************************************/
Model &Server::initFunction( )
{
	passivate();
                
	// sendOutput( Time("00:00:00:00"), ready,  1000);
	return *this ;
}



/*******************************************************************
* Function Name: externalFunction
* Description: the Server receives one job
********************************************************************/
Model &Server::externalFunction( const ExternalMessage &msg )
{         if( msg.port() == in && msg.value()!=0 ){
	pid = static_cast< int >( msg.value() ) ;
	holdIn( active, Time( static_cast<float>( fabs( distribution().get() ) ) ) ) ;
            }
            if( msg.port() == in  && msg.value()==0){
                   holdIn( active, Time( "00:00:05:00 ")
);                        sendOutput(msg.time(), ready,1000);           
         }
        return *this ;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &Server::internalFunction( const InternalMessage & )
{
	passivate();
	return *this;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &Server::outputFunction( const InternalMessage &msg )
{   
	sendOutput( msg.time(), out, pid );
                 sendOutput( msg.time(), ready ,1000);
    
	return *this;
}


Server::~Server()
{
	delete dist;
}
