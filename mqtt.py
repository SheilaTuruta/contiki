# import paho.mqtt.client as mqtt #import the client1
# broker_address="fd00:baba:ca::1" 
# #broker_address="iot.eclipse.org"
# print("creating new instance")
# client = mqtt.Client("P1") #create new instance
# print("connecting to broker")
# client.connect(broker_address) #connect to broker
# print("Subscribing to topic","house/bulbs/bulb1")
# client.subscribe("00124B001375D806/msg")
# # print("Publishing message to topic","house/bulbs/bulb1")
# # client.publish("house/bulbs/bulb1","OFF")


import paho.mqtt.client as mqtt #import the client1
import time
import datetime as dt
import pymysql


host_db = '10.4.6.18'
table = 'measures'
############
def on_message(client, userdata, message):
    print("message received " ,str(message.payload.decode("utf-8")))
    print("message topic=",message.topic)
    print("message qos=",message.qos)
    print("message retain flag=",message.retain)
    print("time now=", dt.datetime.now())
    signal = str(message.topic)  # verificar se quiser valores específicos
    # get value from mqtt
    value = str(message.payload.decode("utf-8")) # verificar se quiser valores específicos
    sql_save = "INSERT INTO "+ table +" (sensor, date, time, value) VALUES (%s, %s, %s, %s)"
    now = dt.datetime.now()
    val = ( str(signal), now.strftime("%d/%m/%Y"), now.strftime("%H:%M:%S.%f")[:-3], str(value))
    cursor.execute(sql_save, val)    
    db.commit()    

########################################
broker_address="fd00:baba:ca::1"
db = pymysql.connect(host=host_db,   # openning database connection
                        user='admin',
                        password='lit',
                        db='db_temp'#,
                        # cursorclass=pymysql.cursors.DictCursor
                        )
cursor = db.cursor()  
#broker_address="iot.eclipse.org"
print("creating new instance")
client = mqtt.Client("P1") #create new instance
client.on_message=on_message #attach function to callback
print("connecting to broker")
client.connect(broker_address) #connect to broker
# client.loop_start() #start the loop
print("Subscribing to topic","+/msg")
client.subscribe("+/msg")
# print("Publishing message to topic","house/bulbs/bulb1")
# client.publish("house/bulbs/bulb1","OFF")
time.sleep(1) # wait
# client.loop_stop() #stop the loop
client.loop_forever() #stop the loop
db.close()
