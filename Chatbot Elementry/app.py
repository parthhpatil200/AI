from flask import Flask,jsonify,render_template,request
import re
app=Flask(__name__)

def chatbot_response(message):
    message=message.lower()
    if re.search(r"\b(hello|hi|hey)\b",message):
        return "Hello! Welcome to TechGear Store!! How can I assist you?"
    elif re.search(r"\b(price|pricing|money)\b",message):
        return "Headphones for Rs. 3500, Keyboard for Rs. 2500, Mouse for Rs. 1500 and SmartWatch for Rs. 2000"
    elif re.search(r"\b(time|timing|hour)\b",message):
        return "The store is open from morning 8 a.m. to 9 p.m. at night. You can visit anytime during this period. We would be glad to serve you :)!!"
    elif re.search(r"\b(contact|number|no.)\b",message):
        return "You can contact us at +91-99999 00000"
    elif re.search(r"\b(item|product|thing|device|sell)\b",message):
        return "We sell Headphones, Keyboard, Mouse and SmartWatch currently!"
    else:
        return "Sorry I don't understand! Please ask me regarding pricing,timings,contact and products"

@app.route("/")
def home():
    return render_template("index.html")

@app.route("/chat",methods=["POST"])
def chat():
    user_message=request.json["message"]
    response=chatbot_response(user_message)
    return jsonify({"response":response})

if __name__=="__main__":
    app.run(debug=True)
