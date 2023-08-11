#pragma once
#ifndef _DBMANAGERGLOBAL_H 
#define _DBMANAGERGLOBAL_H

#ifndef BUILD_STATIC
#if defined(EXPORT_DBMANAGER_LIB)
#define DBMANAGER_EXPORT __declspec(dllexport)
#else
#define DBMANAGER_EXPORT __declspec(dllimport)
#endif
#else
#define DBMANAGER_EXPORT
#endif

#endif