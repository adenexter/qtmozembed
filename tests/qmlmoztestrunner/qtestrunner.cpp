/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qmozcontext.h"
#include "qtestrunner.h"
#include <QApplication>
#include <QtQuickTest/quicktest.h>
#include <QtCore/qstring.h>
#ifdef QT_OPENGL_LIB
#include <QtOpenGL/qgl.h>
#endif
#include <QTimer>
#include <stdio.h>
#if defined(Q_WS_X11)
#include <X11/Xlib.h>
#endif

#ifdef QT_OPENGL_LIB
static QWidget *qmltestrunner_create_gl_viewport()
{
    return new QGLWidget();
}
#endif

static int gargc;
static char **gargv;

QTestRunner::QTestRunner(bool isOpenGL, int agargc, char **agargv)
 : QObject(0), mIsOpenGL(isOpenGL)
{
    gargv = agargv;
    gargc = agargc;
}

void QTestRunner::DropInStartup()
{
    RunMainTest();
    QMozContext::GetInstance()->stopEmbedding();
}

int QTestRunner::RunMainTest()
{
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
#ifdef QT_OPENGL_LIB
    if (mIsOpenGL) {
        return quick_test_main(gargc, gargv, "qmlmoztestrunner",
                               qmltestrunner_create_gl_viewport, ".");
    } else
#endif
    {
        return quick_test_main(gargc, gargv, "qmlmoztestrunner", 0, ".");
    }
#else
    return quick_test_main(gargc, gargv, "qmlmoztestrunner", 0);
#endif
};
