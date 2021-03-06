/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Dialogs 1.1
import "3rd"
Item {

    Drawer {
        id: drawer
        objectName: "drawer"
        width: 0.66 * parent.width
        height: parent.height

        Label {
            text: "Content goes here!"
            anchors.centerIn: parent
        }
        LoggingRectangle{
            id: loggingRectangle
            objectName: "loggingRectangle"
            anchors.fill: parent
            bordercolor: "green"
        }
    }
   
   width: 1200
   height: 675
    // The checkers background
    ShaderEffect {
        id: tileBackground
        anchors.fill: parent

        property real tileSize: 16
        property color color1: Qt.rgba(0.9, 0.9, 0.9, 1);
        property color color2: Qt.rgba(0.85, 0.85, 0.85, 1);

        property size pixelSize: Qt.size(width / tileSize, height / tileSize);

        fragmentShader:
        "
        uniform lowp vec4 color1;
        uniform lowp vec4 color2;
        uniform highp vec2 pixelSize;
        varying highp vec2 qt_TexCoord0;
        void main() {
            highp vec2 tc = sign(sin(3.14159265358979323846 * qt_TexCoord0 * pixelSize));
            if (tc.x != tc.y)
            gl_FragColor = color1;
            else
            gl_FragColor = color2;
        }
        "
    }
    Court {
        focus: true
        id: renderer
        anchors.fill: parent
        anchors.margins: 10
        MouseArea {
            anchors.fill : parent
            onClicked : {
                renderer.focus = true
            }
        }
        
    }

    FileDialog {
        id: openImageDialog
        title: "Please choose a PNG file for your texture"
        nameFilters: [ "PNG Image Files (*.png)"]
        folder: shortcuts.home
        onAccepted: {
            console.log("You chose: " + openImageDialog.fileUrls)
            renderer.textureName = openImageDialog.fileUrls[0]
            renderer.focus = true
        }
        onRejected: {
            console.log("Cancelled")
            renderer.focus = false
        }
    }



    Item {

        id: resource_loader
        
        property var aspectRatio: parent.height/parent.width 
        
        width: parent.width * 0.1
        height: width * aspectRatio

        anchors.top : renderer.top
        anchors.left : renderer.left
        //Control
        //
        Action {
            id: resource_loader_controller
            text: qsTr("&Open")
            onTriggered: {
                openImageDialog.open()
            }
        }
        //View
        Button {
            anchors.fill: parent
            anchors.margins: parent.width * 0.1
            text : "Open"
            highlighted : true
            action: resource_loader_controller
        }


    }
    
    Rectangle {
        id: labelFrame
        anchors.margins: -10
        radius: 5
        color: "white"
        border.color: "black"
        opacity: 0.8
        anchors.fill: label
    }

    Text {
        id: label
        anchors.bottom: renderer.bottom
        anchors.left: renderer.left
        anchors.right: renderer.right
        anchors.margins: 20
        wrapMode: Text.WordWrap
        text: "Genius Sports / WEB ASSEMBLY Tech Demo."
    }


}
