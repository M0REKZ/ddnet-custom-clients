// This file can be included several times.
#pragma once

// Copyright (C) Benjamín Gajardo (also known as +KZ)

enum
{
	// Custom client IDs (Country flag method)
	CUSTOM_CLIENT_ID_KAIZO_NETWORK = 16777216,
	CUSTOM_CLIENT_ID_PDUCKCLIENT = 16777217,
	CUSTOM_CLIENT_ID_GAMER_07 = 16777218, //0.7 Client Reserved
	CUSTOM_CLIENT_ID_ZILLYWOODS_07 = 16777219, //0.7 Client Reserved
	CUSTOM_CLIENT_ID_FCLIENT_07 = 16777220, //0.7 Client Reserved
	CUSTOM_CLIENT_ID_CHILLERBOTUX = 33554432,

	//Range is big enough (16777215 possible IDs in between)
	MINIMUM_CUSTOM_CLIENT_ID = CUSTOM_CLIENT_ID_KAIZO_NETWORK,
	MAXIMUM_CUSTOM_CLIENT_ID = CUSTOM_CLIENT_ID_CHILLERBOTUX,

	// Custom client IDs (Skin Color Method)
	// Range is smaller (65025 possible IDs by using both Body and Feet colors)

	// Body
	CCID_COLOR_BODY_KAIZO_CLIENT = 1,
	CCID_COLOR_BODY_PDUCKCLIENT = 2,
	CCID_COLOR_BODY_CHILLERBOTUX = 3,

	// Feet
	// (Empty...)
};
