#include "MessageXmlWriter.h"
#include <storage/File.h>
#include <storage/Path.h>
#include <storage/Entry.h>
#include <support/Debug.h>
#include <mail/mail_encoding.h>


MessageXmlWriter::MessageXmlWriter(){
    filePath=new BString("");
}

MessageXmlWriter::MessageXmlWriter(const BString &fileName){
	filePath=new BString("");
    SetTo(fileName);
}

MessageXmlWriter::~MessageXmlWriter(){
}

status_t MessageXmlWriter::InitCheck(){
    BFile   file (filePath->String(),B_WRITE_ONLY);
    return file.InitCheck();
}

void MessageXmlWriter::SetTo(const BString &fileName){
    if (fileName!=NULL){
        filePath->SetTo(fileName);
 		doc =TiXmlDocument();
		//add the Comment
		TiXmlDeclaration declare =  TiXmlDeclaration("1.0","UTF-8","yes");
  		TiXmlComment	comment("Generated by MessageXmlWriter");
  		doc.InsertEndChild(declare);
		doc.InsertEndChild(comment);
    }
    
}

status_t MessageXmlWriter::Write(BMessage &message){
  	doc.InsertEndChild(ProcessMessage(NULL,&message));
    if ( doc.SaveFile(filePath->String()) == true)
    	return B_OK;
    else
    	return B_ERROR;
}

status_t MessageXmlWriter::WriteFile(const BString &fileName,const BMessage &message){
	TiXmlDocument	doc;
	TiXmlDeclaration declare =  TiXmlDeclaration("1.0","UTF-8","yes");
	TiXmlComment	comment("Generated by MessageXmlWriter");
	doc.InsertEndChild(declare);
	doc.InsertEndChild(comment);
  	doc.InsertEndChild(ProcessMessage(NULL,(BMessage*)&message));
    if ( doc.SaveFile(fileName.String()) == true)
    	return B_OK;
    else
    	return B_ERROR;
}

TiXmlElement  MessageXmlWriter::ProcessMessage(const char* bName, BMessage *msg){
	TiXmlElement	xmlNode("BMessage");
	TiXmlElement	xmlSubNode("Data");
	if (bName != NULL)
		xmlNode.SetAttribute("name",bName);
	xmlNode.SetAttribute("type","BMessage");
	xmlNode.SetAttribute("what",(int32)(msg->what));
	char		*name;
	uint32	    type;
	int32		count;
	int32		i	= 0;
	int32		q	= 0;
	TRACE();
		while (msg->GetInfo(B_ANY_TYPE,i ,(char **)&name, &type, &count) == B_OK) {
		TRACE();
		switch(type){
			case B_MESSAGE_TYPE:{
				for (q=0;q<count;q++) {
					xmlSubNode=TiXmlElement("Data");
		        	xmlSubNode.SetAttribute("name",name);
					BMessage tmpMessage = BMessage();
					if (msg->FindMessage(name,q, &tmpMessage)== B_OK){
						xmlSubNode = ProcessMessage(name ,&tmpMessage);
					}
					xmlNode.InsertEndChild(xmlSubNode);
				}
				break;
			}
			case B_BOOL_TYPE:{
		        //FindBool()
		        bool tmpBool;
		        for (q=0;q<count;q++) {
					xmlSubNode=TiXmlElement("Data");
		        	xmlSubNode.SetAttribute("name",name);
		        	xmlSubNode.SetAttribute("type","bool");
		        	if (msg->FindBool(name, q, &tmpBool) == B_OK){
						if  (tmpBool == true)
							xmlSubNode.SetAttribute("value","true");
						else
							xmlSubNode.SetAttribute("value","false");
		        	}
					xmlNode.InsertEndChild(xmlSubNode);		        	
				}
				break;
			}
			case B_INT8_TYPE:{
		        //FindInt8()	an int8 or uint8
		        int8 tmpInt8;
				for (q=0;q<count;q++) {
					xmlSubNode=TiXmlElement("Data");
		        	xmlSubNode.SetAttribute("name",name);
		        
					xmlSubNode.SetAttribute("type","int8");
				 	if (msg->FindInt8(name, q, &tmpInt8) == B_OK){
						xmlSubNode.SetAttribute("value",tmpInt8);
					}
					xmlNode.InsertEndChild(xmlSubNode);
				}
				break;
			}
			case B_INT16_TYPE:{
		        //FindInt16()	an int16 or uint16
		        int16 tmpInt16;
		        for (q=0;q<count;q++) {
					xmlSubNode=TiXmlElement("Data");
		        	xmlSubNode.SetAttribute("name",name);
		        
					xmlSubNode.SetAttribute("type","int16");
					if (msg->FindInt16(name, q, &tmpInt16) == B_OK){
						xmlSubNode.SetAttribute("value",tmpInt16);
					}
				xmlNode.InsertEndChild(xmlSubNode);
				}
				break;
			}
			case B_INT32_TYPE:{
				int32 tmpInt32;
				for (q=0;q<count;q++) {
					xmlSubNode=TiXmlElement("Data");
		        	xmlSubNode.SetAttribute("name",name);
		        	xmlSubNode.SetAttribute("type","int32");
					if (msg->FindInt32(name, q, &tmpInt32) == B_OK){
						xmlSubNode.SetAttribute("value",tmpInt32);
					}
					xmlNode.InsertEndChild(xmlSubNode);
				}	
				break;
			}
			case B_INT64_TYPE:{
				int64 tmpInt64;
				for (q=0;q<count;q++) {
					xmlSubNode=TiXmlElement("Data");
		        	xmlSubNode.SetAttribute("name",name);
		    		xmlSubNode.SetAttribute("type","int64");
				 	if (msg->FindInt64(name, q, &tmpInt64) == B_OK){
						xmlSubNode.SetAttribute("value",tmpInt64);
					}
					xmlNode.InsertEndChild(xmlSubNode);
				}
				break;
			}
			case B_FLOAT_TYPE:{
		        float	tmpFloat;
		        for (q=0;q<count;q++) {
					xmlSubNode=TiXmlElement("Data");
		        	xmlSubNode.SetAttribute("name",name);
		    		xmlSubNode.SetAttribute("type","float");
					if (msg->FindFloat(name, q, &tmpFloat) == B_OK){
						xmlSubNode.SetDoubleAttribute("value",tmpFloat);
					}
					xmlNode.InsertEndChild(xmlSubNode);
				}
				break;
			}
			case B_DOUBLE_TYPE:{
				double tmpDouble;
				for (q=0;q<count;q++) {
					xmlSubNode=TiXmlElement("Data");
		        	xmlSubNode.SetAttribute("name",name);
		        	xmlSubNode.SetAttribute("type","double");
					if (msg->FindDouble(name, q, &tmpDouble) == B_OK){
						xmlSubNode.SetDoubleAttribute("value", tmpDouble);
					}
					xmlNode.InsertEndChild(xmlSubNode);
				}
				break;
			}
			case B_STRING_TYPE:{
				const char *tmpChar;
				for (q=0;q<count;q++) {
					xmlSubNode=TiXmlElement("Data");
		        	xmlSubNode.SetAttribute("name",name);
		       		xmlSubNode.SetAttribute("type","string");
					if (msg->FindString(name, q, &tmpChar) == B_OK){
						xmlSubNode.SetAttribute("value",tmpChar);
					}
					xmlNode.InsertEndChild(xmlSubNode);
				}
				break;
			}
			case B_POINT_TYPE:{
				BPoint tmpPoint;
				for (q=0;q<count;q++) {
					xmlSubNode=TiXmlElement("Data");
		        	xmlSubNode.SetAttribute("name",name);
					xmlSubNode.SetAttribute("type","BPoint");
					if (msg->FindPoint(name, q, &tmpPoint) == B_OK){
						xmlSubNode.SetDoubleAttribute("x",tmpPoint.x);
						xmlSubNode.SetDoubleAttribute("y",tmpPoint.y);
					}
					xmlNode.InsertEndChild(xmlSubNode);
				}
				break;
			}
			case B_RECT_TYPE:{
				BRect tmpRect;
				for (q=0;q<count;q++) {
					xmlSubNode=TiXmlElement("Data");
		        	xmlSubNode.SetAttribute("name",name);
					if (msg->FindRect(name, q, &tmpRect) == B_OK){
						xmlSubNode.SetAttribute("type","BRect");
						xmlSubNode.SetDoubleAttribute("top",tmpRect.top);
						xmlSubNode.SetDoubleAttribute("left",tmpRect.left);
						xmlSubNode.SetDoubleAttribute("bottom",tmpRect.bottom);
						xmlSubNode.SetDoubleAttribute("right",tmpRect.right);
					}
					xmlNode.InsertEndChild(xmlSubNode);
				}
				break;
			}
			case B_REF_TYPE:{
				entry_ref tmpRef;
				for (q=0;q<count;q++) {
					xmlSubNode=TiXmlElement("Data");
		        	xmlSubNode.SetAttribute("name",name);
					if (msg->FindRef(name, q, &tmpRef) == B_OK){
						BPath *path= new BPath(&tmpRef);
						xmlSubNode.SetAttribute("type","B_REF_TYPE");
						xmlSubNode.SetAttribute("path",path->Path());
						delete path;
					}
					xmlNode.InsertEndChild(xmlSubNode);
				}
				break;
			}
	/*		case B_MESSENGER_TYPE:{
				for (q=0;q<count;q++) {
					xmlSubNode=TiXmlElement("Data");
		        	xmlSubNode.SetAttribute("name",name);
					if (msg->FindData(name, B_ANY_TYPE, i, (const void **)&data, &numBytes) == B_OK){
						BMessage *messengerArchive	= new BMessage();
						((BMessenger*)data)->Archive(messengerArchive , true);
						xmlSubNode.SetAttribute("type","B_MESSENGER_TYPE");
						xmlSubNode.InsertEndChild(ProcessMessage(messengerArchive));
					}
			}*/
			case B_POINTER_TYPE:{
				void *tmpPointer;
				for (q=0;q<count;q++) {
					xmlSubNode=TiXmlElement("Data");
		        	xmlSubNode.SetAttribute("name",name);
					if (msg->FindPointer(name, q, &tmpPointer) == B_OK){
						char *str = new char[64];
						sprintf(str, "%p", *(void**)tmpPointer);
						xmlSubNode.SetAttribute("type","B_POINTER_TYPE");
						xmlSubNode.SetAttribute("value",str);
					}
					xmlNode.InsertEndChild(xmlSubNode);
				}
				break;
			}
			default:{
				char 		*code	= new char[5];
				const void	*data;
				ssize_t		size	= 0;
				ssize_t		len		= 0;
				sprintf(code, "%c%c%c%c", (uint8)(type), (uint8)(type >> 8), (uint8)(type >> 16), (uint8)(type >> 24));
				for (q=0;q<count;q++) {
					xmlSubNode=TiXmlElement("Data");
					xmlSubNode.SetAttribute("name",name);
					xmlSubNode.SetAttribute("type",code);
					//for now we only support base64
					xmlSubNode.SetAttribute("encode","base64");
					if (msg->FindData(name, type,q, &data, &size) == B_OK){
						//make shure the outputdata will fit
						char *encoded = new char[(size*2)];
						if (data != NULL)
							len=encode_base64(encoded,(char *)data,size, false);
							encoded[len] = '\0';
							if (len>0)
								xmlSubNode.SetAttribute("value",encoded);
					}
					xmlNode.InsertEndChild(xmlSubNode);
				}
			}
		}
		i++;
	}
	return xmlNode;
}
