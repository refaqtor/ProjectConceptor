plugins = \
	AddAttributeCommand \
	ChangeValueCommand \
	CopyCommand \
	DeleteCommand \
	FindCommand \
	GraphEditor \
	GroupCommand \
	InsertCommand \
	MoveCommand \
	NavigatorEditor \
	PasteCommand \
	RemoveAttributeCommand \
	ResizeCommand \
	SelectCommand 


default:
	for dir in $(plugins); do \
		$(MAKE) -C $$dir; \
	done

clean: 
	for dir in $(plugins); do \
		$(MAKE) -C $$dir clean; \
	done    

install: 
	for dir in $(plugins); do \
		$(MAKE) -C $$dir install; \
	done


catkeys:
	for dir in $(plugins); do \
		$(MAKE) -C $$dir catkeys; \
	done

bindcatalogs:
	$(MAKE) -C GraphEditor bindcatalogs; \
	$(MAKE) -C NavigatorEditor bindcatalogs; \

    
 
FORCE:
