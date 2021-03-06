## BeOS Generic Makefile v2.0 ##

## Fill in this file to specify the project being created, and the referenced
## makefile-engine will do all of the hard work for you.  This handles both
## Intel and PowerPC builds of the BeOS.

## Application Specific Settings ---------------------------------------------

# specify the name of the binary
NAME= ProjectConceptor

# specify the type of binary
#	APP:	Application
#	SHARED:	Shared library or add-on
#	STATIC:	Static library archive
#	DRIVER: Kernel Driver
TYPE= APP

# 	If you plan to use localization, specify the application's MIME signature.
APP_MIME_SIG = application/x-vnd.ProjectConceptor

#	specify the source files to use
#	full paths or paths relative to the makefile can be included
# 	all files, regardless of directory, will have their object
#	files created in the common object directory.
#	Note that this means this makefile will not work correctly
#	if two source files with the same name (source.c or source.cpp)
#	are included from different directories.  Also note that spaces
#	in folder names do not work well with this makefile.
SRCS= 	About/AboutWindow.cpp \
		About/AboutView.cpp \
		About/AboutURLView.cpp \
		MainView.cpp \
		ProjectConceptorDefs.cpp \
		ProjectConceptor.cpp \
		Config/ConfigManager.cpp \
		Config/ConfigWindow.cpp \
		Config/ConfigView.cpp \
		Config/PluginView.cpp \
		Config/PluginItem.cpp \
		Config/PluginInfoView.cpp \
		Config/MessageView.cpp \
		Commands/PCommand.cpp \
		Commands/PCommandManager.cpp \
		Document/PDocument.cpp \
		Document/PDocumentManager.cpp \
		Document/PDocLoader.cpp \
		Document/PEditor.cpp \
		Document/PEditorManager.cpp \
		Document/PWindow.cpp \
		Document/HelpManager.cpp \
		ToolBar/BaseItem.cpp \
		ToolBar/Mover.cpp \
		ToolBar/ToolBar.cpp \
		ToolBar/ToolBarSeperator.cpp \
		ToolBar/ToolItem.cpp \
		ToolBar/ToolMenu.cpp\
		ToolBar/ColorToolItem.cpp \
		ToolBar/FloatToolItem.cpp \
		ToolBar/PatternToolItem.cpp \
		Tools/AFont.cpp \
		Tools/PCSavePanel.cpp \
		Tools/Indexer.cpp \
		Tools/InputRequestView.cpp \
 		Tools/InputRequest.cpp \
 		Tools/MessageXmlReader.cpp \
		Tools/MessageXmlWriter.cpp \
		Tools/ShortCutFilter.cpp \
		Tools/TextViewCompleter.cpp \
		Tools/plugins/BasePlugin.cpp \
		Tools/plugins/PluginManager.cpp
#		Tools/FontPanel/FontListView.cpp \
#		Tools/FontPanel/FontPanel.cpp \
#		Tools/FontPanel/FontPreview.cpp \
#		Tools/FontPanel/FontView.cpp \


#	Specify the resource definition files to use. Full or relative paths can be
#	used.
RDEFS= ProjectConceptor.rdef Tools/InputRequest.rdef

#	specify the resource files to use
#	full path or a relative path to the resource file can be used.
RSRCS= 

#	specify additional libraries to link against
#	there are two acceptable forms of library specifications
#	-	if your library follows the naming pattern of:
#		libXXX.so or libXXX.a you can simply specify XXX
#		library: libbe.so entry: be
#
#	- 	if your library does not follow the standard library
#		naming scheme you need to specify the path to the library
#		and it's name
#		library: my_lib.a entry: my_lib.a or path/my_lib.a
LIBS= be root translation tracker localestub $(STDCPPLIBS) tinyxml

#	specify additional paths to directories following the standard
#	libXXX.so or libXXX.a naming scheme.  You can specify full paths
#	or paths relative to the makefile.  The paths included may not
#	be recursive, so include all of the paths where libraries can
#	be found.  Directories where source files are found are
#	automatically included.
LIBPATHS=

#	additional paths to look for system headers
#	thes use the form: #include <header>
#	source file directories are NOT auto-included here
SYSTEM_INCLUDE_PATHS =	/boot/system/develop/headers/private/support \
						/boot/system/develop/headers/private/shared \
						/boot/system/develop/headers/private/interface

#	additional paths to look for local headers
#	thes use the form: #include "header"
#	source file directories are automatically included
LOCAL_INCLUDE_PATHS =	. \
					../include \
					../include/plugins \
					Commands \
					Config \
					DataContainer \
					Document \
					ToolBar \
					About \
					Tools \
					Tools/FontPanel

LOCALES = de en es fr fur hr ro sv

#	specify the level of optimization that you desire
#	NONE, SOME, FULL
# OPTIMIZE= FULL

#	specify any preprocessor symbols to be defined.  The symbols
#	will be set to a value of 1.  For example specify DEBUG if you want
#	DEBUG=1 to be set when compiling.
#DEFINES =   DEBUG

#	specify special warning levels
#	if unspecified default warnings will be used
#	NONE = supress all warnings
#	ALL = enable all warnings
# WARNINGS = ALL

#	specify whether image symbols will be created
#	so that stack crawls in the debugger are meaningful
#	if TRUE symbols will be created
#SYMBOLS = TRUE

#	specify debug settings
#	if TRUE will allow application to be run from
#	a source-level debugger
#DEBUGGER = TRUE

#	specify additional compiler flags for all files
COMPILER_FLAGS =

#	specify additional linker flags
LINKER_FLAGS =

SVG_ICON = ../../Data/Icons/Logogross.svg

#EXTRA_DEPS = copy

TARGET_DIR	=  .

#INSTALL_DIR	= /boot/apps/ProjectConceptor
PLUGIN_DIR	= Plugins


APP_MENU	= Software

## include the makefile-engine
DEVEL_DIRECTORY := \
	$(shell findpaths -r "makefile_engine" B_FIND_PATH_DEVELOP_DIRECTORY)
include $(DEVEL_DIRECTORY)/etc/makefile-engine




default .DEFAULT:
	mkdir -p ../../$(APP_DIR)
	cp -rf $(NAME) ../../$(APP_DIR)
	ln -sf $(NAME) ../../$(APP_DIR)/ProjectConceptor.a
	cp -rf ../.PackageInfo ../../bin
	mkdir -p ../../bin/data/deskbar/menu/Applications
	ln -sf ../../../../apps/ProjectConceptor/$(NAME) ../../bin/data/deskbar/menu/Applications


