# DDNet custom client identification standard
###### By +KZ
Custom clients IDs for DDNet so custom clients can identify which client is each player using by using unused values in the Teeworlds protocol that can be sent to the server and (in most cases) will be sent back to all other clients without any change.

The advantage of the methods used here is that you don't need a 3rd party server for this (like some new clients do, and like T-Client plans to do), you just take advantage of unused values from the Teeworlds protocol.

This gets rid of the dependency of authenticating with a server that we all know some day will be shutdown due to real life reasons, by instead sending the information through the Teeworlds/DDNet server itself.

First implemented in Kaizo Client, but it can also be shared among other clients since this header is published under LGPL.

Clients using this (sorted by implementation date):

* [Kaizo Client](https://github.com/M0REKZ/kaizo-client) (original implementation)
* [Chillerbot-UX](https://chillerbot.github.io/)
* [Duck/Infclass Client](https://pointer31.github.io/duckclient)
* [Rushie Client](https://github.com/RushieClient/RushieClient-ddnet)

# Adding a new client

Just check the file 'custom_clients_ids.h' from this repo: Add a new ID in the format `CUSTOM_CLIENT_ID_YOURCLIENNAME`, and depending on the method you are using you must also add the corresponding IDs to identify your client.

Send a pull request here after that and make sure your client sends the same IDs using the same method.

Currently this repository lists IDs for the following methods:
* [Skin color method](https://github.com/M0REKZ/ddnet-custom-clients#skin-color-method)
* [0.7 Skin part name method](https://github.com/M0REKZ/ddnet-custom-clients#07-skin-part-name-method)
* [Country flag method (obsolete)](https://github.com/M0REKZ/ddnet-custom-clients#country-flag-method)

The country flag method is obsolete and not recommended due to the problems it causes, the IDs still can be found in the file but they are commented out.

Also you may want to add your own icon to [the icons branch](https://github.com/M0REKZ/ddnet-custom-clients/tree/icons).

# How to use

Below you will find how to implement a custom client identification method in your own client.

Also, you may want to use the icons from [the icons branch](https://github.com/M0REKZ/ddnet-custom-clients/tree/icons).

## Skin color method

Your client must check the alpha value for both Body and Feet colors of the player to identify other clients, if a specific combination of both is a custom client ID from the list, the player is using a custom client.

To make your life easier for checking/inserting alpha value, you can use the macros included in this repo:

```C++
//Insert a CCID into skin color:
MACRO_INSERT_CCID_INTO_SKIN_COLOR(
		Msg.m_ColorBody, Msg.m_ColorFeet,
		CCID_COLOR_BODY_YOUR_CLIENT, CCID_COLOR_FEET_YOUR_CLIENT
	)

//Check if skin color contains a specific CCID:
if(
	MACRO_IS_SKIN_COLOR_CCID(
		pInfo->m_ColorBody, pInfo->m_ColorFeet,
		CCID_COLOR_BODY_HIS_CLIENT, CCID_COLOR_FEET_HIS_CLIENT
	)
	)
{
	//Save detected client
	m_aClients[CheckingId].m_CustomClient = CUSTOM_CLIENT_ID_HIS_CLIENT;
}
```

## 0.7 Skin part name method

Used by clients made in the 0.7 days, you need to support this method if you want to detect 0.7 clients such as F-Client, Gamer and ZillyWoods.

Kaizo Client also uses this method for 0.7 connections.

To detect it you need to loop through all the 0.7 Skin parts of the client checking for strings defined in the header file found in this repository, here is some code to show a example:

```C++
// Check for 0.7 custom clients
if(Client()->IsSixup())
{
	bool Found = false;
	for(int CheckingId = 0; CheckingId < MAX_CLIENTS; CheckingId++)
	{
		if(m_aClients[CheckingId].m_CustomClient)
			continue;

		Found = false;
		for(int Client = 0; Client < 4; Client++)
		{
			const char* pClientString = "";
			int CustomClientId = 0;
			switch (Client)
			{
			case 0:
				pClientString = CCID_07_SKIN_PART_NAME_TEEWORLDS_GAMER;
				CustomClientId = CUSTOM_CLIENT_ID_GAMER_07;
				break;
			case 1:
				pClientString = CCID_07_SKIN_PART_NAME_ZILLYWOODS;
				CustomClientId = CUSTOM_CLIENT_ID_ZILLYWOODS_07;
				break;
			case 2:
				pClientString = CCID_07_SKIN_PART_NAME_FCLIENT;
				CustomClientId = CUSTOM_CLIENT_ID_FCLIENT_07;
				break;
			case 3:
				pClientString = CCID_07_SKIN_PART_NAME_KAIZO_CLIENT_07_MODE;
				CustomClientId = CUSTOM_CLIENT_ID_KAIZO_CLIENT;
				break;
			}

			for(int p = 0; p < protocol7::NUM_SKINPARTS; p++)
			{
				if(str_startswith(m_aClients[CheckingId].m_aSixup[g_Config.m_ClDummy].m_aaSkinPartNames[p], pClientString))
				{
					m_aClients[CheckingId].m_CustomClient = CustomClientId;
					Found = true;
					break;
				}
			}
			if(Found)
				break;
		}
	}
}
```
	  
## Country flag method

> [!IMPORTANT]
> Country flag method is obsolete and only used in initial **Kaizo Network Client** versions (which is a very initial version of **Kaizo Client**), *no client uses this method today*.
>
> It's known to cause annoying issues like connection problems or not being able to change back to a normal country flag after sending it to the server.
>
> Please use [Skin color method](https://github.com/M0REKZ/ddnet-custom-clients#skin-color-method) instead.

Your client must check which country flag is the other player using, if it is a ID from the list, you should make the client remember which custom client is the player using since usually custom clients will show the custom country flag and then switch back to a normal country flag.

To send the ID you must set the sent country flag to your client ID, and then reset it to the player country flag after some time, note that this causes connection problems in most cases.
