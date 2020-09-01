/*
Frhed - Free hex editor
Copyright (C) 2000 Raihan Kibria
SPDX-License-Identifier: GPL-3.0-or-later
Last change: 2019-05-25 by Jochen Neubeck
*/
/**
 * @file  version.h
 *
 * @brief Version number (macros) for Frhed.
 *
 */
// These set Frhed release version number
// Note that for releases, these values are read from
// versions.ini file and set here by the SetVersions.py script
#define FRHED_MAJOR_VERSION 0
#define FRHED_MINOR_VERSION 10907
#define FRHED_SUB_RELEASE_NO 2020
#define FRHED_BUILD_NO 0

// Utility macros for formatting version number to string.
#define SHARPEN_A(X) #X
#define SHARPEN_W(X) L#X

#ifdef UNICODE
#define SHARPEN(X) SHARPEN_W(X)
#else
#define SHARPEN(X) SHARPEN_A(X)
#endif

#define FRHED_VERSION_1 FRHED_MAJOR_VERSION
#define FRHED_VERSION_2 FRHED_MAJOR_VERSION.FRHED_MINOR_VERSION
#define FRHED_VERSION_3 FRHED_MAJOR_VERSION.FRHED_MINOR_VERSION.FRHED_SUB_RELEASE_NO
#define FRHED_VERSION_4 FRHED_MAJOR_VERSION.FRHED_MINOR_VERSION.FRHED_SUB_RELEASE_NO.FRHED_BUILD_NO

