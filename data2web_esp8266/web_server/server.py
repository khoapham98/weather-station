from flask import Flask, request

app = Flask(__name__)

# Biến toàn cục lưu dữ liệu mới nhất từ ESP
latest_data = {"temp": "N/A", "humi": "N/A"}

@app.route('/')
def index():
    return f'''
    <h2>DATA READ FROM DHT11 SENSOR</h2>
    <p>Humidity: {latest_data["humi"]} %RH</p>
    <p>Temperature: {latest_data["temp"]} °C</p>

    '''

@app.route('/data', methods=['POST'])
def receive_data():
    global latest_data
    if request.is_json:
        data = request.get_json()
        print("ESP gửi JSON:", data)
        latest_data["temp"] = data.get("temp", "N/A")
        latest_data["humi"] = data.get("humi", "N/A")
    else:
        # Nhận dạng form từ ESP8266
        latest_data["temp"] = request.form.get("temp", "N/A")
        latest_data["humi"] = request.form.get("humi", "N/A")
        print("ESP gửi Form:", latest_data)
    return "Dữ liệu đã nhận", 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)