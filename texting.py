from boltiot import Bolt, Sms #Import Sms and Bolt class from boltiot library  
import json, time,requests
Channel_ID="trashbot_send"
Tele_BotID="902812632:AAEgUwhCVyQzyWVhWJ2KwaJe7NsZsUR-ZrQ"                        
message="The trash can is full - TrashTexter"
def Tele_message(message):
        url='https://api.telegram.org/'+Tele_BotID+ '/sendMessage'
        data={'chat_id':Channel_ID,'text':message}
        try:
                response=requests.request("GET",url,params=data)
                print(response.text)
                telegram_data=json.loads(response.text)
                return telegram_data["ok"]
        except Exception as e:
                print("Error occured in sending message via Telegram")
                print(e)
                return False
Bolt_ID="BOLT1116507"
API_Key="2ef1c496-fd40-49ea-925b-959f9328f2c2"
garbage_full_limit = 10 # the distance between device and  garbage in dustbin
mybolt = Bolt(API_Key,Bolt_ID)#This is to access the bolt device and send commands
response = mybolt.serialRead('10')#fetch data from arduino
while True:
        response = mybolt.serialRead("10")  #Fetching the value from Arduino 
        data = json.loads(response)
        garbage_limit = data['value'].rstrip()
        print("Garbage level is", garbage_limit)
        if int(garbage_limit)<=garbage_full_limit:
                Tele_message(message)
        time.sleep(20)
