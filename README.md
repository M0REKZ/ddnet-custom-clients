# ddnet-custom-clients
Custom clients IDs for DDNet so custom clients can identify which client is each player using by checking invalid country flags OR the unused alpha value in player skin color.

First implemented in Kaizo Client, but it can also be shared among other clients

Clients using this:

* [Kaizo Client](https://github.com/M0REKZ/kaizo-client)
* [Chillerbot-UX](https://chillerbot.github.io/)
* [Duck Client](https://pointer31.github.io/duckclient)

# Adding a new client

Just check the file 'custom_clients_ids.h' from this repo, add a new ID for the skin color method, make sure to send a pull request after that and to use the ID in your custom client.

The country flag method is not recommended since it is known to cause bugs like not being able to switch back to the player flag or even causing connection problems.

But if you still want to add a new client ID for the country flag method, make sure the ID number is greater than the ID for Kaizo Network, this way we avoid conflicts with possible future DDNet country flag additions.

# How to use

### Country flag method
Your client must check which country flag is the other player using, if it is a ID from the list, you should make the client remember which custom client is the player using since usually custom clients will show the custom country flag and then switch back to a normal country flag.

### Skin color method
Your client must check the alpha value for both Body and Feet colors of the player, if a specific combination of both is a custom client ID from the list, the player is using a custom client.

To make your life easier for checking alpha value, you can use a union like this:


    union
		{
			int c = 0;
			unsigned char b[4];
		} data;

		data.c = pInfo->m_ColorBody; // Get body color

		// data.b[3] is the body color alpha
    // do the same for feet color
      
