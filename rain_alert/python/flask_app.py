from flask import (
    Flask, render_template, request
)
import json
import sms



app = Flask(__name__)
message_status=False

@app.route("/read", methods=["GET"])
def read():
    global message_status
    val = request.args.to_dict()
    print(val)
    rain=val['rain']
    temp = val['temp']
    hum = val['hum']

    data=dict()
    data["rain"]=rain
    data["temp"] = temp[0:-1]
    data["hum"] = hum[0:-1]

    if ( (float(rain) > 50) and (message_status == False)):
        message_status=True
        m = "Raining Outside. (Sensor Value: {})".format(rain)
        print(m)
        sms.send_sms(m)
    if (float(rain) < 10):
        message_status = False






    with open("/home/vignesh772/mysite/data/data.json", "w") as outfile:
        json.dump(data, outfile)
    return "ok"

@app.route("/", methods=["GET", "POST"])
def index():

    with open('/home/vignesh772/mysite/data/data.json') as json_file:
        data = json.load(json_file)

    return render_template("index.html", rain=data["rain"], temp=data["temp"], hum = data["hum"])

@app.route("/ui")
def ui():
    with open('/home/vignesh772/mysite/data/data.json') as json_file:
        data = json.load(json_file)
    return data

if __name__ == "__main__":
    app.run()
