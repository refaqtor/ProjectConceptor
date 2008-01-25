#ifndef P_DOCUMENT_MANAGER_H
#define P_DOCUMENT_MANAGER_H

#include <app/Roster.h>
#include <support/List.h>
#include <storage/Entry.h>
#include <storage/Path.h>
/*
 * @author Paradoxon powered by Jesus Christ
 */
#include "PDocument.h"
#include "PWindow.h"

class PDocumentManager : public BArchivable
{

public:
							PDocumentManager(void);
							PDocumentManager(BMessage *archive);
	virtual					~PDocumentManager();

	virtual	status_t		Archive(BMessage *into, bool deep = true) const;
	static	BArchivable		*Instantiate(BMessage *from);

	virtual	void			AddDocument(PDocument *doc);
	virtual	void			RemoveDocument(PDocument *doc);
	virtual	PDocument*		CreateDocument(void);
	virtual	int32			CountPDocuments(void){return documentList->CountItems();};
	virtual	PDocument*		PDocumentAt(int32 index){return (PDocument *)documentList->ItemAt(index);};
	virtual PluginManager*	GetPluginManager(void){return pluginManager;};
	//neeeed QuitRequested!!!!!
protected:
			void			Init(void);
			void			Init(BMessage *archive);

			BList*			documentList;
			PluginManager	*pluginManager;

private:
};
#endif