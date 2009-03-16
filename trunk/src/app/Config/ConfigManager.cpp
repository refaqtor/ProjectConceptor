#include "ConfigManager.h"
#include <stdio.h>
#include <app/Messenger.h>
#include <interface/InterfaceDefs.h>
#include <storage/Entry.h>
#include <storage/Path.h>

#include <support/Debug.h>


//needed for strerror
#include <string.h>

#ifdef B_ZETA_VERSION_BETA
	#include <locale/Locale.h>
#else
	#define _T(a) a
#endif



ConfigManager::ConfigManager(char *path, BMessage *newConfig){
// if no Message was passed we just create a Message :)
 if (newConfig==NULL) {
 	config = new BMessage();
 } 
 else
 	config = newConfig;
 BFile *file = new BFile(path,B_READ_WRITE | B_CREATE_FILE);
 //** @todo check for errors if the config file was created*/
}

//rebuild the hole Config View
void ConfigManager::SetConfigMessage(BMessage *newConfig){

}

void  ConfigManager::LoadDefaults(void){
	char		*xmlString;
	off_t		start,end;
	file->Seek(0,SEEK_SET);
	start = file->Position();
	file->Seek(0,SEEK_END);
	end = file->Position();
	file->Seek(0,SEEK_SET);
	size_t		size= end-start;
	xmlString=new char[size+1];
	file->Read(xmlString, size);
	TiXmlDocument	doc;
	doc.Parse(xmlString);
	delete xmlString;
	if (doc.Error())
		//need to do something
		start=0;
	else{		
	}	
}

void ConfigManager::SaveConfig(){
	TRACE();
  	TiXmlDocument	 doc;
  	doc.InsertEndChild(	ProcessMessage(config));
  	TiXmlPrinter	printer;
  	doc.Accept( &printer);
  	printf("%s",printer.CStr());
  	TRACE();
	//file->Write(printer.CStr(),strlen(printer.CStr()));
}

TiXmlElement  ConfigManager::ProcessMessage( BMessage *msg){
	TRACE();
	msg->PrintToStream();
	TiXmlElement	xmlNode("BMessage");
	xmlNode.SetAttribute("type","BMessage");
	xmlNode.SetAttribute("what",(int32)(msg->what));
	char		*name;
	uint32	type;
	int32		count;
	int32		i =0;
	ssize_t	numBytes;
	TRACE();
		while (msg->GetInfo(B_ANY_TYPE,i ,(char **)&name, &type, &count) == B_OK) {
		TRACE();
		TiXmlElement	xmlSubNode("Data");
		xmlSubNode.SetAttribute("name",name);
		switch(type){
			case B_MESSAGE_TYPE:{
				BMessage tmpMessage;
				xmlSubNode.SetAttribute("type","BMessage");
				if (msg->FindMessage(name, count-1, &tmpMessage)== B_OK){
					xmlSubNode.InsertEndChild(ProcessMessage(&tmpMessage));
				}
				break;
			}
			case B_BOOL_TYPE:{
		        TRACE();
		        //FindBool()
		        bool tmpBool;
		        xmlSubNode.SetAttribute("type","bool");
		        if (msg->FindBool(name, count-1, &tmpBool) == B_OK){
					if  (tmpBool = true)
						xmlSubNode.SetAttribute("value","true");
					else
						xmlSubNode.SetAttribute("value","false");
				}	
				break;
			}
			case B_INT8_TYPE:{
		        TRACE();
		        //FindInt8()	an int8 or uint8	
		        int8 tmpInt8;
				xmlSubNode.SetAttribute("type","int8");
				 if (msg->FindInt8(name, count-1, &tmpInt8) == B_OK){
					xmlSubNode.SetAttribute("value",tmpInt8);
				}
				break;	
			}
			case B_INT16_TYPE:{
		        TRACE();
		        //FindInt16()	an int16 or uint16	
		        int16 tmpInt16;
				xmlSubNode.SetAttribute("type","int16");
				if (msg->FindInt16(name, count-1, &tmpInt16) == B_OK){
					xmlSubNode.SetAttribute("value",tmpInt16);
				}
				break;
			}
			case B_INT32_TYPE:{
				TRACE();
				xmlSubNode.SetAttribute("type","int32");
				int32 tmpInt32;
				if (msg->FindInt32(name, count-1, &tmpInt32) == B_OK){
					xmlSubNode.SetAttribute("value",tmpInt32);
				}	
				break;
			}
			case B_INT64_TYPE:{
				TRACE();
				int64 tmpInt64;
				xmlSubNode.SetAttribute("type","int64");
				 if (msg->FindInt64(name, count-1, &tmpInt64) == B_OK){
					xmlSubNode.SetAttribute("value",tmpInt64);
				}	
				break;
			}
			case B_FLOAT_TYPE:{
		        TRACE();
		        float	tmpFloat;
				xmlSubNode.SetAttribute("type","float");
				if (msg->FindFloat(name, count-1, &tmpFloat) == B_OK){
					xmlSubNode.SetDoubleAttribute("value",tmpFloat);
				}
				break;
			}
			case B_DOUBLE_TYPE:{
				TRACE();
				double tmpDouble;
				xmlSubNode.SetAttribute("type","double");
				if (msg->FindDouble(name, count-1, &tmpDouble) == B_OK){
					xmlSubNode.SetDoubleAttribute("value", tmpDouble);
				}	
				break;
			}	
			case B_STRING_TYPE:{
				TRACE();
				xmlSubNode.SetAttribute("type","string");
				const char *tmpChar;
				 if (msg->FindString(name, count-1, &tmpChar) == B_OK){
					xmlSubNode.SetAttribute("value",tmpChar);
				}
				break;
			}
			case B_POINT_TYPE:{
				TRACE();
				BPoint tmpPoint;
				xmlSubNode.SetAttribute("type","BPoint");
				if (msg->FindPoint(name, count-1, &tmpPoint) == B_OK){
					xmlSubNode.SetDoubleAttribute("x",tmpPoint.x);
					xmlSubNode.SetDoubleAttribute("y",tmpPoint.y);
				}
				break;
			}
			case B_RECT_TYPE:{
				TRACE();
				BRect tmpRect;
				if (msg->FindRect(name, count-1, &tmpRect) == B_OK){
					xmlSubNode.SetAttribute("type","BRect");
					xmlSubNode.SetDoubleAttribute("top",tmpRect.top);
					xmlSubNode.SetDoubleAttribute("left",tmpRect.left);
					xmlSubNode.SetDoubleAttribute("bottom",tmpRect.bottom);
					xmlSubNode.SetDoubleAttribute("right",tmpRect.right);
				}	
				break;
			}	
			case B_REF_TYPE:{
				TRACE();
				entry_ref tmpRef;
				if (msg->FindRef(name, count-1, &tmpRef) == B_OK){
					BPath *path= new BPath(&tmpRef);
					xmlSubNode.SetAttribute("type","B_REF_TYPE");
					xmlSubNode.SetAttribute("path",path->Path());
					delete path;
				}	
				break;
			}	
	/*		case B_MESSENGER_TYPE:{
				if (msg->FindData(name, B_ANY_TYPE, i, (const void **)&data, &numBytes) == B_OK){
					BMessage *messengerArchive	= new BMessage();
					((BMessenger*)data)->Archive(messengerArchive , true);
					xmlSubNode.SetAttribute("type","B_MESSENGER_TYPE");
					xmlSubNode.InsertEndChild(ProcessMessage(messengerArchive));
				}	
			}*/	
			case B_POINTER_TYPE:{
				TRACE();
				void *tmpPointer;
				if (msg->FindPointer(name, count-1, &tmpPointer) == B_OK){
					xmlSubNode.SetAttribute("type","B_POINTER_TYPE");
					xmlSubNode.SetDoubleAttribute("value",(int32)tmpPointer);
				}	
				break;
			}
		}
		xmlNode.InsertEndChild(xmlSubNode);
		i++;
	}
	return xmlNode;
}
