// Copyright (C) Benjamín Gajardo (also known as +KZ)
//
// This file is part of the DDNet custom client identification standard by +KZ
//
// The DDNet custom client identification standard by +KZ is free software:
// you can redistribute it and/or modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation.
// 
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program. If not, see <https://www.gnu.org/licenses/>.


// This file can be included several times.
#pragma once

enum
{
	// Custom client IDs (To save detected IDs)
	// This is a list of clients that can be detected by using this header,
	// you may want to use them to save the clients you already detected.
	//
	// Like:
	//
	// if(MACRO_IS_SKIN_COLOR_CCID(
	//     pInfo->m_ColorBody, pInfo->m_ColorFeet,
	//     CCID_COLOR_BODY_KAIZO_CLIENT, CCID_COLOR_FEET_KAIZO_CLIENT
	//     ))
	// {
	//     m_aClients[id].m_CustomClient = CUSTOM_CLIENT_ID_KAIZO_CLIENT;
	// }
	CUSTOM_CLIENT_ID_KAIZO_CLIENT = 16777216,
	CUSTOM_CLIENT_ID_DUCK_N_INFCLASS_CLIENT = 16777217,
	CUSTOM_CLIENT_ID_GAMER_07 = 16777218,
	CUSTOM_CLIENT_ID_ZILLYWOODS_07 = 16777219,
	CUSTOM_CLIENT_ID_FCLIENT_07 = 16777220,
	CUSTOM_CLIENT_ID_RUSHIECLIENT = 16777221,
	CUSTOM_CLIENT_ID_CHILLERBOTUX = 33554432,

	// Custom client IDs (Skin Color Method)
	// Range is smaller (65025 possible IDs by using Body and Feet color combinations)

	// Body
	CCID_COLOR_BODY_NONE = 0,
	CCID_COLOR_BODY_KAIZO_CLIENT = 1,
	CCID_COLOR_BODY_PDUCKCLIENT = 2,
	CCID_COLOR_BODY_CHILLERBOTUX = 3,
	CCID_COLOR_BODY_RUSHIECLIENT = 4,

	// Feet
	CCID_COLOR_FEET_NONE = 0,
	CCID_COLOR_FEET_KAIZO_CLIENT = 0,
	CCID_COLOR_FEET_PDUCKCLIENT = 0,
	CCID_COLOR_FEET_CHILLERBOTUX = 0,
	CCID_COLOR_FEET_RUSHIECLIENT = 0,


	// Custom client IDs (Country flag method)
	// This method is obsolete and no client uses it today,
	// please use the skin color method instead
	// CUSTOM_CLIENT_ID_KAIZO_NETWORK = 16777216,
	// CUSTOM_CLIENT_ID_PDUCKCLIENT = 16777217,
	// CUSTOM_CLIENT_ID_CHILLERBOTUX = 33554432,
};

// Custom client IDs (0.7 Skin Part Name Method)
// Use this method to identify some clients in 0.7 servers
#define CCID_07_SKIN_PART_NAME_TEEWORLDS_GAMER "gamer!"
#define CCID_07_SKIN_PART_NAME_FCLIENT "fclient!"
#define CCID_07_SKIN_PART_NAME_ZILLYWOODS "zilly!"
#define CCID_07_SKIN_PART_NAME_KAIZO_CLIENT_07_MODE "kaizo!"

//=============================================================
// Ignore this section,
// the values here are only for backwards compatibility:
enum
{
	// Kaizo Network Client was renamed to Kaizo Client.
	//
	// USE CUSTOM_CLIENT_ID_KAIZO_CLIENT INSTEAD
	CUSTOM_CLIENT_ID_KAIZO_NETWORK = CUSTOM_CLIENT_ID_KAIZO_CLIENT,

	// Previously Duck/Infclass Client was just named Duck Client.
	//
	// In this file it was referred as "Pointer's Duck Client" to
	// avoid confusion with Ar1gin's Duck Client
	//
	// USE CUSTOM_CLIENT_ID_DUCK_N_INFCLASS_CLIENT INSTEAD
	CUSTOM_CLIENT_ID_PDUCKCLIENT = CUSTOM_CLIENT_ID_DUCK_N_INFCLASS_CLIENT,

	// This range was intended for Country flag method additions,
	// currently useless but it was used in some client versions.
	//
	// Original comment:
	// "Range is big enough (16777215 possible IDs in between)"
	MINIMUM_CUSTOM_CLIENT_ID = CUSTOM_CLIENT_ID_KAIZO_NETWORK,
	MAXIMUM_CUSTOM_CLIENT_ID = CUSTOM_CLIENT_ID_CHILLERBOTUX,
};
// End of backwards compatibility section
//=============================================================



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
 * TODO: This should not be a lambda
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
