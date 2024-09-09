QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
msvc:CONFIG(release, debug|release) {
QMAKE_CFLAGS_RELEASE   -= -O2              # 取消C优化
QMAKE_CFLAGS_RELEASE   += -Zi              # 生成调试信息，放到pdb文件中
QMAKE_CXXFLAGS_RELEASE -= -O2              # 取消C++优化
QMAKE_CXXFLAGS_RELEASE += -Zi              # 生成调试信息
QMAKE_LFLAGS_RELEASE   -= /INCREMENTAL:NO  # 选择增量链接
QMAKE_LFLAGS_RELEASE   += /DEBUG           # 将调试信息放到PDB文件中
message(MSVC编译器Release关闭优化，生成调试信息使用)
}

mingw:CONFIG(release, debug|release) {
QMAKE_CFLAGS_RELEASE   -= -O2              # 取消C优化
QMAKE_CFLAGS_RELEASE   += -O0              # 显示指定禁止优化
QMAKE_CFLAGS_RELEASE   += -g               # 生成C调试信息
QMAKE_CXXFLAGS_RELEASE -= -O2              # 取消C++优化
QMAKE_CXXFLAGS_RELEASE += -O0              # 显示指定禁止优化
QMAKE_CXXFLAGS_RELEASE += -g               # 生成C++调试信息
QMAKE_LFLAGS_RELEASE   -= -Wl,-s           # 取消Release模式删除所有符号表和重新定位信息的设置
QMAKE_LFLAGS_RELEASE   += -g               # 链接器生成调试信息
message(Mingw编译器Release关闭优化，生成调试信息使用)
}

# 如果不加unix，MinGW也会进入这里
unix:gcc:CONFIG(release, debug|release) {
QMAKE_CFLAGS_RELEASE   -= -O2              # 取消C优化
QMAKE_CFLAGS_RELEASE   += -O0              # 显示指定禁止优化
QMAKE_CFLAGS_RELEASE   += -g               # 生成C调试信息
QMAKE_CXXFLAGS_RELEASE -= -O2              # 取消C++优化
QMAKE_CXXFLAGS_RELEASE += -O0              # 显示指定禁止优化
QMAKE_CXXFLAGS_RELEASE += -g               # 生成C++调试信息
QMAKE_LFLAGS_RELEASE   -= -Wl,-O1          # 取消Release模式链接器优化
QMAKE_LFLAGS_RELEASE   += -g               # 链接器生成调试信息
message(GCC编译器Release关闭优化，生成调试信息使用)
}

SOURCES += \
    Extract_BPDU.cpp \
    case_decoder.cpp \
    case_sindecoder.cpp \
    ccyclebuffer.cpp \
    connectdialog.cpp \
    connectdialogsin.cpp \
    dealsourcepackage.cpp \
    dialog.cpp \
    gdata.cpp \
    main.cpp \
    mainwindow.cpp \
    myInclude.cpp \
    network1.cpp \
    network2.cpp \
    networksin.cpp \
    pack_classify.cpp \
    realtimedecoder.cpp \
    realtimedecodersin.cpp \
    transmission.cpp \
    unpack.cpp

HEADERS += \
    Extract_BPDU.h \
    SocketConstant.h \
    case_decoder.h \
    case_sindecoder.h \
    ccyclebuffer.h \
    connectdialog.h \
    connectdialogsin.h \
    dealsourcepackage.h \
    dialog.h \
    gdata.h \
    mainwindow.h \
    myInclude.h \
    network1.h \
    network2.h \
    networksin.h \
    pack_classify.h \
    port_num.h \
    realtimedecoder.h \
    realtimedecodersin.h \
    sockinfo.h \
    transmission.h \
    unpack.h

FORMS += \
    connectdialog.ui \
    connectdialogsin.ui \
    dialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#LIBS += imageDecode.a
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -lpthread libwsock32 libws2_32
