QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Lepton_parser/CompiledExpression.cpp \
    Lepton_parser/ExpressionProgram.cpp \
    Lepton_parser/ExpressionTreeNode.cpp \
    Lepton_parser/Operation.cpp \
    Lepton_parser/ParsedExpression.cpp \
    Lepton_parser/Parser.cpp \
    basic_text_interpreter.cpp \
    error.cpp \
    from_internal_to_user.cpp \
    main.cpp \
    mainwindow.cpp \
    numerical_methods.cpp \
    particular_interpreter.cpp \
    utilities.cpp

HEADERS += \
    Lepton_parser/CompiledExpression.h \
    Lepton_parser/CustomFunction.h \
    Lepton_parser/Exception.h \
    Lepton_parser/ExpressionProgram.h \
    Lepton_parser/ExpressionTreeNode.h \
    Lepton_parser/Lepton.h \
    Lepton_parser/MSVC_erfc.h \
    Lepton_parser/Operation.h \
    Lepton_parser/ParsedExpression.h \
    Lepton_parser/Parser.h \
    Lepton_parser/windowsIncludes.h \
    basic_text_interpreter.h \
    constants.h \
    error.h \
    from_internal_to_user.h \
    mainwindow.h \
    numerical_methods.h \
    particular_interpreter.h \
    utilities.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    help/Metode Numerice 23.08.2021 19_58_47.png \
    help/Metode Numerice 23.08.2021 20_02_44.png \
    help/Metode Numerice 23.08.2021 20_04_23.png \
    help/Metode Numerice 23.08.2021 20_55_23.png \
    help/Metode Numerice 23.08.2021 20_55_51.png \
    help/Metode Numerice 23.08.2021 20_59_08.png \
    help/Metode Numerice 23.08.2021 20_59_46.png \
    help/Metode Numerice 23.08.2021 21_08_32.png \
    help/Metode Numerice 23.08.2021 21_09_23.png \
    help/Metode Numerice 23.08.2021 21_10_05.png \
    help/Metode Numerice 23.08.2021 21_15_13.png \
    help/Metode Numerice 23.08.2021 21_16_39.png \
    help/Metode Numerice 23.08.2021 21_17_31.png \
    help/Metode Numerice 23.08.2021 21_25_25.png \
    help/Metode Numerice 23.08.2021 21_28_22.png \
    help/Metode Numerice 23.08.2021 21_31_10.png \
    help/Metode Numerice 23.08.2021 21_31_55.png \
    help/img1.png \
    help/img10.png \
    help/img11.png \
    help/img12.png \
    help/img13.png \
    help/img14.png \
    help/img15.png \
    help/img16.png \
    help/img17.png \
    help/img2.png \
    help/img3.png \
    help/img4.png \
    help/img5.png \
    help/img6.png \
    help/img7.png \
    help/img8.png \
    help/img9.png \
    images/calculus_book.png \
    images/exit_80.png \
    images/gear (1).png \
    images/gear (2).png \
    images/gear_2.png \
    images/help_80.png \
    images/images_source.png \
    images/run_64.png

RESOURCES += \
    images/gear.qrc
