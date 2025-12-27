// This file can be included several times.
#pragma once

// Copyright (C) Benjamín Gajardo (also known as +KZ)

enum
{
	// Custom client IDs
	CUSTOM_CLIENT_ID_KAIZO_NETWORK = 16777216,
	CUSTOM_CLIENT_ID_PDUCKCLIENT = 16777217,
	CUSTOM_CLIENT_ID_CHILLERBOTUX = 33554432,

	//Range is big enough (16777215 possible IDs in between)
	MINIMUM_CUSTOM_CLIENT_ID = CUSTOM_CLIENT_ID_KAIZO_NETWORK,
	MAXIMUM_CUSTOM_CLIENT_ID = CUSTOM_CLIENT_ID_CHILLERBOTUX,

	// Other info to be shared among clients
	CUSTOM_CLIENT_ISDUMMY = 33554433,
	CUSTOM_CLIENT_ISBOT = 33554434, // intended for clients like discord bridge bots
};
