import requests

# "variables_values": message,

def send_sms(message):

    url = "https://www.fast2sms.com/dev/bulkV2"

    querystring = {
            "authorization": "g3mOiRkXGy1IdEvawAF4P6c95QYfVJKZh7zbSBtNTe0UqlLCujBGyQR10dCOIMLnzSgv5xPZUmkehu3a",
            "message": message,
            "language": "english",
            "route": "otp",
            "variables_values": message,
            "sender_id":"TXTIND",
            "numbers": "9910776747"}

    headers = {
            'cache-control': "no-cache"
    }
    try:
            response = requests.request("GET", url,headers = headers,params = querystring)
            print(response.text, response)
            print("SMS Successfully Sent")
    except:
            print("Oops! Something wrong")
