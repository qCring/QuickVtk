#pragma once

/**
 * @file quickExport.h
 * @brief export attributes for windows shared library(.DLL)
 * @version 0.1
 * @date 2019-12-22
 * 
 */

#ifdef _WIN32
#ifdef QuickVtkCore_EXPORTS
/* We are building this library */
#define QUICKVTKCORE_API __declspec(dllexport)
#else
/* We are using this library */
#define QUICKVTKCORE_API __declspec(dllimport)
#endif
#else
#define QUICKVTKCORE_API
#endif