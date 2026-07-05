# DDNet custom client identification standard
Custom clients IDs for DDNet so custom clients can identify which client is each player using by using unused values in the Teeworlds protocol that can be sent to the server and (in most cases) will be sent back to all other clients without any change.

The advantage of the methods used here is that you don't need a 3rd party server for this (like Rushie Client and BestClient do, and like T-Client plans to do), you just take advantage of unused values from the Teeworlds protocol.

This gets rid of the dependency of authenticating with a server that we all know some day will be shutdown due to real life reasons, by instead sending the information through the Teeworlds/DDNet server itself.

First implemented in Kaizo Client, but it can also be shared among other clients since this header is published under LGPL.

Clients using this:

* [Kaizo Client](https://github.com/M0REKZ/kaizo-client) (original implementation)
* [Chillerbot-UX](https://chillerbot.github.io/)
* [Duck/Infclass Client](https://pointer31.github.io/duckclient)

# Adding a new client

Just check the file 'custom_clients_ids.h' from this repo, add a new ID for the skin color method, send a pull request here after that and make your client send the ID in the skin color alpha.

The country flag method is not recommended since it is known to cause bugs like not being able to switch back to the player flag or even causing connection problems.

But if you still want to add a new client ID for the country flag method, make sure the ID number is greater than the ID for Kaizo Network, this way we avoid conflicts with possible future DDNet country flag additions.

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
MACRO_IS_SKIN_COLOR_CCID(
		pInfo->m_ColorBody, pInfo->m_ColorFeet,
		CCID_COLOR_BODY_HIS_CLIENT, CCID_COLOR_FEET_HIS_CLIENT
	)
```

## 0.7 Skin part name method

Used by clients made in the 0.7 days, you need to support this method if you want to detect 0.7 clients such as F-Client, Gamer and ZillyWoods.
	  
## Country flag method

> [!IMPORTANT]
> Country flag method is obsolete and only used in initial Kaizo Network Client versions.
>
> It's known to cause issues like connection problems or not being able to change back to a normal country flag after sending it to the server.
>
> Use [Skin color method](https://github.com/M0REKZ/ddnet-custom-clients#skin-color-method) instead.

Your client must check which country flag is the other player using, if it is a ID from the list, you should make the client remember which custom client is the player using since usually custom clients will show the custom country flag and then switch back to a normal country flag.
