import QtQuick 2.5

SpriteSequence {
    id: bubble
    width: 64
    height: 64
    interpolate: false
    goalSprite: ""

    Behavior on scale {
        NumberAnimation { duration: 150; easing.type: Easing.OutBack }
    }

    Sprite {
        name: "big"
        source: "gfx/catch.png"
        frameCount: 1
        to: { "burst" : 0 }
    }

    Sprite {
        name: "burst"
        source: "gfx/catch-action.png"
        frameCount: 3
        frameX: 64
        frameDuration: 200
    }

    Sprite { //WORKAROUND: This prevents the triggering of a rendering error which is currently under investigation.
        name: "dummy"
        source: "gfx/melee-idle.png"
        frameCount: 8
        frameWidth: 64
        frameHeight: 64
        frameX: 0
        frameDuration: 200
    }
    SequentialAnimation on width {
        loops: Animation.Infinite
        NumberAnimation { from: width * 1; to: width * 1.1; duration: 800; easing.type: Easing.InOutQuad }
        NumberAnimation { from: width * 1.1; to: width * 1; duration: 1000; easing.type: Easing.InOutQuad }
    }
    SequentialAnimation on height {
        loops: Animation.Infinite
        NumberAnimation { from: height * 1; to: height * 1.15; duration: 1200; easing.type: Easing.InOutQuad }
        NumberAnimation { from: height * 1.15; to: height * 1; duration: 1000; easing.type: Easing.InOutQuad }
    }
}
