##############################################
# CMakeLists for PhotoQt: http://photoqt.org #
##############################################

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(photoqt)

#### SOURCES ####
# toplevel
SET(photoqt_SOURCES main.cpp mainwindow.cpp globalsettings.h fileformats.h globalvariables.h setupwidgets.h)
# settings/
SET(p "settings")
SET(photoqt_SOURCES ${photoqt_SOURCES} ${p}/settings.cpp ${p}/settingstabexif.cpp ${p}/settingstabexiftiles.cpp ${p}/settingstablookandfeel.cpp)
SET(photoqt_SOURCES ${photoqt_SOURCES} ${p}/settingstabother.cpp ${p}/settingstabothercontext.cpp ${p}/settingstabothercontexttiles.cpp)
SET(photoqt_SOURCES ${photoqt_SOURCES} ${p}/settingstabotherlanguagetiles.cpp ${p}/settingstabshortcuts.cpp ${p}/settingstabshortcutschangecommand.cpp)
SET(photoqt_SOURCES ${photoqt_SOURCES} ${p}/settingstabshortcutskeydetect.cpp ${p}/settingstabshortcutstiles.cpp ${p}/settingstabthumbnail.cpp)
SET(photoqt_SOURCES ${photoqt_SOURCES} ${p}/shortcuts.h ${p}/settingstabotherfiletypestiles.cpp)
# thumbnails/
SET(p "thumbnails")
SET(photoqt_SOURCES ${photoqt_SOURCES} ${p}/thumbnailpixmapitem.cpp ${p}/thumbnails.cpp ${p}/thumbnailview.cpp ${p}/threadforthumbnails.h)
# graphics/
SET(p "graphics")
SET(photoqt_SOURCES ${photoqt_SOURCES} ${p}/graphicsview.cpp ${p}/graphicsitem.cpp ${p}/imagereader.cpp ${p}/graphicsviewlay.cpp)
# widgets/
SET(p "widgets")
SET(photoqt_SOURCES ${photoqt_SOURCES} ${p}/aboutwidget.cpp ${p}/customconfirm.cpp ${p}/dropdownmenu.cpp ${p}/dropdownmenuitem.cpp ${p}/detailswidget.cpp)
SET(photoqt_SOURCES ${photoqt_SOURCES} ${p}/filehandling.cpp ${p}/startupwidget.cpp ${p}/mywidget.cpp ${p}/quicksettings.cpp)
# filterimages/
SET(p "filterimages")
SET(photoqt_SOURCES ${photoqt_SOURCES} ${p}/filterimagessetup.cpp ${p}/filterimagesdisplay.cpp)
# customelements/
SET(p "customelements")
SET(photoqt_SOURCES ${photoqt_SOURCES} ${p}/customcheckbox.cpp ${p}/customcombobox.cpp ${p}/customlineedit.cpp ${p}/custompushbutton.cpp)
SET(photoqt_SOURCES ${photoqt_SOURCES} ${p}/customradiobutton.cpp ${p}/customscrollbar.cpp ${p}/customslider.cpp ${p}/customspinbox.cpp)
SET(photoqt_SOURCES ${photoqt_SOURCES} ${p}/customlabel.cpp ${p}/customtabwidget.cpp ${p}/customline.h)
# manipulation/
SET(p "manipulation")
SET(photoqt_SOURCES ${photoqt_SOURCES} ${p}/scale.cpp)
# [other]/
SET(photoqt_SOURCES ${photoqt_SOURCES} slideshow/slideshowbar.cpp slideshow/slideshowsettings.cpp flowlayout/flowlayout.cpp wallpaper/wallpaper.cpp)

#### HEADER ####
# toplevel
SET(photoqt_HEADERS mainwindow.h globalsettings.h fileformats.h globalvariables.h setupwidgets.h)
# settings/
SET(p "settings")
SET(photoqt_HEADERS ${photoqt_HEADERS} ${p}/shortcuts.h ${p}/settings.h ${p}/settingstabexif.h ${p}/settingstabexiftiles.h ${p}/settingstablookandfeel.h)
SET(photoqt_HEADERS ${photoqt_HEADERS} ${p}/settingstabother.h ${p}/settingstabothercontext.h ${p}/settingstabothercontexttiles.h)
SET(photoqt_HEADERS ${photoqt_HEADERS} ${p}/settingstabotherlanguagetiles.h ${p}/settingstabshortcuts.h ${p}/settingstabshortcutschangecommand.h)
SET(photoqt_HEADERS ${photoqt_HEADERS} ${p}/settingstabshortcutskeydetect.h ${p}/settingstabshortcutstiles.h ${p}/settingstabthumbnail.h)
SET(photoqt_HEADERS ${photoqt_HEADERS} ${p}/settingstabotherfiletypestiles.h)
# thumbnails/
SET(p "thumbnails")
SET(photoqt_HEADERS ${photoqt_HEADERS} ${p}/threadforthumbnails.h ${p}/thumbnailpixmapitem.h ${p}/thumbnails.h ${p}/thumbnailview.h)
# graphics/
SET(p "graphics")
SET(photoqt_HEADERS ${photoqt_HEADERS} ${p}/graphicsview.h ${p}/graphicsitem.h ${p}/imagereader.h ${p}/graphicsviewlay.h)
# widgets/
SET(p "widgets")
SET(photoqt_HEADERS ${photoqt_HEADERS} ${p}/aboutwidget.h ${p}/customconfirm.h ${p}/dropdownmenu.h ${p}/dropdownmenuitem.h ${p}/detailswidget.h)
SET(photoqt_HEADERS ${photoqt_HEADERS} ${p}/filehandling.h ${p}/startupwidget.h ${p}/mywidget.h ${p}/quicksettings.h)
# filterimages/
SET(p "filterimages")
SET(photoqt_HEADERS ${photoqt_HEADERS} ${p}/filterimagessetup.h ${p}/filterimagesdisplay.h)
# customelements/
SET(p "customelements")
SET(photoqt_HEADERS ${photoqt_HEADERS} ${p}/customcheckbox.h ${p}/customcombobox.h ${p}/customlineedit.h ${p}/custompushbutton.h)
SET(photoqt_HEADERS ${photoqt_HEADERS} ${p}/customradiobutton.h ${p}/customscrollbar.h ${p}/customslider.h ${p}/customspinbox.h ${p}/customlabel.h)
SET(photoqt_HEADERS ${photoqt_HEADERS} ${p}/customtabwidget.h ${p}/customline.h)
# manipulation/
SET(p "manipulation")
SET(photoqt_HEADERS ${photoqt_HEADERS} ${p}/scale.h)
# [other]/
SET(photoqt_HEADERS ${photoqt_HEADERS} slideshow/slideshowbar.h slideshow/slideshowsettings.h flowlayout/flowlayout.h wallpaper/wallpaper.h)


#############################################
#### OPTIONS THAT CAN BE SET BY THE USER ####
#############################################

OPTION(EXIV2 "Use exiv2 library" ON)
OPTION(GM "Use graphicsmagick library" ON)
OPTION(QTONLY "ONLY USE QT-ONLY FEATURES" OFF)


################################
#### FIND REQUIRED PACKAGES ####
################################

FIND_PACKAGE(Qt5Widgets 5.2 REQUIRED)
FIND_PACKAGE(Qt5LinguistTools 5.2 REQUIRED)

# Instead of having a hardcoded path for GraphicsMagick, we use a FindMagick.cmake file to search for it
SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake" ${CMAKE_MODULE_PATH})
FIND_PACKAGE(Magick)
FIND_PACKAGE(Exiv2)


###################################
###### REMOVE BEFORE RELEASE ######
###################################
SET(CMAKE_BUILD_TYPE Debug)


####################################
#### TRANSLATIONS AND RESOURCES ####
####################################

# Add *.ts translation files (looping over all of them)
FILE(GLOB files "lang/*.ts")
FOREACH(file ${files})
	QT5_CREATE_TRANSLATION(qm_files ${photoqt_SOURCES} ${file})
ENDFOREACH()

# Copy the language QRC file to the output directory, because the files listed in the
# qrc file are relative to that directory.
ADD_CUSTOM_COMMAND(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/resLang.qrc
		   COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/resLang.qrc ${CMAKE_CURRENT_BINARY_DIR}/resLang.qrc
		   MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/resLang.qrc
		   DEPENDS ${qm_files})

# Set resources
SET(photoqt_RESOURCES resImg.qrc ${CMAKE_CURRENT_BINARY_DIR}/resLang.qrc)

# add resource file
QT5_ADD_RESOURCES(photoqt_RESOURCES_RCC ${photoqt_RESOURCES})



######################
#### FINISHING UP ####
######################

# moc files
QT5_WRAP_CPP(photoqt_HEADERS_MOC ${photoqt_HEADERS})

# include, add defiunitions and include dirs
INCLUDE_DIRECTORIES(${Qt5Widgets_INCLUDES})
ADD_DEFINITIONS(${Qt5Widgets_DEFINITIONS})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

# And add the executeable (on windows we add application icons...)
IF(WIN32)
	ADD_EXECUTABLE(photoqt WIN32 ${photoqt_SOURCES} ${photoqt_HEADERS_MOC} ${qm_files} ${photoqt_RESOURCES_RCC} ${trans_outfile} windowsicons.rc)
ELSEIF(NOT WIN32)
	ADD_EXECUTABLE(photoqt ${photoqt_SOURCES} ${photoqt_HEADERS_MOC} ${qm_files} ${photoqt_RESOURCES_RCC} ${trans_outfile})
ENDIF(WIN32)
QT5_USE_MODULES(photoqt Core Sql Widgets Multimedia Svg)


#Depending on setup, we copy one of the desktop files to photoqt.desktop
IF(GM)
	ADD_CUSTOM_COMMAND(TARGET photoqt POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/for_photoqt_desktop_FULL ${CMAKE_CURRENT_SOURCE_DIR}/photoqt.desktop)
ELSEIF(NOT GM)
	ADD_CUSTOM_COMMAND(TARGET photoqt POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/for_photoqt_desktop_QT ${CMAKE_CURRENT_SOURCE_DIR}/photoqt.desktop)
ENDIF(GM)


MESSAGE("")


########################
#### CUSTOM OPTIONS ####
########################

IF(NOT QTONLY)

	IF(EXIV2)
		IF(NOT ${EXIV2_FOUND})
			MESSAGE(FATAL_ERROR "** Unable to locate Exiv2... is it installed?")
		ELSEIF(${EXIV2_FOUND})
			INCLUDE_DIRECTORIES(${EXIV2_INCLUDE_DIR})
			TARGET_LINK_LIBRARIES(photoqt "exiv2")
			ADD_DEFINITIONS(-DEXIV2)
			MESSAGE("** Exiv2 enabled")
		ENDIF(NOT ${EXIV2_FOUND})
	ELSEIF(NOT EXIV2)
		MESSAGE("** Exiv2 DISABLED")
	ENDIF(EXIV2)

	IF(GM)
		IF(NOT ${MAGICK++_FOUND})
			MESSAGE(FATAL_ERROR "** Unable to locate GraphicsMagick... is it installed?")
		ELSEIF(${MAGICK++_FOUND})
			INCLUDE_DIRECTORIES(${MAGICK++_INCLUDE_DIR})
			TARGET_LINK_LIBRARIES(photoqt "GraphicsMagick++")
			ADD_DEFINITIONS(-DGM)
			MESSAGE("** Graphicsmagick enabled")
		ENDIF(NOT ${MAGICK++_FOUND})
	ELSEIF(NOT GM)
		MESSAGE("** Graphicsmagick DISABLED")
	ENDIF(GM)

ELSEIF(QTONLY)
	MESSAGE("** All non-Qt features DISABLED")
ENDIF(NOT QTONLY)


MESSAGE("")



#######################
#### INSTALL FILES ####
#######################

IF(UNIX)

	# Set the install prefix to /usr/
	SET(PRODUCT_INSTALL_PREFIX /usr)

	# Install executeable
	INSTALL(
		TARGETS photoqt
		DESTINATION bin/
	)

	# Install desktop file
	INSTALL(
		FILES photoqt.desktop
		DESTINATION share/applications
	)

	# And install all the icons
	INSTALL(
		FILES icons/16x16/apps/photoqt.png
		DESTINATION share/icons/hicolor/16x16/apps/
	)
	INSTALL(
		FILES icons/32x32/apps/photoqt.png
		DESTINATION share/icons/hicolor/32x32/apps/
	)
	INSTALL(
		FILES icons/48x48/apps/photoqt.png
		DESTINATION share/icons/hicolor/48x48/apps/
	)
	INSTALL(
		FILES icons/64x64/apps/photoqt.png
		DESTINATION share/icons/hicolor/64x64/apps/
	)
	INSTALL(
		FILES icons/128x128/apps/photoqt.png
		DESTINATION share/icons/hicolor/128x128/apps/
	)
ENDIF(UNIX)



##########################
#### UNINSTALL TARGET ####
##########################

CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/CMake/cmake_uninstall.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake" IMMEDIATE @ONLY)
ADD_CUSTOM_TARGET(uninstall COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

