// This file can be included several times.
#pragma once

// Copyright (C) Benjamín Gajardo (also known as +KZ)

enum
{
	// Custom client IDs (Skin Color Method)
	// Range is smaller (65025 possible IDs by using Body and Feet color combinations)

	// Body
	CCID_COLOR_BODY_NONE = 0,
	CCID_COLOR_BODY_KAIZO_CLIENT = 1,
	CCID_COLOR_BODY_PDUCKCLIENT = 2,
	CCID_COLOR_BODY_CHILLERBOTUX = 3,

	// Feet
	CCID_COLOR_FEET_NONE = 0,
	CCID_COLOR_FEET_KAIZO_CLIENT = 0,
	CCID_COLOR_FEET_PDUCKCLIENT = 0,
	CCID_COLOR_FEET_CHILLERBOTUX = 0,

	// Custom client IDs (Country flag method)
	// This method is obsolete, please use skin color method instead
	CUSTOM_CLIENT_ID_KAIZO_NETWORK = 16777216,
	CUSTOM_CLIENT_ID_PDUCKCLIENT = 16777217,
	CUSTOM_CLIENT_ID_GAMER_07 = 16777218, //0.7 Client Reserved
	CUSTOM_CLIENT_ID_ZILLYWOODS_07 = 16777219, //0.7 Client Reserved
	CUSTOM_CLIENT_ID_FCLIENT_07 = 16777220, //0.7 Client Reserved
	CUSTOM_CLIENT_ID_CHILLERBOTUX = 33554432,

	//Range is big enough (16777215 possible IDs in between)
	MINIMUM_CUSTOM_CLIENT_ID = CUSTOM_CLIENT_ID_KAIZO_NETWORK,
	MAXIMUM_CUSTOM_CLIENT_ID = CUSTOM_CLIENT_ID_CHILLERBOTUX,

};

// Macros for easy implementation

/**
 * Skin Color Method:
 * Inserts the custom client ID into skin color
 * @warning It will overwrite BodyColor and FeetColor!
 *
 * @param BodyColor Body color of the Tee Skin to overwrite
 * @param FeetColor Feet color of the Tee Skin to overwrite
 * @param BodyCCID Body CCID to insert
 * @param FeetCCID Feet CCID to insert
 *
 */
#define MACRO_INSERT_CCID_INTO_SKIN_COLOR(BodyColor, FeetColor, BodyCCID, FeetCCID) \
	{ \
		union \
		{ \
			int c = 0; \
			unsigned char b[4]; \
		} a, b; \
\
		/* Only allow int (TODO: should use decltype) */ \
		static_assert(sizeof(BodyColor) == sizeof(int)); \
		static_assert(sizeof(FeetColor) == sizeof(int)); \
\
		a.c = BodyColor; \
		b.c = FeetColor; \
\
		a.b[3] = (unsigned char)BodyCCID; \
		b.b[3] = (unsigned char)FeetCCID; \
		BodyColor = a.c; \
		FeetColor = b.c; \
	}

/**
 * Skin Color Method:
 * Check if client skin color has a CCID
 *
 * @param BodyColor Body color of the Tee Skin
 * @param FeetColor Feet color of the Tee Skin
 * @param BodyCCID Body CCID to check for
 * @param FeetCCID Feet CCID to check for
 *
 */
#define MACRO_IS_SKIN_COLOR_CCID(BodyColor, FeetColor, BodyCCID, FeetCCID) [&] { \
	union \
	{ \
		int c = 0; \
		unsigned char b[4]; \
	} a, b; \
\
	/* Only allow int (TODO: should use decltype) */ \
	static_assert(sizeof(BodyColor) == sizeof(int)); \
	static_assert(sizeof(FeetColor) == sizeof(int)); \
\
	a.c = BodyColor; \
	b.c = FeetColor; \
	if(a.b[3] == BodyCCID && b.b[3] == FeetCCID) \
		return true; \
	return false; \
}()
