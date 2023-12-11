import paho.mqtt.client as paho
import ssl

broker = "INSERT IP HERE"
#port = 1883
topic="testtopic"
#required tls files should be placed in this directory 
def on_publish(client, userdata, result):
    print("data published")
    pass
client = paho.Client(client_id = "pytest")
client.tls_set(ca_certs = "ca.crt",
                certfile = "client.crt",
                keyfile = "client.key",
                cert_reqs=ssl.CERT_NONE)
client.tls_insecure_set(True)
client.username_pw_set("mqtt_server", "mqtt_server")
client.on_publish = on_publish
client.connect(broker, port = 8883)
ret = client.publish(topic, "test")

