/**																
	\file RecognitionEngine.h
  	\brief DevRecognitionEngine.h contains declaration of function interfaces of the Application for Online Handwritten Character Recognition (OHWR) System
	\date(Date of Creation)
	\date  (Last modified)
  	\author xxxxx
  	\version 1.0.0.0
  	<b> All COPYRIGHTS ARE RESERVERD TO C-DAC GIST PUNE 2012 </b>
*/

#ifndef _RECOGNITIONENGINE_H_
#define _RECOGNITIONENGINE_H_
#ifdef __cplusplus
#include "File_Data_Struct.h"
//#include "TCHAR.h"
#include "tchar.h"
#include "stdafx.h"
#include <vector>
#include <fstream>
#include <iostream>


extern "C"
{  
#endif

   /** 
    \brief maximum length of file path string
	*/
	#define MAX_FILE_PATH  256

	/**
	\brief Global var Engine Directory Path string where all model files and other resoureces are stored
	*/
	extern char*  g_strEngineDirectoryPath;

	/** 
	\brief var WordList Directory Path string
	*/
	extern char*  g_strWordListDirectoryPath;

	/** An enum type. 
	* This enum is used to pass the device specific information such as orientation, to the
	* engine. The engine will perform the transformation required if any as per the engine
	* specific requirements.
*/

	typedef enum{
		TOP_LEFT=0,//< enum value 0 
		TOP_RIGHT, //< enum value 1 
		BTM_LEFT, //< enum value 2 
		BTM_RIGHT//< enum value 3 
	}DEVICE_INFO_T;

	/** An enum type. 
	* This enum is used to pass the Engine type info to engine
	*/
	typedef enum{
		MIXED=1, /**< enum value 1 Mixed_Text(word, numerals, punctuations etc) e.g. Address field*/
		PLAIN,/**< enum value 2 Plain_Text*/
		NUM,/**< enum value 3 Numerals*/
		NUM_SYM,/**<enum value 4 Numerals_Symbols*/
		NUM_DECPT_COMMA,/**<enum value 5 Numerals + Decimal point + Comma*/
		TEXT_PUNC,/**<enum value 6 Pure Text with punctuations (required in Malayalam, Kannada  and Telugu etc.)*/
		AGE,/**<enum value 7 Age*/
		DATE,/**<enum value 8 Date*/
		MONTH,/**<enum value 9 Month*/
		YEAR,/**<enum value 10 Year*/
		HOUR,/**<enum value 11 Hour*/
		MIN,/**<enum value 12 Min*/
		NAME,/**<enum value 13 Name */
	}ENGINE_TYPE;

	/** WORD_SEG_INFO
    \brief  Data strucute used to store word segmentation information
	*/
	
	typedef struct{
		int iNoOfStrokes;//<no of Strokes in word 
		int* arr_iStrokeIndexes;//<array of indexex of Strokes in word 
		int iSuggest;//<no of ranked suggessions from Recognition Engine
		TCHAR** strUniOut;//< engine output(s) of the word. Engine may choose to output more than one word
		int iReserved;//< for possible space characters and indents before the word 
	}WORD_SEG_INFO;

	//* LINE_SEG_INFO
    //brief  Data strucute used to store line segmentation information filled by Recognition Engine DLL
	

	typedef struct{
		int iNoOfWords;//<no of words in line
		WORD_SEG_INFO* ptrWordSegInfo;//< pointer to array word segmetation info
	}LINE_SEG_INFO;

//* SEG_TEXT_BLOCK_INFO
    //brief  Data strucute used to store Text block segmentation information filled
	typedef struct{
		int iNoOfLines;//<no of lines in text block 
		LINE_SEG_INFO* ptrLineSegInfo;//< pointer to array of line segmentation info
	}TEXT_BLOCK_UNI_INFO;

	/**
	\brief It is used to initialize engine parameters. This function is called at the application start or once the user selects the language. On language change, it is called again. 
	\returns is an int as error code
				-ve values refers Engine Successfully Initialized
				+ve values refers Engine Not Initialized
				
	\param [in] WorkingDirPath an const char* const ,contains "ApplicatioBasePath" where it is loaded. The  folder structure inside this base path is as per SRS. The folder structure is shown in Annexure-III
	\param [in] UserID is an integer, userID or equivalent number is passed to the engine. Engine needs to generate log file named <usedID>.txt
	\param [in] test is an DEVICE_INFO_T  enum ,devinfo is a used to provide the device orientation information.
	\exception no exception from this function
	\date  (Date of Creation)
	\date (Last modified)
	\author xxxx
	\version 1.0.0.0

	<b> All COPYRIGHTS ARE RESERVERD TO C-DAC GIST PUNE 2010 </b>
	*/
//	int  __declspec(dllexport)fn_InitEngine (const char* WorkingDirPath,int UserID, DEVICE_INFO_T test);
	int __declspec(dllexport) fn_InitEngine(const char* WorkingDirPath,int UserID,DEVICE_INFO_T test);	

	/**
	\brief This function will call the respective line recognition engine and will return the recognized result for word as Unicode string
	\param [in] pStructStrokeInfo Filled FILE_STROKEINFO structure with Line Information
	\param [in] iStrokeCount is no of strokes
	\param [in]  iDataType is an Engine type like characters, numerals, date ,age, etc.
	\param[in] WordlistIndex is wordlist to be used for recognition(or for postprocessing).
	\param [out] strOut is Output recognized Words 
	\param [in] topN is no. of output words (no. of suggessions) to be wanted
	\return is an int as Positive Integer for Successful recognition indicating total number of	suggested words or Negative Integers for Errors codes
	\exception no exception from this function
	\date (Date of Creation)
	\date  (Last modified)
	\author xxxx
	\version 1.0.0.0
	<b> All COPYRIGHTS ARE RESERVERD TO C-DAC GIST PUNE 2012 </b>

	// int __declspec(dllexport)fn_RecognizeWord (const FILE_STROKEINFO* pStructStrokeInfo, int iStrokeCount , ENGINE_TYPE dataType, unsigned char WordlistIndex, TCHAR ** strOut, int topN );

*/ 
//int fn_RecognizeWord(FILE_STROKEINFO* pStructStrokeInfo, int iStrokeCount, ENGINE_TYPE dataType,TCHAR** strOut,int topN,std::vector<int> uni_code,std::ofstream result);
    int __declspec(dllexport) fn_RecognizeWord(const FILE_STROKEINFO* pStructStrokeInfo, int iStrokeCount, ENGINE_TYPE dataType,unsigned char WordlistIndex,TCHAR** strOut,int topN);
	
	 /**
	\brief This function will call the respective Text Block recognition engine and will return the recognized result for word as Unicode string
	\param [in]  pStructStrokeInfo Filled FILE_STROKEINFO structure with Line Information	
	\param [in] iStrokeCount is no of strokes
	\param [in]  topN is no. of output words (no. of suggessions) to be wanted.
	\param [out] Data strucute used to store Text block segmentation information filled
	\return is an int as Positive Integer for Successful recognition or Negative Integers for Errors codes
	\exception no exception from this function
	\date (Date of Creation)
	\date  (Last modified)
	\author xxxx
	\version 1.0.0.0
	<b> All COPYRIGHTS ARE RESERVERD TO C-DAC GIST PUNE 2012 </b>
*/
	// extern int fn_RecognizeTextBlock (const FILE_STROKEINFO* pStructStrokeInfo, int iStrokeCount , int topN, TEXT_BLOCK_UNI_INFO* ptrTextBlockUniInfo);


	/**
	\brief This function call takes void. It is used as a signal to the engine to free all the allocated resources like memory, file handles etc.
	\return is an int as error code -ve values refers Engine Successfully Initialized , +ve values refers Engine Not Initialized
	\exception no exception from this function
	\date(Date of Creation)
	\date   (Last modified)
	\author xxxxx
	\version 1.0.0.0
	<b> All COPYRIGHTS ARE RESERVERD TO C-DAC GIST PUNE 2012 </b>
 */

	int __declspec(dllexport) fn_FreeEngine();
	
	/**
	\brief 
	\param [in] EngineVersionInfo is a string is the version number given by each center to its language engine. Recommended versioning string should include [center code], [language code] and [version number].
	\exception no exception from this function
	\date (Date of Creation)
	\date  (Last modified)
	\author xxxxx
	\version 1.0.0.0
	<b> All COPYRIGHTS ARE RESERVERD TO C-DAC GIST PUNE 2012 </b>
*/
 void __declspec(dllexport) fn_EngineVersionInfo(char** EngineVersionInfo);
 	
#ifdef __cplusplus
 

#endif
#endif 	
}