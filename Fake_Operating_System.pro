QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# The Windows version of make does not handle spaces well. As a result, we need to ensure that the target name
# does not have any spaces.
TARGET = $$replace(TARGET, " ", _)

###############################################################################
# BEGIN SECTION FOR SPECIFYING SOURCE/LIBRARY/RESOURCE FILES OF PROJECT       #
###############################################################################

# checks to make sure we haven't accidentally opened the project
# from within a ZIP archive (common mistake on Windows)

win32 {
    contains(PWD, .*\.zip.*) | contains(PWD, .*\.ZIP.*) {
        message("")
        message(*******************************************************************)
        message(*** ERROR: You are trying to open this project from within a .ZIP archive:)
        message(*** $$PWD)
        message(*** You need to extract the files out of the ZIP file first.)
        message(*** Open the ZIP in your file explorer and press the Extract button.)
        message(*******************************************************************)
        message("")
        error(Exiting.)
    }
}

# check for intl chars in path (common issue for intl students)
PWD_WITHOUT_BAD_CHARS = $$PWD
PWD_WITHOUT_BAD_CHARS ~= s|[^a-zA-Z0-9_ ().\/:;+-]+|???
BAD_CHARS = $$PWD
BAD_CHARS ~= s|[a-zA-Z0-9_ ().\/:;-]+|
!isEmpty(BAD_CHARS) {
    message("")
    message(*******************************************************************)
    message(*** ERROR: Your project directory contains invalid characters:)
    message(*** $$PWD)
    message(***)
    message(*** The characters that are invalid are: $$BAD_CHARS)
    message(***)
    message(*** You need to store your project in a directory without any punctuation)
    message(*** marks such as commas, or international symbols such as)
    message(*** Chinese or Korean symbols.)
    message(*** If you keep seeing this error try creating a simple directory)
    message(*** name such as "C:\Programs\Homework1.")
    message(*******************************************************************)
    message("")
    error(Exiting.)
}

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# include various source .cpp files and header .h files in the build process
# (student's source code can be put into project root, or src/ subfolder)
SOURCES *= $$files($$PWD/src/*.cpp, true) \

HEADERS *= $$files($$PWD/lib/ProcessManagement/*.h, true)
HEADERS *= $$files($$PWD/lib/MemoryManagement/*.h, true)
HEADERS *= $$files($$PWD/lib/FileSystem/*.h, true)
HEADERS *= $$files($$PWD/lib/GUI/*.h, true)
HEADERS *= $$files($$PWD/lib/TestApp/*.h, true)

# directories examined by Qt Creator when student writes an #include statement
INCLUDEPATH *= $$PWD/lib/ProcessManagement/
INCLUDEPATH *= $$PWD/lib/MemoryManagement/
INCLUDEPATH *= $$PWD/lib/FileSystem/
INCLUDEPATH *= $$PWD/lib/GUI/
INCLUDEPATH *= $$PWD/lib/TestApp/

FORMS += \
    activitymonitor.ui \
    fileexplorer.ui \
    mainwindow.ui \
    mappingdisplayer.ui \
    properties.ui \
    testapp.ui

RESOURCES += \
    resource/resource.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
