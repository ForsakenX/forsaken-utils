

#define INITGUID

//
//  Headers
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

//
//  Windows & Direct Play Headers
//

#include <windowsx.h>
#include <objbase.h>
#include <cguid.h>
#include "dplay.h"
#include "dplobby.h"

//
//  Forsaken Message Formats
//
		
#define MSG_UPDATE					0x11 //
#define MSG_HEREIAM					0x22 //
#define MSG_INIT					0x33 //
#define MSG_SHIPHIT					0x44 //
#define MSG_PRIMBULLPOSDIR			0x55 //
#define MSG_SECBULLPOSDIR			0x66 //
#define MSG_SHIPDIED				0x77 //
#define MSG_DROPPICKUP				0x88 //
#define MSG_KILLPICKUP				0x99 //
#define MSG_SHORTSTATS				0xaa //
#define MSG_STATUS					0xbb //
#define MSG_EXPSECONDARY			0xcc //
#define MSG_SHORTPICKUP				0xee
#define MSG_SHOCKWAVE				0xff
#define MSG_FUPDATE					0x1f
#define MSG_SHORTMINE				0x2f
#define MSG_TEXTMSG					0x3f
#define MSG_SHORTREGENSLOT			0x4f
#define MSG_SHORTTRIGGER			0x5f
#define MSG_SHORTTRIGVAR			0x6f
#define MSG_NAME					0x7f
#define MSG_INTERPOLATE				0x8f
#define MSG_BOMB					0x9f
#define MSG_BGOUPDATE				0xaf
#define MSG_PINGREQUEST				0xbf
#define MSG_PLAYERPINGS				0xbe
#define MSG_PINGREPLY				0xcf
#define MSG_LONGSTATUS				0xdf
#define MSG_SETTIME					0xef
#define MSG_REQTIME					0xf1
#define MSG_ACKMSG					0xf2
#define MSG_GUARANTEEDMSG			0xf3
#define MSG_KILLSDEATHSBIKENUM		0xf4
#define MSG_VERYSHORTUPDATE			0xf5
#define MSG_VERYSHORTFUPDATE		0xf6
#define MSG_ALIVE					0xf7
#define MSG_VERYSHORTINTERPOLATE	0xf8
#define MSG_TEAMGOALS				0xf9
#define MSG_YOUQUIT					0xfa //
#define MSG_SENDKILLSDEATHSBIKENUM	0xfb
#define MSG_SHORTSHIPHIT			0xfc
#define MSG_TITANBITS				0xfd
#define MSG_BIGPACKET				0xfe
#define MSG_SERVERUPDATE			0xe1
#define MSG_GAMEPARAMETERS			0xe2
#define MSG_SESSIONDESC				0xe3
#define MSG_TOSERVER				0xe4
#define MSG_SERVERKILLPICKUP		0xe5 //
#define MSG_SERVERSAYSSHIPDIED		0xe6 //
#define MSG_LEVELNAMES				0xe7 //
#define MSG_EXPLODESHIP				0xe8 //
#define MSG_SHIELDHULL				0xe9 //
#define MSG_SERVERSCORED			0xea //
#define MSG_TRACKERINFO				0xe0 //
#define MSG_TOCLIENT				0xeb //
#define MSG_GROUPONLY_VERYSHORTFUPDATE		0xec  //
#define MSG_VERYSHORTDROPPICKUP				0xed  //

//
//  Forsaken Message Structures
//

// Typedef.h
typedef	unsigned short int	uint16;			/* Unsigned 16 Bit Integer */

typedef struct _STATUSMSG
{
    BYTE        MsgCode;
    BYTE        WhoIAm;
	BOOL		IsHost;
	BYTE		Status;
	BYTE		TeamNumber;
	uint16		TeamScore;		// if leaving game, used to propagate my score to another team member
	BOOL		IAmReady;		// used for team game - game cannot start until everyone is ready
	BYTE		Pickups;		// tells how much of the pickup list I have recieved..
	BYTE		RegenSlots;		// tells how much of the pickup regen slots list I have recieved..
	BYTE		Mines;			// tells how much of the mine list I have recieved..
	BYTE		Triggers;		// tells how much of the mine list I have recieved..
	BYTE		TrigVars;		// tells how much of the mine list I have recieved..
	float		PacketsPerSecond;
	LONGLONG	LevelCheckSum;
} STATUSMSG, *LPSTATUSMSG;

// Mydplay.h
#define	MAXTEXTMSG			128		// the number of chars in a message you can send.....

typedef struct _TEXTMSG
{
    BYTE        MsgCode;
    BYTE        WhoIAm;
	char		Text[MAXTEXTMSG];
	BYTE		TextMsgType;
} TEXTMSG, *LPTEXTMSG;

//
// Forsaken Status Messages
//

#define STATUS_PlayingAVI					0x01	// Playing AVI
#define	STATUS_Title						0x02	// On the Title Screen...
#define	STATUS_Copyright					0x03	// On the Copyright Screen...
#define	STATUS_StartingMultiplayer			0x04	// On the Multiplayer Starting Screen...
#define	STATUS_PreStartingMultiplayerSynch	0x05	// Waiting for everyone to have loaded the right level and be ready
#define	STATUS_StartingMultiplayerSynch		0x06	// Waiting for everyone to have loaded the right level and be ready
													// to Start...
#define	STATUS_QuitCurrentGame				0x07	// About to quit a game and return to the title screen..
#define	STATUS_GetPlayerNum					0x08	// Trying to aquire a Player Number...
#define	STATUS_PlayingDemo					0x09	// Playing Back a Demo...
#define	STATUS_Normal 						0x0a	// normal in game...
#define	STATUS_LevelEnd						0x0b	// the level has ended tell the host I know the level has ended...
#define	STATUS_BetweenLevels    			0x0c	// in title room between levels

#define	STATUS_ViewingScore					0x0d	// tell the host I am looking at the Score....
#define	STATUS_WaitingAfterScore			0x0e	// waiting for other players or waitng for the host to start...
#define	STATUS_Joining						0x0f	// I Want to join your game....
#define	STATUS_Left							0x10	// I have left your game...
#define	STATUS_ChangeLevelPostInitView		0x11	// after a change level init view
#define	STATUS_ChangeLevelPostPlayingDemo	0x12	// after a change level Playing Demo...
#define	STATUS_ChangeLevelPostAttractMode	0x13	// after a change level Attract Mode...
#define	STATUS_AttractMode					0x14	// Playing Back a Demo In Attract Mode...
											
#define	STATUS_StartingSinglePlayer			0x20	// Starting Single Player in game...
#define	STATUS_PostStartingSinglePlayer		0x21	// Starting Single Player in game after the level has been loaded...
#define	STATUS_SinglePlayer					0x22	// Single Player in game...
#define	STATUS_ViewingStats					0x23	// Viewing Stats Single Player...

#define	STATUS_TitleLoadGameStartingSinglePlayer		0x24
#define	STATUS_TitleLoadGamePostStartingSinglePlayer	0x25
#define	STATUS_ChangeLevelPostLoadGame	0x26
#define	STATUS_InGameLoadGameStartingSinglePlayer		0x27

#define	STATUS_WaitingToStartSinglePlayer		0x30	// waiting to start single player game...
#define	STATUS_WaitingToStartMultiPlayerHost	0x31	// waiting to start multi player game for host...
#define	STATUS_WaitingToStartMultiPlayerClient	0x32	// waiting to start multi player game for client...
#define	STATUS_WaitingToStartTeamGame			0x33	// waiting to start multi player game for client...
#define STATUS_QuittingFromTitles				0x34	// quitting game from title screen
#define STATUS_WaitingToStartDemo				0x35	// waiting to start demo
#define STATUS_WaitingToStartEndGameSequence	0x36	// waiting to start end of game demo playback sequence

#define STATUS_WaitingForLobbyConnect			0x37	// waiting for host to select game info in lobby launched game
#define STATUS_QuittingFromInGame				0x38	// quitting completely after stats ( ie. when playing lobby launched game )

#define	STATUS_SplashScreen					0x40	// showing splash screen or AVI...
#define STATUS_FinishedShowingSplashScreen	0x41	// finished showing current splash screen;


#define	STATUS_DisabledByServer				0x50	// Disabled by the Server


#define	STATUS_InitView_0					0x80	// 0 of Preping for a level..
#define	STATUS_InitView_1					0x81	// 1 of Preping for a level..
#define	STATUS_InitView_2					0x82	// 2 of Preping for a level..
#define	STATUS_InitView_3					0x83	// 3 of Preping for a level..
#define	STATUS_InitView_4					0x84	// 4 of Preping for a level..
#define	STATUS_InitView_5					0x85	// 5 of Preping for a level..
#define	STATUS_InitView_6					0x86	// 6 of Preping for a level..
#define	STATUS_InitView_7					0x87	// 7 of Preping for a level..
#define	STATUS_InitView_8					0x88	// 8 of Preping for a level..
#define	STATUS_InitView_9					0x89	// 9 of Preping for a level..
#define	STATUS_InitView_10					0x8a	// 10 of Preping for a level..
											
#define STATUS_WaitingToSendMessages		0xfa	// waiting until all guaranteed messages sent before continuing
#define STATUS_GetLevelNames				0xfb	// Pseudo host is recieving level names from server
#define STATUS_PseudoHostWaitingForAck		0xfc	// Pseudo host waiting for acknowledgement of game parameters from server
#define	STATUS_TurnedOffByServer			0xfd	// The Server has decided I dont need to know about this player...
#define	STATUS_LeftCrashed					0xfe	// I have left and crashed...
#define	STATUS_Null							0xff	// Im not doing anything yet...
#define STATUS_TryingToFindSession			0xf9

const char * StatusDesc( BYTE status )
{
	switch( status )
	{
		case STATUS_PlayingAVI:
			return "Playing AVI...";
		break;
		case STATUS_Title:
			return "On the Title Screen...";
		break;
		case STATUS_Copyright:
			return "On the Copyright Screen...";
		break;
		case STATUS_StartingMultiplayer:
			return "On the Multiplayer Starting Screen...";
		break;
		case STATUS_PreStartingMultiplayerSynch:
			return "Waiting for everyone to have loaded the right level and be ready...";
		break;
		case STATUS_StartingMultiplayerSynch:
			return "Waiting for everyone to have loaded the right level and be ready to Start...";
		break;
		case STATUS_QuitCurrentGame:
			return "About to quit a game and return to the title screen...";
		break;
		case STATUS_GetPlayerNum:
			return "Trying to aquire a Player Number...";
		break;
		case STATUS_PlayingDemo:
			return "Playing Back a Demo...";
		break;
		case STATUS_Normal:
			return "Normal in game...";
		break;
		case STATUS_LevelEnd:
			return "The level has ended tell the host I know the level has ended...";
		break;
		case STATUS_BetweenLevels:
			return "In title room between levels...";
		break;
		case STATUS_ViewingScore:
			return "Tell the host I am looking at the Score....";
		break;
		case STATUS_WaitingAfterScore:
			return "Waiting for other players or waitng for the host to start...";
		break;
		case STATUS_Joining:
			return "Want to join your game....";
		break;
		case STATUS_Left:
			return "I have left your game...";
		break;
		case STATUS_ChangeLevelPostInitView:
			return "After a change level init view...";
		break;
		case STATUS_ChangeLevelPostPlayingDemo:
			return "After a change level Playing Demo...";
		break;
		case STATUS_ChangeLevelPostAttractMode:
			return "after a change level Attract Mode...";
		break;
		case STATUS_AttractMode:
			return "Playing Back a Demo In Attract Mode...";
		break;		
		case STATUS_StartingSinglePlayer:
			return "Starting Single Player in game...";
		break;
		case STATUS_PostStartingSinglePlayer:
			return "Starting Single Player in game after the level has been loaded...";
		break;
		case STATUS_SinglePlayer:
			return "Single Player in game...";
		break;
		case STATUS_ViewingStats:
			return "Viewing Stats Single Player...";
		break;
		case STATUS_TitleLoadGameStartingSinglePlayer:
			return "Title Load Game Starting Single Player...";
		break;
		case STATUS_TitleLoadGamePostStartingSinglePlayer:
			return "Title Load Game Starting Single Player...";
		break;
		case STATUS_ChangeLevelPostLoadGame:
			return "Change Level Post Load Game...";
		case STATUS_InGameLoadGameStartingSinglePlayer:
			return "In Game Load Game Starting Single Player...";
		break;
 		case STATUS_WaitingToStartSinglePlayer:
			return "Waiting to start single player game...";
		break;
		case STATUS_WaitingToStartMultiPlayerHost:
			return "Waiting to start multi player game for host...";
		break;
 		case STATUS_WaitingToStartMultiPlayerClient:
			return "Waiting to start multi player game for client...";
		break;
 		case STATUS_WaitingToStartTeamGame:
			return "Waiting to start multi player game for client...";
		break;
		case STATUS_QuittingFromTitles:
			return "Quitting game from title screen...";
		break;
		case STATUS_WaitingToStartDemo:
			return "Waiting to start demo...";
		break;
		case STATUS_WaitingToStartEndGameSequence:
			return "Waiting to start end of game demo playback sequence...";
		break;
		case STATUS_WaitingForLobbyConnect:
			return "Waiting for host to select game info in lobby launched game...";
		break;
		case STATUS_QuittingFromInGame:
			return "Quitting completely after stats ( ie. when playing lobby launched game )...";
		break;
		case STATUS_SplashScreen:
			return "Showing splash screen or AVI...";
		break;
		case STATUS_FinishedShowingSplashScreen:
			return "Finished showing current splash screen...";
		break;
		case STATUS_DisabledByServer:
			return "Disabled by the Server...";
		break;
		case STATUS_InitView_0:
			return "0 of Preping for a level..";
		break;
		case STATUS_InitView_1:
			return "1 of Preping for a level..";
		break;
		case STATUS_InitView_2:
			return "2 of Preping for a level..";
		break;
		case STATUS_InitView_3:
			return "3 of Preping for a level..";
		break;
		case STATUS_InitView_4:
			return "4 of Preping for a level..";
		break;
		case STATUS_InitView_5:
			return "5 of Preping for a level..";
		break;
		case STATUS_InitView_6:
			return "6 of Preping for a level..";
		break;
		case STATUS_InitView_7:
			return "7 of Preping for a level..";
		break;
		case STATUS_InitView_8:
			return "8 of Preping for a level..";
		break;
		case STATUS_InitView_9:
			return "9 of Preping for a level..";
		break;
		case STATUS_InitView_10:
			return "10 of Preping for a level..";
		break;						
		case STATUS_WaitingToSendMessages:
			return "waiting until all guaranteed messages sent before continuing...";
		break;
		case STATUS_GetLevelNames:
			return "Pseudo host is recieving level names from server...";
		break;
		case STATUS_PseudoHostWaitingForAck:
			return "Pseudo host waiting for acknowledgement of game parameters from server...";
		break;
		case STATUS_TurnedOffByServer:
			return "The Server has decided I dont need to know about this player...";
		break;
		case STATUS_LeftCrashed:
			return "I have left and crashed...";
		break;
		case STATUS_Null:
			return "Im not doing anything yet...";
		break;
		case STATUS_TryingToFindSession:
			return "Trying to find session...";
		break;
		default:
			return "Unknown Status...";
	}
}

//
//  GUID's
//

DEFINE_GUID( MY_SESSION_GUID,
			 0xd559fc00, 0xdc12, 0x11cf, 0x9c, 0x4e, 0x0, 0xa0, 0xc9, 0x5, 0x42, 0x5e );


//
//  Prototypes
//

const char * StatusName( BYTE status );
void WaitForMessage( HANDLE, LPDIRECTPLAY4A );
HRESULT ReceiveMessage( LPDIRECTPLAY4A );
void HandleSystemMessage( LPDIRECTPLAY4A, DPMSG_GENERIC*, DWORD, DPID, DPID );
void HandleApplicationMessage( LPDIRECTPLAY4A, DPMSG_GENERIC*, DWORD, DPID, DPID );
BOOL FAR PASCAL EnumSessionsCallback(const DPSESSIONDESC2*, DWORD*, DWORD, void*);

//
//  Main Block
//

int main (int argc, char **argv)
{

	std::cout << "\n\n";

	HRESULT hr;

	//
	//  Initialize COM
	//

	hr = CoInitialize( NULL );
	if( FAILED(hr) ){
		std::cout << "Failed to initialize COM! \n";
		return 1;
	}

	
	//
	// Direct Play Lobby
	//
		
	LPDIRECTPLAYLOBBY3A pDPLobby = NULL;

	if ( FAILED( hr = CoCreateInstance( CLSID_DirectPlayLobby,
		                                NULL,
										CLSCTX_INPROC_SERVER,
										IID_IDirectPlayLobby3A,
										(VOID**)&pDPLobby ) ) )
	{
		std::cout << "Failed to initialize DirectPlayLobby! \n";
		return 1;
	}

	//
	// Direct Play 4 Interface
	//

	LPDIRECTPLAY4A pDP = NULL;

	hr = CoCreateInstance( CLSID_DirectPlay, NULL, CLSCTX_INPROC_SERVER, IID_IDirectPlay4A, (VOID**)&pDP );

	if ( FAILED( hr ) ){
		std::cout << "Failed to initialize DPlay4! \n";
		return 1;
	}

	
	//
	// Create Address
	//

	void*   pAddress      = NULL;
	DWORD	dwAddressSize = 0;
	DPCOMPOUNDADDRESSELEMENT AddressElements[2];

	AddressElements[0].guidDataType = DPAID_ServiceProvider;
	AddressElements[0].dwDataSize   = sizeof(GUID);
	AddressElements[0].lpData       = (LPVOID)&DPSPGUID_TCPIP;

	AddressElements[1].guidDataType = DPAID_INet;
	AddressElements[1].dwDataSize   = lstrlen("192.168.0.8")+1;
	AddressElements[1].lpData       = (LPSTR) "192.168.0.8";

	hr = pDPLobby->CreateCompoundAddress(  AddressElements, 2, NULL, &dwAddressSize );

	if ( hr != DPERR_BUFFERTOOSMALL ){
		std::cout << "CreateCompoundAddress != DPERR_BUFFERTOOSMALL  \n";
		switch(hr)
		{
			case DPERR_INVALIDPARAMS:
			  std::cout << "CreateCompoundAddress DPERR_INVALIDPARAMS  \n";
			break;
			case DPERR_BUFFERTOOSMALL:
			  std::cout << "CreateCompoundAddress DPERR_BUFFERTOOSMALL \n";
			break;
			case DPERR_INVALIDFLAGS:
			  std::cout << "CreateCompoundAddress DPERR_INVALIDFLAGS \n";
			break;
		}
		return 1;
	}
		
	pAddress = GlobalAllocPtr(GHND, dwAddressSize);

	if( pAddress == NULL ){
	  std::cout << "CreateCompoundAddress DPERR_NOMEMORY \n";
	  return 1;
    }

	hr = pDPLobby->CreateCompoundAddress( AddressElements, 2, pAddress, &dwAddressSize);

	if(FAILED(hr)){
		std::cout << "CreateCompoundAddress != DP_OK  \n";
		switch(hr)
		{
			case DPERR_INVALIDPARAMS:
			  std::cout << "CreateCompoundAddress DPERR_INVALIDPARAMS  \n";
			break;
			case DPERR_BUFFERTOOSMALL:
			  std::cout << "CreateCompoundAddress DPERR_BUFFERTOOSMALL \n";
			break;
			case DPERR_INVALIDFLAGS:
			  std::cout << "CreateCompoundAddress DPERR_INVALIDFLAGS \n";
			break;
		}
		return 1;
	}

	//
	//  Initialize Connection
	//

	hr = pDP->InitializeConnection(pAddress, 0);

	if(FAILED(hr)){
		std::cout << "Could not create a connection to the host... \n";
		switch ( hr ) {
			case DPERR_ALREADYINITIALIZED:
				std::cout << "InitializeConnection DPERR_ALREADYINITIALIZED";
			break;
			case DPERR_INVALIDFLAGS:
				std::cout << "InitializeConnection DPERR_INVALIDFLAGS";
			break;
			case DPERR_INVALIDPARAMS:
				std::cout << "InitializeConnection DPERR_INVALIDPARAMS";
			break;
			case DPERR_UNAVAILABLE:
				std::cout << "InitializeConnection DPERR_UNAVAILABLE \n";
			break;
			default:
				std::cout << "InitializeConnection UnknownError: " << hr << "\n";
		}
		return 1;
	}
	
	std::cout << "Connection established... \n";

	//
	// Enumerate Sessions
	//

	std::vector<DPSESSIONDESC2> sessions;	// holds list of sessions found

	DPSESSIONDESC2 dpsd;
    ZeroMemory( &dpsd, sizeof(DPSESSIONDESC2) );
	dpsd.dwSize          = sizeof(DPSESSIONDESC2);
	dpsd.guidApplication = GUID_NULL;//FORSAKEN;

	while(sessions.size() == 0)
	{

		std::cout << "Enumerating sessions... \n";

		hr = pDP->EnumSessions( &dpsd, 0, EnumSessionsCallback, &sessions, 0 );

		if(FAILED(hr)){
			std::cout << "Failed to Enumerate Sessions... \n";
			switch ( hr ) {
				case DPERR_CONNECTING:
					std::cout << "EnumSessions  DPERR_CONNECTING\n";
				break;
				case DPERR_CONNECTIONLOST:
					std::cout << "EnumSessions DPERR_CONNECTIONLOST \n";
				break;
				case DPERR_EXCEPTION:
					std::cout << "EnumSessions  DPERR_EXCEPTION\n";
				break;
				case DPERR_GENERIC:
					std::cout << "EnumSessions  DPERR_GENERIC\n";
				break;
				case DPERR_INVALIDOBJECT: 
					std::cout << "EnumSessions  DPERR_INVALIDOBJECT\n";
				break;
				case DPERR_INVALIDPARAMS: 
					std::cout << "EnumSessions  DPERR_INVALIDPARAMS\n";
				break; 
				case DPERR_NOCONNECTION:
					std::cout << "EnumSessions DPERR_NOCONNECTION \n";
				break;
				case DPERR_UNINITIALIZED:
					std::cout << "EnumSessions  DPERR_UNINITIALIZED\n";
				break;
				case DPERR_USERCANCEL:
					std::cout << "EnumSessions  DPERR_USERCANCEL\n";
				break;

			}
			return 1;
		}

		if(sessions.size() > 0)
			break;

		printf("No sessions were found on the host... \n");

		Sleep(1000);

	}

	for (int i = 0; i < sessions.size(); i++)
		printf("\t %3d: %s \n", (i+1), sessions[i].lpszSessionNameA);

	//
	// Session Information
	//

	LPDPSESSIONDESC2 sessionInfo;
	sessionInfo = &sessions[0];

	//
	//  Open Session
	//
	
	/*

		To join a session, it is only necessary to fill in
		the dwSize and guidInstance members of the DPSESSIONDESC2
		structure. The lpszPassword member must also be filled in
		if the session was marked as password protected. An
		enumerated session will have the DPSESSION_PASSWORDREQUIRED
		flag set if it requires a password. 
	*/

	hr = pDP->Open( sessionInfo, DPOPEN_JOIN );

	if(FAILED(hr)){
		switch(hr)
		{
			case DPERR_ACCESSDENIED:
				std::cout << "DirectPlay->Open DPERR_ACCESSDENIED";
			break;  
			case DPERR_ALREADYINITIALIZED:
				std::cout << "DirectPlay->Open DPERR_ALREADYINITIALIZED";
			break;  
			case DPERR_AUTHENTICATIONFAILED:
				std::cout << "DirectPlay->Open DPERR_AUTHENTICATIONFAILED";
			break;  
			case DPERR_CANNOTCREATESERVER:
				std::cout << "DirectPlay->Open DPERR_CANNOTCREATESERVER";
			break;  
			case DPERR_CANTCREATEPLAYER:
				std::cout << "DirectPlay->Open DPERR_CANTCREATEPLAYER";
			break; 
			case DPERR_CANTLOADCAPI:
				std::cout << "DirectPlay->Open DPERR_CANTLOADCAPI";
			break;  
			case DPERR_CANTLOADSECURITYPACKAGE:
				std::cout << "DirectPlay->Open DPERR_CANTLOADSECURITYPACKAGE";
			break;  
			case DPERR_CANTLOADSSPI:
				std::cout << "DirectPlay->Open DPERR_CANTLOADSSPI";
			break;  
			case DPERR_CONNECTING:
				std::cout << "DirectPlay->Open DPERR_CONNECTING";
			break;  
			case DPERR_CONNECTIONLOST:
				std::cout << "DirectPlay->Open DPERR_CONNECTIONLOST";
			break;  
			case DPERR_ENCRYPTIONFAILED:
				std::cout << "DirectPlay->Open DPERR_ENCRYPTIONFAILED";
			break;  
			case DPERR_ENCRYPTIONNOTSUPPORTED:
				std::cout << "DirectPlay->Open DPERR_ENCRYPTIONNOTSUPPORTED";
			break;  
			case DPERR_INVALIDFLAGS:
				std::cout << "DirectPlay->Open DPERR_INVALIDFLAGS";
			break;  
			case DPERR_INVALIDPARAMS:
				std::cout << "DirectPlay->Open DPERR_INVALIDPARAMS";
			break;  
			case DPERR_INVALIDPASSWORD:
				std::cout << "DirectPlay->Open DPERR_INVALIDPASSWORD";
			break;  
			case DPERR_LOGONDENIED:
				std::cout << "DirectPlay->Open DPERR_LOGONDENIED";
			break;  
			case DPERR_NOCONNECTION:
				std::cout << "DirectPlay->Open DPERR_NOCONNECTION";
			break;  
			case DPERR_NONEWPLAYERS:
				std::cout << "DirectPlay->Open DPERR_NONEWPLAYERS";
			break;  
			case DPERR_NOSESSIONS:
				std::cout << "DirectPlay->Open DPERR_NOSESSIONS";
			break;  
			case DPERR_SIGNFAILED:
				std::cout << "DirectPlay->Open DPERR_SIGNFAILED";
			break;  
			case DPERR_TIMEOUT:
				std::cout << "DirectPlay->Open DPERR_TIMEOUT";
			break;  
			case DPERR_UNINITIALIZED:
				std::cout << "DirectPlay->Open DPERR_UNINITIALIZED";
			break;  
			case DPERR_USERCANCEL:
				std::cout << "DirectPlay->Open DPERR_USERCANCEL";
			break;
			default:
				std::cout << "DirectPlay->Open Unknown Error";
		}
		return 1;
	}

	std::cout << "Session Opened... \n";

	//
	//  Create Player
	//
	
	DPID PlayerID = NULL;

	DPNAME PlayerName;
    ZeroMemory( &PlayerName, sizeof(DPNAME) );
	PlayerName.dwSize = sizeof(DPNAME);
	PlayerName.lpszShortNameA = "Test";
	PlayerName.lpszLongNameA  = NULL;

	HANDLE  hEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
	if( hEvent == NULL )
    {
		std::cout << "CreateEvent DPERR_NOMEMORY";
        return 1;
    }

	hr = pDP->CreatePlayer( &PlayerID, &PlayerName, hEvent, NULL, 0, 0 );

	if(FAILED(hr)){
		switch(hr)
		{
			case DPERR_CANTADDPLAYER:
				std::cout << "DirectPlay->CreatePlayer DPERR_CANTADDPLAYER";
			break;
			case DPERR_CANTCREATEPLAYER:
				std::cout << "DirectPlay->CreatePlayer DPERR_CANTCREATEPLAYER";
			break;  
			case DPERR_CONNECTIONLOST:
				std::cout << "DirectPlay->CreatePlayer DPERR_CONNECTIONLOST";
			break;  
			case DPERR_INVALIDFLAGS:
				std::cout << "DirectPlay->CreatePlayer DPERR_INVALIDFLAGS";
			break;  
			case DPERR_INVALIDPARAMS:
				std::cout << "DirectPlay->CreatePlayer DPERR_INVALIDPARAMS";
			break;  
			case DPERR_NOCONNECTION:
				std::cout << "DirectPlay->CreatePlayer DPERR_NOCONNECTION";
			break;
			default:
				std::cout << "DirectPlay->CreatePlayer Unknown Error";
		}
		return 1;
	}

	std::cout << "Player Created... \n";

	/*
		See Also:
					DPNAME, DPMSG_CREATEPLAYERORGROUP, IDirectPlay4::DestroyPlayer,
					IDirectPlay4::EnumPlayers, IDirectPlay4::Receive, IDirectPlay4::Send,
					IDirectPlay4::SetPlayerData, IDirectPlay4::SetPlayerName,
					IDirectPlay4::GetPlayerFlags 
	*/
	
	std::cout << "Listening for player messages... \n";

	WaitForMessage( hEvent, pDP );

	return 0;

}




//
//  Enumerate Sessions
//


BOOL FAR PASCAL EnumSessionsCallback(	const DPSESSIONDESC2* pSessionDesc,
										DWORD*				  pdwTimeOut,
										DWORD				  dwFlags,
										void*			      pContext )
{

    if( dwFlags & DPESC_TIMEDOUT )
        return FALSE;
	
	DPSESSIONDESC2 sessionInfo;
	ZeroMemory( &sessionInfo, sizeof(DPSESSIONDESC2) );

	sessionInfo.dwSize           = sizeof(DPSESSIONDESC2);
	sessionInfo.dwFlags          = pSessionDesc->dwFlags;
	sessionInfo.dwMaxPlayers     = pSessionDesc->dwMaxPlayers;
	sessionInfo.dwCurrentPlayers = pSessionDesc->dwCurrentPlayers;
	//sessionInfo.lpszPasswordA    = pSessionDesc->lpszPasswordA;
	sessionInfo.dwReserved1      = 0;
	sessionInfo.dwReserved2      = 0;
	sessionInfo.dwUser1          = 0;
	sessionInfo.dwUser2          = 0;
	sessionInfo.dwUser3          = 0;
	sessionInfo.dwUser4          = 0;

	sessionInfo.guidInstance     = pSessionDesc->guidInstance;
	sessionInfo.guidApplication  = pSessionDesc->guidApplication;

	sessionInfo.lpszSessionNameA = (char*) malloc( (size_t) (lstrlen(pSessionDesc->lpszSessionNameA)+1) );
	if( sessionInfo.lpszSessionNameA == NULL ){
		std::cout << "\n\n Insufficient memory available to copy \n\n";
		return FALSE;
	}else{
		free( sessionInfo.lpszSessionNameA );
		if ( lstrcpy(sessionInfo.lpszSessionNameA, pSessionDesc->lpszSessionNameA) == NULL ) {
			std::cout << "\n\n Buffer was to small to copy into... \n\n";
			return FALSE;
		}
	}

	(*(std::vector<DPSESSIONDESC2>*)pContext).push_back(sessionInfo);

	return TRUE;
}

//
//  WaitForMessage
//

void WaitForMessage( HANDLE hEvent, LPDIRECTPLAY4A pDP )
{
	while( true )
    {

        if( hEvent )
        {
            if( WAIT_TIMEOUT == WaitForSingleObject( hEvent, INFINITE ) )
            {
				std::cout << "There was a timeout waiting for a message... \n";
                break;
            }
        }

		ReceiveMessage( pDP );

    }
}

//-----------------------------------------------------------------------------
// Name: ReceiveMessage()
// Desc:
//-----------------------------------------------------------------------------
HRESULT ReceiveMessage( LPDIRECTPLAY4A pDP )
{
    DPID    idFrom, idTo;
    VOID*   pMsgBuffer      = NULL;
    DWORD   dwMsgBufferSize = 0L;
    HRESULT hr;

    // Loop until all messages are read
	while( true )
	{
		//std::cout << "Loop Start \n";

        // Read messages from any player, including system player
        idFrom = 0;
        idTo   = 0;

        hr = pDP->Receive( &idFrom, &idTo, DPRECEIVE_ALL, pMsgBuffer, &dwMsgBufferSize );
		
		switch(hr)
		{

			// Not enough room, so resize buffer
			case DPERR_BUFFERTOOSMALL:

				//std::cout << "pDP->Receive DPERR_BUFFERTOOSMALL \n";

				if( pMsgBuffer )
					GlobalFreePtr( pMsgBuffer );

				pMsgBuffer = GlobalAllocPtr( GHND, dwMsgBufferSize );
				if( pMsgBuffer == NULL )
					hr = DPERR_OUTOFMEMORY;

				continue;

			break;

			// successfully read a message
			case DP_OK:
				
				// Message is not big enough
				if( dwMsgBufferSize < sizeof(DPMSG_GENERIC) )
					continue;

				// system message
				if( idFrom == DPID_SYSMSG )
				{
					//std::cout << "Recieved System Message... \n";
					HandleSystemMessage( pDP, (DPMSG_GENERIC*)pMsgBuffer,
										 dwMsgBufferSize, idFrom, idTo );
				}

				// application message
				else
				{
					//std::cout << "Recieved Application Message... \n";
					HandleApplicationMessage( pDP, (DPMSG_GENERIC*)pMsgBuffer,
											  dwMsgBufferSize, idFrom, idTo );
				}

			break;

			case DPERR_NOMESSAGES:
				//std::cout << "pDP->Receive DPERR_NOMESSAGES \n";
				return hr;
			break;

			// Real Errors
			default:
				switch(hr)
				{
					case DPERR_GENERIC:
						std::cout << "pDP->Receive DPERR_GENERIC";
					break;  
					case DPERR_INVALIDOBJECT:
						std::cout << "pDP->Receive DPERR_INVALIDOBJECT";
					break;  
					case DPERR_INVALIDPARAMS:
						std::cout << "pDP->Receive DPERR_INVALIDPARAMS";
					break;  
					case DPERR_INVALIDPLAYER:
						std::cout << "pDP->Receive DPERR_INVALIDPLAYER";
					break;
					default:
						std::cout << "pDP->Receive Unknown Error";
				}
				return hr;
			break;
		}

	}

    // Free any memory we created
    if( pMsgBuffer )
        GlobalFreePtr( pMsgBuffer );

    return DP_OK;
}


//-----------------------------------------------------------------------------
// Name: HandleApplicationMessage()
// Desc:
//-----------------------------------------------------------------------------
void HandleApplicationMessage( LPDIRECTPLAY4A pDP, DPMSG_GENERIC* pMsg,
                               DWORD dwMsgSize, DPID idFrom, DPID idTo )
{

	// Message Types
	LPSTATUSMSG lpStatus;
    LPTEXTMSG	lpTextMsg;

	// Need to convert pMsg from DPMSG_GENERIC back into message buffer
	BYTE * MsgPnt = (BYTE*)pMsg;

	// White space
	std::cout << "\n\n";

	// Alphabetical Order

	switch ( *MsgPnt )
	{

		// Special Message Types
		
		case MSG_SERVERUPDATE:
			std::cout << "HandleApplicationMessage MSG_SERVERUPDATE \n";
		break;
		case MSG_BIGPACKET:
			std::cout << "HandleApplicationMessage MSG_BIGPACKET \n";
		break;
		case MSG_GUARANTEEDMSG:
			std::cout << "HandleApplicationMessage MSG_GUARANTEEDMSG \n";
		break;


		// A
		
		case MSG_ACKMSG:
			std::cout << "HandleApplicationMessage MSG_ACKMSG \n";
		break;

		// B

		case MSG_BGOUPDATE:
			std::cout << "HandleApplicationMessage MSG_BGOUPDATE \n";
		break;
		case MSG_BOMB:
			std::cout << "HandleApplicationMessage MSG_BOMB \n";
		break;

		// C

		// D

		case MSG_DROPPICKUP:
			std::cout << "HandleApplicationMessage MSG_DROPPICKUP \n";
		break;

		// E

		case MSG_EXPLODESHIP:
			std::cout << "HandleApplicationMessage MSG_EXPLODESHIP \n";
		break;
		case MSG_EXPSECONDARY:
			std::cout << "HandleApplicationMessage MSG_EXPSECONDARY \n";
		break;

		// F

		case MSG_FUPDATE:
			std::cout << "HandleApplicationMessage MSG_FUPDATE \n";
		break;

		// G

		case MSG_GAMEPARAMETERS:
			std::cout << "HandleApplicationMessage MSG_GAMEPARAMETERS \n";
		break;
		case MSG_GROUPONLY_VERYSHORTFUPDATE:
			std::cout << "HandleApplicationMessage MSG_GROUPONLY_VERYSHORTFUPDATE \n";
		break;

		// H
		
		case MSG_HEREIAM:
			std::cout << "HandleApplicationMessage MSG_HEREIAM \n";
		break;

		// I

		case MSG_INIT:
			std::cout << "HandleApplicationMessage MSG_INIT \n";
		break;
		case MSG_INTERPOLATE:
			std::cout << "HandleApplicationMessage MSG_INTERPOLATE \n";
		break;

		// J

		// K

		case MSG_KILLPICKUP:
			std::cout << "HandleApplicationMessage MSG_KILLPICKUP \n";
		break;
		case MSG_KILLSDEATHSBIKENUM:
			std::cout << "HandleApplicationMessage MSG_KILLSDEATHSBIKENUM \n";
		break;

		// L

		case MSG_LEVELNAMES:
			std::cout << "HandleApplicationMessage MSG_LEVELNAMES \n";
		break;
		case MSG_LONGSTATUS:
			std::cout << "HandleApplicationMessage MSG_LONGSTATUS \n";
		break;

		// M

		// N

		case MSG_NAME:
			std::cout << "HandleApplicationMessage MSG_NAME \n";
		break;

		// O

		// P

		case MSG_PINGREPLY:
			std::cout << "HandleApplicationMessage MSG_PINGREPLY \n";
		break;
		case MSG_PINGREQUEST:
			std::cout << "HandleApplicationMessage MSG_PLAYERPINGS \n";
		break;
		case MSG_PLAYERPINGS:
			std::cout << "HandleApplicationMessage MSG_PLAYERPINGS \n";
		break;
		case MSG_PRIMBULLPOSDIR:
			std::cout << "HandleApplicationMessage MSG_PRIMBULLPOSDIR \n";
		break;

		// Q

		// R

		case MSG_REQTIME:
			std::cout << "HandleApplicationMessage MSG_REQTIME \n";
		break;

		// S

	    case MSG_SECBULLPOSDIR:
			std::cout << "HandleApplicationMessage MSG_SECBULLPOSDIR \n";
		break;
		case MSG_SERVERKILLPICKUP:
			std::cout << "HandleApplicationMessage MSG_SERVERKILLPICKUP \n";
		break;
		case MSG_SENDKILLSDEATHSBIKENUM:
			std::cout << "HandleApplicationMessage MSG_SENDKILLSDEATHSBIKENUM \n";
		break;
		case MSG_SERVERSAYSSHIPDIED:
			std::cout << "HandleApplicationMessage MSG_SERVERSAYSSHIPDIED \n";
		break;
		case MSG_SERVERSCORED:
			std::cout << "HandleApplicationMessage MSG_SERVERSCORED \n";
		break;
		case MSG_SESSIONDESC:
			std::cout << "HandleApplicationMessage MSG_SESSIONDESC \n";
		break;
		case MSG_SETTIME:
			std::cout << "HandleApplicationMessage MSG_SETTIME \n";
		break;
		case MSG_SHIELDHULL:
			std::cout << "HandleApplicationMessage MSG_SHIELDHULL \n";
		break;
		case MSG_SHIPDIED:
			std::cout << "HandleApplicationMessage MSG_SHIPDIED \n";
		break;
		case MSG_SHIPHIT:
			std::cout << "HandleApplicationMessage MSG_SHIPHIT \n";
		break;
		case MSG_SHOCKWAVE:
			std::cout << "HandleApplicationMessage MSG_SHOCKWAVE \n";
		break;
		case MSG_SHORTMINE:
			std::cout << "HandleApplicationMessage MSG_SHORTMINE \n";
		break;
		case MSG_SHORTPICKUP:
			std::cout << "HandleApplicationMessage MSG_SHORTPICKUP \n";
		break;
		case MSG_SHORTREGENSLOT:
			std::cout << "HandleApplicationMessage MSG_SHORTREGENSLOT \n";
		break;
		case MSG_SHORTSHIPHIT:
			std::cout << "HandleApplicationMessage MSG_SHORTSHIPHIT \n";
		break;
		case MSG_SHORTSTATS:
			std::cout << "HandleApplicationMessage MSG_SHORTSTATS \n";
		break;
		case MSG_SHORTTRIGGER:
			std::cout << "HandleApplicationMessage MSG_SHORTTRIGGER \n";
		break;
		case MSG_SHORTTRIGVAR:
			std::cout << "HandleApplicationMessage MSG_SHORTTRIGVAR \n";
		break;
		case MSG_STATUS:

			std::cout << "HandleApplicationMessage MSG_STATUS \n";
			lpStatus = (LPSTATUSMSG)MsgPnt;

			printf( "WhoIam: %i \n", lpStatus->WhoIAm);
			printf( "IsHost: %s \n", (lpStatus->IsHost ? "true" : "false"));
			printf( "Status: %s \n", StatusDesc(lpStatus->Status));
			printf( "PkRate: %i \n", (int)lpStatus->PacketsPerSecond);

			/*
				BYTE        MsgCode;
				BYTE		TeamNumber;
				uint16		TeamScore;		// if leaving game, used to propagate my score to another team member
				BOOL		IAmReady;		// used for team game - game cannot start until everyone is ready
				BYTE		Pickups;		// tells how much of the pickup list I have recieved..
				BYTE		RegenSlots;		// tells how much of the pickup regen slots list I have recieved..
				BYTE		Mines;			// tells how much of the mine list I have recieved..
				BYTE		Triggers;		// tells how much of the mine list I have recieved..
				BYTE		TrigVars;		// tells how much of the mine list I have recieved..
				LONGLONG	LevelCheckSum;
			*/

		break;

		// T

		case MSG_TEAMGOALS:
			std::cout << "HandleApplicationMessage MSG_TEAMGOALS \n";
		break;
		case MSG_TEXTMSG:
			std::cout << "HandleApplicationMessage MSG_TEXTMSG \n";

			lpTextMsg = (LPTEXTMSG)MsgPnt;

			/*
			typedef struct _TEXTMSG
			{
				BYTE        MsgCode;
				BYTE        WhoIAm;
				char		Text[MAXTEXTMSG];
				BYTE		TextMsgType;
			} TEXTMSG, *LPTEXTMSG;
			*/

			printf("WhoIam:  %i \n", lpTextMsg->WhoIAm);
			printf("Message: %s \n", &lpTextMsg->Text[0]);

			/*
			switch (lpTextMsg->TextMsgType)
			{
				case TEXTMSGTYPE_QuickTauntWhisper:
				break;
				case TEXTMSGTYPE_Taunt1:
				break;
				case TEXTMSGTYPE_Taunt2:
				break;
				case TEXTMSGTYPE_Taunt3:
				break;
				case TEXTMSGTYPE_QuickTaunt:
				break;
				case TEXTMSGTYPE_JoiningTeamGame:
				break;
				case TEXTMSGTYPE_TitleMessage:
				break;
				case TEXTMSGTYPE_CaptureFlagMessage:
				break;
				case TEXTMSGTYPE_ScoredWithFlag:
				break;
				case TEXTMSGTYPE_ReturningFlag:
				break;
				case TEXTMSGTYPE_ReturnedFlag:
				break;
				case TEXTMSGTYPE_FlagDriftedIn:
				break;
				case TEXTMSGTYPE_FlagEscaped:
				break;
				case TEXTMSGTYPE_BountyMessage:
				break;
				case TEXTMSGTYPE_SpeechTaunt:
				break;
				default:
				break;
			}
			*/

		break;
		case MSG_TOSERVER:
			std::cout << "HandleApplicationMessage MSG_TOSERVER \n";
		break;
		case MSG_TOCLIENT:
			std::cout << "HandleApplicationMessage MSG_TOCLIENT \n";
		break;
		case MSG_TITANBITS:
			std::cout << "HandleApplicationMessage MSG_TITANBITS \n";
		break;
		case MSG_TRACKERINFO:
			std::cout << "HandleApplicationMessage MSG_TRACKERINFO \n";
		break;

		// U
		
		case MSG_UPDATE:
			std::cout << "HandleApplicationMessage MSG_UPDATE \n";
		break;

		// V

		case MSG_VERYSHORTDROPPICKUP:
			std::cout << "HandleApplicationMessage MSG_VERYSHORTDROPPICKUP \n";
		break;
		case MSG_VERYSHORTFUPDATE:
			std::cout << "HandleApplicationMessage MSG_VERYSHORTFUPDATE \n";
		break;
		case MSG_VERYSHORTINTERPOLATE:
			std::cout << "HandleApplicationMessage MSG_VERYSHORTINTERPOLATE \n";
		break;
		case MSG_VERYSHORTUPDATE:
			std::cout << "HandleApplicationMessage MSG_VERYSHORTUPDATE \n";
		break;

		// W

		// X

		// Y

		case MSG_YOUQUIT:
			std::cout << "HandleApplicationMessage MSG_YOUQUIT \n";
		break;

		// Z

		// Default

		default:
			std::cout << "HandleApplicationMessage Unknown Message \n";
		break;

	}



}



//-----------------------------------------------------------------------------
// Name: HandleSystemMessage()
// Desc:
//-----------------------------------------------------------------------------
void HandleSystemMessage( LPDIRECTPLAY4A pDP, DPMSG_GENERIC* pMsg,
                          DWORD dwMsgSize, DPID idFrom, DPID idTo )
{
    
	std::cout << "\n\n";

	if (!pMsg){
		std::cout << "HandleSystemMessage !pMsg \n";
		return;
	}

    switch( pMsg->dwType )
    {
		case DPSYS_CREATEPLAYERORGROUP:
			std::cout << "HandleSystemMessage DPSYS_CREATEPLAYERORGROUP \n";
		break;
		case DPSYS_SESSIONLOST:
			std::cout << "HandleSystemMessage DPSYS_SESSIONLOST \n";
		break;
		case DPSYS_HOST:
			std::cout << "HandleSystemMessage DPSYS_HOST \n";
		break;
		case DPSYS_DESTROYPLAYERORGROUP:
			std::cout << "HandleSystemMessage DPSYS_DESTROYPLAYERORGROUP \n";
		break;
		case DPSYS_SETSESSIONDESC:
			std::cout << "HandleSystemMessage DPSYS_SETSESSIONDESC \n";
		break;
		case DPSYS_ADDGROUPTOGROUP:
			std::cout << "HandleSystemMessage DPSYS_ADDGROUPTOGROUP \n";
		break;
		case DPSYS_ADDPLAYERTOGROUP:
			std::cout << "HandleSystemMessage DPSYS_ADDPLAYERTOGROUP \n";
		break;
		case DPSYS_CHAT:
			std::cout << "HandleSystemMessage DPSYS_CHAT \n";
		break;
		case DPSYS_DELETEGROUPFROMGROUP:
			std::cout << "HandleSystemMessage DPSYS_DELETEGROUPFROMGROUP \n";
		break;
		case DPSYS_DELETEPLAYERFROMGROUP:
			std::cout << "HandleSystemMessage DPSYS_DELETEPLAYERFROMGROUP \n";
		break;
		case DPSYS_SECUREMESSAGE:
			std::cout << "HandleSystemMessage DPSYS_SECUREMESSAGE \n";
		break;
		case DPSYS_SETPLAYERORGROUPDATA:
			std::cout << "HandleSystemMessage DPSYS_SETPLAYERORGROUPDATA \n";
		break;
		case DPSYS_SETPLAYERORGROUPNAME:
			std::cout << "HandleSystemMessage DPSYS_SETPLAYERORGROUPNAME \n";
		break;
		case DPSYS_STARTSESSION:
			std::cout << "HandleSystemMessage DPSYS_STARTSESSION \n";
		break;
		default:
			std::cout << "HandleSystemMessage Unknown Message \n";
		break;
	}

}






