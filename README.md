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

# How to use

## Skin color method
Your client must check the alpha value for both Body and Feet colors of the player to identify other clients, if a specific combination of both is a custom client ID from the list, the player is using a custom client.

To make your life easier for checking/setting alpha value, you can use a union like this:


    union
	{
		int ColorValue = 0;
		unsigned char Bytes[4];
	} data;

	data.ColorValue = pInfo->m_ColorBody; // Get body color

	// data.Bytes[3] is the body color alpha
    // do the same for feet color
      
## Country flag method

> [!IMPORTANT]
> Country flag method is obsolete and only used in initial Kaizo Network Client versions.
>
> It's known to cause issues like connection problems or not being able to change back to a normal country flag after sending it to the server.
>
> Use [Skin color method](#skin-color-method) instead.

Your client must check which country flag is the other player using, if it is a ID from the list, you should make the client remember which custom client is the player using since usually custom clients will show the custom country flag and then switch back to a normal country flag.
