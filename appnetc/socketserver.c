
#include "include/aeserver.h"
aeServer* serv;

void appnetServerOnRecv( aeServer* s , aeConnection *c , char* buff , int len );
void appnetServerOnClose( aeServer* s , aeConnection *c );
void appnetServerOnConnect( aeServer* s , int fd );
aeServer* appnetTcpServInit( char* listen_ip , int port  );

void appnetServerOnRecv( aeServer* serv , aeConnection *conn , char* buff , int len )
{
	 printf( "PHPD len=%d,recv=[%s] \n" , len ,buff ); 
	 char* send_buff = "ww";
	 
	 serv->send( conn->fd , send_buff , strlen( send_buff ));
//	 serv->close( conn->fd );
}

void appnetServerOnClose( aeServer* s , aeConnection *c )
{
      printf( "PHPD close fd=%d,threadid=%d\n" , c->fd,pthread_self() );
}

void appnetServerOnConnect( aeServer* s , int fd )
{
     printf( "PHPD New Client Connected fd=%d,threadid=%d \n", fd,pthread_self()   );
     char* buff = "connect ok!"; 
}


aeServer* appnetTcpServInit( char* listen_ip , int port  )
{
     serv = aeServerCreate( listen_ip , port );

	 //回调改为从reactor线程中回调，如果加上worker后，在worker中回调。
     serv->onConnect = 	&appnetServerOnConnect;
     serv->onRecv = 	&appnetServerOnRecv;
     serv->onClose = 	&appnetServerOnClose;
     return serv;
}

void appnetTcpServRun()
{
     serv->runForever( serv );
}

int main()
{
  appnetTcpServInit( "0.0.0.0" , 3011 );
  appnetTcpServRun();
return 0;
}
