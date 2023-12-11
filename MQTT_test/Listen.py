import paho.mqtt.client as paho
import ssl

broker = "INSERT IP HERE"

#required tls files need to be placed in this directory 

def onMessageFunc(client, userdata, message):
    print("Message received", str(message.payload.decode("utf-8", "ignore")))

client = paho.Client(client_id = "pytest")
client.tls_set(ca_certs = "ca.crt",
                certfile = "client.crt",
                keyfile = "client.key",
                cert_reqs=ssl.CERT_NONE)
client.tls_insecure_set(True)
client.username_pw_set("mqtt_server", "mqtt_server")
client.on_message = onMessageFunc
client.connect(broker, port = 8883)
client.subscribe("testtopic")
client.loop_forever()
