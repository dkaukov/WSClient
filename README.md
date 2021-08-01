# WSClient for Qt6

QTCPsocket based Websocket client 

Library used came from https://github.com/cculianu/WebSocket

This WSClient is targeted to work with TCI protocol https://github.com/maksimus1210/TCI (TCI uses ws;// on transport layer)

This project is the sub of larger project, located here: https://github.com/VK6NX/Remote_ATU

Current WSClient mean to be inegrated into QML under Qt6 and became integrated part of ATUconnect (explained in RemoteATU), replacing current standalone TCI-MQTT-Gateway https://github.com/dkaukov/tci-mqtt-gateway/releases/tag/v.0.1

Current caveats:
1. Unable to send the "configuration command" via ws once ws connection established and running (app crashes). Can possibly be issue with threading.
2. Unable to capture connection failures. For some reason those does not appear.
