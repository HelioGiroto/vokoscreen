
#include "QvkAlsaWatcher.h" 


using namespace std;


QvkAlsaWatcher::QvkAlsaWatcher()
{
    AlsaCardCounter = -1;
    QTimer *timer = new QTimer( this );
    connect( timer, SIGNAL( timeout() ), this, SLOT( AlsaWatcherTimer() ) );
    timer->start( 500 );
}


QvkAlsaWatcher::~QvkAlsaWatcher()
{
}


void QvkAlsaWatcher::AlsaWatcherTimer()
{
   register int  err;
   int           cardNum;
   cardNum = -1;
   QStringList cardList;
   for (;;)
   {
      if ( ( err = snd_card_next( &cardNum ) ) < 0 )
      {
         printf( "Can't get the next card number: %s\n", snd_strerror( err ) );
         break;
      }
      else
      {
	if ( cardNum > -1 ) 
	  cardList.append( "card" + QString::number( cardNum ) );
      }
      
      if ( cardNum < 0 ) break;
   }
   
   if ( AlsaCardCounter != cardList.count() )
   {
      AlsaCardCounter = cardList.count() ;
      emit changed( cardList );
   }
}

